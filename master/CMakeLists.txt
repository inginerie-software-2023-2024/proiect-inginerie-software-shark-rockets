# Build master binary
set(TARGET master)

find_package(Boost REQUIRED COMPONENTS filesystem regex)

add_executable(
    ${TARGET} 
    src/master.cpp 
    src/master_state.cpp
    src/file_system_manager.cpp
    src/utils.cpp
    src/user.cpp
    src/worker.cpp
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
