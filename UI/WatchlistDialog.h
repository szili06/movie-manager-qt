#ifndef A8_9_SZILI_06_WATCHLISTDIALOG_H
#define A8_9_SZILI_06_WATCHLISTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class WatchlistDialog : public QDialog {
public:
    int selectedType = 1;

    WatchlistDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Select Watchlist Format");
        setMinimumWidth(300);

        auto* layout = new QVBoxLayout(this);
        layout->setContentsMargins(20, 20, 20, 20);
        layout->setSpacing(15);

        auto* label = new QLabel("Please choose your preferred watchlist format:");
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        auto* btnCsv = new QPushButton("CSV (Comma Separated Values)");
        auto* btnHtml = new QPushButton("HTML (HyperText Markup Language)");

        btnCsv->setStyleSheet("padding: 8px; font-weight: bold;");
        btnHtml->setStyleSheet("padding: 8px; font-weight: bold;");

        connect(btnCsv, &QPushButton::clicked, [this]() { selectedType = 1; accept(); });
        connect(btnHtml, &QPushButton::clicked, [this]() { selectedType = 2; accept(); });

        layout->addWidget(btnCsv);
        layout->addWidget(btnHtml);
    }
};

#endif //A8_9_SZILI_06_WATCHLISTDIALOG_H
