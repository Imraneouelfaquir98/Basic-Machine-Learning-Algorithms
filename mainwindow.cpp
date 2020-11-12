#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "operators.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setInteraction(QCP::iRangeDrag,true);
    ui->widget->setInteraction(QCP::iRangeZoom,true);
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->xAxis->setRange(-1, 1);
    ui->widget->yAxis->setRange(-1, 1);
    ui->widget->graph(0)->setScatterStyle(Disk(QColor("red" )));
    ui->widget->graph(1)->setScatterStyle(Disk(QColor("blue")));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsNone);
    connect(ui->widget,SIGNAL(mouseDoubleClick(QMouseEvent*)),SLOT(clickedGraph(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addPoint(double x, double y)
{
    if(ui->Red->isChecked()){
        qvRed_x.append(x);
        qvRed_y.append(y);
        addSample(x, y, 1);
        updatMinMax(x,y);
    }
    else if(ui->Blue->isChecked()){
        qvBlue_x.append(x);
        qvBlue_y.append(y);
        addSample(x, y,-1);
        updatMinMax(x,y);
    }
    else if(ui->Default->isChecked() && problemResolved){
        vector<double> X(3,1); X[0] = x, X[1] = y;
        double val = this->W*X;
        if(val > 0){
            qvRed_x.append(x);
            qvRed_y.append(y);
            addSample(x, y, 1);
        }
        else{
            qvBlue_x.append(x);
            qvBlue_y.append(y);
            addSample(x, y,-1);
        }
        updatMinMax(x,y);
    }
}

void MainWindow::clearData()
{
    qvRed_x.clear();
    qvRed_y.clear();
    qvBlue_x.clear();
    qvBlue_y.clear();
    this->S.clear();
    this->W.clear();
    ui->widget->removeItem(separator);
    problemResolved = false;
}

void MainWindow::plot()
{
    ui->widget->graph(0)->setData(qvRed_x,qvRed_y);
    ui->widget->graph(1)->setData(qvBlue_x,qvBlue_y);
    ui->widget->replot();
    ui->widget->update();
}

void MainWindow::updatMinMax(double x, double y)
{
    min = (min>x)? x : min;
    min = (min>y)? y : min;
    max = (max<x)? x : max;
    max = (max<y)? y : max;
    max +=(max>0)?max/6:-max/6; min +=(min<0)?min/6:-min/6;
}

void MainWindow::addSample(double x1, double x2, int y)
{
    this->S.resize(this->S.size()+1);
    this->S[this->S.size()-1].X.resize(3);
    this->S[this->S.size()-1].X[0] = x1;
    this->S[this->S.size()-1].X[1] = x2;
    this->S[this->S.size()-1].X[2] =  1;
    this->S[this->S.size()-1].y    =  y;
}

void MainWindow::drowSeparator()
{
    if(this->W[0] == 0 && this->W[1] == 0){
        printf("No separator\n");
    }
    else if(this->W[0] != 0){
        problemResolved = true;
        paintLine();
    }
    else if(this->W[0] == 0 && this->W[1] != 0){
        problemResolved = true;
        paintLine();
    }
}

void MainWindow::paintLine()
{
    if(this->W[0] != 0 || this->W[1] != 0){
        separator = new QCPItemLine(ui->widget);
        QPen pen(QColor(204,0,204,255));
        pen.setWidth(5);
        separator->setPen(pen);
        if(this->W[0] != 0){
            separator->start->setCoords(-(this->W[1]*min+this->W[2])/this->W[0], min);
            separator->end->setCoords  (-(this->W[1]*max+this->W[2])/this->W[0], max);
        }
        else if(this->W[0] == 0 && this->W[1] != 0){
            separator->start->setCoords( 0, max);
            separator->end->setCoords  ( 0, min);
        }
        ui->widget->addItem(separator);
        plot();
    }
}

void MainWindow::registerData()
{
    FILE* fichier = NULL;
    fichier = fopen("Data.txt", "w");

    if (fichier != NULL)
    {
        fprintf(fichier,"Data of Adaline Algorithm with 300 iteration\n\n\n");
        for(int i=0; i<S.size(); i++){
            fprintf(fichier, "  X%d =[%4.2f, %4.2f, %4.2f],  y%d = %d\n\n",i,S[i].X[0],S[i].X[1],S[i].X[2],i,S[i].y);
        }
        fprintf(fichier,"\n\n\n  W* = [%4.2f, %4.2f, %4.2f]",W[0],W[1],W[2]);
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier Data.txt");
    }
}

void MainWindow::on_clearData_clicked()
{
    clearData();
    plot();
    min = 999999; max =-999999;
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    if(ui->Red->isChecked() || ui->Blue->isChecked() || ui->Default->isChecked()){
        QPoint point = event->pos();
        addPoint(ui->widget->xAxis->pixelToCoord(point.x()),ui->widget->yAxis->pixelToCoord(point.y()));
        plot();
    }
}

void MainWindow::on_perceptronButton_clicked()
{
    vector<double> W0(3,1);
    this->W.clear();
    this->W = perceptron->training(W0,this->S);
    ui->widget->removeItem(separator);
    ui->widget->replot();
    ui->widget->update();

    drowSeparator();
}

void MainWindow::on_AdalineButton_clicked()
{
    vector<double> W0(3,0);
    this->W.clear();
    this->W = adaline->training(W0,S);
    ui->widget->removeItem(separator);
    ui->widget->replot();
    ui->widget->update();

    drowSeparator();
    registerData();
}

void MainWindow::on_PocketLAButton_clicked()
{
    vector<double> W0(3,0);
    this->W.clear();
    this->W = pocketla->training(W0,this->S);
    ui->widget->removeItem(separator);
    ui->widget->replot();
    ui->widget->update();

    drowSeparator();
}

void MainWindow::on_BackPropAButton_clicked()
{
    vector<double> W0(3,0);
    this->W.clear();
    this->W = backpropagation->training(W0,this->S);
    ui->widget->removeItem(separator);
    ui->widget->replot();
    ui->widget->update();

    drowSeparator();
}
