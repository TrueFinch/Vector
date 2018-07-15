cmake_minimum_required(VERSION 3.10)
project(vector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(SOURCE_FILES vector.hpp iterator.hpp Tests.cpp)

#include(CodeCoverage)

add_executable(vector_test ${SOURCE_FILES})
add_executable(vector_cov ${SOURCE_FILES})

target_compile_options(vector_cov PRIVATE -g3 -fsanitize=address -O0 -coverage)
set_target_properties(vector_cov  PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage -fsanitize=address")


#target_compile_options(vector_cov PRIVATE -g -O0 -coverage -Wall -fprofile-arcs -ftest-coverage)
#set_target_properties(vector_cov PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
