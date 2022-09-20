cmake_minimum_required(VERSION 3.21)
project(lab_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab_4 App.cpp
        ExtendedTest.h
        ExtendedTest.cpp
        ShortTest.h
        ShortTest.cpp
        SortedBag.cpp
        SortedBag.h
        SortedBagIterator.cpp
        SortedBagIterator.h)
