# Build worker binary
set(TARGET worker)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(
    ${TARGET}  
    src/worker.cpp 
    src/utils.cpp
    src/worker_impl.cpp
    src/health_check.cpp
)
target_include_directories(
    ${TARGET}  
    PRIVATE 
        ${GENERATED_OUTPUT_DIR}/src
        ${UTIL_INCLUDE}
)
target_link_libraries(
    ${TARGET}  
    PRIVATE 
        proto
        shared_util
        ${Boost_LIBRARIES}
)
