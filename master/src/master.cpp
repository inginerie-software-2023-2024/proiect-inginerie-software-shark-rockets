#include <grpc/status.h>
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>
#include "connection_service.grpc.pb.h"
#include "connection_service.pb.h"
#include "eucalypt_service.grpc.pb.h"
#include "eucalypt_service.pb.h"
#include "file_system_manager.hpp"
#include "logging.hpp"
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"
#include "master_state.hpp"
#include "utils.hpp"
#include "worker_service.grpc.pb.h"
#include "worker_service.pb.h"

class MasterServiceImpl final : public MasterService::Service {
 private:
  MasterState master_state;
  std::string eucalypt_address;
  std::unique_ptr<ConnectionService::Stub> connection_service;

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
  void setConnectionService() {
    const auto eucalypt_channel = grpc::CreateChannel(
        eucalypt_address, grpc::InsecureChannelCredentials());
    connection_service = ConnectionService::NewStub(eucalypt_channel);
  }

  void setEucalyptAddress(std::string eucalypt_address) {
    this->eucalypt_address = eucalypt_address;
  }

  grpc::Status RegisterWorker(grpc::ServerContext* context,
                              const RegisterWorkerRequest* request,
                              RegisterWorkerReply* response) override {
    auto [worker_ip, worker_emit_port] = extract_socket_from_context(context);
    int worker_listen_port = request->worker_port();

    LOG_INFO << "Master: received a register worker request:"
             << " ip: " << worker_ip << ',' << " port: " << worker_listen_port
             << '\n';
    master_state.create_worker(worker_ip, worker_listen_port, worker_emit_port);
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
      LOG_ERROR << "Request doesn't have a uuid!" << std::endl;
      return grpc::Status::CANCELLED;
    }
    uuid = std::string(uuid_it->second.data(), uuid_it->second.size());

    // Get the user who initiated the request.
    std::unique_ptr<User> user;
    if (request->token() != "") {
      CheckConnectionTokenRequest token_request;
      CheckConnectionTokenReply token_reply;
      grpc::ClientContext contextToken;

      token_request.set_token(request->token());
      token_request.set_job_uuid(uuid);

      auto token_status = connection_service->CheckConnectionToken(
          &contextToken, token_request, &token_reply);

      if (token_status.ok()) {
        if (token_reply.ok() == 0) {
          const std::string error_msg =
              "Invalid token, please check your token and quota again.";
          LOG_ERROR << "Invalid token!" << std::endl;
          grpc::Status err_status =
              grpc::Status(grpc::StatusCode::RESOURCE_EXHAUSTED, error_msg);
          return err_status;
        } else {
          user = std::make_unique<User>(token_reply.email());
        }
      } else {
        LOG_ERROR << "Failed to validate token!" << std::endl;
        return grpc::Status::CANCELLED;
      }
    } else {
      user = std::make_unique<User>();  // Guest
    }

    LOG_INFO << "Master: received a register job request: path="
             << request->path() << ", mapper=" << request->mapper()
             << ", reducer=" << request->reducer()
             << ", file location=" << request->file_regex()
             << ", job uuid=" << uuid << ", R=" << request->r() << std::endl;

    std::vector<nfs::fs::path> job_files =
        nfs::on_job_register_request(uuid, user, request->file_regex());

    // No files to process.
    if (job_files.empty()) {
      LOG_ERROR << "No files to process!" << std::endl;
      return grpc::Status::CANCELLED;
    }

    // Store metadata about a job.
    master_state.setup_job(uuid, user->get_email(), request->path(),
                           request->mapper(), request->reducer(),
                           (int)job_files.size(), request->r());

    // Kicks off the map leg for this job.
    master_state.start_map_leg(uuid, job_files);

    response->set_ok(true);
    return grpc::Status::OK;
  }

  grpc::Status AckWorkerFinish(
      [[maybe_unused]] grpc::ServerContext* context,
      [[maybe_unused]] const AckWorkerFinishRequest* request,
      [[maybe_unused]] AckWorkerFinishReply* response) override {
    LOG_INFO << "Worker finished task " << request->task_uuid() << std::endl;
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
    LOG_INFO << "Master received grpc call from Eucalypt with message: "
             << request->message() << '\n';
    response->set_ok(true);
    return grpc::Status::OK;
  }
};

int main(int argc, char** argv) {
  auto vm = parse_args(argc, argv);
  logging::Logger::load_cli_config(vm, "master.log");
  nfs::sanity_check();

  // This is hardcoded for now...
  std::string master_server_address = "0.0.0.0:50051";

  Persistor::set_eucalypt_address(get_arg<std::string>(vm, "eucalypt-address"));

  // Start a grpc server, waiting for job requests and worker heartbeats
  MasterServiceImpl master_service;
  EucalyptServiceImpl eucalypt_service;
  grpc::ServerBuilder builder;

  master_service.setEucalyptAddress(
      get_arg<std::string>(vm, "eucalypt-address"));
  master_service.setConnectionService();

  builder.AddListeningPort(master_server_address,
                           grpc::InsecureServerCredentials());
  builder.RegisterService(&master_service);
  builder.RegisterService(&eucalypt_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  LOG_INFO << "Master: listening on port 50051\n";
  server->Wait();

  return 0;
}
