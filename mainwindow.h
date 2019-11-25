#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include<QtCharts/QChart>
#include<QtCharts/QChartView>
#include<QtDataVisualization>
#include <QChartView>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>

#include <QVector>
#include <QTimer>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //bool eventFilter(QObject *watched,QEvent *event);

    void piedrawing();
    void iniChart();
private:
    Ui::MainWindow *ui;
    QtCharts::QPieSlice *slice1;
    QtCharts::QPieSlice *slice2;
    QtCharts::QPieSlice *slice3;
    QtCharts::QPieSeries *series1;
    QtCharts::QChart *chart;
    QtCharts::QChartView *mChart;
    QtCharts::QValueAxis *vaX;
    QtCharts::QValueAxis *vaY1;
    QtCharts::QValueAxis *vaY2;
    QtCharts::QSplineSeries *spY1 ;
    QtCharts::QSplineSeries *spY2;
    QVector<QPointF>  vecKv;
};
#endif // MAINWINDOW_H
