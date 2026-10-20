#include "ChartWidget.h"

ChartWidget::ChartWidget(const std::map<std::string, int> &data, QWidget *parent)
    : QChartView(parent) {
    auto *series = new QBarSeries();
    auto *set = new QBarSet("Number of Movies");

    QStringList categories;
    for (const auto& pair : data) {
        *set << pair.second;
        categories << QString::fromStdString(pair.first);
    }
    series->append(set);

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Movie Genres Statistics");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor("#2b2b2b")));
    chart->setTitleBrush(QBrush(Qt::white));
    
    int maxVal = 0;
    for (const auto& pair : data) if (pair.second > maxVal) maxVal = pair.second;

    auto *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(Qt::white);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis();
    axisY->setRange(0, maxVal + 1);
    axisY->setLabelsColor(Qt::white);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(Qt::white);

    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(800, 600);
    setStyleSheet("background-color: #2b2b2b;");
}
