#pragma once
#include <grpcpp/grpcpp.h>
#include <worker_service.grpc.pb.h>
#include <boost/filesystem.hpp>
#include <boost/functional/hash.hpp>
#include <string>
#include <thread>
#include <unordered_set>
#include "job.hpp"
#include "job_leg.hpp"
#include "monitor.hpp"
#include "task.hpp"

enum WorkerType { Mapper, Reducer };

using Socket = std::pair<std::string, int>;
using reassign_cb = std::function<void(const std::unordered_set<std::string>&)>;
// A worker seen through the master's point of view.
class Worker {
 private:
  // The address and port of the worker.
  std::string addr_;
  int listen_port_;  // the port that the worker is listening to
  int emit_port_;    // the port that the worker is sending messages from

  // TCP connection to the worker.
  std::shared_ptr<grpc::Channel> channel;

  // Stub for the WorkerService.
  std::unique_ptr<WorkerService::Stub> stub;

  // The jobs currently assigned to the worker.
  // We store them explicitly so that we can re-assign them in case this worker goes down.
  std::unordered_set<std::string> assigned_tasks;

  std::atomic<bool> active_ = true;
  std::unique_ptr<HealthCheckMonitor> monitor_;

 public:
  // Constructs a new worker by creating a new grpc channel to the specified address.
  Worker(std::string addr, int listen_port, int emit_port,
         reassign_cb failure_cb);

  bool assign_work(const Job& job, const Task& task);

  const std::string& address() const;

  Socket get_emit_socket() const;

  Socket get_listen_socket() const;

  int listen_port() const;

  // Return an integer: the load of this worker.
  int load() const;

  void finish_task(const std::string& task_uuid);

  bool is_active() const;
};

struct SocketHash {
  std::size_t operator()(const Socket& socket) const noexcept {
    std::size_t seed = 0;
    boost::hash_combine(seed, std::hash<std::string>{}(socket.first));
    boost::hash_combine(seed, std::hash<int>{}(socket.second));
    return seed;
  }
};

using WorkerDict =
    std::unordered_map<Socket, std::unique_ptr<Worker>, SocketHash>;
