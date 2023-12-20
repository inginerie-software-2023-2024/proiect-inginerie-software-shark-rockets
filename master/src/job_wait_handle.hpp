#pragma once
#include <condition_variable>
#include <mutex>

// Used for waiting until a job has finished running.
class JobWaitHandle {
 private:
  std::mutex m;
  std::condition_variable cv;
  bool finished;

 public:
  JobWaitHandle();

  // Mark the job as finished and notify all the waiting threads.
  void set_finished();

  // Block this thread while waiting for the job to be marked as finished.
  void wait();
};