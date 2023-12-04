#include "master_state.hpp"
#include <stdexcept>

void MasterState::push_worker(std::unique_ptr<Worker> new_worker) {
  std::lock_guard<std::mutex> lock(master_lock);
  workers.push_back(std::move(new_worker));
}

std::unique_ptr<Worker> MasterState::pop_worker() {
  std::lock_guard<std::mutex> lock(master_lock);

  if (workers.empty())
    throw std::runtime_error("No registered workers!");

  // Find the worker with the lowest load.
  auto best = workers.begin();
  for (auto iter = workers.begin() + 1; iter != workers.end(); iter++) {
    if ((*iter)->load() < (*best)->load()) {
      best = iter;
    }
  }

  std::unique_ptr to_return = std::move(*best);
  workers.erase(best);
  return to_return;
}