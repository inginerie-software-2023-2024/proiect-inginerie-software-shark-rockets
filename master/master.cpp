#include <grpcpp/grpcpp.h>
#include "master_service.pb.h"
#include "master_service.grpc.pb.h"
#include "worker_service.pb.h"
#include "worker_service.grpc.pb.h"
#include "master_state.hpp"
#include <string>
#include <iostream>

class MasterServiceImpl final : public MasterService::Service
{
private:
    MasterState master_state;

public:
    grpc::Status RegisterWorker(grpc::ServerContext *context,
                                const RegisterWorkerRequest *request,
                                RegisterWorkerReply *response) override
    {
        std::cout << "Master: received a register worker request:"
                  << " ip: " << request->ip() << ','
                  << " port: " << request->port() << '\n';

        master_state.register_worker(request->ip(), request->port());
        response->set_ok(true);
        return grpc::Status::OK;
    }

    grpc::Status RegisterJob(grpc::ServerContext *context,
                             const RegisterJobRequest *request,
                             RegisterJobReply *response) override
    {
        std::cout << "Master: received a register job request: path=" << request->path()
                  << ", mapper=" << request->mapper()
                  << ", reducer=" << request->reducer() << '\n';

        std::pair<std::string, int> worker = master_state.get_worker();
        std::cout << "Master: we will assign the tasks to " << worker.first << ':' << worker.second << '\n';

        // should probably create these connections when we register a worker ...
        auto channel = grpc::CreateChannel(worker.first + ":" + std::to_string(worker.second),
                                           grpc::InsecureChannelCredentials());
        auto worker_service = WorkerService::NewStub(channel);

        // naive implementation :)
        AssignWorkRequest mapper_work_request;
        mapper_work_request.set_path(request->path());
        mapper_work_request.set_mode("mapper");
        mapper_work_request.set_class_(request->mapper());
        AssignWorkReply mapper_work_reply;
        grpc::ClientContext context_mapper;
        auto status_mapper_worker = worker_service->AssignWork(&context_mapper, mapper_work_request, &mapper_work_reply);

        AssignWorkRequest reducer_work_request;
        reducer_work_request.set_path(request->path());
        reducer_work_request.set_mode("reducer");
        reducer_work_request.set_class_(request->reducer());
        AssignWorkReply reducer_work_reply;
        grpc::ClientContext context_reducer;
        auto status_reducer_worker = worker_service->AssignWork(&context_reducer, reducer_work_request, &reducer_work_reply);

        if (status_mapper_worker.ok() && status_reducer_worker.ok())
            response->set_ok(true);
        else
            response->set_ok(false);

        return grpc::Status::OK;
    }
};

int main()
{
    // This is hardcoded for now...
    std::string master_server_address = "0.0.0.0:50051";

    // Start a grpc server, waiting for job requests and worker heartbeats
    MasterServiceImpl master_service;
    grpc::ServerBuilder builder;

    builder.AddListeningPort(master_server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&master_service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "Master: listening on port 50051\n";
    server->Wait();

    return 0;
}