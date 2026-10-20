#ifndef WATCHLISTWINDOW_H
#define WATCHLISTWINDOW_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include "WatchlistTableModel.h"
class WatchlistWindow : public QWidget {
    Q_OBJECT

    WatchlistTableModel* model;
    QTableView* tableView;

public:
    explicit WatchlistWindow(MovieService& service, QWidget* parent = nullptr);

public slots:
    void refresh();
};

#endif // WATCHLISTWINDOW_H
