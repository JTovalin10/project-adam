#include "ThreadPool.h"

#include <cstddef>
#include <memory>
#include <mutex>
#include <random>

WorkStealingThreadPool::WorkStealingThreadPool(std::size_t num_threads) {
  for (std::size_t i{0}; i < num_threads; i++) {
    queues_.push_back(std::make_unique<WorkQueue>());

    threads_.emplace_back(&WorkStealingThreadPool::WorkerThread, this, i);
  }
}

WorkStealingThreadPool::~WorkStealingThreadPool() {
  shutdown_.store(true);
  cv_.notify_all();

  // loops through each thread and calls join which will finish its job
  // this way all threads finish their job
  for (auto& thread : threads_) {
    thread.join();
  }
}

void WorkStealingThreadPool::Submit(std::function<void()> task) {
  // round robin technique to add the job
  size_t index = next_queue_.fetch_add(1) % queues_.size();

  queues_[index]->PushBottom(std::move(task));

  cv_.notify_one();
}

void WorkStealingThreadPool::WorkerThread(const size_t thread_id) {
  while (true) {
    std::optional<std::function<void()>> task = queues_[thread_id]->PopBottom();

    // check if we have a task and if not try to steal one
    if (!task.has_value()) {
      task = TrySteal(thread_id);
    }

    // execute the task and try again (it will grab its own task or steal again)
    if (task.has_value()) {
      (*task)();
      continue;
    }

    // shut down once we hit deconstructor
    if (shutdown_) {
      break;
    }

    // if all is false, then just sleep until we submit
    std::unique_lock lock(global_mutex_);
    cv_.wait(lock);
  }
}

std::optional<std::function<void()>> WorkStealingThreadPool::TrySteal(
    const size_t thief_id) {
  // this creates a different starting point so that they all dont try to access
  // the same queues[index]

  // both are static threa_local so that each thread has their own version and
  // is only created once as it lives in static storage duration
  static thread_local std::mt19937 gen(std::random_device{}());

  static thread_local std::uniform_int_distribution<size_t> dist(
      0, queues_.size() - 1);

  size_t start = dist(gen);

  std::optional<std::function<void()>> task = std::nullopt;
  for (size_t i = 0; i < queues_.size(); i++) {
    size_t victim_id = (start + i) % queues_.size();

    if (victim_id == thief_id) {
      continue;
    }

    task = queues_[victim_id]->Steal();

    if (task.has_value()) {
      return task;
    }
  }
  return std::nullopt;
}
