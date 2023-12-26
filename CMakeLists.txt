cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS Off)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra")

project(Koala)

option(IN_DOCKER "Build inside Docker" OFF)

if(IN_DOCKER)
    add_definitions(-DDOCKER_BUILD)
endif()

set(KOALA_INTERFACE "${CMAKE_SOURCE_DIR}/map_reduce/src")
set(UTIL_INCLUDE "${CMAKE_SOURCE_DIR}/shared/src")
set(GENERATED_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/.generated")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/package")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/package/lib")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(USER_CODE "Build user test code" ON)
option(BUILD_TESTS "Build the tests" OFF)
option(DISABLE_LOGS "Disable logs at compile times" OFF)

if(DISABLE_LOGS)
    add_definitions(-DNDEBUG)
endif()

set(BOOST_ROOT "$ENV{HOME}/boost")
set(Boost_NO_SYSTEM_PATHS ON)

add_subdirectory(proto)
add_subdirectory(shared)
add_subdirectory(master)
add_subdirectory(worker)
add_subdirectory(map_reduce)

if(USER_CODE)
    add_subdirectory(sandbox)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
install(
    TARGETS 
        master worker koala
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
