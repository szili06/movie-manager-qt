#ifndef ADMINGUI_H
#define ADMINGUI_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QShortcut>
#include "../Service/MovieService.h"

class AdminGUI : public QWidget {
    Q_OBJECT
    MovieService* service;
    QTableWidget* adminTable;

public:
    explicit AdminGUI(MovieService& service, QWidget* parent = nullptr);
    void populateAdminList();
    void handleAdminCellEdited(QTableWidgetItem* item);
    void showStats();
    void undoAction();
    void redoAction();
};

#endif // ADMINGUI_H
