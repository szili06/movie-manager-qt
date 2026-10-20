//
// Created by szili on 4/23/26.
//

#include "Watchlist.h"
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QProcess>

void Watchlist::addMovie(const Movie &m) {
    movies.push_back(m);
    writeToFile();
}

void Watchlist::removeMovie(const Movie &m) {
    auto it = std::find(movies.begin(), movies.end(), m);
    if (it != movies.end()) {
        movies.erase(it);
        writeToFile();
    }
}

std::vector<Movie> Watchlist::getAll() const {
    return this->movies;
}

void CSVWatchlist::writeToFile() const {
    std::ofstream file(this->filename);
    if (!file.is_open()) return;
    for (const auto& m : this->movies) {
        file << m <<"\n";

    }
}

void CSVWatchlist::displayWatchlist() const {
    QString path = QFileInfo(QString::fromStdString(this->filename)).absoluteFilePath();
    QProcess::startDetached("libreoffice", {"--calc", path});
}

void HTMLWatchList::writeToFile() const {
    std::ofstream file(this->filename);
    if (!file.is_open()) return;
    file << "<!DOCTYPE html>\n<html>\n<head><title>Watch List</title></head>\n<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr><td>Title</td><td>Genre</td><td>Year</td><td>Likes</td><td>Trailer</td></tr>\n";
    for (const auto& m : this->movies) {
        file << "<tr><td>" << m.getTitle() << "</td>"
        << "<td>" << m.getGenre() << "</td>"
        << "<td>" << m.getReleaseYear() << "</td>"
        << "<td>" << m.getNrOfLikes() << "</td>"
        << "<td><a href=\"" << m.getTrailerLink().getUrl() << "\">Link</a></td></tr>\n";
    }
    file << "</table></body></html>";
    file.close();
}

void HTMLWatchList::displayWatchlist() const {
    QString path = QFileInfo(QString::fromStdString(this->filename)).absoluteFilePath();
    QProcess::startDetached("xdg-open", {path});
}
