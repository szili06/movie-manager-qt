//
// Created by szili on 5/7/26.
//
#ifndef A8_9_SZILI_06_GUI_H
#define A8_9_SZILI_06_GUI_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include "../Service/MovieService.h"
#include <QLabel>
#include <QMessageBox>
#include <QFormLayout>
#include <QDesktopServices>
#include <QUrl>
#include "../UI/ChartWidget.h"

#include "../UI/AdminGUI.h"
#include "../UI/UserGUI.h"

class GUI : public QWidget {
    Q_OBJECT
    MovieService* service;
    QStackedWidget* stackedWidget;
    AdminGUI* adminView;
    UserGUI* userView;

public:
    explicit GUI(MovieService& service, QWidget* parent = nullptr);
    ~GUI() override = default;
};

#endif //A8_9_SZILI_06_GUI_H