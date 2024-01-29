# Build shared libs lib
set(TARGET shared_util)

find_package(Boost REQUIRED COMPONENTS log log_setup)

add_library(
    ${TARGET} 
    src/shared_util.cpp
    src/logging.cpp
)

target_link_libraries(
    ${TARGET} 
    PRIVATE
        ${Boost_LIBRARIES}
)
