//
// Created by szili on 6/4/26.
//

#include "WatchlistWindow.h"

WatchlistWindow::WatchlistWindow(MovieService &service, QWidget *parent) : QWidget(parent, Qt::Window), model(new WatchlistTableModel(service, this)) {
    setWindowTitle("Watchlist - Table View");
    resize(800, 400);

    auto* layout = new QVBoxLayout(this);

    tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setAlternatingRowColors(true);
    tableView->verticalHeader()->setDefaultSectionSize(35);

    layout->addWidget(tableView);
}

void WatchlistWindow::refresh() {
    model->resetData();
}
