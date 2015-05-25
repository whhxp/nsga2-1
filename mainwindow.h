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
protected slots:
    void makePlot(vector<double> y1, vector<double> y2, vector<double> y1f0, vector<double> y2f0);
private:
    Ui::MainWindow *ui;
    Nsga2 *nsga2;
    QTimer *timer;
};

#endif // MAINWINDOW_H
