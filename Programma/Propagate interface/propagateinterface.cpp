#include "propagateinterface.h"
#include "propagate.h"
#include "propagateRoot.h"
#include <vector>

using namespace std;

propagateinterface::propagateinterface() //Constructor
{ //Set all the protected memeber defautl to zero
    setMiniBatchSize(0);
    setEvaluationImages("");
    setEvaluationNumbers("");
    setTrainingImages("");
    setTrainingNumbers("");
    setEta(0);
}

propagateinterface::~propagateinterface() //Destructor
{
    if(make) destroyCurrentNetwork();//Only when a network is created, the delete's are called
    make = false;
}

propagateinterface::propagateinterface(const propagateinterface &Propagateinterface1) //copy constructor
{
    MiniBatchSize = Propagateinterface1.MiniBatchSize;
    Eta = Propagateinterface1.Eta;
    RootBool = Propagateinterface1.RootBool;
    EvaluationImages = Propagateinterface1.EvaluationImages;
    EvaluationNumbers = Propagateinterface1.EvaluationNumbers;
    TrainingImages = Propagateinterface1.TrainingImages;
    TrainingNumbers = Propagateinterface1.TrainingNumbers;
    LoadNetworkPath = Propagateinterface1.LoadNetworkPath;
    NetworkLoad = Propagateinterface1.NetworkLoad;
    make = false;
    nInputs = Propagateinterface1.nInputs;
    Threshold = Propagateinterface1.Threshold;
    makePropagate();

    Iterations = Propagateinterface1.Iterations;
    EvaluationError = Propagateinterface1.EvaluationError;
    TrainingError = Propagateinterface1.TrainingError;
    TruePositive = Propagateinterface1.TruePositive;
    TrueNegative = Propagateinterface1.TrueNegative;
    FalsePositive = Propagateinterface1.FalsePositive;
    FalseNegative = Propagateinterface1.FalseNegative;
}

propagateinterface& propagateinterface::operator = (const propagateinterface& Propagateinterface1) //assignment operator
{

    Eta = Propagateinterface1.Eta;
    RootBool = Propagateinterface1.RootBool;
    EvaluationImages = Propagateinterface1.EvaluationImages;
    EvaluationNumbers = Propagateinterface1.EvaluationNumbers;
    TrainingImages = Propagateinterface1.TrainingImages;
    TrainingNumbers = Propagateinterface1.TrainingNumbers;
    LoadNetworkPath = Propagateinterface1.LoadNetworkPath;
    NetworkLoad = Propagateinterface1.NetworkLoad;
    make = false;
    nInputs = Propagateinterface1.nInputs;
    Threshold = Propagateinterface1.Threshold;
    makePropagate();

    Iterations = Propagateinterface1.Iterations;
    EvaluationError = Propagateinterface1.EvaluationError;
    TrainingError = Propagateinterface1.TrainingError;
    TruePositive = Propagateinterface1.TruePositive;
    TrueNegative = Propagateinterface1.TrueNegative;
    FalsePositive = Propagateinterface1.FalsePositive;
    FalseNegative = Propagateinterface1.FalseNegative;
    return *this;
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
              Prop = new propagate(LoadNetworkPath,Eta,MiniBatchSize,EvaluationImages,EvaluationNumbers,TrainingImages,TrainingNumbers);
         } else {
              Prop = new propagate(Eta, MiniBatchSize,NumberOfNeuronsPerLayer,nInputs,EvaluationImages,EvaluationNumbers,TrainingImages,TrainingNumbers); // constructor met random waarden
         }
         Prop->setThreshold(Threshold);
    }
    make = true;
    Iterations.clear();
    EvaluationError.clear();                  //
    TrainingError.clear();
    TruePositive.clear();
    TrueNegative.clear();
    FalsePositive.clear();
    FalseNegative.clear();
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
    setEvaluationError(0);
    setTrainingError(0);
    setIterations(NEpochs);
    vector<vector<float>> temp;
    if (RootBool) //Root network
    {
        temp.push_back(RootProp->propagateNEpochs());
        NEpochs = 1;
    } else { //Own network
        temp = Prop->propagateNEpochs(NEpochs);
    }
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
    cout<<"Test: RootBool passed to interface: "<<RootBool<<endl;
}

//Setfunctions for the dimensions of the network==================================================

void propagateinterface::setNumberOfNeuronsPerLayer(vector<int> A)
{
    NumberOfNeuronsPerLayer = A;
    cout<<"Test: NumberOfNeuronsPerLayer passed to interface: "<<endl;      //NumberOfNeuronsPerLayer<<endl;
}


//Set functions for the training of the network (propagate)=======================================

void propagateinterface::setMiniBatchSize(int A)
{
    MiniBatchSize = A;
    cout<<"Test: MiniBatchSize passed to interface: "<<MiniBatchSize<<endl;
}

void propagateinterface::setEta(float E)
{
    Eta = E;
    cout<<"Test: Eta passed to interface: "<<Eta<<endl;
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
    cout<<"Test: EvaluationImages passed to interface: "<<EvaluationImages<<endl;
}

void propagateinterface::setEvaluationNumbers(string A)
{
    EvaluationNumbers = A;
    cout<<"Test: EvaluationNumbers passed to interface: "<<EvaluationNumbers<<endl;
}

void propagateinterface::setTrainingImages(string A)
{
    TrainingImages = A;
    cout<<"Test: TraningImages passed to interface: "<<TrainingImages<<endl;
}

void propagateinterface::setTrainingNumbers(string A)
{
    TrainingNumbers = A;
    cout<<"Test: TrainingNumbers passed to interface: "<<TrainingNumbers<<endl;
}

void propagateinterface::setLoadNetworkPath(string A)
{
    LoadNetworkPath = A;
}

void propagateinterface::setThreshold(float T)
{
    Threshold = T;
    cout<<"Test: Threshold passed to interface: "<<Threshold<<endl;
}


//Getfunctions for the dimensions of the network=================================================

vector<int> propagateinterface::getNumberOfNeuronsPerLayer()
{
    return NumberOfNeuronsPerLayer;   //returns a vectorof intigers, possible right?
}

int propagateinterface::getMiniBatchSize()
{
    return MiniBatchSize;
}

void propagateinterface::saveNetwork(string A)
{
    if (RootBool)
    {
  //      RootProp->saveNetwerk(A);
    } else {
        Prop->saveNetwork(A);
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
    temp.push_back(0);
    for (size_t i=0;i<FalseNegative.size();i++)
    {
        temp.push_back((TruePositive.at(i)+TrueNegative.at(i))/(TruePositive.at(i)+TrueNegative.at(i)+FalseNegative.at(i)+FalsePositive.at(i)));
    }
    return temp;
}

vector<float> propagateinterface::getSensitivity()
{
    vector<float> temp;
    temp.push_back(0);
    for (size_t i=0;i<FalseNegative.size();i++)
    {
        temp.push_back((TruePositive.at(i))/(TruePositive.at(i)+FalseNegative.at(i)));
    }
    return temp;
}

vector<float> propagateinterface::getSpecificity()
{
    vector<float> temp;
    temp.push_back(0);
    for (size_t i=0;i<FalseNegative.size();i++)
    {
        temp.push_back((TrueNegative.at(i))/(TrueNegative.at(i)+FalsePositive.at(i)));
    }
    return temp;
}

vector<float> propagateinterface::getPrecision()
{
    vector<float> temp;
    temp.push_back(0);
    for (size_t i=0;i<FalseNegative.size();i++)
    {
        temp.push_back((TruePositive.at(i))/(TruePositive.at(i)+FalsePositive.at(i)));
    }
    return temp;
}
