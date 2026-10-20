//
// Created by szili on 3/24/26.
//

#include "Movie.h"
#include <utility>
#include "Exceptions.h"
#include <sstream>
#include <vector>

Movie::Movie(std::string title, std::string genre, int releaseYear, Link  trailerLink, const int nrOfLikes) :
    title(std::move(title)),
    genre(std::move(genre)),
    releaseYear(releaseYear),
    trailerLink(std::move(trailerLink)),
    nrOfLikes(nrOfLikes)
{}

std::string Movie::getTitle() const {
    return this->title;
}

std::string Movie::getGenre() const {
    return this->genre;
}

int Movie::getReleaseYear() const {
    return this->releaseYear;
}

int Movie::getNrOfLikes() const {
    return this->nrOfLikes;
}

Link Movie::getTrailerLink() const {
    return this->trailerLink;
}

void Movie::setTitle(const std::string& t){
    this->title = t;
}

void Movie::setGenre(const std::string& g) {
    this->genre = g;
}

void Movie::setReleaseYear(int ry) {
    this->releaseYear = ry;
}

void Movie::setTrailerLink(const Link &tl) {
    this->trailerLink = tl;
}

void Movie::setLikes(int nl) {
    this->nrOfLikes = nl;
}

void Movie::like() {
    nrOfLikes++;
}
bool Movie::operator==(const Movie& other) const {
    return this->title == other.title && this->genre == other.genre && this->releaseYear == other.releaseYear;
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    os << movie.title << "," << movie.genre << "," << movie.releaseYear << "," << movie.nrOfLikes << "," << movie.trailerLink;
    return os;
}

std::istream& operator>>(std::istream& is, Movie& movie) {
    std::string line;
    while (std::getline(is, line) && line.empty())continue;
    if (line.empty()) return is;

    std::stringstream ss(line);
    std::string part;
    std::vector<std::string> parts;
    while (std::getline(ss, part, ',')) {
        parts.push_back(part);
    }
    if (parts.size() == 5) {
        movie.title = parts[0];
        movie.genre = parts[1];
        try {
            movie.releaseYear = std::stoi(parts[2]);
            movie.nrOfLikes = std::stoi(parts[3]);
        } catch (...) {
            throw InputException("Invalid numeric format in movie data!");
        }
        movie.trailerLink = Link(parts[4]);
    } else {
        throw InputException("Invalid movie data format! Expected: Title,Genre,Year,Likes,TrailerLink");
    }
    return is;
}

std::string Movie::toString() const {
    std::string result;
    result += "Title: " + this->title + "\n";
    result += "Genre: " + this->genre + "\n";
    result += "Release year: " + std::to_string(this->releaseYear) + "\n";
    result += "Nr of likes: " + std::to_string(this->nrOfLikes) + "\n";
    result += "Trailer link: " + this->trailerLink.getUrl() + "\n";
    return result; }