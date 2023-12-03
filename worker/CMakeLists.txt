# Build worker binary
set(TARGET worker)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(
    ${TARGET}  
    src/worker.cpp
    src/utils.cpp
)
target_include_directories(
    ${TARGET}  
    PRIVATE 
        ${GENERATED_OUTPUT_DIR}/src
)
target_link_libraries(
    ${TARGET}  
    PRIVATE 
        proto
        ${Boost_LIBRARIES}
)
