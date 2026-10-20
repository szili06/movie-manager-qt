#include "Exceptions.h"

const char* ValidationException::what() const noexcept {
    return message.c_str();
}

const char* RepositoryException::what() const noexcept {
    return message.c_str();
}

const char* InputException::what() const noexcept {
    return message.c_str();
}