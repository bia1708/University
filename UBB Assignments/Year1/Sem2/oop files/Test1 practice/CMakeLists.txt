cmake_minimum_required(VERSION 3.21)
project(Test1_practice)

set(CMAKE_CXX_STANDARD 14)

add_executable(Test1_practice main.cpp Domain.cpp Domain.h Repository.cpp Repository.h Service.cpp Service.h UI.cpp UI.h)
