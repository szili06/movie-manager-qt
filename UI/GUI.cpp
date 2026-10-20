#include "../UI/GUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

GUI::GUI(MovieService &s, QWidget *parent) : QWidget(parent), service(&s) {
    auto* mainLayout = new QVBoxLayout(this);

    auto* menuLayout = new QHBoxLayout();
    auto* btnAdmin = new QPushButton("Admin Mode");
    auto* btnUser = new QPushButton("User Mode");
    menuLayout->addWidget(btnAdmin);
    menuLayout->addWidget(btnUser);
    mainLayout->addLayout(menuLayout);

    stackedWidget = new QStackedWidget();
    adminView = new AdminGUI(*this->service);
    userView = new UserGUI(*this->service);
    stackedWidget->addWidget(adminView);
    stackedWidget->addWidget(userView);

    connect(userView, &UserGUI::dataChanged, adminView, &AdminGUI::populateAdminList);

    mainLayout->addWidget(stackedWidget);

    connect(btnAdmin, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(0); });
    connect(btnUser, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(1); });

    setLayout(mainLayout);
    resize(1200, 800);
    setStyleSheet("QWidget { background-color: #2b2b2b; color: #ffffff; font-family: 'Segoe UI', sans-serif; font-size: 16px; }"
                  "QPushButton { padding: 12px; }"
                  "QTableWidget QPushButton { padding: 0px; }"
                  "QTableWidget { background-color: #363636; alternate-background-color: #2d2d2d; border: 1px solid #555; }"
                  "QHeaderView::section { background-color: #454545; color: white; padding: 6px; border: none; }");
}