cmake_minimum_required(VERSION 3.21)
project(lab_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab_3 App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h
        SortedIndexedList.h
        SortedIndexeList.cpp)
