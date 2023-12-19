
set(TARGET test_worker)

add_executable(
    ${TARGET}
    test.cpp
)

target_include_directories(
    ${TARGET} 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${GENERATED_OUTPUT_DIR}/src
)

target_link_libraries(
    ${TARGET} 
    GTest::GTest 
    GTest::Main
    proto
)
