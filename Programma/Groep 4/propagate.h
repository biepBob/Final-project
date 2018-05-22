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
		propagate(float E, int Size,const vector<int>& nNeurons, const int nInputs,  const string EvalImageString, const string EvalLabelString, const string TrainImageString,const string 				TrainLabelString); // constructor 1
		propagate(const string fileName, float E, int Size,  const string EvalImageString, const string EvalLabelString, const string TrainImageString,const string 				TrainLabelString); // constructor 2
		~propagate(); // destuctor
		propagate(const propagate& prop);// copyconstructor
		propagate& operator = (const propagate& net); // Assignment constructor

		void setEta(float);
		void setMiniBatchSize(int);
		void setThreshold(float);
		
		void setTrainImages(batch&);
		void setEvalImages(batch&);
		
		float getEta() const;
		int getMiniBatchSize() const;
		float getThreshold() const;
		
		void loadNetwork(const string );
		void saveNetwork(const string );
		
		vector<float> resultFunc(const vector<float>& Input);
		tuple<vector<int>,vector<vector<float>>> evaluateHistogram();

		vector<vector<float>> propagateNEpochs(const int N);
		vector<float> evaluate();


	protected:
	
		vector<float> IntToVec(const float);
		
		float propagateEpoch();
		void propagateMiniBatch();
		void deriveWeightsAndBias(const vector<vector<float>>&, const vector<vector<vector<float>>>&);	// Adjust the biases and weights of the network by a gradient descend method
	
	
		// Data members
		float Eta;		// Learning rate 'eta'
		int MiniBatchSize;	// Number of training sets in a minibatch
		
		float CostMiniBatch;	// Mean costfunction of one minibatch
		float TrainingError; // training error of the epoch
		float ValidationError; // Validation error of the epoch
		float Threshold = 0.5;
		
		vector<int> ChooseTrainingSample;
		
		
		network CurrentNetwork;	// The network that is being trained
		
		batch EvaluationBatch;
		batch TrainingBatch;
		vector<shared_ptr<testimage>> TrainImages;	// datamember -> Only need to get the images once
		vector<shared_ptr<testimage>> EvalImages;	// datamember -> Only need to get the images once
		

};

#endif
