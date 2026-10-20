//
// Created by szili on 4/20/26.
//

#ifndef A6_7_SZILI_06_1_WATCHLIST_H
#define A6_7_SZILI_06_1_WATCHLIST_H

#include "../Domain/Movie.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <utility>

/**
 * @brief Abstract base class for managing a movie watchlist.
 * Provides basic functionality to add, remove, and retrieve movies.
 * Subclasses must implement file persistence and display methods.
 */
class Watchlist {
protected:
    /**
     * @brief A vector containing the Movie objects in the watchlist.
     */
    std::vector<Movie> movies;

    /**
     * @brief The filename where the watchlist will be saved.
     */
    std::string filename;
public:
    /**
     * @brief Constructor for Watchlist.
     * @param fn The filename for persistence.
     */
    Watchlist(std::string fn) : filename(std::move(fn)) {}

    /**
     * @brief Virtual destructor for Watchlist.
     */
    virtual ~Watchlist() = default;

    /**
     * @brief Adds a movie to the watchlist and saves changes.
     * @param m The movie to be added.
     */
    virtual void addMovie(const Movie& m);

    /**
     * @brief Removes a movie from the watchlist and saves changes.
     * @param m The movie to be removed.
     */
    virtual void removeMovie(const Movie& m);

    /**
     * @brief Returns all movies in the watchlist.
     * @return A vector of movies.
     */
    [[nodiscard]] virtual std::vector<Movie> getAll() const;

    /**
     * @brief Saves the watchlist to a file. Must be implemented by subclasses.
     */
    virtual void writeToFile() const = 0;

    /**
     * @brief Displays the watchlist using an external application. Must be implemented by subclasses.
     */
    virtual void displayWatchlist() const = 0;
};

/**
 * @brief Watchlist implementation that saves data in CSV format.
 */
class CSVWatchlist : public Watchlist {
public:
    /**
     * @brief Constructor for CSVWatchlist.
     * @param fn The filename for the CSV file.
     */
    CSVWatchlist(std::string fn) : Watchlist(std::move(fn)) {
        this->CSVWatchlist::writeToFile();
    }

    /**
     * @brief Saves movies to a CSV file.
     */
    void writeToFile() const override;

    /**
     * @brief Opens the CSV file using the system's default application (e.g., Notepad, Excel).
     */
    void displayWatchlist() const override;
};

/**
 * @brief Watchlist implementation that saves data in HTML format.
 */
class HTMLWatchList : public Watchlist {
public:
    /**
     * @brief Constructor for HTMLWatchList.
     * @param fn The filename for the HTML file.
     */
    HTMLWatchList(std::string fn) : Watchlist(std::move(fn)) {
        this->HTMLWatchList::writeToFile();
    }

    /**
     * @brief Saves movies to an HTML file in a table format.
     */
    void writeToFile() const override;

    /**
     * @brief Opens the HTML file using the system's default web browser.
     */
    void displayWatchlist() const override;
};

#endif //A6_7_SZILI_06_1_WATCHLIST_H
