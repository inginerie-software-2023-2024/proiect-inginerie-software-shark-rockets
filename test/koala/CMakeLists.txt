
set(TARGET test_koala)

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
)
