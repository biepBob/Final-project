//Robin Brabants
//robin.brabants@student.uantwerpen.be
//30/03/2018


#include <iostream>
#include <fstream>
#include <TApplication.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1F.h>
#include <TMath.h>
#include <string>
#include <map>
#include <vector>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "propagateRoot.h"

#include "TMVA/efficiencies.h"

	
int main()
{
	propagateRoot propagate("t10k-images.idx3-ubyte", "t10k-labels.idx1-ubyte", "train-images.idx3-ubyte", "train-labels.idx1-ubyte") ;


	propagate.propagateNEpochs();
	
	// input
	string TestImageString="t10k-images.idx3-ubyte";
	string TestLabelString="t10k-labels.idx1-ubyte";
	batch Test(TestImageString, TestLabelString);
	
	vector<shared_ptr<testimage>> TestImages = Test.getTestImages();
	
	int j =0;
	
	vector<float> pixels_vector = TestImages.at(j)->getConcatenatedColumns();
	////
	
	
	
	propagate.Application(pixels_vector);
	cout<<"real number: "<<TestImages.at(j)->getRealNumber()<<endl;
	
	
	return 0;
	
}


