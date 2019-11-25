#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QVector>
#include<QPieSeries>
#include<Q3DBars>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    piedrawing();
    iniChart();
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniChart()
{
    mChart = new QtCharts::QChartView();
    mChart->setEnabled(true);
    mChart->chart()->setTitle("Kv-Vacuum");
    mChart->chart()->legend()->hide();
    mChart->chart()->setTheme(QtCharts::QChart::ChartTheme::ChartThemeDark);

    vaX = new QtCharts::QValueAxis();
    vaY1 = new QtCharts::QValueAxis();
    vaY2 = new QtCharts::QValueAxis();

    spY1 = new QtCharts::QSplineSeries();
    spY2 = new QtCharts::QSplineSeries();

    //vecKv = new QVector<QPointF>;
    //vecVacc = new QVector<QPointF>;

    vaX->setRange(0, 200);
    vaX->setTickCount(7);
    vaX->setLabelsColor(QColor(0, 255, 0));
    vaX->setTitleText("Sample-Points");

    vaY1->setRange(0, 200);
    vaY1->setTickCount(6);
    vaY1->setLabelsColor(QColor(255,0, 0));
    vaY1->setTitleText("Voltage-Kv");

    vaY2->setRange(0, 10);
    vaY2->setTickCount(6);
    vaY2->setLabelsColor(QColor(0, 0, 255));
    vaY2->setTitleText("Penning-V");

    mChart->chart()->addAxis(vaX, Qt::AlignBottom);
    mChart->chart()->addAxis(vaY1, Qt::AlignLeft);
    mChart->chart()->addAxis(vaY2, Qt::AlignRight);
    mChart->chart()->addSeries(spY1);
    mChart->chart()->addSeries(spY2);


    spY1->attachAxis(vaX);
    spY1->attachAxis(vaY1);
    spY1->setColor(QColor(255, 0, 0));
    spY1->setUseOpenGL();// 开启openGL加速

    spY2->attachAxis(vaX);
    spY2->attachAxis(vaY2);
    spY2->setColor(QColor(0, 0, 255));
    spY2->setUseOpenGL();
    if(vecKv.count()>0)
      vecKv.clear();
    for(int i=0;i<200;i=i+6){
         vecKv.append(QPointF(i+0.0,qrand() %100));
    }
    spY1->replace(vecKv);
    ui->horizontalLayout->insertWidget(1,mChart);
}
void MainWindow::piedrawing()
{    
    slice1=new QtCharts::QPieSlice(tr("铺布完成层数"),0.6,this);
    slice1->setLabelVisible(true);
    slice1->setBrush(Qt::green);

    slice2=new QtCharts::QPieSlice(tr("剩余层数"),0.2,this);
    slice2->setLabelVisible(true);
    slice2->setBrush(Qt::blue);

    slice3=new QtCharts::QPieSlice(tr("裁床"),0.2,this);
    slice3->setLabelVisible(true);
    slice3->setBrush(Qt::red);



    series1=new QtCharts::QPieSeries(this);
    series1->append(slice1);
    series1->append(slice2);
    series1->append(slice3);
    series1->setHoleSize(0.4);
    series1->setPieStartAngle(120);
    series1->setPieEndAngle(-120);    
    QtCharts::QChart *chart=new QtCharts::QChart();
    chart->addSeries(series1);

    chart->setAnimationOptions(QtCharts::QChart::AllAnimations);
    QtCharts::QChartView *chartView=new QtCharts::QChartView(this);

    chartView->setChart(chart);
    chartView->show();
    ui->horizontalLayout->insertWidget(0,chartView);
}
