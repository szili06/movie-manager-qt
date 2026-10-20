#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChart>
#include <map>
#include <string>

class ChartWidget : public QChartView {
    Q_OBJECT
public:
    explicit ChartWidget(const std::map<std::string, int> &data, QWidget *parent = nullptr);
};

#endif // CHARTWIDGET_H
