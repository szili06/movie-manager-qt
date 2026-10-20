//
// Created by szili on 3/25/26.
//

#include "MovieValidator.h"

void MovieValidator::validate(const Movie& movie) {
    std::string errors;

    if (movie.getTitle().empty()) {
        errors += "Title cannot be empty!\n";
    }
    if (movie.getGenre().empty()) {
        errors += "Genre cannot be empty!\n";
    }
    if (movie.getNrOfLikes() < 0) {
        errors += "Number of likes cannot be negative!\n";
    }

    int year = movie.getReleaseYear();
    if (year < 1888) {
        errors += "Year must be 1888 or later!\n";
    }

    std::string url = movie.getTrailerLink().getUrl();
    if (url.find("http") != 0 && url.find("www") != 0) {
        errors += "Link must start with 'http' or 'www'!\n";
    }

    if (!errors.empty()) {
        throw ValidationException(errors);
    }
}