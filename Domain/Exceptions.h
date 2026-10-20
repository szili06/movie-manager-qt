//
// Created by szili on 3/25/26.
//

#ifndef A4_5_SZILI_06_EXCEPTIONS_H
#define A4_5_SZILI_06_EXCEPTIONS_H
#include <exception>
#include <string>

/**
 * @brief A custom exception class used to signal validation errors.
 */
class ValidationException : public std::exception {
    std::string message;
public:
    explicit ValidationException(std::string msg) : message(std::move(msg)) {}
    ~ValidationException() override = default;

    [[nodiscard]] const char* what() const noexcept override;
};

/**
 * @brief A custom exception class used to signal repository errors.
 */
class RepositoryException : public std::exception {
    std::string message;
public:
    explicit RepositoryException(std::string msg) : message(std::move(msg)) {}
    ~RepositoryException() override = default;

    [[nodiscard]] const char* what() const noexcept override;
};

/**
 * @brief A custom exception class used to signal user input errors.
 */
class InputException : public std::exception {
    std::string message;
public:
    explicit InputException(std::string msg) : message(std::move(msg)) {}
    ~InputException() override = default;

    [[nodiscard]] const char* what() const noexcept override;
};

#endif //A4_5_SZILI_06_EXCEPTIONS_H
