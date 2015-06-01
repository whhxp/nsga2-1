#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVector>
#include <qcustomplot.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    f = 0;
    init = 0;

    nsga2 = NULL;

    MinMax(1);

    timer = new QTimer(this);
    timer->setInterval(100);

    connect(ui->Start,SIGNAL(clicked()),this->timer,SLOT(start()));
   // connect(ui->Start,SIGNAL(clicked()),this,SLOT(Nsga()));
    connect(ui->Stop,SIGNAL(clicked()),this->timer,SLOT(stop()));
    connect(timer,SIGNAL(timeout()), this, SLOT(Nsga()));
    connect(ui->Init,SIGNAL(clicked()),this,SLOT(Init()));
    connect(ui->varebl_spin_f1,SIGNAL(valueChanged(int)),this,SLOT(MinMax(int)));
    connect(ui->varebl_spin_f2,SIGNAL(valueChanged(int)),this,SLOT(MinMax(int)));
    connect(ui->comboBox,SIGNAL(activated(QString)),this,SLOT(hide(QString)));
    connect(ui->sortowanie,SIGNAL(activated(QString)),this,SLOT(sortowanieY(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

   void MainWindow::exe2()
   {
       timer->stop();
       init = 1;
       if(nsga2 != NULL) delete nsga2;
       ui->statusBar->showMessage(" Inicjalizacja populacji Zitzler-Deb-Thiele's function N.1  ", 1000);
       min.clear();
       max.clear();

       min.push_back(-10);
       min.push_back(-10);

       max.push_back(10);
       max.push_back(10);

       str1 = "x^2";
       str2 = "(x-2)^2";
       v1 = 2;
       v2 = 2;

       nsga2 =  new  Nsga2(ui->spinBox->value(),ui->crossover->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
       nsga2->init_population();
       nsga2->evaluation();
       nsga2->fast_non_dominated_sort();
       nsga2->crowding_distance_assigment();

       ui->textEdit->setText(QString().fromStdString(nsga2->toStringF1(f)));
       qDebug() << "Inicjalizacja" << endl;
       qDebug() << QString().fromStdString(nsga2->toStringF1(f)) << endl;

       vector<double> y1 = nsga2->returnY1();
       vector<double> y2 = nsga2->returnY2();

       vector<double> y1f0 = nsga2->returnY1F0();
       vector<double> y2f0 = nsga2->returnY2F0();

       makePlot(y1, y2,y1f0,y2f0);
   }

void MainWindow::exe1()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji funkcja Binh and Korn ", 1000);
    min.clear();
    max.clear();

    min.push_back(0);
    min.push_back(0);

    max.push_back(5);
    max.push_back(3);

    str1 = "4 * x^2 + 4 * y^2";
    str2 = "(x-5)^2 + (y-5)^2";
    v1 = 2;
    v2 = 2;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->crossover->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
    nsga2->init_population();
    nsga2->evaluation();
    nsga2->fast_non_dominated_sort();
    nsga2->crowding_distance_assigment();

    ui->textEdit->setText(QString().fromStdString(nsga2->toStringF1(f)));
    qDebug() << "Inicjalizacja" << endl;
    qDebug() << QString().fromStdString(nsga2->toStringF1(f)) << endl;

    vector<double> y1 = nsga2->returnY1();
    vector<double> y2 = nsga2->returnY2();

    vector<double> y1f0 = nsga2->returnY1F0();
    vector<double> y2f0 = nsga2->returnY2F0();

    makePlot(y1, y2,y1f0,y2f0);
}

void MainWindow::Init()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji ", 1000);
    vector<double> Hmin = MIN();
    vector<double> Hmax = MAX();
    min.clear();
    max.clear();

    int i = 0, j = 0;
    while(min.size() < ui->varebl_spin_f1->value())
    {
        min.push_back(Hmin[i]);
        i++;
    }
    while(max.size() < ui->varebl_spin_f2->value())
    {
        max.push_back(Hmax[j]);
        j++;
    }
    str1 = ui->function1->text().toStdString();
    str2 = ui->function2->text().toStdString();
    v1 = ui->varebl_spin_f1->value();
    v2 = ui->varebl_spin_f2->value();

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->crossover->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
    nsga2->init_population();
    nsga2->evaluation();
    nsga2->fast_non_dominated_sort();
    nsga2->crowding_distance_assigment();

    ui->textEdit->setText(QString().fromStdString(nsga2->toStringF1(f)));
    //qDebug() << "Inicjalizacja" << endl;
    //qDebug() << QString().fromStdString(nsga2->toStringF1(f)) << endl;

    vector<double> y1 = nsga2->returnY1();
    vector<double> y2 = nsga2->returnY2();

    vector<double> y1f0 = nsga2->returnY1F0();
    vector<double> y2f0 = nsga2->returnY2F0();

    makePlot(y1, y2,y1f0,y2f0);



}

void MainWindow::Nsga()
{
    if(nsga2 == NULL)
    {
        ui->statusBar->showMessage(" Brak zainicjalizowanej populacji", 1000);
        timer->stop();

        return;
    }
    else
    {
    ui->statusBar->showMessage(" Realizacja algorytmu NSGA-II ",1000);

    try
    {
        nsga2->MainLoop();
    }
    catch (exception &e)
    {
        qDebug() << QString().fromUtf8(e.what()) << endl;
        qDebug() << "Bład" << endl;
    }

    ui->textEdit->clear();
    ui->textEdit->setText(QString().fromStdString(nsga2->toStringF1(f)));

    //qDebug() << "Nsga" << endl;
    //qDebug() << QString().fromStdString(nsga2->toStringF1(f)) << endl;

    vector<double> y1 = nsga2->returnY1();
    vector<double> y2 = nsga2->returnY2();

    vector<double> y1f0 = nsga2->returnY1F0();
    vector<double> y2f0 = nsga2->returnY2F0();

    makePlot(y1, y2,y1f0,y2f0);

    if(nsga2->Pareto())
     {
        static int i = 0;
        if( i >= ui->spinBox_2->value())
        {
         timer->stop();
         i = 0;
         QMessageBox dialog(this);
         dialog.setText(" Osiągnięto zbiór pareto optymalny !!");
         dialog.exec();
        }
        i++;
     }


    }
}

void MainWindow::makePlot(vector<double> y1, vector<double> y2,vector<double> y1f, vector<double> y2f)
{

    ui->customPlot->clearGraphs();
    QPen pen;
    pen.setColor(QColor(160,0,0));
    // generate some data:
    QVector<double> x, y; // initialize with entries 0..100
    for (unsigned int i=0; i<y1.size(); ++i)
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
    for (unsigned int i=0; i<y1f.size(); ++i)
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
    ui->customPlot->xAxis->setRange(-50, 50);//f1
    ui->customPlot->yAxis->setRange(-50, 50);//f2
    ui->customPlot->rescaleAxes(true);
    ui->customPlot->replot();
}

void MainWindow::MinMax(int value)
{

    ui->max_x->hide();
    ui->max_y->hide();
    ui->max_z->hide();
    ui->max_g->hide();
    ui->max_h->hide();

    ui->min_x->hide();
    ui->min_y->hide();
    ui->min_z->hide();
    ui->min_g->hide();
    ui->min_h->hide();

    int i = ui->varebl_spin_f1->value();
    int j =  ui->varebl_spin_f2->value();
    int max = i > j ? i : j;

    switch(max)
    {
    case 5:
        ui->max_h->show();
        ui->min_h->show();

    case 4:
        ui->max_g->show();
        ui->min_g->show();

    case 3:
        ui->max_z->show();
        ui->min_z->show();

    case 2:
        ui->max_y->show();
        ui->min_y->show();

    case 1:
        ui->max_x->show();
        ui->min_x->show();
    }
}

vector<double> MainWindow::MIN()
{
    vector<double> min;

    min.push_back( ui->min_x->value());
    min.push_back( ui->min_y->value());
    min.push_back( ui->min_z->value());
    min.push_back( ui->min_g->value());
    min.push_back( ui->min_h->value());

    return min;

}

vector<double> MainWindow::MAX()
{
    vector<double> max;
    max.push_back( ui->max_x->value());
    max.push_back( ui->max_y->value());
    max.push_back( ui->max_z->value());
    max.push_back( ui->max_g->value());
    max.push_back( ui->max_h->value());

    return max;
}


void MainWindow::hide(QString s)
{
    if(s != "Parser")
    {
        ui->Grup_Parser->hide();
        ui->ograniczenia->hide();
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(Init()));
    }
    else if( s == "Parser")
    {
        ui->Grup_Parser->show();
        ui->ograniczenia->show();
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(Init()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe1()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe2()));

        return;
    }

    if( s == "Binh and Korn")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe1()));
    }

    if( s == "Zitzler-Deb-Thiele's function N.1")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe2()));
    }
}


void MainWindow::sortowanieY(QString s)
{
    if(init != 1) return;

    if(s == "f1")
    {
        f = 0;
        ui->textEdit->clear();
        ui->textEdit->setText(QString().fromStdString(nsga2->toStringF1(f)));
    }
    else if( s == "f2")
    {
        f = 1;

        ui->textEdit->clear();
        ui->textEdit->setText(QString().fromStdString(nsga2->toStringF1(f)));
    }


}


