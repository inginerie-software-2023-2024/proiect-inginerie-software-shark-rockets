# Build libkoala to be linked against by user code
set(TARGET koala)

set(Boost_USE_STATIC_LIBS   Off) # static boost libs installed via apt-get are not compiled with position independent code, XXX
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
