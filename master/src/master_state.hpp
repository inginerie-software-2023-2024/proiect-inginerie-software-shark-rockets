#pragma once
#include <mutex>
#include <queue>
#include "worker.hpp"

class MasterState {
 private:
  std::vector<std::unique_ptr<Worker>> workers;
  std::mutex master_lock;

 public:
  // Moves a new worker into the data structure, transferring ownership.
  void push_worker(std::unique_ptr<Worker> new_worker);

  // Pops the worker with the smallest load and returns ownership to the caller.
  std::unique_ptr<Worker> pop_worker();
};
