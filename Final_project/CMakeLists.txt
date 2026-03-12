cmake_minimum_required(VERSION 4.0)
project(Final_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_executable(Final_project main.cpp
        include/core/Exchange.h
        src/core/Exchange.cpp)

target_include_directories(Final_project PRIVATE include)