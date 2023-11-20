# Build worker binary
set(TARGET worker)

add_executable(
    ${TARGET}  
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
)
