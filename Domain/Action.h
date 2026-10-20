//
// Created for Assignment 10 - Undo/Redo with inheritance and polymorphism.
//

#ifndef ACTION_H
#define ACTION_H

#include "Movie.h"
#include "../Repo/Repo.h"
#include <memory>
#include <stack>
#include <utility>

class Action {
public:
    virtual ~Action() = default;

    virtual void undo() = 0;

    virtual void redo() = 0;
};

class ActionAdd : public Action {
    Movie addedMovie;
    Repo<Movie>& repo;
public:
    ActionAdd(Movie  movie, Repo<Movie>& repo)
        : addedMovie(std::move(movie)), repo(repo) {}

    void undo() override {
        repo.removeElement(addedMovie);
    }

    void redo() override {
        repo.addElement(addedMovie);
    }
};

class ActionRemove : public Action {
    Movie removedMovie;
    Repo<Movie>& repo;
public:
    ActionRemove(Movie  movie, Repo<Movie>& repo)
        : removedMovie(std::move(movie)), repo(repo) {}

    void undo() override {
        repo.addElement(removedMovie);
    }

    void redo() override {
        repo.removeElement(removedMovie);
    }
};

class ActionUpdate : public Action {
    Movie oldMovie;
    Movie newMovie;
    Repo<Movie>& repo;
public:
    ActionUpdate(Movie  oldMovie, Movie  newMovie, Repo<Movie>& repo)
        : oldMovie(std::move(oldMovie)), newMovie(std::move(newMovie)), repo(repo) {}

    void undo() override {
        repo.updateElement(newMovie, oldMovie);
    }

    void redo() override {
        repo.updateElement(oldMovie, newMovie);
    }
};

#endif // ACTION_H
