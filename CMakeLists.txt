cmake_minimum_required(VERSION 3.20)
project(stdlib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(stdlib INTERFACE)

target_include_directories(stdlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(stdlib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/vector.h
        ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/stack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/List.h
        ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/detail/vector.tpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/detail/stack.tpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stdlib/detail/List.tpp
)

add_executable(stack_test ./tests/tester.cpp ./tests/stack.cpp)
target_link_libraries(stack_test PRIVATE stdlib)
# add_executable(vector_test ./tests/tester.cpp ./tests/vector.cpp)
# target_link_libraries(vector_test PRIVATE stdlib)