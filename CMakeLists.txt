cmake_minimum_required(VERSION 3.14)

project(stdlib
        VERSION 1.0.0
        DESCRIPTION "My standard library"
        LANGUAGES CXX
)

add_library(stdlib INTERFACE
        stdlib/vector/vector.h
        stdlib/vector/vector.tpp)
add_library(stdlib::stdlib ALIAS stdlib)

target_include_directories(stdlib
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_compile_features(stdlib INTERFACE cxx_std_17)