#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVector>
#include <qcustomplot.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);

    connect(ui->Start,SIGNAL(clicked()),this,SLOT(Nsga()));



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Nsga()
{

    Nsga2 *ag = new Nsga2(ui->spinBox->value(),10);
    ag->init_population(1,3);
    ag->evaluation();
    ag->fast_non_dominated_sort();
    ag->show();

    vector<double> y1 = ag->returnY1();
    vector<double> y2 = ag->returnY2();

    vector<double> y1f0 = ag->returnY1F0();
    vector<double> y2f0 = ag->returnY2F0();

    makePlot(y1, y2,y1f0,y2f0);

    ui->progressBar->setValue(15);
}

void MainWindow::makePlot(vector<double> y1, vector<double> y2,vector<double> y1f, vector<double> y2f)
{

    ui->customPlot->clearGraphs();
    QPen pen;
    pen.setColor(QColor(160,0,0));
    // generate some data:
    QVector<double> x, y; // initialize with entries 0..100
    for (int i=0; i<y1.size(); ++i)
    {
        x.push_back(y1[i]);
        y.push_back(y2[i]);
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setData(x, y);
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    pen.setColor(QColor(0,160,0));
    // generate some data:
    QVector<double> qx2, qy2; // initialize with entries 0..100
    for (int i=0; i<y1f.size(); ++i)
    {
        qx2.push_back(y1f[i]);
        qy2.push_back(y2f[i]);
    }
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
    ui->customPlot->graph()->setData(qx2, qy2);


    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("f1");
    ui->customPlot->yAxis->setLabel("f2");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, 9);
    ui->customPlot->yAxis->setRange(0, 9);
    ui->customPlot->replot();
}
