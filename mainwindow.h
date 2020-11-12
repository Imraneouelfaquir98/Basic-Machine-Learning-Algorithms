#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "disk.h"
#include "perceptron.h"
#include "pocketla.h"
#include "adaline.h"
#include "backpropagation.h"
#include "point.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    vector<Point>  S;
    vector<double> W;

    double min = 999999, max =-999999;
    bool problemResolved = false;
    QCPItemLine     *separator;
    Perceptron      *perceptron      = new Perceptron();
    Adaline         *adaline         = new Adaline   ();
    PocketLA        *pocketla        = new PocketLA  ();
    BackPropagation *backpropagation = new BackPropagation();

    void addPoint(double x, double y);
    void clearData();
    void plot();
    void updatMinMax(double x, double y);
    void addSample(double x1, double x2, int y);
    void drowSeparator();
    void paintLine();

    void registerData();

private slots:
    void on_clearData_clicked();
    void clickedGraph(QMouseEvent * event);
    void on_perceptronButton_clicked();
    void on_AdalineButton_clicked();

    void on_PocketLAButton_clicked();

    void on_BackPropAButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> qvBlue_x, qvBlue_y;
    QVector<double> qvRed_x , qvRed_y ;
};

#endif // MAINWINDOW_H
