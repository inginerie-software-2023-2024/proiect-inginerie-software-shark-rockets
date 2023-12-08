#pragma once
#include <grpcpp/grpcpp.h>
#include <worker_service.grpc.pb.h>
#include <boost/functional/hash.hpp>
#include <string>
#include <unordered_set>

enum WorkerType { Mapper, Reducer };

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

 public:
  // Constructs a new worker by creating a new grpc channel to the specified address.
  Worker(std::string addr, int listen_port, int emit_port);

  // Make a grpc call to assign work to this worker.
  // Return the worker's reply to the work request.
  // If the grpc call fails, throw an exception.
  bool assign_work(const std::string& binary_path, WorkerType type,
                   const std::string& exec_class, const std::string& input_file,
                   const std::string& task_uuid);

  const std::string& address() const;

  std::pair<std::string, int> get_emit_socket() const;

  int listen_port() const;

  // Return an integer: the load of this worker.
  int load() const;

  void finish_task(const std::string& task_uuid);
};

struct SocketHash {
  std::size_t operator()(
      const std::pair<std::string, int>& socket) const noexcept {
    std::size_t seed = 0;
    boost::hash_combine(seed, std::hash<std::string>{}(socket.first));
    boost::hash_combine(seed, std::hash<int>{}(socket.second));
    return seed;
  }
};

using WorkerDict = std::unordered_map<std::pair<std::string, int>,
                                      std::unique_ptr<Worker>, SocketHash>;
