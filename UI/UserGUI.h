#ifndef USERGUI_H
#define USERGUI_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include "../Service/MovieService.h"

class WatchlistWindow;

class UserGUI : public QWidget {
    Q_OBJECT
    MovieService* service;
    QTableWidget* watchlistTable;
    WatchlistWindow* watchlistWindow = nullptr;

public:
    explicit UserGUI(MovieService& service, QWidget* parent = nullptr);
    void populateWatchlist();
    void openBrowseDialog();
    void openWatchlistTableView();

signals:
    void dataChanged();
};

#endif // USERGUI_H
