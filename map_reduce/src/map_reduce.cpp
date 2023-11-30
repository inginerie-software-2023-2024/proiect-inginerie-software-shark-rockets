#include "map_reduce.hpp"
#include <grpcpp/grpcpp.h>
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"
#include "utils.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <unordered_map>

namespace map_reduce
{
    // Avoid static initialization order fiasco with construct on first use idiom (and constinit)
    // I feel this can be improved :)

    constinit std::unique_ptr<MasterService::Stub> master_service;

    std::string &get_executable_path()
    {
        static std::string executable_path;
        return executable_path;
    }

    std::string &get_file_pattern()
    {
        static std::string file_path;
        return file_path;
    }

    std::unordered_map<std::string, Mapper *> &get_mappers()
    {
        static std::unordered_map<std::string, Mapper *> mappers;
        return mappers;
    }

    std::unordered_map<std::string, Reducer *> &get_reducers()
    {
        static std::unordered_map<std::string, Reducer *> reducers;
        return reducers;
    }
}

bool map_reduce::register_mapper(const std::string &name, Mapper *mapper)
{
    // check mappers are not registered after map_reduce::init() is called
    get_mappers()[name] = mapper;
    return true;
}

bool map_reduce::register_reducer(const std::string &name, Reducer *reducer)
{
    // check reducers are not registered after map_reduce::init() is called
    get_reducers()[name] = reducer;
    return true;
}

void map_reduce::init(int argc, char **argv)
{
    // this is quick and dirty - should probably parse args with boost::program_options

    // argv[0] (implicit) -> location of the binary
    // argv[1] -> master address as ip.ip.ip.ip:port
    // argv[2] -> mode: user, mapper, reducer
    // argv[3] -> name of class to run, if mode is mapper or reducer, file pattern if mode is user

    if (argc < 4)
        throw std::runtime_error("Invalid usage, expected 3 arguments");

    get_executable_path() = argv[0];

    if (strcmp(argv[2], "mapper") == 0)
    {
        // start in mapper mode
        // check if this mapper is in the set of known mappers...

        get_mappers()[argv[3]]->map();
        exit(0);
    }
    else if (strcmp(argv[2], "reducer") == 0)
    {
        // start in reducer mode
        // check if this reducer is in the set of known reducers...

        get_reducers()[argv[3]]->reduce();
        exit(0);
    }
    else if (strcmp(argv[2], "user") == 0)
    {
        get_file_pattern() = argv[3];
    }

    // start in user mode
    auto channel = grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials());
    master_service = MasterService::NewStub(channel);
}

void map_reduce::register_job(const std::string &mapper_name, const std::string &reducer_name)
{
    // check that the provided mapper and reducer are known ...

    std::cout << "User: sending a register job request with mapper " << mapper_name << " and reducer " << reducer_name << '\n';

    RegisterJobRequest request;
    request.set_path(get_executable_path());
    request.set_mapper(mapper_name);
    request.set_reducer(reducer_name);
    request.set_file_pattern(get_file_pattern());
    // request.set_user_name("gogu"); // send optional parameter

    RegisterJobReply reply;
    grpc::ClientContext context;
    context.AddMetadata("uuid",generate_uuid());
    
    auto status = master_service->RegisterJob(&context, request, &reply);

    if (status.ok())
        std::cout << "User: success, got " << reply.ok() << " from master\n";
    else
        std::cout << "User: failure, status is not ok\n";
}
