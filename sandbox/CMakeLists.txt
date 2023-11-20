# Build sample binary, links against koala
# This is dev only code that supports 2 configuration, it is similar to the configuration the user has to use to develop the code 
# 1. building the whole project and the sample from the root CMakeList if the USER_CODE flag is set in cli
# 2. building the sample frome a already built and installed koala
cmake_minimum_required(VERSION 3.22)
project(UserCode)
set(TARGET sample)

if(NOT TARGET koala)
    set(KOALA_INSTALL "${CMAKE_SOURCE_DIR}/../install")
    message(WARNING "Building only user code, fall back on already installed koala in
                     ${KOALA_INSTALL}")
    if(EXISTS "${KOALA_INSTALL}")
        set(KOALA_INTERFACE "${KOALA_INSTALL}/include")
        add_library(koala SHARED IMPORTED)
        set_target_properties(koala PROPERTIES IMPORTED_LOCATION "${KOALA_INSTALL}/lib/libkoala.so")    
    else()
        message(FATAL_ERROR "koala not found")
    endif()
endif()

add_executable(
    ${TARGET} 
    src/sample.cpp 
)
target_include_directories(
    ${TARGET} 
    PRIVATE 
        ${KOALA_INTERFACE}
)

target_link_libraries(
    ${TARGET}  
    PRIVATE 
        koala
)
