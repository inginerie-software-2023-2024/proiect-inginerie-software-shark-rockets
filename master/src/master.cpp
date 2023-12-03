#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>
#include "eucalypt_service.grpc.pb.h"
#include "eucalypt_service.pb.h"
#include "file_system_manager.hpp"
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"
#include "master_state.hpp"
#include "utils.hpp"
#include "worker_service.grpc.pb.h"
#include "worker_service.pb.h"

class MasterServiceImpl final : public MasterService::Service {
 private:
  MasterState master_state;

  std::string extract_ip_from_context(grpc::ServerContext* context) {
    std::string peer = context->peer();  // is of the form ipv4:ip:port
    int first_colon = peer.find(':');
    int second_colon = peer.find(':', first_colon + 1);

    return peer.substr(first_colon + 1, second_colon - first_colon - 1);
  }

 public:
  grpc::Status RegisterWorker(grpc::ServerContext* context,
                              const RegisterWorkerRequest* request,
                              RegisterWorkerReply* response) override {
    std::string worker_ip = extract_ip_from_context(context);
    int worker_port = request->worker_port();

    std::cout << "Master: received a register worker request:"
              << " ip: " << worker_ip << ',' << " port: " << worker_port
              << '\n';

    master_state.register_worker(worker_ip, worker_port);
    response->set_ok(true);
    return grpc::Status::OK;
  }

  grpc::Status RegisterJob(grpc::ServerContext* context,
                           const RegisterJobRequest* request,
                           RegisterJobReply* response) override {
    std::cout << "Master: received a register job request: path="
              << request->path() << ", mapper=" << request->mapper()
              << ", reducer=" << request->reducer()
              << ", file location=" << request->file_regex() << '\n';

    std::vector<nfs::fs::path> job_files =
        nfs::on_job_register_request(context, request);

    // Just print them for now, use this vector to asssign input to workers
    std ::cout << "Listing job files..." << std::endl;
    for (const auto& it : job_files) {
      std::cout << "Job file: " << it << std::endl;
    }

    std::pair<std::string, int> worker = master_state.get_worker();
    std::cout << "Master: we will assign the tasks to " << worker.first << ':'
              << worker.second << '\n';

    // should probably create these connections when we register a worker ...
    auto channel =
        grpc::CreateChannel(worker.first + ":" + std::to_string(worker.second),
                            grpc::InsecureChannelCredentials());
    auto worker_service = WorkerService::NewStub(channel);

    // naive implementation :)
    AssignWorkRequest mapper_work_request;
    mapper_work_request.set_path(request->path());
    mapper_work_request.set_mode("mapper");
    mapper_work_request.set_class_(request->mapper());
    AssignWorkReply mapper_work_reply;
    grpc::ClientContext context_mapper;
    auto status_mapper_worker = worker_service->AssignWork(
        &context_mapper, mapper_work_request, &mapper_work_reply);

    AssignWorkRequest reducer_work_request;
    reducer_work_request.set_path(request->path());
    reducer_work_request.set_mode("reducer");
    reducer_work_request.set_class_(request->reducer());
    AssignWorkReply reducer_work_reply;
    grpc::ClientContext context_reducer;
    auto status_reducer_worker = worker_service->AssignWork(
        &context_reducer, reducer_work_request, &reducer_work_reply);

    if (status_mapper_worker.ok() && status_reducer_worker.ok())
      response->set_ok(true);
    else
      response->set_ok(false);

    return grpc::Status::OK;
  }
};

class EucalyptServiceImpl final : public EucalyptService::Service {
  grpc::Status CheckConnection([[maybe_unused]] grpc::ServerContext* context,
                               const CheckConnectionRequest* request,
                               CheckConnectionReply* response) override {
    std::cout << "Master received grpc call from Eucalypt with message: "
              << request->message() << '\n';
    response->set_ok(true);
    return grpc::Status::OK;
  }
};

int main() {
  nfs::sanity_check();
  // This is hardcoded for now...
  std::string master_server_address = "0.0.0.0:50051";

  // Start a grpc server, waiting for job requests and worker heartbeats
  MasterServiceImpl master_service;
  EucalyptServiceImpl eucalypt_service;
  grpc::ServerBuilder builder;

  builder.AddListeningPort(master_server_address,
                           grpc::InsecureServerCredentials());
  builder.RegisterService(&master_service);
  builder.RegisterService(&eucalypt_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Master: listening on port 50051\n";
  server->Wait();

  return 0;
}
