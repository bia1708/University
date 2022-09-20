cmake_minimum_required(VERSION 3.21)
project(a8_9_bia1708)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a8_9_bia1708
        extra/Comparator.cpp
        extra/Comparator.h
        extra/ComparatorAscendingByNumberOfParticipants.cpp
        extra/ComparatorAscendingByNumberOfParticipants.h
        extra/ComparatorAscendingByTitle.cpp
        extra/ComparatorAscendingByTitle.h
        extra/sort.cpp
        extra/sort.h
        AdministratorService.cpp
        AdministratorService.h
        Domain.cpp
        Domain.h
        DynamicArray.cpp
        DynamicArray.h
        main.cpp
        Repository.cpp
        Repository.h
        UI.cpp
        UI.h
        UserService.cpp
        UserService.h HTMLRepository.cpp HTMLRepository.h FileRepository.cpp FileRepository.h RepositoryException.cpp RepositoryException.h CSVRepository.cpp CSVRepository.h Validator.cpp Validator.h)
