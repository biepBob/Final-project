#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QFileDialog"
#include"QMessageBox"
#include"QMainWindow"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<vector>
#include<QGroupBox>
#include "plotgraph.h"
#include "propagateinterface.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    makePlot(ui->plot1, "The Evaluation Error");

    makePlot(ui->plot1_2, "The Training Error");

    makePlot(ui->plot2_Acc, "The Accuracy");

    makePlot(ui->plot2_Pres,"The Precision");

    makePlot(ui->plot2_Sens, "The Sensitivity");

    makePlot(ui->plot2_Spec, "The Specificity");

    //setup histogram environment in widget
    ui-> widget_hist->addGraph();
    //set title
    ui-> widget_hist->plotLayout()->insertRow(0);
    ui-> widget_hist->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget_hist, "Neuron Output Distribution"));
    //set axis
    ui-> widget_hist->xAxis->setLabel("Neuron output");
    ui->widget_hist->xAxis->setRange(0,1);
    ui-> widget_hist->yAxis->setLabel("Number of entries");
    //set legend
    ui-> widget_hist->legend->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete plotting;        //doet de constructor in plotgraph.cpp dit werk al niet?
    delete propinterface;   //"                     "propagateinterface.cpp "    " ?
}

void MainWindow::saveAs(QCustomPlot *Parentplot)    //from our class plotgraph, we define the memberfunction saveGraph. The function needs as variabel an object from clas QCostumPlot
{
    QString Filename = QFileDialog::getSaveFileName(this, "Save");  //VOLGENS MIJ ZIT DE FOUT IN 'THIS' OF OMDAT het verwijst naar QCostumPlot& (zie error). OOK NUTTIG IS MSSCHN OM HET TE SCHRIJVEN ZONDER INPUT, EN TE ZIEN OF HET 'plotting' KENT ALS PRIVATE OFZO
    QFile File(Filename);                               //Constructs a new file object to represent the file with the given fileName

    if(!File.open(QIODevice::WriteOnly))
    {
        qDebug()<<File.errorString();
    }
    else
    {
        Parentplot->savePng(Filename);
    }
}

void MainWindow::makePlot(QCustomPlot *Parentplot, const QString &text)     //function that designs a plot-environment
{
    //setup graph environment in widget "*Parentplot"
    Parentplot->addGraph();
    // scatter and line-style
    Parentplot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    Parentplot->graph(0)->setLineStyle(QCPGraph::lsLine);
    //set title
    Parentplot->plotLayout()->insertRow(0);
    Parentplot->plotLayout()->addElement(0, 0, new QCPPlotTitle(Parentplot, text));
    //set axis
    Parentplot->xAxis->setLabel("Epoch");
    //ui->plot1->yAxis->setLabel("Left axis label1");
    //set legend
    Parentplot->legend->setVisible(false);
}

void MainWindow::makeHist(int afb)
{
    vector<float> dumdum=HistogramDatam.at(HistogramNeuronm).at(afb);
    /*make dummy vector----------------------------------------------
    dumdum.resize(5000);
    for(int i=0; i<dumdum.size(); i++)
    {
        dumdum.at(i)=((double) rand() / (RAND_MAX)); //random values between 0 and 1
    }
    //---------------------------------------------------------------*/


   float BinNumber=ceil(sqrt(dumdum.size()));   //sqrt-rule for number of bins,  cout rond af naar boven
   //values of input vector between 0 end 1
   float BinWidth=1/BinNumber;
   vector<float> BinsFill;      //y- value
   vector<float> BinsPos;       //x-position
   BinsFill.resize(BinNumber);
   BinsPos.resize(BinNumber);

   for(int i=0; i<BinsPos.size();i++)
   {
       BinsPos.at(i)= (BinWidth/2)*(1+2*i); //eerste bin, halverwege Binwidth, tweede op twee derde enz...
   }

   for(int j=0; j<dumdum.size();j++)
   {
       float Value=dumdum.at(j);
       for(int i=0; i<BinsFill.size();i++)
       {
           float max=BinsPos.at(i)+0.5*BinWidth;
           float min=BinsPos.at(i)-0.5*BinWidth;
           if(Value>=min && Value<=max) //check if value belongs to bin
           {
               BinsFill.at(i)++;
           }
       }
   }

   QVector<double> QBinsFill, QBinsPos;
   QBinsFill.resize(BinsFill.size());
   QBinsPos.resize(BinsPos.size());

   for(int i=0; i<QBinsFill.size(); i++)
   {
       QBinsFill[i] = BinsFill.at(i);
       QBinsPos[i]=BinsPos.at(i);
   }

   QCPBars *bars1 = new QCPBars(ui->widget_hist->xAxis, ui->widget_hist->yAxis);




   //----
   //int c=ceil((HistogramNeuronm+100/10)*2.55);
   //QColor color=qRgb(c,c,c);
   //QPen pen;
   QBrush brush;
   //pen.setColor(color);
   //bars1->setBrush(QColor(ceil((((double) rand() / (RAND_MAX))*255)),ceil((((double) rand() / (RAND_MAX))*255)),ceil((((double) rand() / (RAND_MAX))*255))));


   //bars1->setBrush(QColor(ceil(((afb*14+100)/10)*9.55),  ceil(((afb*4+100)/10)*9.55),  ceil(((afb+100)/10)*9.55)));
   bars1->setBrush(QColor(histcolorvector.at(afb).at(0),histcolorvector.at(afb).at(1),histcolorvector.at(afb).at(2)));


   //bars1->addToLegend();
   //bars1->setPen(pen);
//-----



   ui->widget_hist->addPlottable(bars1);
   bars1->setWidth(BinWidth);
   bars1->setData(QBinsPos, QBinsFill);
   bars1->rescaleAxes(1);
   ui->widget_hist->replot();
}


cv::Mat MainWindow::QimageToMat(QImage image){
    cv::Mat size = cv::Mat(image.height(),image.width(),CV_8UC4,(uchar*)image.bits(),image.bytesPerLine());
    cv::Mat img = cv::Mat(size.rows,size.cols,CV_8UC3);
    int from_to[]={0,0, 1,1, 2,2 };
    cv::mixChannels(&size,1,&img,1,from_to,3);
    return img;
}

void MainWindow::on_Load_Button_clicked()
{


    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"");  //getOpenFileName is a static function from QFileDialog class (that inherits from QDialog) that returns an existing file selected by the user. If the user presses Cancel, it returns a null string
    if(QString::compare(filename,QString()) !=0)             //compare function from QString library compares 'filename' to QString() wich is the constructor that returns a null string. So this checks if 'filename' is null. This is the case when 'cancel'   is clicked (see line above)                 //WHERE IS THE CONSTRUCTOR OF THE CLASS 'QFileDialog' called?
    {
        cv::Mat image;
        image=cv::imread(filename.toStdString()); //krijgt pad mee van file om te lezen

        cv::cvtColor(image, image, CV_BGR2RGB);


        ui->ImageUp->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888)).scaled(ui->ImageUp->width(),ui->ImageUp->height()));
        ui->ImageDown->update();

    }
}

void MainWindow::on_Grijs_Waarden_clicked()
{

    if(ui->ImageUp->pixmap()!=0){
    ui->ImageDown->QLabel::clear();
    const QPixmap* pixmap = ui->ImageUp->pixmap();
    QImage image(pixmap->toImage());

    cv::Mat img=QimageToMat(image);

    cv::cvtColor(img,img, CV_BGR2GRAY );

    ui->ImageDown->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Indexed8)).scaled(ui->ImageDown->width(),ui->ImageDown->height()));
}

}

void MainWindow::on_Zwart_Wit_clicked()
{
    if(ui->ImageUp->pixmap()!=0){
    ui->ImageDown->QLabel::clear();
    const QPixmap* pixmap = ui->ImageUp->pixmap();
    QImage image(pixmap->toImage());


    cv::Mat img=QimageToMat(image);


    cv::cvtColor(img,img,CV_BGR2GRAY);
    //int thresh=200;
    int thresh=ui->Threshold->value();
    cv::threshold(img,img,thresh,255,0);


    ui->ImageDown->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Indexed8)).scaled(ui->ImageDown->width(),ui->ImageDown->height()));
}
}

void MainWindow::on_Crop_Button_clicked()
{   if(ui->ImageUp->pixmap()!=0){
    ui->ImageDown->QLabel::clear();
        const QPixmap* pixmap = ui->ImageUp->pixmap();
        QImage image(pixmap->toImage());


        cv::Mat img=QimageToMat(image);



        cv::cvtColor(img,img,CV_BGR2RGB);

        cv::Size size2(28,28);
        cv::Mat resize2;
        cv::resize(img,resize2,size2);
        ui->ImageUp->setPixmap(QPixmap::fromImage(QImage(resize2.data, resize2.cols, resize2.rows, resize2.step, QImage::Format_RGB888)).scaled(ui->ImageUp->width(),ui->ImageUp->height()));
    }
}

void MainWindow::on_Threshold_actionTriggered(int action)
{   if(ui->ImageUp->pixmap()!=0){
    ui->ImageDown->QLabel::clear();
       const QPixmap* pixmap = ui->ImageUp->pixmap();
       QImage image(pixmap->toImage());


       cv::Mat img=QimageToMat(image);


       cv::cvtColor(img,img,CV_BGR2GRAY);
       //int thresh=200;
       int thresh=ui->Threshold->value();
       cv::threshold(img,img,thresh,255,0);
       ui->Threshold_Display->display(thresh);
       ui->ImageDown->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Indexed8)).scaled(ui->ImageDown->width(),ui->ImageDown->height()));
       ui->Zwart_Wit->click();
    }
}

//plotting buttons-----------------------------------------------------------------------------------




void MainWindow::on_Bt_clear1_clicked()
{
    plotting->clearData();
    plotting->plotData(ui->plot1,0);
    plotting->clearData();
    plotting->plotData(ui->plot1_2,0);
}

void MainWindow::on_Bt_save1_clicked()
{
    saveAs(ui->plot1);           //Use the memberfunctionsGraph from the class plotgraph on the object plotting of that class, and use as input 'plot1' of the object ui of class mainwindow
}

void MainWindow::on_Bt_save1_2_clicked()
{
   saveAs(ui->plot1_2);
}

void MainWindow::on_check_dat_Acc_toggled(bool checked)
{
    if(checked)
    {
         plotting->setQV_y(propinterface->getAccuracy());
         std::cout<<"Acc toggled"<<endl;
         //plotting->convertData();
         plotting->plotData(ui->plot2_Acc,0);
    }
    else
    {
        plotting->clearData();
        plotting->plotData(ui->plot2_Acc,0);
    }
}

void MainWindow::on_check_dat_Spec_toggled(bool checked)
{
    if(checked)
    {
         plotting->setQV_y(propinterface->getSpecificity());
         std::cout<<"Spec toggled"<<endl;
         //plotting->convertData();
         plotting->plotData(ui->plot2_Spec,0);
    }
    else
    {
        plotting->clearData();
        plotting->plotData(ui->plot2_Spec,0);
    }
}

void MainWindow::on_check_dat_Pres_toggled(bool checked)
{
    if(checked)
    {
        plotting->setQV_y(propinterface->getPrecision());
        std::cout<<"Prec toggled"<<endl;
        //plotting->convertData();
        plotting->plotData(ui->plot2_Pres,0);
    }
    else
    {
        plotting->clearData();
        plotting->plotData(ui->plot2_Pres,0);
    }
}

void MainWindow::on_check_dat_Sens_toggled(bool checked)
{
    if(checked)
    {
        plotting->setQV_y(propinterface->getSensitivity());
        std::cout<<"Sens toggled"<<endl;
        //plotting->convertData();
        plotting->plotData(ui->plot2_Sens,0);
    }
    else
    {
       plotting->clearData();
       plotting->plotData(ui->plot2_Sens,0);
       ///plotting->settestvalue(14);
       ///plotting->gettestvalue();
    }
}

void MainWindow::on_check_UseRoot_toggled(bool checked)
{
     RooTBoolm=checked;
     cout<<"RooTBoolm is "<<RooTBoolm<<endl;
}

void MainWindow::on_Grootte_Mini_Batches_valueChanged(int arg1)
{
    MiniBatchSizem=arg1;
}

void MainWindow::on_Aantal_Epochs_valueChanged(int arg1)
{
    NumberOfEpochsm=arg1;
}



void MainWindow::on_Confirm_layer_clicked()
{
    int Layers=ui->Aantal_Lagen->value();      //number of layers                   ///Layers en numberoflayers is eigenlijk numberofhiddenlayers (dus uitgezonderd laatste outputlayer en inputlayer)
    int AddedLayers=Layers-(NumberofLayersm);
            //Boxes is a protected QVector of QSpinBoxes of the mainwindow class

    if (NumberofLayersm==0)
    {
        Boxes.resize(Layers);
        for(int i=0;i<Layers;i++)               //if the amount of layers is set to n, the amount of boxes that have to appear is n-1, because the last layer always has 10 neurons, the chances of the character being 0, 1, 2, ..., 9
        {
            QSpinBox *box = new QSpinBox();
            box->setRange(0,999);
            Boxes[i]=box;                           //put box in vector of boxes
            layout->addWidget(Boxes[i]);            //add box to horizontal layout
        }
    }
    else if (AddedLayers>0)
    {
        for(int i=NumberofLayersm;i<Layers;i++)
        {
            QSpinBox *box = new QSpinBox();
            box->setRange(0,999);
            Boxes.push_back(box);
            layout->addWidget(Boxes[i]);
        }
    }

    else (AddedLayers<0);
    {
        for (int i=1;i<-AddedLayers+1;i++)    //Bij het verlagen met 2 verlaagt het slechts een
        {
            layout->removeWidget(Boxes[NumberofLayersm-i]);
            delete Boxes[NumberofLayersm-i];
            Boxes.pop_back();
        }
    }
    ui->widget->setLayout(layout);
    NumberofLayersm=Layers;
}

void MainWindow::on_Confirm_neuron_clicked()
{
    int Layers=ui->Aantal_Lagen->value();   //number of layers
    vector<int> VecNeurons;                 //vector with number of neurons, pass later to interface
    VecNeurons.resize(Boxes.size());
    for(int i=0;i<Layers;i++)
    {
        VecNeurons.at(i)=Boxes[i]->value();    //fill vector with values of the spinboxes
    }
    VecNeurons.push_back(10);                    ////laatste layer heeft 10 neuronen
    NumberOfNeuronsPerLayerm=VecNeurons;        //pass vector to interface

    for(int i=0;i<NumberOfNeuronsPerLayerm.size();i++)
    {
        cout<<"elements of NumberOfNeuronsPerLayerm"<<NumberOfNeuronsPerLayerm[i]<<endl;
    }

    ui->MakeProgagateWidget->setEnabled(true);
}
















void MainWindow::on_Bt_save_Acc_clicked()
{
   saveAs(ui->plot2_Acc);
}

void MainWindow::on_Bt_save_Sens_clicked()
{
    saveAs(ui->plot2_Sens);
}

void MainWindow::on_Bt_save_Spec_clicked()
{
    saveAs(ui->plot2_Spec);
}

void MainWindow::on_Bt_save_Pres_clicked()
{
    saveAs(ui->plot2_Pres);
}

void MainWindow::on_Locatie_Trainingimage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"");  //getOpenFileName is a static function from QFileDialog class (that inherits from QDialog) that returns an existing file selected by the user. If the user presses Cancel, it returns a null string

    TrainingImagesm=filename.toStdString();
}

void MainWindow::on_Locatie_Traininglabel_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"");  //getOpenFileName is a static function from QFileDialog class (that inherits from QDialog) that returns an existing file selected by the user. If the user presses Cancel, it returns a null string

    TrainingNumbersm=filename.toStdString();
}

void MainWindow::on_Locatie_Testimage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"");  //getOpenFileName is a static function from QFileDialog class (that inherits from QDialog) that returns an existing file selected by the user. If the user presses Cancel, it returns a null string

    EvaluationImagesm=filename.toStdString();
}

void MainWindow::on_Locatie_Testlabel_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"");  //getOpenFileName is a static function from QFileDialog class (that inherits from QDialog) that returns an existing file selected by the user. If the user presses Cancel, it returns a null string

    EvaluationNumbersm=filename.toStdString();
}

void MainWindow::on_Laad_Gewichten_en_Bias_clicked() //returns path not just filename
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("*.csv"));  //getOpenFileName is a static function from QFileDialog class (that inherits from QDialog) that returns an existing file selected by the user. If the user presses Cancel, it returns a null string     ///geeft het pad van het geselecteerdee bestand, dus kan buiten map volledig bestandpad geven
    LoadBiasAndWeightsm=filename.toStdString();
   // std::cout<<filename.toStdString()<<"test"<<endl;
    ui->MakeProgagateWidget->setEnabled(true);
    ui->Label_Network_Loaded->show();

}

void MainWindow::on_Identificeer_clicked()
{   const QPixmap* pixmap = ui->ImageDown->pixmap();
    QImage imagedown(pixmap->toImage().scaled(28,28));

    cv::Mat img=QimageToMat(imagedown);
    vector<float>image(img.rows*img.cols,0);
    for(int i=0; i<img.cols;i++){
        for(int j=0; j<img.rows;j++){
            image.at(j+i*img.rows)=img.at<float>(j,i);
            if( image.at(j+i*img.rows) != image.at(j+i*img.rows) )
                image.at(j+i*img.rows) = 0.0;
        }
    }
    vector<float>vecc = propinterface->evaluateSingleImage(image);
    cout<<img.rows<<endl;
    cout<<img.cols<<endl;
    float max = *max_element(vecc.begin(), vecc.end());

    for (int i=0; i<vecc.size();i++)
    {
        if(vecc[i]==max)
        {
            ui->lcdNumber->display(i);
        }
    }
    for(int i; i<vecc.size();i++)
    {
    cout<<"element "<<i<<" is "<<vecc[i]<<endl;
    }

}

void MainWindow::on_Random_Waarden_2_clicked() //save training
{
        QString Filename = QFileDialog::getSaveFileName(this, "Save");
        QFile File(Filename);         //Constructs a new file object to represent the file with the given fileName
        if(!File.open(QIODevice::WriteOnly))
        {
            qDebug()<<File.errorString();
        }
        else
        {
            propinterface->saveNetwork(Filename.toStdString());
            std::cout<<Filename.toStdString()<<endl;
        }
}


void MainWindow::on_Start_Training_clicked()
{
    cout<<"On start training clicked"<<endl;
    int A=ui->Trainingepochs->value();
    for(int i=0;i<A;i++)
    {
        cout<<"looping"<<endl;
        propinterface->propagateNEpochs(NumberOfEpochsm);

        ///plotting EvaluationError
        // met gebruik te maken van klasse plothgraph---------------
        plotting->setQV_y(propinterface->getEvaluationError());     //stelt private QV_y van klasse plotgraph gelijk aan te plotteninputvector (en omzetting van vector<float> naar QVector<double>
        //plotting->convertData();                                  //Niet nodig nu, want omzetting gebeurde hier boven ook al
        plotting->plotData(ui->plot1,0);
        //----------------------------------------------------------/

        ///Plotting TrainingError
        // met gebruik te maken van klasse plothgraph---------------
        plotting->setQV_y(propinterface->getTrainingError());     //stelt private QV_y van klasse plotgraph gelijk aan te plotteninputvector (en omzetting van vector<float> naar QVector<double>
        //plotting->convertData();                                  //Niet nodig nu, want omzetting gebeurde hier boven ook al
        plotting->plotData(ui->plot1_2,0);
        //----------------------------------------------------------/
    }
}




void MainWindow::on_NewNetwork_clicked(bool checked)
{
    if(checked==true){
        NetworkLoadm=0;
        cout<<"Networkloadm set to "<<NetworkLoadm<<endl;
        ui->NewNetworkWidget->setEnabled(true);
        ui->LoadNetworkWidget->setDisabled(true);
    }
}

void MainWindow::on_LoadNetwork_clicked(bool checked)
{
    if(checked==true){
        NetworkLoadm=1;
        cout<<"Networkloadm set to "<<NetworkLoadm<<endl;
        ui->LoadNetworkWidget->setEnabled(true);
        ui->NewNetworkWidget->setDisabled(true);
        ui->Label_Network_Loaded->hide();
    }
}

void MainWindow::on_ValueEta_valueChanged(double arg1)
{
    Etam=arg1;
}

void MainWindow::on_ValueTreshhold_valueChanged(double arg1)
{
    Thresholdm=arg1;
}

void MainWindow::on_MakePropagate_clicked()
{
    ui->pushButtonevalhist->setEnabled(true);
    makePropagate();
    ui->NewNetworkWidget->setDisabled(true);
    ui->LoadNetworkWidget->setDisabled(true);
    ui->MakeProgagateWidget->setDisabled(true);
}

void MainWindow::makePropagate()
{
    //propinterface->setNumberOfEpochs(); NOG NIET!
    cout<<"On make propagate clicked..."<<endl;
    propinterface->setEta(Etam);
    //propinterface->setNumberOfLayers(NumberofLayersm);
    propinterface->setEvaluationImages(EvaluationImagesm);
    propinterface->setEvaluationNumbers(EvaluationNumbersm);
    propinterface->setTrainingImages(TrainingImagesm);
    propinterface->setTrainingNumbers(TrainingNumbersm);
    propinterface->setMiniBatchSize(MiniBatchSizem);
    propinterface->useRooT(RooTBoolm);
    //propinterface->loadNetwork(LoadBiasAndWeightsm);
    propinterface->setLoadNetworkPath(LoadBiasAndWeightsm);
    propinterface->useLoadNetwork(NetworkLoadm);
    propinterface->setNumberOfNeuronsPerLayer(NumberOfNeuronsPerLayerm);
    propinterface->setThreshold(Thresholdm);
    //propinterface->setTrainingError(TrainingErrorm); moet dit??
    propinterface->makePropagate();
}

//-------------------------------------------------------
void MainWindow::on_comboBox_activated(int index)
{
    HistogramNeuronm=index;
}
//-------------------------------------------------------


void MainWindow::on_pushButton_clicked()
{
    saveAs(ui->widget_hist);
}


void MainWindow::on_pushButtonevalhist_clicked()
{
HistogramDatam=propinterface->getRawHistogram();
ui->comboBox->setEnabled(true);
ui->pushButtonplothist->setEnabled(true);
}



void MainWindow::on_pushButtonplothist_clicked()
{
           histcolorvector.push_back({ 53  ,  42 ,  135});
           histcolorvector.push_back({ 15  ,  92  , 221});
           histcolorvector.push_back({ 18  , 125  , 216});
           histcolorvector.push_back({  7  , 156  , 207});
           histcolorvector.push_back({ 21  , 177  , 180});
           histcolorvector.push_back({ 89  , 189 ,  140});
           histcolorvector.push_back({165  , 190  , 107});
           histcolorvector.push_back({225  , 185 ,   82});
           histcolorvector.push_back({252 ,  206,    46});
           histcolorvector.push_back({249 ,  251  ,  14});


    ui->widget_hist->clearPlottables(); //clear graph
    for(int i=0; i<10;i++)
    {

        ui->widget_hist->replot();
        makeHist(i);
    }
}
