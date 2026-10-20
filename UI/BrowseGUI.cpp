#include "BrowseGUI.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

BrowseGUI::BrowseGUI(MovieService& service, QWidget* parent) 
    : QDialog(parent), service(&service) {
    filteredMovies = this->service->allMovies();
    setupUI();
    updateView();
}

void BrowseGUI::setupUI() {
    setWindowTitle("Browse Movies");
    setMinimumSize(400, 250);
    setStyleSheet("QDialog { background-color: #2b2b2b; color: #ffffff; } "
                  "QLabel { font-size: 16px; padding: 2px; } "
                  "QPushButton { padding: 8px; background-color: #3d3d3d; border: none; border-radius: 4px; }");

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setAlignment(Qt::AlignCenter);

    auto* formLayout = new QFormLayout();
    titleLabel = new QLabel();
    genreLabel = new QLabel();
    yearLabel = new QLabel();
    likesLabel = new QLabel();

    titleLabel->setAlignment(Qt::AlignCenter);
    genreLabel->setAlignment(Qt::AlignCenter);
    yearLabel->setAlignment(Qt::AlignCenter);
    likesLabel->setAlignment(Qt::AlignCenter);

    formLayout->addRow("Title:", titleLabel);
    formLayout->addRow("Genre:", genreLabel);
    formLayout->addRow("Year:", yearLabel);
    formLayout->addRow("Likes:", likesLabel);
    layout->addLayout(formLayout);

    auto* btnLayout = new QHBoxLayout();
    auto* btnFilter = new QPushButton("Filter");
    auto* btnAdd = new QPushButton("Add");
    auto* btnNext = new QPushButton("Next");

    btnLayout->addWidget(btnFilter);
    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnNext);
    layout->addLayout(btnLayout);

    connect(btnNext, &QPushButton::clicked, this, &BrowseGUI::nextMovie);
    connect(btnAdd, &QPushButton::clicked, this, &BrowseGUI::addToWatchlist);
    connect(btnFilter, &QPushButton::clicked, this, &BrowseGUI::filterMovies);
}

void BrowseGUI::updateView() {
    if (filteredMovies.empty()) {
        titleLabel->setText("No movies found.");
        genreLabel->clear(); yearLabel->clear(); likesLabel->clear();
        return;
    }
    const auto& m = filteredMovies[currentIndex % filteredMovies.size()];
    titleLabel->setText(QString::fromStdString(m.getTitle()));
    genreLabel->setText(QString::fromStdString(m.getGenre()));
    yearLabel->setText(QString::number(m.getReleaseYear()));
    likesLabel->setText(QString::number(m.getNrOfLikes()));
    playTrailer();
}

void BrowseGUI::nextMovie() {
    if (!filteredMovies.empty()) {
        currentIndex++;
        updateView();
    }
}

void BrowseGUI::addToWatchlist() {
    if (!filteredMovies.empty()) {
        try {
            service->addToWatchList(filteredMovies[currentIndex % filteredMovies.size()]);
            QMessageBox::information(this, "Success", "Added to watchlist!");
            nextMovie();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
}

void BrowseGUI::filterMovies() {
    bool ok;
    QString genre = QInputDialog::getText(this, "Filter", "Enter genre:", QLineEdit::Normal, "", &ok);
    if (ok) {
        filteredMovies = service->filterMovies(genre.toStdString());
        currentIndex = 0;
        updateView();
    }
}

void BrowseGUI::playTrailer() {
    if (!filteredMovies.empty()) {
        QDesktopServices::openUrl(QUrl(QString::fromStdString(filteredMovies[currentIndex % filteredMovies.size()].getTrailerLink().getUrl())));
    }
}
