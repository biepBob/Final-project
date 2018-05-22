#ifndef PROPAGATEINTERFACE_H
#define PROPAGATEINTERFACE_H
#include <vector>
#include <string>
#include "propagate.h"
#include "propagateRoot.h"


using namespace std;

class propagateinterface
{
public:
    propagateinterface();        //constructor for the class
    ~propagateinterface();       //destructor
    void makePropagate();
    void propagateNEpochs(int); //{gebruik dezelfde functie in propagate en propagateRooT}
    vector<float> evaluateSingleImage (vector<float>);     //function with input: grayscalevalues of 28x28image in vector of floats, and output:a vector of size 10 with chances of being number 0,1,2,...9
    
    void useLoadNetwork(bool);
    void useRooT(bool);   //                          //moet verbonden worden met een aan en uit toggle en de private variabel 'UseRoot' gelijk stellen aan 1 of 0
    void setNumberOfLayers(int);
    void setNumberOfNeuronsPerLayer(vector<int>);   //vector van intigers zodat het x-te element het aantal neuronen van de x-te laag meegeeft.
                                                    //Laatste laag wordt niet meegeteld, dus als er n lagen zijn is de vector n-1 lang.
                                                    //private variabelen NumberofLayers wordt hiermee berekend en de private vector van intigers NumberOfNeuronsPerLayer eraan gelijk worden gesteld
    void setMiniBatchSize(int);
//    void setNumberOfLayers(int);
    void setEta(float); //construeren

    void setIterations(int);
    void setEvaluationError(float);
    void setTrainingError(float);		     //setfuncties
    void setTruePositive(float);
    void setTrueNegative(float);
    void setFalsePositive(float);
    void setFalseNegative(float);
    void setThreshold(float);

    void setEvaluationImages(string);
    void setEvaluationNumbers(string);
    void setTrainingImages(string);
    void setTrainingNumbers(string);
    void setLoadNetworkPath(string);

    int getMiniBatchSize();             	     //getfuncties
    int getNumberOfLayers();                     //
    void loadNetwork(string);
    void saveNetwork(string);
    vector<int> getNumberOfNeuronsPerLayer();    //

    vector<int> getIterations();
    vector<float> getEvaluationError();                  //
    vector<float> getTrainingError();                    //
    vector<vector<vector<float>>> getRawHistogram();
    
    vector<float> getTruePositive();                     //
    vector<float> getTrueNegative();                     //getfuncties
    vector<float> getFalsePositive();                    //
    vector<float> getFalseNegative();                    //
    vector<float> getAccuracy();                     //
    vector<float> getSensitivity();                     //getfuncties
    vector<float> getSpecificity();                    //
    vector<float> getPrecision();                    //
    float getThreshold();
    string getEvaluationImages();                //
    string getEvaluationNumbers();               //
    string getTrainingImages();                  //
    string getTrainingNumbers();                 //

protected:
    int MiniBatchSize;
    int NumberOfLayers=0;                       //default value equal to 0
    float Eta = 0;
    vector<int> NumberOfNeuronsPerLayer;
    bool RootBool = false;
    string EvaluationImages;
    string EvaluationNumbers;
    string TrainingImages;
    string TrainingNumbers;
    string LoadNetworkPath;
    
    vector<int> Iterations;
    vector<float> EvaluationError;
    vector<float> TrainingError;

    vector<float> TruePositive;
    vector<float> TrueNegative;
    vector<float> FalsePositive;
    vector<float> FalseNegative;

private:
    propagate* Prop;
    propagateRoot* RootProp;
   
    bool NetworkLoad = false;
    bool make = false;
    int nInputs = 784;
    float Threshold;
//copyconstructor
    void destroyCurrentNetwork();
};


#endif // PROPAGATEINTERFACE_H
