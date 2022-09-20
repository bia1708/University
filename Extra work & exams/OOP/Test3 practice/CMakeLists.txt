cmake_minimum_required(VERSION 3.21)
project(Test_Practice_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Test_Practice_3 main.cpp Client.cpp Client.h Dwelling.cpp Dwelling.h Person.cpp Person.h Company.cpp Company.h RealEstateAgency.cpp RealEstateAgency.h UI.cpp UI.h)
