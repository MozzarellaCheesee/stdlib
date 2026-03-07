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

add_executable(tests ./tests/entrypoint.cpp)
target_link_libraries(tests PRIVATE stdlib)