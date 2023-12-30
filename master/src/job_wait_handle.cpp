#include "job_wait_handle.hpp"

JobWaitHandle::JobWaitHandle() : finished(false) {}

void JobWaitHandle::set_finished() {
  {
    std::lock_guard lock(m);
    finished = true;
  }
  cv.notify_all();
}

void JobWaitHandle::wait() {
  std::unique_lock lk(m);
  cv.wait(lk, [this] { return this->finished; });
}