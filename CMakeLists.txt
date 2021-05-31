cmake_minimum_required(VERSION 3.16.3)
set (CMAKE_CXX_STANDARD 20)
set (project_name "extra_udp")

project(${project_name} VERSION 1.0.1 DESCRIPTION "")
add_library(${project_name} SHARED
    build/extra_udp.cpp
    build/node.cpp
    build/extra_udp_send.cpp
    build/extra_udp_recv.cpp
)
include_directories(${CMAKE_SOURCE_DIR})
set_target_properties(${project_name} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${project_name} PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
