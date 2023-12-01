#pragma once
#include <grpcpp/grpcpp.h>
#include <worker_service.grpc.pb.h>
#include <string>

enum WorkerType { Mapper, Reducer };

// A worker seen through the master's point of view.
class Worker {
 private:
  // The address and port of the worker.
  std::string a;
  int p;

  // TCP connection to the worker.
  std::shared_ptr<grpc::Channel> channel;

  // Stub for the WorkerService.
  std::unique_ptr<WorkerService::Stub> stub;

  // The number of jobs currently assigned to the worker.
  int num_jobs;

 public:
  // Constructs a new worker by creating a new grpc channel to the specified address.
  Worker(std::string addr, int port);

  // Make a grpc call to assign work to this worker.
  // Return the worker's reply to the work request.
  // If the grpc call fails, throw an exception.
  bool assign_work(const std::string& binary_path, WorkerType type,
                   const std::string& exec_class,
                   const std::string& input_file);

  const std::string& address() const;

  int port() const;

  // Return an integer: the load of this worker.
  int load() const;
};