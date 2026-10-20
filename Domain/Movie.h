//
// Created by szili on 3/24/26.
//

#ifndef A4_5_SZILI_06_MOVIE_H
#define A4_5_SZILI_06_MOVIE_H
#include <string>
#include "Link.h"
#include <iostream>


class Movie {
    /**
     * @brief A std::string containing the title of the Movie.
     */
    std::string title;
    /**
     * @brief A std::string containing the genre of the Movie.
     */
    std::string genre;
    /**
     * @brief An int containing the release year of the Movie.
     */
    int releaseYear{};
    /**
     * @brief An int containing the number of likes of the Movie.
     */
    int nrOfLikes{};
    /**
     * @breif A Link containing the trailer of the movie.
     */
    Link trailerLink;

    public:

        /**
         * @brief Default constructor.
         */
        Movie() = default;

        /**
         * @brief Parameterized constructor for Movie.
         * @param title Title of the movie.
         * @param genre Genre of the movie.
         * @param releaseYear Year the movie was released.
         * @param trailerLink Link to the movie trailer.
         * @param nrOfLikes Number of likes the movie has received.
         */
        Movie(std::string title, std::string genre, int releaseYear, Link trailerLink, int nrOfLikes);
        /**
         * @brief Getter for the field nrOfLikes
         * @return the value of nrOfLikes
         */
        [[nodiscard]] int getNrOfLikes() const;
        /**
         * @brief Getter for the field trailerLink
         * @return the value of trailerLink
         */
        [[nodiscard]] Link getTrailerLink() const;
        /**
         * @brief Getter for the field title
         * @return the value of title
         */
        [[nodiscard]] std::string getTitle() const;

        /**
         * @brief Getter for the field genre
         * @return the value of genre
         */
        [[nodiscard]] std::string getGenre() const;

        /**
         * @brief Getter for the field releaseYear
         * @return the value of releaseYear
         */
        [[nodiscard]] int getReleaseYear() const;
        /**
         * @brief Setter for the field title
         * @param t the new value for title
         */
        void setTitle(const std::string& t);
        /**
         * @brief Setter for the field genre
         * @param genre the new value for genre
         */
        void setGenre(const std::string& genre);
        /**
         * @brief Setter for the field releaseYear
         * @param releaseYear the new value of releaseYear
         */
        void setReleaseYear(int releaseYear);

        /**
         * @brief Setter for the field trailerLink
         * @param trailerLink the new value of trailerLink
         */
        void setTrailerLink(const Link &trailerLink);

        /**
         * @brief Setter for the field nrOfLikes
         * @param nrOfLikes the new value of nrOfLikes
         */
        void setLikes(int nrOfLikes);
        /**
         * @brief Increments the nrOfLikes field's value
         */
        void like();
        /**
         * @brief Override for == operation
         */
        bool operator==(const Movie &other) const;
        /**
         * @brief Converts movie into printable string
         * @return printable string
         */
        [[nodiscard]] std::string toString() const;

        /**
         * @brief Writes a Movie object to an output stream.
         * @param os The output stream to write to.
         * @param movie The Movie object to be written.
         * @return The output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);

        /**
         * @brief Reads a Movie object from an input stream.
         * @param is The input stream to read from.
         * @param movie The Movie object where the read data will be stored.
         * @return The input stream.
         */
        friend std::istream& operator>>(std::istream& is, Movie& movie);
};


#endif //A4_5_SZILI_06_MOVIE_H