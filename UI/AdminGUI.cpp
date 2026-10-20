#include "../UI/AdminGUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "../UI/ChartWidget.h"

AdminGUI::AdminGUI(MovieService& service, QWidget* parent) : QWidget(parent), service(&service) {
    auto* layout = new QVBoxLayout(this);

    // Undo/Redo buttons
    auto* undoRedoLayout = new QHBoxLayout();
    auto* btnUndo = new QPushButton("Undo");
    auto* btnRedo = new QPushButton("Redo");
    connect(btnUndo, &QPushButton::clicked, this, &AdminGUI::undoAction);
    connect(btnRedo, &QPushButton::clicked, this, &AdminGUI::redoAction);
    undoRedoLayout->addWidget(btnUndo);
    undoRedoLayout->addWidget(btnRedo);
    undoRedoLayout->addStretch();
    layout->addLayout(undoRedoLayout);

    // Keyboard shortcuts: Ctrl+Z for undo, Ctrl+Y for redo
    auto* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    connect(undoShortcut, &QShortcut::activated, this, &AdminGUI::undoAction);
    auto* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    connect(redoShortcut, &QShortcut::activated, this, &AdminGUI::redoAction);

    adminTable = new QTableWidget();
    adminTable->setColumnCount(7);
    adminTable->setHorizontalHeaderLabels({"Title", "Genre", "Year", "Likes", "Link", "Trailer", "Action"});
    adminTable->setEditTriggers(QAbstractItemView::DoubleClicked);
    adminTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    adminTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    adminTable->setSortingEnabled(true);
    adminTable->setAlternatingRowColors(true);
    adminTable->verticalHeader()->setDefaultSectionSize(40);
    
    connect(adminTable, &QTableWidget::itemChanged, this, &AdminGUI::handleAdminCellEdited);
    layout->addWidget(adminTable);
    populateAdminList();
}

void AdminGUI::populateAdminList() {
    adminTable->blockSignals(true);
    adminTable->clearContents();
    
    auto movies = service->allMovies();
    adminTable->setRowCount(static_cast<int>(movies.size() + 1));
    
    for (int i = 0; i < movies.size(); ++i) {
        auto* titleItem = new QTableWidgetItem(QString::fromStdString(movies[i].getTitle()));
        titleItem->setData(Qt::UserRole, QString::fromStdString(movies[i].getTitle()));
        titleItem->setData(Qt::UserRole + 1, QString::fromStdString(movies[i].getGenre()));
        titleItem->setData(Qt::UserRole + 2, movies[i].getReleaseYear());
        
        adminTable->setItem(i, 0, titleItem);
        adminTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movies[i].getGenre())));
        adminTable->setItem(i, 2, new QTableWidgetItem(QString::number(movies[i].getReleaseYear())));
        adminTable->setItem(i, 3, new QTableWidgetItem(QString::number(movies[i].getNrOfLikes())));
        adminTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(movies[i].getTrailerLink().getUrl())));
        
        auto* btnTrailer = new QPushButton("Open Trailer");
        QString url = QString::fromStdString(movies[i].getTrailerLink().getUrl());
        connect(btnTrailer, &QPushButton::clicked, [url]() {
            QDesktopServices::openUrl(QUrl(url));
        });
        adminTable->setCellWidget(i, 5, btnTrailer);

        auto* btnDelete = new QPushButton("Delete");
        connect(btnDelete, &QPushButton::clicked, [this, i]() {
            auto movies = service->allMovies();
            const auto& m = movies[i];
            service->removeMovie(m.getTitle(), m.getGenre(), m.getReleaseYear());
            populateAdminList();
        });
        adminTable->setCellWidget(i, 6, btnDelete);
    }

    auto* btnStats = new QPushButton("Show Statistics");
    connect(btnStats, &QPushButton::clicked, this, &AdminGUI::showStats);
    adminTable->setCellWidget(static_cast<int>(movies.size()), 5, btnStats);

    int lastRow = static_cast<int>(movies.size());
    adminTable->setCellWidget(lastRow, 0, new QLineEdit());    adminTable->setCellWidget(lastRow, 1, new QLineEdit());
    adminTable->setCellWidget(lastRow, 2, new QLineEdit());
    adminTable->setCellWidget(lastRow, 3, new QLineEdit());
    adminTable->setCellWidget(lastRow, 4, new QLineEdit());

    auto* btnAdd = new QPushButton("Add");
    connect(btnAdd, &QPushButton::clicked, [this, lastRow]() {
        auto* editTitle = qobject_cast<QLineEdit*>(adminTable->cellWidget(lastRow, 0));
        auto* editGenre = qobject_cast<QLineEdit*>(adminTable->cellWidget(lastRow, 1));
        auto* editYear = qobject_cast<QLineEdit*>(adminTable->cellWidget(lastRow, 2));
        auto* editLikes = qobject_cast<QLineEdit*>(adminTable->cellWidget(lastRow, 3));
        auto* editLink = qobject_cast<QLineEdit*>(adminTable->cellWidget(lastRow, 4));

        if (editTitle && editGenre && editYear && editLikes && editLink) {
            try {
                service->addMovie(editTitle->text().toStdString(), editGenre->text().toStdString(),
                             editYear->text().toInt(), Link(editLink->text().toStdString()),
                             editLikes->text().toInt());
                populateAdminList();
            }
            catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", e.what());
            }
            catch (...) {
                QMessageBox::critical(this, "Error", "An unknown error occurred while adding the movie.");
            }
        }
    });
    adminTable->setCellWidget(lastRow, 6, btnAdd);
    adminTable->blockSignals(false);
}

void AdminGUI::handleAdminCellEdited(QTableWidgetItem* item) {
    int row = item->row();
    if (row >= (int)service->allMovies().size()) return;
    
    auto* firstItem = adminTable->item(row, 0);
    if (!firstItem) return;

    std::string oldTitle = firstItem->data(Qt::UserRole).toString().toStdString();
    std::string oldGenre = firstItem->data(Qt::UserRole + 1).toString().toStdString();
    int oldYear = firstItem->data(Qt::UserRole + 2).toInt();

    std::string newTitle = adminTable->item(row, 0)->text().toStdString();
    std::string newGenre = adminTable->item(row, 1)->text().toStdString();
    int newYear = adminTable->item(row, 2)->text().toInt();
    int newLikes = adminTable->item(row, 3)->text().toInt();
    std::string newLink = adminTable->item(row, 4)->text().toStdString();

    try {
        service->updateMovie(oldTitle, oldGenre, oldYear, newTitle, newGenre, newYear, newLink, newLikes);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    } catch (...) {
        QMessageBox::critical(this, "Error", "An unknown error occurred while updating the movie.");
    }
    populateAdminList();
}

void AdminGUI::showStats() {
    auto* dialog = new QDialog(this);
    dialog->setWindowTitle("Genre Statistics");
    auto* layout = new QVBoxLayout(dialog);
    auto* chart = new ChartWidget(service->getGenreCounts(), dialog);
    layout->addWidget(chart);
    dialog->exec();
    delete dialog;
}

void AdminGUI::undoAction() {
    try {
        service->undo();
        populateAdminList();
    } catch (const std::exception& e) {
        QMessageBox::information(this, "Undo", e.what());
    }
}

void AdminGUI::redoAction() {
    try {
        service->redo();
        populateAdminList();
    } catch (const std::exception& e) {
        QMessageBox::information(this, "Redo", e.what());
    }
}
