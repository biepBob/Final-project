
#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H

#include "qcustomplot.h"
//#include "mainwindow.h" NIET INCLUDEN!
#include <vector>

using namespace std;

class plotgraph         //class with functions to plot data       //THE CLASS/LIBRARY 'QCustomPlot is actually already a class that is used to plot and edit graphs etc. Our class 'plotgraph' uses objects of this class combined with selfdefined functions
{
public:
    plotgraph();        //constructor
    ~plotgraph();       //destructor

    void convertData();                      //function that converts private membert "V_y" (wich is a vector of floats) to a QVector of doubles         /INEENS MET QVECTOR WERKEN ZOU BETER ZIJN N
    void clearData();                                   //clears the Qvectors QV_x and QV_y that get plotted
    void plotData(QCustomPlot *Parentplot, int);        //((plots on a graph Parentplot and dataset 'int'))  function to plot. It needs an object ('Parentplot') of class QCustumPlot as argument, it also makes the Qv_x vector for x-axis
    vector<float> dummyData1();                         //function returns the private 'V_y' vector of floats with quadratic values ([0 1 4 9 16 ...])
    vector<float> dummyData2();                         //"                                                      " values i*i+100*i; ([0 100 204 309 416 ...])
    vector<float> dummyData3();                         //"                                                      " values i*i-100*i; ([0 -100 -196 -281 ...])
    void setQV_y(vector<float>);                  //set functie voor de te de plotten vector, zet Qvector en niet gewone V_y, zodat resize niet meer nodig is!!
    QVector<double> getQV_y();

private:
    //plotgraph-class
    vector<float> V_y;          //dummydata input
    QVector<double> QV_x,QV_y;  //Qvectors that are plotted: x-values and y-values
    //int Testvalue;
};

#endif // PLOTGRAPH_H


