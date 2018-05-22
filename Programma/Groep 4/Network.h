#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"

#include <vector>
#include <string>


using namespace std;

class network {
	public:
		network(const vector<int>& nNeurons, const int nInputs); 		// Constructor3, when no weights or biases are given. Paramters are # neurons for every layer, #inputs for the first layer of neurons, # layers.
		network(const string fileName);					// Constructor2, when weights and bias values are loaded from a file
											//
		~network(); 			// Destructor
		network(const network& net); 	// Copy constructor
		network& operator = (const network& net);	// Assignment constructor

		void setWeights(const vector<vector<vector<float>>>&);	// set-function for the weights in the network
		void setBias(const vector<vector<float>>&);		// set-function for the biases in the network
		void setNumberofLayers(const int);			// set-function for the number of layers in the network

		vector<vector<vector<float>>> getWeights();		// get-function that returns the weights of the network
		vector<vector<float>> getBias();			// get-function that returns the biases of the network
		int getNumberofLayers() const;				// get-function that returns the number of layers in the netwok
		vector<vector<float>> getLayerResult();				// get-function that returns the ouput output vector of each layer

		vector<vector<vector<float>>> loadLayers(const string); 				// Loads weigths and biases from a csv file 
		void saveLayers(const string); 				// Saves the current values of all the biases and weights in the network


		vector<vector<float>> errorFunc(const vector<float>& y);	// Calculates the error function of all neurons in the network for given 'y' and the previous calculated 'a'.
		vector<float> resultFunc(const vector<float>& Input);		// Calculates the result (output) vector of each layer from a given 'Input' for the network. Returns output of last layer.
		float costFunc(const vector<float>& a,const vector<float>& y); 	// Calculates the cost function for a given output (of the network) 'a' and 
												// the expected output 'y'.
		
	protected:
	
		// Data members
		vector<layer> Layers;				// The network is constructed out of layer objects which are stored in a vector.
		int NumberofLayers;				// The amount of layers in the network.
		vector<vector<float>> LayerResult;	        // The vector of output vectors of each layer. Contains the output of each neuron in each layer including input vector
		//bool NetworkHasChanged  
};
#endif // NETWORK_H
