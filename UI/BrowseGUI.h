#ifndef BROWSEGUI_H
#define BROWSEGUI_H

#include <QDialog>
#include <QLabel>
#include "MovieService.h"

class BrowseGUI : public QDialog {
    Q_OBJECT
    MovieService* service;
    QLabel* titleLabel{};
    QLabel* genreLabel{};
    QLabel* yearLabel{};
    QLabel* likesLabel{};
    int currentIndex = 0;
    std::vector<Movie> filteredMovies;

public:
    explicit BrowseGUI(MovieService& service, QWidget* parent = nullptr);

private:
    void setupUI();
    void updateView();
    void nextMovie();
    void addToWatchlist();
    void filterMovies();
    void playTrailer();
};

#endif // BROWSEGUI_H
