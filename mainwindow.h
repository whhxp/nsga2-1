#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <individual.h>
#include <nsga2.h>

#include <string>
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void Nsga();
    void Init();
    void MinMax(int value);
    void hide(QString s);
    void sortowanieY(QString s);
    void exe1();
    void exe2();

protected slots:
    void makePlot(vector<double> y1, vector<double> y2, vector<double> y1f0, vector<double> y2f0);

private:
    int f;
    Ui::MainWindow *ui;
    Nsga2 *nsga2;
    QTimer *timer;
    int init;

    string str1;
    string str2;
    int v1;
    int v2;
    vector<double> min;
    vector<double> max;


    vector<double> MIN();
    vector<double> MAX();
};

#endif // MAINWINDOW_H
