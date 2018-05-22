/*Heb ik nu gecommend (alles van Root)
#ifndef PROPAGATEROOT_H
#define PROPAGATEROOT_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/TMVAMultiClassGui.h"
#include "TMVA/Types.h"
#include "TMVA/Reader.h"
#include "TMVA/IMethod.h"
#include "TMVA/MethodBase.h"


#include "batch.h"
#include "testimage.h"

class propagateRoot
{
	public: 
		propagateRoot(std::string,std::string,std::string,std::string);		// constructor
		
		~propagateRoot();		// destructor
	
		void makeRootFile(std::string,std::string,std::string,std::string)	;		// puts the training and test images in a root file with classified trees according to the numbers, the root file is called "multisignal.root"
		
		vector<float> propagateNEpochs();	// This trains and tests a boosted decision tree method  and outputs weightfiles that are later used by Application(), files with the training and testing results are also saved


		vector<float> IntToVec(float);			// Transforms the probabilities in zeros except for the given number, which gets transformed in a 1

		vector<float> evaluate();			// Function to calculate ValidationError, TruePositive, TrueNegative, FalsePositive, FalseNegative
		
		float costFunc(vector<float>,vector<float> );			// calculating cost function
		
		tuple<vector<int>,vector<vector<float>>> evaluateHistogram();		// forming a tuple with the real image value and the ten output values from the neural network 

		vector<float> Application(vector<float>);			// reads the weightfiles and evaluates an image
		

 	
	protected:
		int AT0;							// Amount of training images for number 0
		int AT1;							// Amount of training images for number 1
		int AT2;							// Amount of training images for number 2
		int AT3;							// Amount of training images for number 3
		int AT4;							// Amount of training images for number 4
		int AT5;							// Amount of training images for number 5
		int AT6;							// Amount of training images for number 6
		int AT7;							// Amount of training images for number 7
		int AT8;							// Amount of training images for number 8
		int AT9;							// Amount of training images for number 9
		vector <int> UsedPixels;					// used pixels in the training and testing
		
		vector<shared_ptr<testimage>> TrainImages;			// vector with the pixels of all the training images
		vector<shared_ptr<testimage>> TestImages;			// vector with the pixels of all the test images
		
		vector<float> cuts;						// Vector with the thresholds for each number, calculated by RooT

		float TrainingError;						// Error of the training images
		float ValidationError;						// Error of the test images
		
		
		std::string name_str;
		const char * name;
		
		vector<float> value; // vector that holds the output for every single evaluation
		
		vector<float> pixel;
		
		
		
};

#endif
*/

		

