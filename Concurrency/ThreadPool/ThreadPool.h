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
  /**
   * Constructs the ThreadPool
   *
   * ARGS:
   * num_threads: a size_t integer that represents the number of threads the
   * client wants to use
   *
   */
  explicit WorkStealingThreadPool(size_t num_threads);

  /**
   * Deconstructor for the ThreadPool, it will execute all tasks before
   * deconstruction
   */
  ~WorkStealingThreadPool();

  /**
   * Adds a task to the workpool in a round robin way to evenly distibute the
   * work
   *
   * ARGS:
   * task: the task to add to the pool
   */
  void Submit(std::function<void()> task);

 private:
  struct WorkQueue {
    std::deque<std::function<void()>> tasks;
    std::mutex mutex;

    /**
     * Adds task to the WorkQueue
     *
     * ARGS:
     * task: task to add
     */
    void PushBottom(std::function<void()>&& task) {
      std::lock_guard lock(mutex);

      tasks.push_back(std::move(task));
    }

    /**
     * removes the task at the back of the queue and returns it
     *
     * RETURNS:
     * if a task exist it returns the task. Else, it will return nullopt
     */
    std::optional<std::function<void()>> PopBottom() {
      std::lock_guard lock(mutex);
      if (tasks.empty()) {
        return std::nullopt;
      }
      std::function<void()> task = std::move(tasks.back());
      tasks.pop_back();
      return task;
    }

    /**
     * Steals task from the front of the queue and returns it
     *
     * RETURNS:
     * if a task exists it returns the task, else it will return nullopt
     */
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

  /**
   * main function that loops infinitely executing its own or stealing tasks
   * until deconstruction
   *
   * ARGS:
   * thread_id: a size_t integer that represents the thread id that goes from 0
   * - num_threads
   *
   */
  void WorkerThread(const size_t thread_id);

  /**
   * attempts to steal from another thread to do its work
   *
   * ARGS:
   * thief_id: the id of the thief so that we dont attempt to steal our own work
   *
   * RETURNS:
   * std::function<void()> if a task was found. else, nullopt
   */
  std::optional<std::function<void()>> TrySteal(const size_t thief_id);

  std::vector<std::unique_ptr<WorkQueue>> queues_;
  std::vector<std::thread> threads_;
  std::atomic<bool> shutdown_{false};
  std::condition_variable cv_;
  std::mutex global_mutex_;
  std::atomic<size_t> next_queue_{0};
};

#endif  // WORK_STEALING_POOL_H_
