cmake_minimum_required(VERSION 3.21)
project(t1_bia1708_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(t1_bia1708_1
        Domain.cpp
        Domain.h
        main.cpp
        Service.cpp
        Service.h
        Repository.cpp
        Repository.h
        UI.cpp
        UI.h)
