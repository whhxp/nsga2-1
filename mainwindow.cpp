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



//Zitzler–Deb–Thiele's function N. 6
void MainWindow::exe10()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji Zitzler–Deb–Thiele's function N. 6 ", 1000);

    getRestrictions();


    str1 = " 1 - exp(-4*x) *( sin(6 * _pi * x ) )^6";
    str2 = " ( 1 + 9 * ( (y + z + g + h) / 9 )^(0.25) ) * ( 1 - ( (1 - exp(-4*x) *( sin(6 * _pi * x ) )^6) / (1 + 9 * ( (y + z + g + h) / 9 )^(0.25) ) )^2 )";
    v1 = 5;
    v2 = 5;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Zitzler–Deb–Thiele's function N. 4
void MainWindow::exe9()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji Zitzler–Deb–Thiele's function N. 4 ", 1000);

    getRestrictions();


    str1 = "x";
    str2 = " (41 + ( (y^2 - 10*cos(4*_pi*y) ) + (z^2 - 10*cos(4*_pi*z) ) + (g^2 - 10*cos(4*_pi*g) ) +  (h^2 - 10*cos(4*_pi*h) )))"
            "* (1 - sqrt( x /  (41 + ( (y^2 - 10*cos(4*_pi*y) ) + (z^2 - 10*cos(4*_pi*z) ) + (g^2 - 10*cos(4*_pi*g) ) +  (h^2 - 10*cos(4*_pi*h) ))) )) ";
    v1 = 5;
    v2 = 5;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Zitzler–Deb–Thiele's function N. 3
void MainWindow::exe8()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji Zitzler–Deb–Thiele's function N. 3 ", 1000);

    getRestrictions();


    str1 = "x";
    str2 = "  (1 + (9/29)*(y + z + g + h))  *  (1 - sqrt( x /( 1 + (9/29)*(y + z + g + h))) - (x /( 1 + (9/29)*(y + z + g + h))) * sin(10*_pi*x) )";
    v1 = 5;
    v2 = 5;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Zitzler–Deb–Thiele's function N. 2
void MainWindow::exe7()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji Zitzler–Deb–Thiele's function N. 2 ", 1000);

    getRestrictions();


    str1 = "x";
    str2 = "  (1 + (9/29)*(y + z + g + h))  *  (1 - ( x /( 1 + (9/29)*(y + z + g + h)))^2 )";
    v1 = 5;
    v2 = 5;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Zitzler–Deb–Thiele's function N. 1
void MainWindow::exe6()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji Zitzler–Deb–Thiele's function N. 1 ", 1000);

    getRestrictions();


    str1 = "x";
    str2 = "  (1 + (9/29)*(y + z + g + h))  *  (1 - sqrt( x /( 1 + (9/29)*(y + z + g + h))))";
    v1 = 5;
    v2 = 5;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Fonseca and Fleming function
void MainWindow::exe5()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji Fonseca and Fleming function ", 1000);

    getRestrictions();

    str1 = " 1 - exp( -1*( (x - 1/sqrt(5))^2 + (y - 1/sqrt(5))^2 + (z - 1/sqrt(5))^2 + (g - 1/sqrt(5))^2 + (h - 1/sqrt(5))^2   )   )";
    str2 = " 1 - exp( -1*( (x + 1/sqrt(5))^2 + (y + 1/sqrt(5))^2 + (z + 1/sqrt(5))^2 + (g + 1/sqrt(5))^2 + (h + 1/sqrt(5))^2   )   )";
    v1 = 5;
    v2 = 5;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Kursawe function:
void MainWindow::exe4()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji Kursawe function ", 1000);


    getRestrictions();

    str1 = "-10*exp(-0.2*sqrt(x^2 + y^2)) -10*exp(-0.2*exp(-0.2*sqrt(y^2 + z^2))) ";
    str2 = " abs(x)^0.8 + 5*sin(x^3) + abs(y)^0.8 + 5*sin(y^3) + abs(z)^0.8 + 5*sin(z^3)";
    v1 = 3;
    v2 = 3;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Poloni's two objective function:
void MainWindow::exe3()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji Poloni's two objective function: ", 1000);

    getRestrictions();

    str1 = "1 + (0.87364 - (0.5*sin(x) - 2*cos(x) + sin(y)-1.5*cos(y)) )^2 + (2.7485 - (1.5*sin(x) - cos(x) + 2*sin(y) - 0.5*cos(y)) )^2";
    str2 = "(x+3)^2 + (y+1)^2";
    v1 = 2;
    v2 = 2;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Schaffer function N. 1
void MainWindow::exe2()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacj Schaffer function N. 1: ", 1000);

    getRestrictions();

    str1 = "x^2";
    str2 = "(x-2)^2";
    v1 = 1;
    v2 = 1;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

//Schaffer function N. 2
void MainWindow::exe1()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji funkcja Schaffer function N. 2 ", 1000);

    getRestrictions();

    // (x>4)? (x-4): (100000000000000)

    str1 = "(x<=1)? (-x) : ( (x>1 && x<=3)? (x-2): ( (x>3 && x<=4)? (4-x): ( (x>4)? (x-4): (100000000000000)     )))";
    str2 = "(x-5)^2";
    v1 = 2;
    v2 = 2;

    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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

void MainWindow::setRestrictions(vector<double> min, vector<double> max)
{
    ui->min_x->setValue(min[0]);
    ui->min_y->setValue(min[1]);
    ui->min_z->setValue(min[2]);
    ui->min_g->setValue(min[3]);
    ui->min_h->setValue(min[4]);

    ui->max_x->setValue(max[0]);
    ui->max_y->setValue(max[1]);
    ui->max_z->setValue(max[2]);
    ui->max_g->setValue(max[3]);
    ui->max_h->setValue(max[4]);
}

void MainWindow::Init()
{
    timer->stop();
    init = 1;
    if(nsga2 != NULL) delete nsga2;
    ui->statusBar->showMessage(" Inicjalizacja populacji ", 1000);

    str1 = ui->function1->text().toStdString();
    str2 = ui->function2->text().toStdString();
    v1 = ui->varebl_spin_f1->value();
    v2 = ui->varebl_spin_f2->value();

    getRestrictions();
    nsga2 =  new  Nsga2(ui->spinBox->value(),ui->offspring->value(),ui->crossover->value(),ui->mutation->value(),ui->crossover_index->value(),ui->mutation_index->value(),str1,v1,str2,v2,min,max);
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
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(Init()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe1()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe2()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe3()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe4()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe5()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe6()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe7()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe8()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe9()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe10()));


    }
    else if( s == "Parser")
    {
        ui->Grup_Parser->show();
        ui->ograniczenia->show();
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(Init()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe1()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe2()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe3()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe4()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe5()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe6()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe7()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe8()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe9()));
        disconnect(ui->Init,SIGNAL(clicked()),this,SLOT(exe10()));



        vector<double> Min,Max;
        Min.push_back(-1);
        Min.push_back(-1);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(6);
        Max.push_back(6);
        Max.push_back(0);
        Max.push_back(0);
        Max.push_back(0);

        ui->varebl_spin_f1->setValue(2);
        ui->varebl_spin_f2->setValue(2);

        setRestrictions(Min,Max);
        return;
    }

    if( s == "Schaffer function N. 2")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe1()));
        vector<double> Min,Max;
        Min.push_back(-5);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(10);
        Max.push_back(0);
        Max.push_back(0);
        Max.push_back(0);
        Max.push_back(0);

        ui->varebl_spin_f1->setValue(1);
        ui->varebl_spin_f2->setValue(1);

        setRestrictions(Min,Max);
    }

    if( s == "Schaffer function N. 1")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe2()));
        vector<double> Min,Max;
        Min.push_back(-10);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(10);
        Max.push_back(0);
        Max.push_back(0);
        Max.push_back(0);
        Max.push_back(0);

        ui->varebl_spin_f1->setValue(1);
        ui->varebl_spin_f2->setValue(1);

        setRestrictions(Min,Max);
    }

    if(s == "Poloni's two objective function")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe3()));
        vector<double> Min,Max;
        Min.push_back(-3.1415);
        Min.push_back(-3.1415);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(3.1415);
        Max.push_back(3.1415);
        Max.push_back(5);
        Max.push_back(0);
        Max.push_back(0);

        ui->varebl_spin_f1->setValue(2);
        ui->varebl_spin_f2->setValue(2);

        setRestrictions(Min,Max);
    }

    if(s == "Kursawe function")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe4()));

        vector<double> Min,Max;
        Min.push_back(-5);
        Min.push_back(-5);
        Min.push_back(-5);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(5);
        Max.push_back(5);
        Max.push_back(5);
        Max.push_back(0);
        Max.push_back(0);

        ui->varebl_spin_f1->setValue(3);
        ui->varebl_spin_f2->setValue(3);

        setRestrictions(Min,Max);
    }

    if(s == "Fonseca and Fleming function")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe5()));

        vector<double> Min,Max;
        Min.push_back(-4);
        Min.push_back(-4);
        Min.push_back(-4);
        Min.push_back(-4);
        Min.push_back(-4);

        Max.push_back(4);
        Max.push_back(4);
        Max.push_back(4);
        Max.push_back(4);
        Max.push_back(4);

        ui->varebl_spin_f1->setValue(5);
        ui->varebl_spin_f2->setValue(5);

        setRestrictions(Min,Max);
    }

    if(s == "Zitzler–Deb–Thiele's function N. 1")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe6()));

        vector<double> Min,Max;
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);

        ui->varebl_spin_f1->setValue(5);
        ui->varebl_spin_f2->setValue(5);

        setRestrictions(Min,Max);
    }




    if(s == "Zitzler–Deb–Thiele's function N. 2")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe7()));

        vector<double> Min,Max;
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);

        ui->varebl_spin_f1->setValue(5);
        ui->varebl_spin_f2->setValue(5);

        setRestrictions(Min,Max);
    }

    if(s == "Zitzler–Deb–Thiele's function N. 3")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe8()));

        vector<double> Min,Max;
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);

        ui->varebl_spin_f1->setValue(5);
        ui->varebl_spin_f2->setValue(5);

        setRestrictions(Min,Max);
    }

    if(s == "Zitzler–Deb–Thiele's function N. 4")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe9()));

        vector<double> Min,Max;
        Min.push_back(0);
        Min.push_back(-5);
        Min.push_back(-5);
        Min.push_back(-5);
        Min.push_back(-5);

        Max.push_back(1);
        Max.push_back(5);
        Max.push_back(5);
        Max.push_back(5);
        Max.push_back(5);

        ui->varebl_spin_f1->setValue(5);
        ui->varebl_spin_f2->setValue(5);

        setRestrictions(Min,Max);
    }

    if(s == "Zitzler–Deb–Thiele's function N. 6")
    {
        connect(ui->Init,SIGNAL(clicked()),this,SLOT(exe10()));

        vector<double> Min,Max;
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);
        Min.push_back(0);

        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);
        Max.push_back(1);

        ui->varebl_spin_f1->setValue(5);
        ui->varebl_spin_f2->setValue(5);

        setRestrictions(Min,Max);
    }



}

void MainWindow::getRestrictions()
{
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


