#include "master_state.hpp"
#include <stdexcept>

// Obviously, this is a naive implementation of the master state :)
void MasterState::register_worker(const std::string& ip, int port) {
  std::lock_guard<std::mutex> lock(master_lock);
  workers.emplace_back(ip, port);
}

std::pair<std::string, int> MasterState::get_worker() {
  std::lock_guard<std::mutex> lock(master_lock);

  if (workers.empty())
    throw std::runtime_error("No registered workers!");

  return workers[0];
}
