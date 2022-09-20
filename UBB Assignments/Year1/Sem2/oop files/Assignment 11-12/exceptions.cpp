//
// Created by bia on 19/05/2022.
//

#include "exceptions.h"

#include <utility>
#include <iostream>

AppError::AppError(std::string message) : message(std::move(message)) {}

void AppError::print_error() const {
    std::cerr << message << std::endl;
}

const char *AppError::what() const noexcept {
    return message.c_str();
}

EventError::EventError(std::string message) : AppError(std::move(message)) {}

RepositoryError::RepositoryError(std::string message) : AppError(std::move(message)) {}

ServiceError::ServiceError(std::string message) : AppError(std::move(message)) {}
