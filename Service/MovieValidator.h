//
// Created by szili on 3/25/26.
//

#ifndef A4_5_SZILI_06_MOVIEVALIDATOR_H
#define A4_5_SZILI_06_MOVIEVALIDATOR_H
#include "../Domain/Movie.h"
#include "../Domain/Exceptions.h"

/**
 * @brief A utility class responsible for validating the data integrity of Movie objects.
 */
class MovieValidator {
public:
    /**
     * @brief Checks if the attributes of a given Movie object meet the required criteria.
     * @param movie The Movie object to be validated.
     * @throws ValidationException If any of the movie's attributes fail validation (e.g., empty title, negative release year).
     */
    static void validate(const Movie& movie);
};

#endif //A4_5_SZILI_06_MOVIEVALIDATOR_H