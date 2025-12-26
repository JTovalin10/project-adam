#ifndef WORK_STEALING_POOL_H_
#define WORK_STEALING_POOL_H_

#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <optional>
#include <random>
#include <thread>
#include <vector>

class WorkStealingThreadPool {
 public:
  // HINT: Need to populate queues_ with WorkQueue objects
  // Problem: WorkQueue contains mutex (non-copyable)
  // Question: How do you add non-copyable objects to a vector?
  //
  // HINT: Need to spawn threads that run WorkerThread
  // Problem: WorkerThread is a member function needing 'this' pointer
  // Question: How do you pass member function + 'this' to std::thread
  // constructor? Question: Each thread needs unique ID - how do you pass it?
  explicit WorkStealingThreadPool(size_t num_threads);

  // HINT: Threads are in infinite loops
  // Question: How do you signal all threads to stop looping?
  // Question: Some threads might be sleeping on cv_ - wake one or all?
  // Question: What happens if you destroy pool while threads still running?
  // Question: What vector operation waits for thread to finish?
  ~WorkStealingThreadPool();

  // HINT: Task needs to go into some queue
  // Question: Which queue? Does it matter for correctness? For performance?
  // Question: How do you ensure even distribution across queues?
  //
  // HINT: Threads might be sleeping waiting for work
  // Question: How do you wake a sleeping thread?
  // Question: Wake one thread or all threads?
  void Submit(std::function<void()> task);

 private:
  struct WorkQueue {
    std::deque<std::function<void()>> tasks;
    std::mutex mutex;

    // HINT: Multiple threads might access this deque concurrently
    // Question: What happens without synchronization?
    // Question: Which end of deque - front or back? Does it matter?
    // Question: What RAII pattern ensures mutex is always unlocked?
    void PushBottom(std::function<void()>&& task) {
      std::lock_guard lock(mutex);

      tasks.push_back(std::move(task));
    }

    // HINT: Owner thread takes tasks from its own queue
    // Question: Same end you pushed to, or opposite end? Why?
    // Question: What if deque is empty? Can't return task that doesn't exist
    // Question: Still need to lock mutex even though you "own" this queue?
    std::optional<std::function<void()>> PopBottom() {
      std::lock_guard lock(mutex);
      if (tasks.empty()) {
        return std::nullopt;
      }
      std::function<void()> task = std::move(tasks.back());
      tasks.pop_back();
      return task;
    }
    // HINT: Thief thread steals from victim's queue
    // Question: Same end as PopBottom or opposite end? Why does it matter?
    // Question: Do you need mutex even though different thread from owner?
    // Question: What if queue is empty when you try to steal?
    std::optional<std::function<void()>> Steal() {
      std::lock_guard lock(mutex);

      if (tasks.empty()) {
        return std::nullopt;
      }
      // grab from the front as its more likely to be cold so ~300 cpu cycles
      // this way the owner is more likely to have the task in L1 cache so ~3
      // cpu cycles
      std::function<void()> task = std::move(tasks.front());
      tasks.pop_front();
      return task;
    }
  };

  // HINT: This is the main loop each thread runs
  // Question: Loop forever or until some condition? What condition?
  //
  // HINT: Thread needs work - where to look first?
  // Question: Which queue should this thread check first?
  // Question: Which WorkQueue method does owner call on its own queue?
  //
  // HINT: No local work found - what's fallback strategy?
  // Question: Give up immediately or try stealing?
  // Question: How do you steal from other threads?
  //
  // HINT: No work anywhere in entire pool
  // Question: Busy-spin checking queues or sleep? Which is better for CPU?
  // Question: How do you make thread sleep until work arrives?
  // Question: What object makes threads sleep/wake?
  // Question: Sleeping requires a mutex - which one? Why?
  //
  // HINT: Got a task (either local or stolen)
  // Question: Execute inside lock or outside lock? Why does it matter?
  void WorkerThread(const size_t thread_id);

  // HINT: Try to find work by stealing from other threads
  // Question: Can you steal from your own queue? Why not?
  // Question: How do you iterate other threads without hitting yourself?
  // Question: Check queues in order, randomly, or round-robin?
  // Question: What if every queue you check is empty?
  // Question: Which WorkQueue method does thief call on victim's queue?
  std::optional<std::function<void()>> TrySteal(const size_t thief_id);

  std::vector<std::unique_ptr<WorkQueue>> queues_;
  std::vector<std::thread> threads_;
  std::atomic<bool> shutdown_{false};
  std::condition_variable cv_;
  std::mutex global_mutex_;
  std::atomic<size_t> next_queue_{0};
};

#endif  // WORK_STEALING_POOL_H_
