#include "WatchlistTableModel.h"
#include <vector>

WatchlistTableModel::WatchlistTableModel(MovieService& service, QObject* parent)
    : QAbstractTableModel(parent), service(service) {
}

int WatchlistTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(service.getWatchList().size());
}

int WatchlistTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return 5;
}

QVariant WatchlistTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};

    auto watchlist = service.getWatchList();
    if (index.row() >= static_cast<int>(watchlist.size())) return {};

    const Movie& movie = watchlist[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0: return QString::fromStdString(movie.getTitle());
            case 1: return QString::fromStdString(movie.getGenre());
            case 2: return movie.getReleaseYear();
            case 3: return movie.getNrOfLikes();
            case 4: return QString::fromStdString(movie.getTrailerLink().getUrl());
            default: return {};
        }
    }

    if (role == Qt::TextAlignmentRole) {
        if (index.column() == 2 || index.column() == 3)
            return Qt::AlignCenter;
    }

    return {};
}

QVariant WatchlistTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Title";
            case 1: return "Genre";
            case 2: return "Year";
            case 3: return "Likes";
            case 4: return "Trailer Link";
            default: return {};
        }
    }

    return section + 1; // Row numbers for vertical header
}

void WatchlistTableModel::resetData() {
    beginResetModel();
    endResetModel();
}
