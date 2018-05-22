#ifndef PROPAGATE_H
#define PROPAGATE_H

#include <vector>
#include <string>

#include "Network.h"
#include "batch.h"


// Helper functions
void setAllElementsToOneValue(vector<vector<float>>& multivec, const float value);
void setAllElementsToOneValue(vector<vector<vector<float>>>& multivec, const float value);
// Functions for testing
void printVec(const vector<float>& vec);
void printVec(const vector<vector<float>>& multivec);
void printVec(const vector<vector<vector<float>>>& multivec);


class propagate{
	public:
		propagate(float E, int Size,const vector<int>& nNeurons, const int nInputs,  const string EvalImageString, const string EvalLabelString, const string TrainImageString, const string TrainLabelString); // constructor 1
		propagate(const string fileName, float E, int Size,  const string EvalImageString, const string EvalLabelString, const string TrainImageString, const string TrainLabelString); // constructor 2
		~propagate(); // destuctor

		void setEta(float);		// Sets the value of the learning rate
		void setMiniBatchSize(int);	// Sets the number of training samples in a minibatch
		void setThreshold(float);	// Sets the threshold value for the outputs of the last layer
		
		void setTrainImages(batch&);	// Sets the vector containing the images for training the network
		void setEvalImages(batch&);	// Sets the vector containing the images for evaluating (testing) the network
		
		float getEta() const;		// Gets the value of the learning rate
		int getMiniBatchSize() const;	// Gets the number of training samples in a minibatch
		float getThreshold() const;	// Gets the threshold value for the outputs of the last layer
		
		void loadNetwork(const string );	// Loads the biases and weights from a file to the current network
		void saveNetwork(const string );	// Saves the current biases and weights of the network to a file 
		
		vector<float> resultFunc(const vector<float>& Input);	// Calculates the ouput of the last layer -> output of the network
		tuple<vector<int>,vector<vector<float>>> evaluateHistogram();	// Gives values for showing the ouput of the network with the number it should represent

		vector<vector<float>> propagateNEpochs(const int N);	// Trains the network for 'N' epochs
		vector<float> evaluate();				// Calculates the values to evaluate the performing of the network


	protected:
	
		vector<float> IntToVec(const float);	// Returns a vector that respresents one given number between 0-9
		
		float propagateEpoch();		// Trains the network for one epoch
		void propagateMiniBatch();	// Trains the network for 'MiniBatchSize' training samples and then derives the weights and biases
		void deriveWeightsAndBias(const vector<vector<float>>&, const vector<vector<vector<float>>>&);	// Adjust the biases and weights of the network by a gradient descend method
	
		// Data members
		float Eta;		// Learning rate 'eta'
		int MiniBatchSize;	// Number of training samples in a minibatch
		
		float CostMiniBatch;	// Mean costfunction of one minibatch
		float TrainingError;	// Training error of one epoch
		float ValidationError;	// Validation error of one epoch
		float Threshold = 0.5;	// Threshold value for the outputs of the last layer
		
		vector<int> ChooseTrainingSample;	// Vector that is used to select a random training sample
		
		network CurrentNetwork;		// The network that is being trained
		
		batch TrainingBatch;		// Contains the training images of the MINST database
		batch EvaluationBatch;		// Contains the evaluation (test) images of the MINST database
		vector<shared_ptr<testimage>> TrainImages;	// Contains the pixel values and number it represents of each training image
		vector<shared_ptr<testimage>> EvalImages;	// Contains the pixel values and number it represents of each evaluate (test) image
		
	private:
		propagate(const propagate& prop);		// copy constructor
		propagate& operator = (const propagate& net); 	// Assignment constructor
	
};

#endif
