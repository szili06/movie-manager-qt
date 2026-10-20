//
// Created by szili on 3/24/26.
//

#include "MovieService.h"
#include <algorithm>
#include "../Service/MovieValidator.h"
#include <utility>

void MovieService::clearRedoStack() {
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

MovieService::MovieService(std::unique_ptr<Repo<Movie>> repo) : repo(std::move(repo)) {
}

void MovieService::setWatchlist(std::unique_ptr<Watchlist> wl) {
    this->watchList = std::move(wl);
}

void MovieService::addMovie(std::string title, std::string genre, const int releaseYear, Link trailerLink, const int nrOfLikes) {
    Movie movie = Movie(std::move(title), std::move(genre), releaseYear, std::move(trailerLink), nrOfLikes);
    MovieValidator::validate(movie);
    this->repo->addElement(movie);
    clearRedoStack();
    undoStack.push(std::make_unique<ActionAdd>(movie, *this->repo));
}

void MovieService::removeMovie(std::string title, std::string genre, const int releaseYear) {
    const Movie movieKey{std::move(title), std::move(genre), releaseYear, Link(), 0};
    Movie fullMovie = this->repo->getElement(movieKey);
    this->repo->removeElement(fullMovie);
    clearRedoStack();
    undoStack.push(std::make_unique<ActionRemove>(fullMovie, *this->repo));
}

std::vector<Movie> MovieService::allMovies() const {
    return this->repo->getData();
}

void MovieService::likeMovie(const Movie &movie) const {
    try {
        Movie& movieToLike = this->repo->getElement(movie);
        const Movie oldMovie = movieToLike;
        movieToLike.like();
        this->repo->updateElement(oldMovie, movieToLike);
    }
    catch (const RepositoryException&) {
        return;
    }
}

void MovieService::updateMovie(std::string title, std::string genre, int releaseYear, std::string newTitle, std::string newGenre, int newReleaseYear, std::string newTrailerLink, int newLikes) {
    Movie movieToFind{std::move(title), std::move(genre), releaseYear, Link(), 0};
    Movie oldMovie = this->repo->getElement(movieToFind);

    Movie newMovie(std::move(newTitle), std::move(newGenre), newReleaseYear, Link(std::move(newTrailerLink)), newLikes);
    MovieValidator::validate(newMovie);

    this->repo->updateElement(oldMovie, newMovie);
    clearRedoStack();
    undoStack.push(std::make_unique<ActionUpdate>(oldMovie, newMovie, *this->repo));
}

void MovieService::addToWatchList(const Movie &movie) const {
    if (this->watchList == nullptr) {
        throw RepositoryException("Watchlist not initialized!");
    }
    std::vector<Movie> currentWl = this->watchList->getAll();
    if (const auto it = std::find(currentWl.begin(), currentWl.end(), movie); it != currentWl.end()) {
        throw RepositoryException("Movie already in watchlist!");
    }
    this->watchList->addMovie(movie);
}

void MovieService::removeFromWatchList(const Movie &movie, const bool like) const {
    if (this->watchList == nullptr) {
        throw RepositoryException("Watchlist not initialized!");
    }
    std::vector<Movie> currentWl = this->watchList->getAll();
    if (const auto it = std::find(currentWl.begin(), currentWl.end(), movie); it == currentWl.end()) {
        throw RepositoryException("Movie not found in watchlist!");
    }

    if (like) {
        this->likeMovie(movie);
    }
    this->watchList->removeMovie(movie);
}

std::vector<Movie> MovieService::getWatchList() const {
    if (this->watchList == nullptr) {
        return {};
    }
    return this->watchList->getAll();
}

Movie MovieService::findMovie(std::string title, std::string genre, const int releaseYear) const {
    return this->repo->getElement(Movie(std::move(title), std::move(genre), releaseYear, Link(), 0));
}

std::vector<Movie> MovieService::filterMovies(std::string genre) const {
    std::vector<Movie> all = this->repo->getData();
    if (genre.empty()) {
        return all;
    }
    std::vector<Movie> filteredMovies;
    std::copy_if(all.begin(), all.end(), std::back_inserter(filteredMovies), [&genre](const Movie& m){return m.getGenre() == genre;});
    return filteredMovies;
}

std::map<std::string, int> MovieService::getGenreCounts() const {
    std::map<std::string, int> counts;
    for (const auto& m : this->repo->getData()) {
        counts[m.getGenre()]++;
    }
    return counts;
}

void MovieService::showWatchlist() const {
    if (this->watchList != nullptr) {
        this->watchList->displayWatchlist();
    }
}

void MovieService::undo() {
    if (undoStack.empty()) {
        throw std::runtime_error("No more actions to undo!");
    }
    auto action = std::move(undoStack.top());
    undoStack.pop();
    action->undo();
    redoStack.push(std::move(action));
}

void MovieService::redo() {
    if (redoStack.empty()) {
        throw std::runtime_error("No more actions to redo!");
    }
    auto action = std::move(redoStack.top());
    redoStack.pop();
    action->redo();
    undoStack.push(std::move(action));
}

Repo<Movie>& MovieService::getRepo() const {
    return *this->repo;
}
