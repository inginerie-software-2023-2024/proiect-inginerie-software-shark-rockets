# This generates the code from .proto files and compiles a static library libproto to be linked against by all the targets in project

# Set Grpc install location
set(GRPC_INSTALL_PATH "$ENV{HOME}/grpc_install")
list(APPEND CMAKE_PREFIX_PATH "${GRPC_INSTALL_PATH}")


file(MAKE_DIRECTORY ${GENERATED_OUTPUT_DIR})

# Find the required packages
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILES
    src/master_service.proto
    src/worker_service.proto
    src/eucalypt_service.proto
)
# Add Library target with protobuf sources
add_library(proto ${PROTO_FILES})
target_link_libraries(proto
    PUBLIC
        gRPC::grpc++
)
target_include_directories(proto PUBLIC ${GENERATED_OUTPUT_DIR})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

# Generate protobuff sources
protobuf_generate(
    TARGET 
        proto 
    LANGUAGE 
        cpp
    PROTOC_OUT_DIR 
        ${GENERATED_OUTPUT_DIR}
)
protobuf_generate(
    TARGET 
        proto 
    LANGUAGE 
        grpc 
    GENERATE_EXTENSIONS 
        .grpc.pb.h .grpc.pb.cc 
    PLUGIN 
        "protoc-gen-grpc=${grpc_cpp_plugin_location}"
    PROTOC_OUT_DIR 
        ${GENERATED_OUTPUT_DIR}
)
