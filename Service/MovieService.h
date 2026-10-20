//
// Created by szili on 3/24/26.
//

#ifndef A4_5_SZILI_06_MOVIESERVICE_H
#define A4_5_SZILI_06_MOVIESERVICE_H
#include "../Domain/Movie.h"
#include "../Repo/Repo.h"
#include "../Repo/Watchlist.h"
#include "../Domain/Action.h"
#include <memory>
#include <vector>
#include <stack>
#include <string>
#include <map>

/**
 * @brief Service class that handles the business logic for managing movies and a user watchlist.
 */
class MovieService {
    /**
     * @brief The main repository storing the complete database of movies.
     * Polymorphic pointer to handle different persistence types.
     */
    std::unique_ptr<Repo<Movie>> repo;

    /**
     * @brief A secondary repository specifically for storing movies the user has added to their watchlist.
     */
    std::unique_ptr<Watchlist> watchList;

    /**
     * @brief Stack of actions for undo functionality.
     */
    std::stack<std::unique_ptr<Action>> undoStack;

    /**
     * @brief Stack of actions for redo functionality.
     */
    std::stack<std::unique_ptr<Action>> redoStack;

    /**
     * @brief Clears the redo stack. Called whenever a new action is performed.
     */
    void clearRedoStack();

public:
    /**
     * @brief Constructor.
     * @param repo The repository implementation to use.
     */
    MovieService(std::unique_ptr<Repo<Movie>> repo);

    /**
     * @brief Sets the watchlist for the service.
     * @param wl A unique pointer to the watchlist implementation.
     */
    void setWatchlist(std::unique_ptr<Watchlist> wl);

    /**
     * @brief Adds a new movie to the main repository.
     */
    void addMovie(std::string title, std::string genre, int releaseYear, Link trailerLink, int nrOfLikes);

    /**
     * @brief Removes a movie from the main repository.
     */
    void removeMovie(std::string title, std::string genre, int releaseYear);

    /**
     * @brief Retrieves all movies currently stored in the main repository.
     */
    [[nodiscard]] std::vector<Movie> allMovies() const;

    /**
     * @brief Increments the like count for a specific movie in the repository.
     */
    void likeMovie(const Movie &movie) const;

    /**
     * @brief Updates the details of an existing movie in the main repository.
     */
    void updateMovie(std::string title, std::string genre, int releaseYear, std::string newTitle, std::string newGenre,
                     int newReleaseYear, std::string trailerLink, int newLikes);

    /**
     * @brief Adds a specific movie to the user's personal watchlist.
     */
    void addToWatchList(const Movie &movie) const;

    /**
     * @brief Removes a specific movie from the user's personal watchlist.
     */
    void removeFromWatchList(const Movie &movie, bool like) const;

    /**
     * @brief Retrieves all movies currently stored in the user's watchlist.
     */
    [[nodiscard]] std::vector<Movie> getWatchList() const;

    /**
     * @brief Finds and returns a movie inside the repo
     */
    [[nodiscard]] Movie findMovie(std::string title, std::string genre, int releaseYear) const;

    /**
     * @brief Finds all movies based on genre
     */
    [[nodiscard]] std::vector<Movie> filterMovies(std::string genre) const;

    /**
     * @brief Returns a map with genres as keys and the number of movies as values.
     */
    [[nodiscard]] std::map<std::string, int> getGenreCounts() const;

    /**
     * @brief Displays the watchlist by using the watchlist's displayWatchlist() function.
     */
    void showWatchlist() const;

    /**
     * @brief Undoes the last action performed on the main repository.
     * @throws std::runtime_error if there is nothing to undo.
     */
    void undo();

    /**
     * @brief Redoes the last undone action on the main repository.
     * @throws std::runtime_error if there is nothing to redo.
     */
    void redo();

    /**
     * @brief Returns a reference to the underlying repository (needed by Action classes).
     */
    Repo<Movie>& getRepo() const;
};

#endif //A4_5_SZILI_06_MOVIESERVICE_H
