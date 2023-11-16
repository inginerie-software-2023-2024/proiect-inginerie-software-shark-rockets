# Build master binary
set(TARGET master)

add_executable(
    ${TARGET} 
    src/master.cpp 
    src/master_state.cpp
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
)
