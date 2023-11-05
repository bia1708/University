cmake_minimum_required(VERSION 3.21)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1 main.cpp Product.cpp Product.h Bill.cpp Bill.h Inventory.cpp Inventory.h)
