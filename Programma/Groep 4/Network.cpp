#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>

#include "Network.h"


//Author: Robbe (& Marjan)=========================================================================


//Constructor for the network class when Weights and biases are loaded from a file
network::network(const string fileName)
{
	cout << "Data loaded from file: " << fileName << '\n';
	vector<vector<vector<float>>> dataFloat = loadLayers(fileName);
	for (int i=0; i < NumberofLayers; ++i)  // Iterates over the layers of the network
	{
		Layers.push_back(layer(dataFloat.at(i+2), dataFloat.at(1).at(i))); //creates a vector of neurons using layer/constructor1 wich in turn uses neuron/constructor1
	}
}


network::network(const vector<int>& nNeurons, const int nInputs)	//Constructor for the network class when random weights and biases are chosen
{
	NumberofLayers = nNeurons.size();
	//bool input = false;

	Layers.push_back(layer(nNeurons.at(0),nInputs));	// First layer of neurons (each neuron gets 'nInputs' input values) 
	for(int i=1; i < NumberofLayers; ++i)			//Iterates over the layers of the network
	{ 
		Layers.push_back(layer(nNeurons.at(i), nNeurons.at(i-1)));	//creates a vector of neurons using layer/constructor2 wich in turn uses neuron/constructor2
	}
}


network::~network()	//Destructor
{

}
//=================================================================================================

network::network(const network& net)	//Copy constructor
{ 
	Layers = net.Layers;
	NumberofLayers = net.NumberofLayers;
	//NetworkHasChanged  = net.NetworkHasChanged;
}

network& network::operator = (const network& net) //Assigment operator (constructor)
{
	if (&net != this)
	{
		Layers = net.Layers;
		NumberofLayers = net.NumberofLayers;
		//NetworkHasChanged  = net.NetworkHasChanged;
	}
	return *this;
}

//set- and getFunctions==================================================================================================================================
//=======================================================================================================================================================

void network::setWeights(const vector<vector<vector<float>>>& NetworkWeights)	// sets weights for every layer
{

	int count = 0;
	for_each(Layers.begin(), Layers.end(),		// For each layer i in the 'Layers' vector
		[&](layer& Layer) {			// change their weights to one of layer i of 'NetworkWeights'.
			Layer.setWeights(NetworkWeights.at(count++));	// Here is the post-increment of 'count' usefull.
	});
}

void network::setBias(const vector<vector<float>>& NetworkBias)	// sets biases for every layer
{

	int count = 0;
	for_each(Layers.begin(), Layers.end(),		// For each layer i in the 'Layers' vector
		[&](layer& Layer) {			// change their biases to one of layer i of 'NetworkBias'.
			Layer.setBias(NetworkBias.at(count++));	// Here is the post-increment of 'count' usefull.
	});
}

void network::setNumberofLayers(const int NLayers)	// sets amount of layers in the network
{
	NumberofLayers = NLayers;
}

vector<vector<vector<float>>> network::getWeights()
{
	vector<vector<vector<float>>> weights;
	
	for(int i=0; i < NumberofLayers; ++i){
		weights.push_back((Layers.at(i)).getWeights());
	}
	return weights;
}

vector<vector<float>> network::getBias()
{
	vector<vector<float>> bias;
	for(int i=0; i < NumberofLayers; ++i){
		bias.push_back((Layers.at(i)).getBias());
	}
	return bias;
}

int network::getNumberofLayers() const
{
	return NumberofLayers;
}


vector<vector<float>> network::getLayerResult() 
{
	return LayerResult;
}


//Load and savefunctions=================================================================================================================================
//=======================================================================================================================================================

vector<vector<vector<float>>> network::loadLayers(const string fileName) //Function to load already exsisting weights and bias
{
	
//Load values from a CSV-file as a vector of vectors of strings
        ifstream file(fileName);
        vector<vector<string>> dataString;
        vector<vector<vector<string>>> TotdataString;
        string line;
	string delimeter = ",";
	        // Iterate through each line and split the content using delimeter ","
	        while (getline(file, line))
	        {
	                vector<string> vec; //Temorary vector
	                boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
                        if(line.empty())
                        {
                                TotdataString.push_back(dataString);
                                dataString.clear();
                        } //If a empty line is found the program pushes the temporary vector<vector<string>> in the main object vectro<vector<vector<string>>> and clears the temporary storage object
                        else{
                                dataString.push_back(vec);
                        }
	        }
	        // Close the File
	        file.close();

//Transformation of strings to floats (vector<vector<string>> dataString => vector<vector<float>> dataFloat)
	vector<vector<vector<float>>> dataFloat; //Has the same structure as TotdataString
	for(vector<vector<string>> vecvec : TotdataString)
        { //iterates through each object in TotdataString and converts it to a float
                vector<vector<float>> FillFill;
                for(vector<string> vec : vecvec)
                {
        		vector<float> Fill;
                        for(string data : vec)
                        {
        			Fill.push_back(stof(data));
                        }
        		FillFill.push_back(Fill);
                }
                dataFloat.push_back(FillFill);
        }
        
	//Evaluating the dimensions of the loaded file        
        vector<float> Dimens = dataFloat.at(0).at(0);
	//int NInputs = Dimens.at(0);
	size_t NLayers1 = Dimens.at(1);
        size_t NLayers2 = Dimens.size()-2;
        
	//Comparing number of layers with dimensions to values for numbers of neurons per layer
	if(NLayers1 == NLayers2){
		setNumberofLayers(NLayers1);
	}
	else{
		cout << "Error: Dimensions of loadfile are incorrect" << "\n" << "The first row of the loadfile is not consistent" << endl;
		exit(1);
	}

	//Comparing number of layers with dimensions of bias
        vector<vector<float>> NetworkBias = dataFloat.at(1);
	if(NetworkBias.size() != NLayers1)
	{
		cout << "Error: Dimensions of loadfile are incorrect" << "\n" << "Not enough/too many biases for the amount of layers" << endl;
		exit(1);
	}

        vector<vector<vector<float>>> NetworkWeights;
        for(unsigned int i=2; i< NLayers1+2; ++i)
        {
		//Checking if the amount of weights matrices is the same as the number of layers
		if((dataFloat.at(i)).size() == Dimens.at(i))
		{
                	NetworkWeights.push_back(dataFloat.at(i));
		}
		else{
			cout << "Error: Dimensions of loadfile are incorrect" << "\n" << "Not enough/too many biases for the amount of neurons in layer " << i-1 << endl;
			exit(1);
		}
        }

	if(NetworkWeights.size() != NLayers1)
	{
		cout << "Error: Dimensions of loadfile are incorrect" << "\n" << "Too many/Not enough weights for the number of layers" << endl;
		exit(1);
	}

cout << "Weigths and biases are loaded correctly\n";
return dataFloat;
}

//Author: Tycho=========================================================================
void network::saveLayers(const string fileName)
{      

	const char* commaDelim = ",";						// used as delimiter between biases of the same layer and weights of the same neuron
	const char* newLineDelim = "\n";					// end of line character
	const size_t nInputs = getWeights().front().front().size(); 		// # weights of first neuron of first layer = # inputs of network
	
	// Creating 'ofstream' object
	ofstream outFile(fileName);
	
	// Beginning of writing to file
	outFile << nInputs;							// prints # inputs of network to 'fileName' 
	outFile << commaDelim << getNumberofLayers();				// second value of first row of 'fileName' is # layers in network
	for_each(Layers.begin(),Layers.end(),[&](layer& Layer)			// For each layer i in the 'Layers' vector
	{
		outFile << commaDelim << Layer.getNumberOfNeurons();		// prints # neurons to 'saveFile'
	});									// & in [] so the variables 'saveFile' and 'commaDelim' are know in this print function.
	
	outFile << newLineDelim << newLineDelim;				// adds an empty line to saveFile
	
	// printing BIAS values to file
	for_each(Layers.begin(),Layers.end(),[&](layer& Layer)			// For each layer i in the 'Layers' vector
	{
		const vector<float>& layerBias = Layer.getBias();					// temporarily vector to store the biases of layer i
		copy(layerBias.begin(),layerBias.end()-1,ostream_iterator<float>(outFile, commaDelim));	// prints those biases to file 'saveFile'
		outFile << layerBias.back() << newLineDelim;						// prints bias of last neuron in layer i and start a new line in the file
	});
	
	outFile << newLineDelim;							// second 'end of line character' in row -> adds empty line in file
	
	// printing WEIGHTS values to file 
	for_each(Layers.begin(),Layers.end(),[&](layer& Layer)			// For each layer i in the 'Layers' vector
	{
		const vector<vector<float> >& layerWeights = Layer.getWeights();					// temporarily vector to store the weights of layer i
		for_each(layerWeights.begin(),layerWeights.end(),[&](const vector<float>& neuronWeights)		// For each neuron j in layer i
		{
			copy(neuronWeights.begin(),neuronWeights.end()-1,ostream_iterator<float>(outFile, commaDelim));	// prints those weights to file 'saveFile'
			outFile << neuronWeights.back() << newLineDelim;						// prints weight of last neuron in layer i and start a new line in the file
		});
		outFile << newLineDelim;					// second 'end of line character' in row -> adds empty line in file
	});
	
	// End of writing to file
	 outFile.close();
}


//Error-,Result and costFunc=============================================================================================================================
//=======================================================================================================================================================
//Author: Marjan & Yannick=========================================================================

vector<vector<float>> network::errorFunc(const vector<float>& y)// calculates error function for given y and the previous calculated layerresult
{   
	vector<vector<vector<float>>> W = getWeights();  	// matrix/layer
	vector<vector<float>> B = getBias(); 			// vector/layer 
	vector<vector<float>> A = LayerResult;   // Contains results of every layer, inluding input of first layer; size = Numberoflayers+1

//////// errorfunction of last layer
	vector<vector<float>> wll = W.at(NumberofLayers-1); 	// weights wjk between last j layer and second-last k layer
	vector<float> bll = B.at(NumberofLayers-1);		// bias last layer
 	vector<float> all = A.at(NumberofLayers);		// output last layer
	vector<float> avl = A.at(NumberofLayers-1); 		// input last layer (output second last layer)
	vector<float> Dll;					// errorfunc last layer

	//cout << "Calculation error function last layer" << endl;
	//layer L = Layers.at(NumberofLayers-1);  // call last layer of vector of layers
	for (unsigned int i=0; i<all.size(); ++i) // loop over neurons last layer
	{ 
		//neuron N = L.Neurons.at(i); // call i-th neuron out of vector of neurons of layer l
		//N.setBias(bll.at(i)); // set bias of i-th neuron in layer l
		//N.setWeights(wll.at(i)); // set weights of i-th neuron in layer l			
		//N.activateFunc(avl);  // call activateFunc to calculate z 
		float x = (all.at(i)-y.at(i))*((Layers.at(NumberofLayers-1)).dsigmoid()).at(i); // calculate errorfunction
		Dll.push_back(x); 
	}

//////// errorfunction of previous layers by recursive prescription
	vector<float> Dl; // temporary storage for error function of one layer
	vector<vector<float>> DD = {Dll}; // error function: vector/layer
	for (signed int l = NumberofLayers-2; l>=0; --l) // loop over #layers starting at second last, l=layer
	{ 
		//cout << "Calculation error function for layer " << l+1 << endl;
		Dl.clear();  //  clear temporary storage
		//layer L = Layers.at(l);  // call l-th layer out of vector of layers
		for (unsigned int i=0; i<A.at(l+1).size(); ++i) //loop over #neurons per layer, i=neuron #neuronen = output
		{  
			//neuron N = L.Neurons.at(i); // call i-th neuron out of vector of neurons of layer l
			//N.setBias(B.at(l).at(i)); // set bias of i-th neuron in layer l
			//N.setWeights(W.at(l).at(i)); // set weights of i-th neuron in layer l	
			//N.activateFunc(A.at(l)); // calculate z with input of layer l
			float WD = 0;		
			for (unsigned int j=0; j<DD.at(0).size(); ++j) // vector multiplication of Wkj*D(l+1)
			{
				WD = WD + W.at(l).at(j).at(i) * DD.at(0).at(j);  // use always first vector of DD
			}

			Dl.push_back(WD * ((Layers.at(l)).dsigmoid()).at(i)); // add errorfunc for i-th neuron to Dl
		}		
		DD.insert(DD.begin(), Dl);  // add errorfunc for l-th layer in front of DD
	}
	return DD;
}


vector<float> network::resultFunc(const vector<float>& Image)	// calculates the result of every layer, returns result last layer
{  
	LayerResult.clear(); // Clear layerresult vector
	LayerResult.push_back(Image); // first vector is the input --> size LayerResult = NumberOfLayers+1
	vector<float> result = Image; // Start for recursive function
	for (signed int l=0; l<NumberofLayers; ++l)  // loop over all layers
	{
		result = (Layers.at(l)).resultFunc(result);  // result of layer l+1
		LayerResult.push_back(result);  // add vector result to LayerResult

	}
	return result;	// the result (output) vector of the last layer -> output of network
}


float network::costFunc(const vector<float>& a ,const vector<float>& y)  // Calculates cost function for given y and a. 
{ 
	float C = 0;
	for (unsigned int i=0; i<a.size(); ++i)
	{
		C = C + pow((y.at(i)-a.at(i)),2);
	}
	return C/2;
}


