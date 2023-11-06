# Follow-up: hide generated code in a folder in map_reduce/, master/ and worker/
# Follow-up: split proto definitions to avoid code pollution

# Master
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --grpc_out=master --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/master_service.proto
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --cpp_out=master proto/master_service.proto
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --grpc_out=master --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/worker_service.proto
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --cpp_out=master proto/worker_service.proto

# Worker
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --grpc_out=worker --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/master_service.proto
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --cpp_out=worker proto/master_service.proto
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --grpc_out=worker --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/worker_service.proto
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --cpp_out=worker proto/worker_service.proto

# User library
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --grpc_out=map_reduce --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/master_service.proto
build/_deps/grpc-build/third_party/protobuf/protoc --proto_path=proto --cpp_out=map_reduce proto/master_service.proto
