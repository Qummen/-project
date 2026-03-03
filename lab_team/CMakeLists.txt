cmake_minimum_required(VERSION 4.0)
project(lab_team)

set(CMAKE_CXX_STANDARD 20)


add_executable(lab_team main.cpp
        include/core/Exchange.h
        src/core/Exchange.cpp
        include/exchanges/OKX.h
        src/exchanges/OKX.cpp)

target_include_directories(lab_team PRIVATE include)