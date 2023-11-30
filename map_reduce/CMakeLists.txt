# Build libkoala to be linked against by user code
set(TARGET koala)

add_library(
    ${TARGET} SHARED
    src/map_reduce.cpp
    src/utils.cpp
)
target_include_directories(
    ${TARGET} 
    PUBLIC
        ${GENERATED_OUTPUT_DIR}/src
)
target_link_libraries(
    ${TARGET}  
    PUBLIC 
        proto
)

install(FILES src/koala.hpp DESTINATION include)
