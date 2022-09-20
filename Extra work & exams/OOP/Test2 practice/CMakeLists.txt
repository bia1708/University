cmake_minimum_required(VERSION 3.21)
project(test2_practice)

set(CMAKE_CXX_STANDARD 14)

add_executable(test2_practice main.cpp Domain.cpp Domain.h Repository.cpp Repository.h Service.cpp Service.h UI.cpp UI.h)
