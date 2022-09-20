cmake_minimum_required(VERSION 3.21)
project(t2_bia1708_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(t2_bia1708_1
        Engine.cpp
        Engine.h ElectricEngine.cpp ElectricEngine.h TurboEngine.cpp TurboEngine.h Car.cpp Car.h Service.cpp Service.h UI.cpp UI.h main.cpp)
