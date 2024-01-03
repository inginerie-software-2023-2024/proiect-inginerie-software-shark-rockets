
set(TARGET test_koala)

find_package(Boost REQUIRED COMPONENTS program_options filesystem)

add_definitions(-DNO_LOGGING)

add_executable(
    ${TARGET}
    test.cpp
    # ${TARGET_FILES}
)

target_include_directories(
    ${TARGET} 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${GENERATED_OUTPUT_DIR}/src
        ${UTIL_INCLUDE}
)

target_link_libraries(
    ${TARGET} 
    GTest::GTest 
    GTest::Main
    proto
    shared_util
    ${Boost_LIBRARIES}
)
