
#include "plotgraph.h"
#include "mainwindow.h"
#include "qcustomplot.h"
//#include"QFileDialog"
#include <QFileDialog>
#include"QMessageBox"
#include"QMainWindow"
#include <vector>
using namespace std;

plotgraph::plotgraph()
{
   //create object
}

plotgraph::~plotgraph()
{
    //delete object                 //WHERE AND WHEN IS DESTRUCTOR USED? NOT IN MAIN SO...?
}

void plotgraph::convertData()
{
    QV_y.resize(V_y.size());
    for(int i=0;i<QV_y.size();++i)
    {
        QV_y[i] = V_y.at(i);
    }
}

void plotgraph::clearData()
{
    QV_x.clear();
    QV_y.clear();
}

void plotgraph::plotData(QCustomPlot *Parentplot, int p)   //int p is used to indicate the number of the dataset plotted on the graph (in case of multiple datasets)
{
    // make x-vector with size of y-vector, as step
     QV_x.resize(QV_y.size());
     for(int i=0;i<QV_y.size();++i)
     {
         QV_x[i] = i;
     }
    Parentplot->graph(p)->setData(QV_x,QV_y);
    Parentplot->rescaleAxes();
    Parentplot->replot();
}

vector<float> plotgraph::dummyData1()
{
    V_y.resize(51);

   for (int i=0;i<51;++i)
   {
       V_y.at(i)=i*i;
   }
   return V_y;
}

vector<float> plotgraph::dummyData2()
{
    V_y.resize(51);

   for (int i=0;i<51;++i)
   {
       V_y.at(i)=i*i+100*i;
   }
   return V_y;
}

vector<float> plotgraph::dummyData3()
{
    V_y.resize(51);

   for (int i=0;i<51;++i)
   {
       V_y.at(i)=i*i-100*i;
   }
   return V_y;
}

//*-----------------------------------------testing if the functions of mainwindow have acces to the private variabels of plotting object of class plotgraph is this object is private of mainwindow class: answer is yes
void plotgraph::setQV_y(vector<float> inputvec)
{
    QV_y.resize(inputvec.size());
    for(int i=0;i<QV_y.size();++i)
    {                                       //set QV_y (and convert)
        QV_y[i] = inputvec.at(i);
    }
}

QVector<double> plotgraph::getQV_y()
{
    return QV_y;
}


