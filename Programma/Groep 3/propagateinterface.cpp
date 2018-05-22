#include "propagateinterface.h"
#include "propagate.h"
#include "propagateRoot.h"
#include <vector>

using namespace std;

propagateinterface::propagateinterface() //Constructor
{ //Set all the protected memeber defautl to zero
    setMiniBatchSize(0);
    setNumberOfLayers(0);
    setEvaluationImages("");
    setEvaluationNumbers("");
    setTrainingImages("");
    setTrainingNumbers("");
    setEta(0);
}

propagateinterface::~propagateinterface() //Destructor
{
    if(make) destroyCurrentNetwork();//Only when a network is created, the delete's are called
}

void propagateinterface::makePropagate() //Make a propagate object
{   // gebruik bool om slechts 1 network in te laden 
    // gebruik bool om de juiste constructor te gebruiken (in laden of random weights) 
    if (make) destroyCurrentNetwork();
    if (RootBool)
    { // RooT

            RootProp = new propagateRoot(EvaluationImages,EvaluationNumbers,TrainingImages,TrainingNumbers);

    } else {
         if (NetworkLoad)
         {
//              Prop = new propagate(); // constructor met load csv
         } else {
              Prop = new propagate(Eta, MiniBatchSize,NumberOfNeuronsPerLayer,nInputs,EvaluationImages,EvaluationNumbers,TrainingImages,TrainingNumbers); // constructor met random waarden
         }
         Prop->setThreshold(Threshold);
    }
    make = true;
    Iterations.clear();
    EvaluationError.clear();                  //
    TrainingError.clear(); 
}

void propagateinterface::useLoadNetwork(bool b)
{
    NetworkLoad = b;
}

void propagateinterface::destroyCurrentNetwork()
{
    if (RootBool)
    {
        delete RootProp;
    } else {
        delete Prop;
    }
}

void propagateinterface::propagateNEpochs(int NEpochs)
{
    if (RootBool) //Root network
    {
       vector<float> temp = RootProp->propagateNEpochs();
       setIterations(NEpochs);
        setTrainingError(temp.at(0));
        setEvaluationError(temp.at(1));
        setTruePositive(temp.at(2));
        setTrueNegative(temp.at(3));
        setFalsePositive(temp.at(4));
        setFalseNegative(temp.at(5));
       
    } else { //Own network
        vector<vector<float>> temp = Prop->propagateNEpochs(NEpochs);
        setIterations(NEpochs);
        for (int i = 0; i < NEpochs; i++)
        {
            setTrainingError(temp.at(i).at(0));
            setEvaluationError(temp.at(i).at(1));
            setTruePositive(temp.at(i).at(2));
            setTrueNegative(temp.at(i).at(3));
            setFalsePositive(temp.at(i).at(4));
            setFalseNegative(temp.at(i).at(5));
        }
    }
}

vector<vector<vector<float>>> propagateinterface::getRawHistogram()
{
    tuple<vector<int>,vector<vector<float>>>  evalHist;
    if (RootBool)
    {
        evalHist = RootProp->evaluateHistogram();
    } else {
        evalHist = Prop->evaluateHistogram();
    }
    vector<int> numbers = get<0>(evalHist);
    vector<vector<float>> outputs = get<1>(evalHist);
    vector<vector<vector<float>>> Raw;
    Raw.resize(10);
    for (int i = 0; i < 10; i++)
        Raw.at(i).resize(10);

    for (uint i = 0; i < numbers.size(); i++)
    {
        for (uint j = 0; j < outputs.at(0).size(); j++)
        {
            Raw.at(numbers.at(i)).at(j).push_back(outputs.at(i).at(j));
        }
    }
    return Raw;
}

vector<float> propagateinterface::evaluateSingleImage (vector<float> image)
{
    if (RootBool)
    {
       return RootProp->Application(image);
    } else {
        return Prop->resultFunc(image); //Gives the result of the network for one input image
    }
}

void propagateinterface::useRooT(bool b)
{
    RootBool = b;
}

//Setfunctions for the dimensions of the network==================================================

void propagateinterface::setNumberOfNeuronsPerLayer(vector<int> A)
{
    NumberOfNeuronsPerLayer = A;
}

/*
void propagateinterface::setNumberOfLayers(int A)
{
    NumberOfLayers=A;
}*/

//Set functions for the training of the network (propagate)=======================================

void propagateinterface::setMiniBatchSize(int A)
{
    MiniBatchSize = A;
}

void propagateinterface::setEta(float E)
{
    Eta = E;
}

void propagateinterface::setIterations(int N)
{
    if (Iterations.empty())
    {
         Iterations.push_back(1);
         N--;
    }
    for (int i = 0; i < N; i++) 
    {
         Iterations.push_back(Iterations.back()+1);
    }
}

void propagateinterface::setEvaluationError(float A)
{
    EvaluationError.push_back(A);
}

void propagateinterface::setTrainingError(float A)
{
    TrainingError.push_back(A);
}

void propagateinterface::setTruePositive(float A)
{
    TruePositive.push_back(A);
}

void propagateinterface::setTrueNegative(float A)
{
    TrueNegative.push_back(A);
}

void propagateinterface::setFalsePositive(float A)
{
    FalsePositive.push_back(A);
}

void propagateinterface::setFalseNegative(float A)
{
    FalseNegative.push_back(A);
}

void propagateinterface::setEvaluationImages(string A)
{
    EvaluationImages = A;
}

void propagateinterface::setEvaluationNumbers(string A)
{
    EvaluationNumbers = A;
}

void propagateinterface::setTrainingImages(string A)
{
    TrainingImages = A;
}

void propagateinterface::setTrainingNumbers(string A)
{
    TrainingNumbers = A;
}

void propagateinterface::setLoadNetworkPath(string A)
{
    LoadNetworkPath = A;
}

void propagateinterface::setNumberOfLayers(int N)
{
    NumberOfLayers = N;
}

void propagateinterface::setThreshold(float T)
{
    Threshold = T;
}


//Getfunctions for the dimensions of the network=================================================

int propagateinterface::getNumberOfLayers()
{
    return NumberOfLayers;
}

vector<int> propagateinterface::getNumberOfNeuronsPerLayer()
{
    return NumberOfNeuronsPerLayer;   //returns a vectorof intigers, possible right?
}

int propagateinterface::getMiniBatchSize()
{
    return MiniBatchSize;
}


void propagateinterface::loadNetwork(string A)
{
    if (RootBool)
    {
//        RootProp->loadNetwerk(A);
    } else {
        Prop->loadNetwerk(A);
    }
}

void propagateinterface::saveNetwork(string A)
{
    if (RootBool)
    {
  //      RootProp->saveNetwerk(A);
    } else {
        Prop->saveNetwerk(A);
    }
}

vector<int> propagateinterface::getIterations()
{
    return Iterations;
}

vector<float> propagateinterface::getEvaluationError()
{
    return EvaluationError;
}

vector<float> propagateinterface::getTrainingError()
{
    return TrainingError;
}

vector<float> propagateinterface::getTruePositive()
{
    return TruePositive;
}

vector<float> propagateinterface::getTrueNegative()
{
    return TrueNegative;
}

vector<float> propagateinterface::getFalsePositive()
{
    return FalsePositive;

}

vector<float> propagateinterface::getFalseNegative()
{
    return FalseNegative;
}

string propagateinterface::getEvaluationImages()
{
    return EvaluationImages;
}

string propagateinterface::getEvaluationNumbers()
{
    return EvaluationNumbers;
}

string propagateinterface::getTrainingImages()
{
    return TrainingImages;
}

string propagateinterface::getTrainingNumbers()
{
    return TrainingNumbers;
}

float propagateinterface::getThreshold()
{
    return Threshold;
}


vector<float> propagateinterface::getAccuracy()
{
    vector<float> temp;
    for (size_t i=0;i<FalseNegative.size();i++)
    {
        temp.push_back((TruePositive.at(i)+TrueNegative.at(i))/(TruePositive.at(i)+TrueNegative.at(i)+FalseNegative.at(i)+FalsePositive.at(i)));
    }
    return temp;
}

vector<float> propagateinterface::getSensitivity()
{
    vector<float> temp;
    for (size_t i=0;i<FalseNegative.size();i++)
    {
        temp.push_back((TruePositive.at(i))/(TruePositive.at(i)+FalseNegative.at(i)));
    }
    return temp;
}

vector<float> propagateinterface::getSpecificity()
{
    vector<float> temp;
    for (size_t i=0;i<FalseNegative.size();i++)
    {
        temp.push_back((TrueNegative.at(i))/(TrueNegative.at(i)+FalsePositive.at(i)));
    }
    return temp;
}

vector<float> propagateinterface::getPrecision()
{
    vector<float> temp;
    for (size_t i=0;i<FalseNegative.size();i++)
    {
        temp.push_back((TruePositive.at(i))/(TruePositive.at(i)+FalsePositive.at(i)));
    }
    return temp;
}
