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

  Socket extract_socket_from_context(grpc::ServerContext* context) {
    std::string peer = context->peer();  // is of the form ipv4:ip:port
    int first_colon = peer.find(':');
    int second_colon = peer.find(':', first_colon + 1);

    std::string ip =
        peer.substr(first_colon + 1, second_colon - first_colon - 1);
    int port = std::stoi(
        peer.substr(second_colon + 1, peer.size() - second_colon - 1));

    return {ip, port};
  }

 public:
  grpc::Status RegisterWorker(grpc::ServerContext* context,
                              const RegisterWorkerRequest* request,
                              RegisterWorkerReply* response) override {
    auto [worker_ip, worker_emit_port] = extract_socket_from_context(context);
    int worker_listen_port = request->worker_port();

    std::cout << "Master: received a register worker request:"
              << " ip: " << worker_ip << ',' << " port: " << worker_listen_port
              << '\n';

    auto worker = std::make_unique<Worker>(worker_ip, worker_listen_port,
                                           worker_emit_port);
    master_state.push_worker(std::move(worker));
    response->set_ok(true);
    return grpc::Status::OK;
  }

  grpc::Status RegisterJob(grpc::ServerContext* context,
                           const RegisterJobRequest* request,
                           RegisterJobReply* response) override {

    // Retrieve the uuid from the request context.
    const auto& metadata = context->client_metadata();
    auto uuid_it = metadata.find("uuid");
    std::string uuid;

    // No uuid.
    if (uuid_it == metadata.end()) {
      std::cerr << "Request doesn't have a uuid!" << std::endl;
      return grpc::Status::CANCELLED;
    }
    uuid = std::string(uuid_it->second.data(), uuid_it->second.size());

    // Get the user who initiated the request.
    std::unique_ptr<User> user;
    if (request->has_user_name()) {
      user = std::make_unique<User>(request->user_name());
    } else {
      user = std::make_unique<User>();  // Guest
    }

    std::cout << "Master: received a register job request: path="
              << request->path() << ", mapper=" << request->mapper()
              << ", reducer=" << request->reducer()
              << ", file location=" << request->file_regex()
              << ", job uuid=" << uuid << std::endl;

    std::vector<nfs::fs::path> job_files =
        nfs::on_job_register_request(uuid, user, request->file_regex());

    // No files to process.
    if (job_files.empty()) {
      std::cerr << "No files to process!" << std::endl;
      return grpc::Status::CANCELLED;
    }

    // Store metadata about a job.
    master_state.setup_job(uuid, user->get_name(), request->path(),
                           request->mapper(), request->reducer());

    // Kicks off the map leg for this job.
    master_state.start_map_leg(uuid, job_files);

    response->set_ok(true);
    return grpc::Status::OK;
  }

  grpc::Status AckWorkerFinish(
      [[maybe_unused]] grpc::ServerContext* context,
      [[maybe_unused]] const AckWorkerFinishRequest* request,
      [[maybe_unused]] AckWorkerFinishReply* response) override {
    std::cout << "Worker finished task " << request->task_uuid() << std::endl;
    master_state.mark_task_as_finished(extract_socket_from_context(context),
                                       request->task_uuid());
    response->set_ok(true);
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
