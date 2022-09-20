//
// Created by bia on 11/05/2022.
//
#pragma once
#include <exception>
#include <string>

class RepositoryException : public std::exception
{
protected:
    std::string message;

public:
    RepositoryException();
    explicit RepositoryException(const std::string& msg);
    virtual ~RepositoryException() {}
    virtual const char* what();
};

class DuplicateEventException : public RepositoryException
{
public:
    const char* what();
};

class FileException : public std::exception
{
protected:
    std::string message;

public:
    explicit FileException(const std::string& msg);
    virtual const char* what();
};