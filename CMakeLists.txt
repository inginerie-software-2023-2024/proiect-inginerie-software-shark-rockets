cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS Off)

project(Koala)

set(KOALA_INTERFACE "${CMAKE_SOURCE_DIR}/map_reduce/src")
set(GENERATED_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/.generated")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/package")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/package/lib")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(USER_CODE "Build user test code" ON)

add_subdirectory(proto)
add_subdirectory(master)
add_subdirectory(worker)
add_subdirectory(map_reduce)

if(USER_CODE)
    add_subdirectory(sandbox)
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
install(
    TARGETS 
        master worker koala
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
