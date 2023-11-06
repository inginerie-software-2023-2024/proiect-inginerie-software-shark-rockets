cmake_minimum_required(VERSION 3.22)
project(MapReduce)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(ABSL_ENABLE_INSTALL ON)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.59.2
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

# Follow-up: should not include all generated files manually

# Master node
add_executable(master master/master.cpp master/master_state.cpp
  master/master_service.grpc.pb.cc master/master_service.pb.cc
  master/worker_service.grpc.pb.cc master/worker_service.pb.cc)
target_link_libraries(master grpc++)

# Worker node
add_executable(worker worker/worker.cpp 
  worker/master_service.grpc.pb.cc worker/master_service.pb.cc
  worker/worker_service.grpc.pb.cc worker/worker_service.pb.cc)
target_link_libraries(worker grpc++)

# User code
add_executable(sample sample.cpp map_reduce/map_reduce.cpp map_reduce/master_service.grpc.pb.cc map_reduce/master_service.pb.cc)
target_include_directories(sample PRIVATE map_reduce)
target_link_libraries(sample grpc++)

# Add debug symbols
set(CMAKE_BUILD_TYPE RelWithDebInfo)
