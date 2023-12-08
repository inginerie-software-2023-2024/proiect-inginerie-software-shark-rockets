#pragma once
#include <grpcpp/grpcpp.h>
#include <sys/wait.h>
#include <thread>
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"
#include "worker_service.grpc.pb.h"

class WorkerServiceImpl final : public WorkerService::Service {
 private:
  // Used to communicate with the master.
  std::shared_ptr<grpc::Channel> chan_to_master;
  std::unique_ptr<MasterService::Stub> master_stub;

  std::string master_address_;

  // Threads that are used to notify process completion.
  std::vector<std::thread> notify_threads;

  // Waits for the process to terminate and then notifies the master.
  void wait_then_notify_master(pid_t pid, std::string task_uuid);

 public:
  // Constructs the channel to the master and the master stub.
  WorkerServiceImpl(std::string master_address);

  // joins() all the notification threads.
  ~WorkerServiceImpl();

  // Notifies the master that the worker service is up and listening to the given port.
  // Returns master's reply.
  // Throws an error if the grpc call failed.
  bool notify_master(int port);

  // Impl WorkerService.
  grpc::Status AssignWork(grpc::ServerContext* context,
                          const AssignWorkRequest* request,
                          AssignWorkReply* response) override;
};