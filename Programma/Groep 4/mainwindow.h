#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>                      //This class is included, becuase the class 'Mainwindow' is created in this script that inherits from this class
#include "QFileDialog"
#include "QLabel"
#include <vector>
using namespace std;
#include "qcustomplot.h"
#include "plotgraph.h"
#include "propagateinterface.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>


namespace Ui {
class MainWindow;                      //declare the class 'MainWindow' in the Ui namespace, which is the standard namespace for the UI classes generated from .ui files by the uic tool
}

class MainWindow : public QMainWindow                   //MainWindow inherits from QMainWindow class
{
    Q_OBJECT                                            //macro, this way the class 'MainWindow' is declared as an QObject  Any QObject subclass that declares signals and slots must contain the Q_OBJECT macro in its definition.

public:
    explicit MainWindow(QWidget *parent = 0);           //constructor, default argument called 'parent' is set to 0 because the widget has no parent (top-level widget)
    ~MainWindow();                                      //destructor (for the class 'MainWindow()')
    void saveAs(QCustomPlot *Parentplot);               //save the graph
    void calc_Acc();
    void calc_Pres();
    void calc_Sens();
    void calc_Spec();
    void makePropagate();
    void makePlot(QCustomPlot *Parentplot, const QString &text);
    void makeHist(int afb);
private slots:                                          //A slot is a function that is used to accept and respond to a signal.
    void on_Load_Button_clicked();                      //slot to load image (.jpeg or .png) that will get resized and...

    void on_Grijs_Waarden_clicked();                    //slot to make grayscale version

    void on_Zwart_Wit_clicked();                        //slot to make B&W version

    void on_Crop_Button_clicked();                      //slot to make a 28x28 image version (SO NO CROPPING BUT RESIZING!!)

    void on_Threshold_actionTriggered(int action);      //slot to change Threshold for grayscale values

    void on_Bt_clear1_clicked();                        //slot to clear graph in plot window

    void on_Bt_save1_clicked();                         //slot to save the plotted graph in theplot window

    void on_Bt_save1_2_clicked();

    void on_check_dat_Acc_toggled(bool checked);           //slot that tells if checkbox1 is toggled

    void on_check_dat_Pres_toggled(bool checked);           //"                " checkbox2 is toggled

    void on_check_dat_Sens_toggled(bool checked);           //"                " checkbox3 is toggled

    void on_check_dat_Spec_toggled(bool checked);

    void on_check_UseRoot_toggled(bool checked);

    void on_Confirm_layer_clicked();

    void on_Confirm_neuron_clicked();

    void on_Grootte_Mini_Batches_valueChanged(int arg1);

    void on_Bt_save_Acc_clicked();

    void on_Bt_save_Sens_clicked();

    void on_Bt_save_Spec_clicked();

    void on_Bt_save_Pres_clicked();

    void on_Locatie_Trainingimage_clicked();

    void on_Locatie_Traininglabel_clicked();

    void on_Locatie_Testimage_clicked();

    void on_Locatie_Testlabel_clicked();

    void on_Laad_Gewichten_en_Bias_clicked();

    void on_Identificeer_clicked();

    void on_Start_Training_clicked();

    void on_NewNetwork_clicked(bool checked);

    void on_LoadNetwork_clicked(bool checked);

    void on_ValueEta_valueChanged(double arg1);

    void on_ValueTreshhold_valueChanged(double arg1);

    void on_Aantal_Epochs_valueChanged(int arg1);

    void on_MakePropagate_clicked();

    void on_Random_Waarden_2_clicked();



    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_pushButtonevalhist_clicked();

    void on_pushButtonplothist_clicked();

private:
    Ui::MainWindow *ui;                                 //declare a member variable which is a pointer to the MainWindow UI class    (UI:: is the used namespace like std:: in other cases)
    plotgraph *plotting= new plotgraph;
    propagateinterface *propinterface= new propagateinterface;
    QVector<QSpinBox*> Boxes;               //vector with boxes for the number of neurons per layer
    QHBoxLayout *layout = new QHBoxLayout;
    cv::Mat QimageToMat(QImage);

    QVector<double> Accuracy;
    QVector<double> Precision;
    QVector<double> Sensitivity;
    QVector<double> Specificity;

    QGroupBox *createNewNetworkGroup();


    int MiniBatchSizem=1;
    int NumberOfMiniBatchesm;
    int NumberOfEpochsm;
    int NumberofLayersm=0;                       //default value equal to 0
    vector<int> NumberOfNeuronsPerLayerm;
    bool RooTBoolm=0; //=0                         //default value equal to 0
    bool NetworkLoadm=0;
    string EvaluationImagesm="/home/student/Dropbox/Programmeren/Stylesheet28/mnist/t10k-images.idx3-ubyte";
    string EvaluationNumbersm="/home/student/Dropbox/Programmeren/Stylesheet28/mnist/t10k-labels.idx1-ubyte";
    string TrainingImagesm="/home/student/Dropbox/Programmeren/Stylesheet28/mnist/train-images.idx3-ubyte";
    string TrainingNumbersm="/home/student/Dropbox/Programmeren/Stylesheet28/mnist/train-labels.idx1-ubyte";
    //string TestImagesm;       //is dit niet hetzelfde als EvaluationImagesm
    //string TestNumbersm;
    string LoadBiasAndWeightsm;
    float EvaluationErrorm;
    float TrainingErrorm;
    float TruePositivem;
    float TrueNegativem;
    float FalsePositivem;
    float FalseNegativem;
    float Etam=0.5;
    float Thresholdm=0.7;
    vector<vector<vector<float>>> HistogramDatam;
    int HistogramNeuronm=0;
    vector<vector<int>> histcolorvector;
};

#endif // MAINWINDOW_H
