cmake_minimum_required(VERSION 3.16.3)
set (CMAKE_CXX_STANDARD 20)
set (project_name "extra_udp")

project(${project_name} VERSION 1.0.1 DESCRIPTION "")
add_library(${project_name} SHARED
    build/cpp/extra_udp.cpp
    build/cpp/node.cpp
    build/cpp/extra_udp_send.cpp
    build/cpp/extra_udp_recv_malloc.cpp
    build/cpp/extra_udp_recv_existing.cpp
)
include_directories(${CMAKE_SOURCE_DIR})
set_target_properties(${project_name} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${project_name} PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output/cpp)
