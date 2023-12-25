# Build libkoala to be linked against by user code
set(TARGET koala)

find_package(Boost REQUIRED COMPONENTS program_options filesystem)

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
    PRIVATE
    ${Boost_LIBRARIES}
    PUBLIC 
        proto
)

install(FILES src/koala.hpp DESTINATION include)
