#include "../UI/UserGUI.h"
#include "../UI/BrowseGUI.h"
#include "../UI/WatchlistTableModel.h"
#include "../UI/WatchlistWindow.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableView>
#include <QDialog>

UserGUI::UserGUI(MovieService& service, QWidget* parent) : QWidget(parent), service(&service) {
    auto* layout = new QVBoxLayout(this);

    watchlistTable = new QTableWidget();
    watchlistTable->setColumnCount(5);
    watchlistTable->setHorizontalHeaderLabels({"Title", "Genre", "Year", "Likes", "Action"});
    watchlistTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    watchlistTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    watchlistTable->verticalHeader()->setDefaultSectionSize(40);
    layout->addWidget(watchlistTable);

    auto* btnLayout = new QHBoxLayout();
    auto* btnExternal = new QPushButton("See External File (CSV/HTML)");
    auto* btnBrowse = new QPushButton("Browse Movies");
    
    connect(btnExternal, &QPushButton::clicked, [this]() {
        this->service->showWatchlist();
    });
    connect(btnBrowse, &QPushButton::clicked, this, &UserGUI::openBrowseDialog);
    
    auto* btnTableView = new QPushButton("View Watchlist (Table View)");
    connect(btnTableView, &QPushButton::clicked, this, &UserGUI::openWatchlistTableView);

    btnLayout->addWidget(btnBrowse);
    btnLayout->addWidget(btnExternal);
    btnLayout->addWidget(btnTableView);
    layout->addLayout(btnLayout);

    populateWatchlist();
}

void UserGUI::populateWatchlist() {
    watchlistTable->clearContents();
    const auto watchlist = service->getWatchList();
    watchlistTable->setRowCount(static_cast<int>(watchlist.size()));

    for (int i = 0; i < watchlist.size(); ++i) {
        watchlistTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(watchlist[i].getTitle())));
        watchlistTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(watchlist[i].getGenre())));
        watchlistTable->setItem(i, 2, new QTableWidgetItem(QString::number(watchlist[i].getReleaseYear())));
        watchlistTable->setItem(i, 3, new QTableWidgetItem(QString::number(watchlist[i].getNrOfLikes())));

        auto* btnRemove = new QPushButton("Remove");
        Movie m = watchlist[i];
        connect(btnRemove, &QPushButton::clicked, [this, m]() {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Rate Movie", "Did you like this movie?",
                                         QMessageBox::Yes|QMessageBox::No);
            const bool liked = (reply == QMessageBox::Yes);
            try {
                service->removeFromWatchList(m, liked);
                populateWatchlist();
                if (watchlistWindow && watchlistWindow->isVisible())
                    watchlistWindow->refresh();
                emit dataChanged();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", e.what());
            }
        });
        watchlistTable->setCellWidget(i, 4, btnRemove);
    }
}

void UserGUI::openBrowseDialog() {
    BrowseGUI dialog(*service, this);
    dialog.exec();
    populateWatchlist();
    if (watchlistWindow && watchlistWindow->isVisible())
        watchlistWindow->refresh();
}

void UserGUI::openWatchlistTableView() {
    if (!watchlistWindow) {
        watchlistWindow = new WatchlistWindow(*service, this);
    }
    watchlistWindow->refresh();
    watchlistWindow->show();
    watchlistWindow->raise();
    watchlistWindow->activateWindow();
}
