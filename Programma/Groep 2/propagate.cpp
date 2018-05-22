#include <iostream>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <algorithm>

#include "propagate.h"
using namespace std;


// Helper functions ===========================================
void setAllElementsToOneValue(vector<vector<float>>& multivec, const float value)
{
	for_each(multivec.begin(),multivec.end(),[&](vector<float>& lowervec)		
		{
			fill(lowervec.begin(),lowervec.end(),value);						
		});	
}

void setAllElementsToOneValue(vector<vector<vector<float>>>& multivec, const float value)
{
	for_each(multivec.begin(),multivec.end(),[&](vector<vector<float>>& lower1vec)
		{
			for_each(lower1vec.begin(),lower1vec.end(),[&](vector<float>& lower2vec)
			{
				fill(lower2vec.begin(),lower2vec.end(),value);				
			});
		});
}

// For testing purposes =======================================
void printVec(const vector<float>& vec)
{
	copy(vec.begin(),vec.end()-1,ostream_iterator<float>(cout,","));
	cout << vec.back();
}

void printVec(const vector<vector<float>>& multivec)
{
	for_each(multivec.begin(),multivec.end(),[&](const vector<float>& lowervec)		
		{
			printVec(lowervec);						
		});	
}

void printVec(const vector<vector<vector<float>>>& multivec)
{
	for_each(multivec.begin(),multivec.end(),[&](const vector<vector<float>>& lowervec)
		{
			printVec(lowervec);
		});
}

//=============================================================

// propagate ==========================================================
//=====================================================================
propagate::propagate(float eta, int miniBatchSize,const vector<int>& nNeurons, const int nInputs, const string EvalImageString, const string EvalLabelString, const string TrainImageString,const string TrainLabelString) // constructor
:CurrentNetwork(nNeurons,nInputs),TrainingBatch(TrainImageString,TrainLabelString),EvaluationBatch(EvalImageString,EvalLabelString)
{ 
    setEta(eta);
    setMiniBatchSize(miniBatchSize);
	
    setTrainImages(TrainingBatch);
    setEvalImages(EvaluationBatch);
}

propagate::propagate(const string fileName, float eta, int miniBatchSize,  const string EvalImageString, const string EvalLabelString, const string TrainImageString,const string TrainLabelString) // constructor
:CurrentNetwork(fileName),TrainingBatch(TrainImageString,TrainLabelString),EvaluationBatch(EvalImageString,EvalLabelString)
{ 
    setEta(eta);
    setMiniBatchSize(miniBatchSize);
	
    setTrainImages(TrainingBatch);
    setEvalImages(EvaluationBatch);
}

propagate::~propagate() // destructor
{

}

//=====================================================================
void propagate::setEta(float inputEta)
{
    Eta = inputEta;
}

void propagate::setMiniBatchSize(int inputMiniBatchSize)
{
    MiniBatchSize = inputMiniBatchSize;
}

void propagate::setThreshold(float Thresh)
{
    Threshold = Thresh;
}

void propagate::setTrainImages(batch& trainingBatch)
{
	TrainImages = trainingBatch.getTestImages();
}

void propagate::setEvalImages(batch& evaluationBatch)
{
	EvalImages = evaluationBatch.getTestImages();
}

float propagate::getEta() const
{
    return Eta;
}

int propagate::getMiniBatchSize() const
{
    return MiniBatchSize;
}

float propagate::getThreshold() const
{
    return Threshold;
}

void propagate::loadNetwork(const string fileName)
{
	CurrentNetwork.loadLayers(fileName);
}

void propagate::saveNetwork(const string fileName)
{
	CurrentNetwork.saveLayers(fileName);
}

vector<float> propagate::IntToVec(const float a)
{
	vector<float>  L(10,0.0);
	L.at(a)=1.0;             //vector begins with element 0.
	return L;
}

vector<float> propagate::resultFunc(const vector<float>& Input)
{
    return CurrentNetwork.resultFunc(Input);
}

vector<vector<float>> propagate::propagateNEpochs(const int N)  // propagate N epochs, returns evalerror, trainingerror, fals negative, false positive, true negatieve, true positive per epoch
// perform an evaluation on test sample after each epoch: batch evaluationbatch --> determine numbers
// validation error = mean costfunction of test (evaluation) data
// training error = mean costfunction of training data
{
	cout << "Started propagating " << N << " Epochs" << endl;
	vector<vector<float>> Data;
	Data.clear();

	for (int i=0; i<N; ++i)
	{
		cout << "i: " << i << '\n';
		float trainError = propagateEpoch();   // training error
		vector<float> valError = evaluate(); // validation error, ....

		valError.insert(valError.begin(), trainError);

		Data.push_back(valError);
		cout 	<< "TrainingError " << Data.at(i).at(0) << '\n'
			<< "ValidationError " << Data.at(i).at(1) << '\n'
  	   	  	<< "TruePositive " << Data.at(i).at(2) << '\n'
	   	 	<< "TrueNegative " << Data.at(i).at(3) << '\n'
	   	 	<< "FalsePositive " << Data.at(i).at(4) << '\n'
	   	 	<< "FalseNegative " << Data.at(i).at(5) << '\n';
	}	
	return Data; 
}


float propagate::propagateEpoch()
{
	cout << "Started propagating epoch." << endl;
	srand(time(0));  	// otherwise everytime the same random shuffle

	const int NtrainingSamples = TrainImages.size();  		// number of training samples
	const int remain = NtrainingSamples % MiniBatchSize; 		// remainder of dividing 'NtrainingSample' by 'MiniBatchSize'
	const int NusedTrainingSamples = NtrainingSamples-remain;	// the amount of training samples that will be used in this epoch, which is a multiple of MiniBatchSize

	// numbers in random sequence
	ChooseTrainingSample.clear(); // vector of numbers between 0 and 'NusedTrainingSamples'-1, new shuffle every epoch
    	for (int i=0; i<NusedTrainingSamples; ++i)
	{
        	ChooseTrainingSample.push_back(i);
    	} 
    	std::random_shuffle(ChooseTrainingSample.begin(), ChooseTrainingSample.end()); // random shuffle

	// number of minibatches
	const int Nminibatches = NusedTrainingSamples/MiniBatchSize;
	
	// loop over verschillende minibatches and calculate trainingerror
	TrainingError = 0;
    	for (int i=0; i<Nminibatches ; ++i)
    	{
		propagateMiniBatch();
		TrainingError = TrainingError + CostMiniBatch;
    	}
	TrainingError = TrainingError/(static_cast<float>(NusedTrainingSamples));
        CurrentNetwork.saveLayers("tempBWsaveFile.csv");	// each epoch, the current biases and weights are saved
	
	return TrainingError;
}

vector<float> propagate::evaluate()
{
	const size_t NevalImages = EvalImages.size();

	cout << "Started evaluating epoch with " << NevalImages << " evaluation images." << endl;

	ValidationError = 0;
	int TP = 0;
	int TN = 0;
	int FP = 0;
	int FN = 0;

	for (size_t i=0 ; i<NevalImages ; ++i)
	{
		vector<float> a = CurrentNetwork.resultFunc(EvalImages.at(i)->getConcatenatedColumns() );
		vector<float> y = IntToVec(static_cast<float>(EvalImages.at(i)->getRealNumber()));			
		ValidationError = ValidationError + CurrentNetwork.costFunc(a, y);

		for (size_t j=0; j<a.size(); ++j)
		{
			if (a.at(j)<Threshold && y.at(j)==0.0)
				{ ++TN; }
			else if (a.at(j)<Threshold && y.at(j)!=0.0)
				{ ++FN; }
			else if (a.at(j)>Threshold && y.at(j)!=1.0)
				{ ++FP; }
			else
				{ ++TP; }
		}
	}

	ValidationError = ValidationError/(static_cast<float>(NevalImages));
        vector<float> Data = {ValidationError,(float) TP,(float) TN,(float) FP,(float) FN};

	return Data;
}

tuple<vector<int>,vector<vector<float>>> propagate::evaluateHistogram()
{
	const size_t NevalImages = EvalImages.size();
    	vector<int> listNumbers;
    	vector<vector<float>> outputs;
    	
	for (size_t i=0; i<NevalImages; ++i)
   	{
		outputs.push_back(CurrentNetwork.resultFunc(EvalImages.at(i)->getConcatenatedColumns()));
		listNumbers.push_back(EvalImages.at(i)->getRealNumber());
    	}
	return make_tuple(listNumbers,outputs);
}

void propagate::propagateMiniBatch() // propagate one minibatch
{
	const float startingValue = 0.0;
	
	vector<vector<float>> SumGradientBias = CurrentNetwork.getBias();	// now 'SumGradientBias' has the same structure as the bias vector
	setAllElementsToOneValue(SumGradientBias,startingValue);		// All elements of 'SumGradientBias' are now 0
	
	vector<vector<vector<float>>> SumGradientWeights = CurrentNetwork.getWeights();	// now 'SumGradientWeights' has the same structure as the weights vector
	setAllElementsToOneValue(SumGradientWeights,startingValue);			// All elements of 'SumGradientWeights' are now 0
	

	const int Nlayers = CurrentNetwork.getNumberofLayers();	// The amount of layers in the network

	CostMiniBatch = 0;
	for (int iSample=0 ; iSample<MiniBatchSize ; ++iSample)   // loop over all training samples in one minibatch
	{
		// Get a training sample
		vector<float> TrainingSampleIN = TrainImages.at(ChooseTrainingSample.back())->getConcatenatedColumns();		// Current training sample input
		
		float numOut = static_cast<float>(TrainImages.at(ChooseTrainingSample.back())->getRealNumber());
		vector<float> TrainingSampleOut = IntToVec(numOut);								// Current training sample output
		ChooseTrainingSample.pop_back();			// This training sample index will not be used again (in this epoch)
	
		// Calculate output and errorfunction of all neurons in the network
		CurrentNetwork.resultFunc(TrainingSampleIN);				// calculates the output of all neurons in the network
		vector<vector<float>> layersOutput = CurrentNetwork.getLayerResult();	// contains the ouput of all neurons in the network for the current training sample
		vector<vector<float>> Error = CurrentNetwork.errorFunc(TrainingSampleOut); // contains errorfunction of all neurons in the network for the current training sample
		
		// Cost function of training sample added to total cost of minibatch
		CostMiniBatch += CurrentNetwork.costFunc(layersOutput.back(),TrainingSampleOut); // (x +=5 -> x = x + 5)
	
		for (int jlayer=0 ; jlayer<Nlayers ; ++jlayer)	// For each layer j
		{
			const int Nneurons = (Error.at(jlayer)).size();		// Amount of neurons in layer j
			for (int kneuron=0 ; kneuron<Nneurons ; ++kneuron)	// For each neuron k in layer j
			{
				// Calculates gradient of cost for each bias for one sample & added to 'SumGradientBias' of that bias
				SumGradientBias.at(jlayer).at(kneuron) += Error.at(jlayer).at(kneuron);	
				// amount of inputs of neuron k in layer j
				const int Ninputs = (layersOutput.at(jlayer)).size();	// (because layersOutput[0]=inputs of network and each neuron in a layer has the same amount of inputs.)
				for (int linput=0; linput<Ninputs; ++linput)		// For each input l of neuron k in layer j
					{
						// Calculates gradient of cost for each weight for one sample & added to 'SumGradientWeights' of that weight
						SumGradientWeights.at(jlayer).at(kneuron).at(linput) += (layersOutput.at(jlayer).at(linput))*(Error.at(jlayer).at(kneuron));
					}	
			}
		}
	}
	
	deriveWeightsAndBias(SumGradientBias, SumGradientWeights);	// adjust the biases and weights
}

void propagate::deriveWeightsAndBias(const vector<vector<float>>& sumGradientBias, const vector<vector<vector<float>>>& sumGradientWeights)
{
	vector<vector<float>> newBias = CurrentNetwork.getBias();		// Biases of the network
	vector<vector<vector<float>>> newWeights = CurrentNetwork.getWeights();	// Weights of the network
	const int Nlayers = CurrentNetwork.getNumberofLayers();			// Amount of layers in the network
	const float flMiniBatchSize = static_cast<float>(MiniBatchSize);	// Amount of samples in a minibatch, converted to float because the value is used in (float) calculations
	
	for (int ilayer=0 ; ilayer<Nlayers; ++ilayer)	// For each layer i
	{
		const int Nneurons = (newWeights.at(ilayer)).size();	// Amount of neurons in layer i
		for (int jneuron=0 ; jneuron<Nneurons ; ++jneuron)	// For each neuron j in layer i
		{
			newBias.at(ilayer).at(jneuron) -= (Eta/flMiniBatchSize)*(sumGradientBias.at(ilayer).at(jneuron));	// gradient descend method to change biases
			
			const int Ninputs = ((newWeights.at(ilayer)).at(jneuron)).size();	// Amount of inputs for neuron j of layer i
			for (int kinput=0 ; kinput<Ninputs ; ++kinput)				// For each input k of neuron j in layer i
			{
				newWeights.at(ilayer).at(jneuron).at(kinput) -= (Eta/flMiniBatchSize)*(sumGradientWeights.at(ilayer).at(jneuron).at(kinput));	// gradient descend method to change weights
			}
		}
	}
	// Adjust the values of the biases and weights of the network
	CurrentNetwork.setBias(newBias);
	CurrentNetwork.setWeights(newWeights);
}

