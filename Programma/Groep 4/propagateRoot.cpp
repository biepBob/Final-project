/*
#include "propagateRoot.h"


propagateRoot::propagateRoot(std::string EvaluationImages,std::string EvaluationNumbers,std::string TrainingImages,std::string TrainingNumbers)
	{
	makeRootFile(EvaluationImages,EvaluationNumbers,TrainingImages,TrainingNumbers);
	cout<<"object created"<<endl;
	}
	
propagateRoot::~propagateRoot()
	{
	}
	
void propagateRoot::makeRootFile(std::string EvaluationImages,std::string EvaluationNumbers,std::string TrainingImages,std::string TrainingNumbers)
	{
	
	// get the training and test batches:
	
	
	
	batch Test(EvaluationImages, EvaluationNumbers);
	
	batch Train(TrainingImages, TrainingNumbers);
	
	
	// and save them in a vector of pointers:
	
	TrainImages = Train.getTestImages();
	TestImages = Test.getTestImages();
	
	// opens Root file 'multisignal.Root" to which the training and test data will be written:
	
	TFile* file = TFile::Open("multisignal.root", "recreate");
	
	// makes a TTree for every number:
	
	TTree* Tree0 = new TTree("Tree0","Tree0 Tree");
	TTree* Tree1 = new TTree("Tree1","Tree1 Tree");
	TTree* Tree2 = new TTree("Tree2","Tree2 Tree");
	TTree* Tree3 = new TTree("Tree3","Tree3 Tree");
	TTree* Tree4 = new TTree("Tree4","Tree4 Tree");
	TTree* Tree5 = new TTree("Tree5","Tree5 Tree");
	TTree* Tree6 = new TTree("Tree6","Tree6 Tree");
	TTree* Tree7 = new TTree("Tree7","Tree7 Tree");
	TTree* Tree8 = new TTree("Tree8","Tree8 Tree");
	TTree* Tree9 = new TTree("Tree9","Tree9 Tree");
	

	int Solution;

	
	vector<float> pixels(784);
	
	// puts references to the pixels of an image in the branches and names them pixel1, pixel2 ...:
	
	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();

		Tree0->Branch(name, &pixels[i], 64000,1);
		Tree1->Branch(name, &pixels[i], 64000,1);
		Tree2->Branch(name, &pixels[i], 64000,1);
		Tree3->Branch(name, &pixels[i], 64000,1);
		Tree4->Branch(name, &pixels[i], 64000,1);
		Tree5->Branch(name, &pixels[i], 64000,1);
		Tree6->Branch(name, &pixels[i], 64000,1);
		Tree7->Branch(name, &pixels[i], 64000,1);
		Tree8->Branch(name, &pixels[i], 64000,1);
		Tree9->Branch(name, &pixels[i], 64000,1);

	}
		
		
	// keeps track of the number of training images in each tree:
	
	AT0 = 0;
	AT1 = 0;
	AT2 = 0;
	AT3 = 0;
	AT4 = 0;
	AT5 = 0;
	AT6 = 0;
	AT7 = 0;
	AT8 = 0;
	AT9 = 0;

	// keeps track of the number of testing images in each tree:
		
	int Ate0 = 0;
	int Ate1 = 0;
	int Ate2 = 0;
	int Ate3 = 0;
	int Ate4 = 0;
	int Ate5 = 0;
	int Ate6 = 0;
	int Ate7 = 0;
	int Ate8 = 0;
	int Ate9 = 0;

	//places the values of the pixels for the training images in the branches according to the number:
	
	for(unsigned int j = 0; j < TrainImages.size(); j++) 
	//for(int j = 0; j < 1000; j++) 
	{
		vector<float> image_vector = TrainImages.at(j)->getConcatenatedColumns();
		Solution = TrainImages.at(j)->getRealNumber();
		
		for (int k = 0; k <784; k++) 
			{
			pixels[k] = image_vector[k] ;
			}
			
		if (Solution == 0)
		{
			Tree0->Fill();
			AT0++;
		}
		else if (Solution == 1)
		{
			Tree1->Fill();
			AT1++;
		}
		else if (Solution == 2)
		{
			Tree2->Fill();
			AT2++;
		}
		else if (Solution == 3)
		{
			Tree3->Fill();			
			AT3++;
		}
		else if (Solution == 4)
		{
			Tree4->Fill();
			AT4++;
		}
		else if (Solution == 5)
		{
			Tree5->Fill();
			AT5++;
		}
		else if (Solution == 6)
		{
			Tree6->Fill();
			AT6++;
		}
		else if (Solution == 7)
		{
			Tree7->Fill();
			AT7++;
		}
		else if (Solution == 8)
		{
			Tree8->Fill();
			AT8++;
		}
		else if (Solution == 9)
		{
			Tree9->Fill();
			AT9++;
		}
	}
	
	
	std::cout << "Number of training images per number: " << AT0 << " " << AT1 << " " << AT2 << " " << AT3 << " " << AT4 << " " << AT5 << " " << AT6 << " " << AT7 << " " << AT8 << " " << AT9 << std::endl;
	
	
	
	//places the values of the pixels for the testing images in the branches according to the number:
	
	for(unsigned int l = 0; l < TestImages.size(); l++) 
	//for(int l = 0; l < 250; l++) 
	{
		vector<float> image_vector = TestImages.at(l)->getConcatenatedColumns();
		Solution = TestImages.at(l)->getRealNumber();
		
		for (int m = 0; m < 784; m++) 
			{
			pixels[m] = image_vector[m] ;
			}
			
		if (Solution == 0)
		{
			Tree0->Fill();
			Ate0++;
		}
		else if (Solution == 1)
		{
			Tree1->Fill();
			Ate1++;
		}
		else if (Solution == 2)
		{
			Tree2->Fill();
			Ate2++;
		}
		else if (Solution == 3)
		{
			Tree3->Fill();
			Ate3++;
		}
		else if (Solution == 4)
		{
			Tree4->Fill();
			Ate4++;
		}
		else if (Solution == 5)
		{
			Tree5->Fill();
			Ate5++;
		}
		else if (Solution == 6)
		{
			Tree6->Fill();
			Ate6++;
		}
		else if (Solution == 7)
		{
			Tree7->Fill();
			Ate7++;
		}
		else if (Solution == 8)
		{
			Tree8->Fill();
			Ate8++;
		}
		else if (Solution == 9)
		{
			Tree9->Fill();
			Ate9++;
		}
	}
	
	
	
	std::cout << "Number of testing images per number: " << Ate0 << " " << Ate1 << " " << Ate2 << " " << Ate3 << " " << Ate4 << " " << Ate5 << " " << Ate6 << " " << Ate7 << " " << Ate8 << " " << Ate9 << std::endl;


	// writes the trees:
	
	Tree0->Write();
	Tree1->Write();
	Tree2->Write();
	Tree3->Write();
	Tree4->Write();
	Tree5->Write();
	Tree6->Write();
	Tree7->Write();
	Tree8->Write();
	Tree9->Write();

	file->Close();
	
	std::cout << "The root tree file has been written" << std::endl;
	
	delete file;
	
	}
	
vector<float> propagateRoot::propagateNEpochs()
	{

	// read the data from the root file:
	
	TFile* file1 = TFile::Open("multisignal.root", "read");


	// Get the signal training and test trees from TFile source(s):

	TTree* tree0 = (TTree*)file1->Get("Tree0");
	TTree* tree1 = (TTree*)file1->Get("Tree1");	
	TTree* tree2 = (TTree*)file1->Get("Tree2");	
	TTree* tree3 = (TTree*)file1->Get("Tree3");	
	TTree* tree4 = (TTree*)file1->Get("Tree4");	
	TTree* tree5 = (TTree*)file1->Get("Tree5");	
	TTree* tree6 = (TTree*)file1->Get("Tree6");	
	TTree* tree7 = (TTree*)file1->Get("Tree7");	
	TTree* tree8 = (TTree*)file1->Get("Tree8");	
	TTree* tree9 = (TTree*)file1->Get("Tree9");

	// This loads the tools library:

	TMVA::Tools::Instance();
	
	vector<int> CheckTrain (10,0);
	
	TString outfileName;
	std::string name_str;
	const char * name;
	int nBackgroundTrain;
	TCut preselectionCut;
	TMVA::IMethod* imethod;
	TMVA::MethodBase* method;
	float cut;
	int max = 0;
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	// number 0:
	
	
	// Create a new root output file:

	
	outfileName = "MulticlassNumbers0.root";			// output file with the results of the training and testing
	TFile* outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing
	
	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[0] = 1;
	TMVA::Factory *factory0 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )


	// add variables to the factory object with the same names as used in the root file
	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		
		// pixels that stay constant for every separate tree will give an error in root, thats why we will filter them out:
		
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{}
		else 
		{
		factory0->AddVariable( name,name,"units", 'F' );
		UsedPixels.push_back(i);
		}
	}

	
	//Add training and test trees to the factory object, signal is the number zero, the rest is background

	factory0->AddSignalTree (tree0,1);
	factory0->AddBackgroundTree (tree1,1);
	factory0->AddBackgroundTree (tree2,1);
	factory0->AddBackgroundTree (tree3,1);
	factory0->AddBackgroundTree (tree4,1);
	factory0->AddBackgroundTree (tree5,1);
	factory0->AddBackgroundTree (tree6,1);
	factory0->AddBackgroundTree (tree7,1);
	factory0->AddBackgroundTree (tree8,1);
	factory0->AddBackgroundTree (tree9,1);	
	
	
	// number of background training images:
	
	nBackgroundTrain = AT1 + AT2+ AT3+ AT4+ AT5+ AT6+ AT7+ AT8+ AT9;
	
	  
	preselectionCut = "";
	
	// select training and test data for signal and background:
	
	factory0->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT0)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");
	
	// book the boosted decision tree method:

	factory0->BookMethod(TMVA::Types::kBDT, "BDT0","");



	// Train MVAs using the set of training events
	factory0->TrainAllMethods();				

	// ---- Evaluate all MVAs using the set of test events
	factory0->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory0->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 0 is done!" << std::endl;
	
	
	imethod = factory0->GetMethod("BDT0");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	
	delete outputFile;
	delete factory0;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 1:
	
	
	
	outfileName = "MulticlassNumbers1.root";			// output file
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing

	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[1] = 1;
	
	TMVA::Factory *factory1 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )

	

	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		
		factory1->AddVariable( name,name,"units", 'F' );
		}
	}

	
	//Training and test trees adding to factory1:

	factory1->AddBackgroundTree (tree0,1);
	factory1->AddSignalTree (tree1,1);
	factory1->AddBackgroundTree (tree2,1);
	factory1->AddBackgroundTree (tree3,1);
	factory1->AddBackgroundTree (tree4,1);
	factory1->AddBackgroundTree (tree5,1);
	factory1->AddBackgroundTree (tree6,1);
	factory1->AddBackgroundTree (tree7,1);
	factory1->AddBackgroundTree (tree8,1);
	factory1->AddBackgroundTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT2+ AT3+ AT4+ AT5+ AT6+ AT7+ AT8+ AT9;
	
	  
	preselectionCut = "";
	factory1->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT1)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");
	
	
	factory1->BookMethod(TMVA::Types::kBDT, "BDT1","");


	// Train MVAs using the set of training events
	factory1->TrainAllMethods();				

	// ---- Evaluate all MVAs using the set of test events
	factory1->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory1->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 1 is done!" << std::endl;
	
	
	imethod = factory1->GetMethod("BDT1");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory1;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 2:
	
	
	outfileName = "MulticlassNumbers2.root";			// output file
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing
	
	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[2] = 1;

	TMVA::Factory *factory2 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )

	

	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		
		factory2->AddVariable( name,name,"units", 'F' );
		}
	}


	
	//Training and test trees adding to factory1:

	factory2->AddBackgroundTree (tree0,1);
	factory2->AddBackgroundTree (tree1,1);
	factory2->AddSignalTree (tree2,1);
	factory2->AddBackgroundTree (tree3,1);
	factory2->AddBackgroundTree (tree4,1);
	factory2->AddBackgroundTree (tree5,1);
	factory2->AddBackgroundTree (tree6,1);
	factory2->AddBackgroundTree (tree7,1);
	factory2->AddBackgroundTree (tree8,1);
	factory2->AddBackgroundTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT1+ AT3+ AT4+ AT5+ AT6+ AT7+ AT8+ AT9;
	
	  
	preselectionCut = "";
	factory2->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT2)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");
	

	
	factory2->BookMethod(TMVA::Types::kBDT, "BDT2","");


	// Train MVAs using the set of training events
	factory2->TrainAllMethods();			

	// ---- Evaluate all MVAs using the set of test events
	factory2->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory2->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 2 is done!" << std::endl;
	
	imethod = factory2->GetMethod("BDT2");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory2;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 3:
	
	
	
	outfileName = "MulticlassNumbers3.root";			// output file 
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing

	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[3] = 1;
	
	TMVA::Factory *factory3 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )


	
	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		
		factory3->AddVariable( name,name,"units", 'F' );
		}	
	}

	
	//Training and test trees adding to factory1:

	factory3->AddBackgroundTree (tree0,1);
	factory3->AddBackgroundTree (tree1,1);
	factory3->AddBackgroundTree (tree2,1);
	factory3->AddSignalTree (tree3,1);
	factory3->AddBackgroundTree (tree4,1);
	factory3->AddBackgroundTree (tree5,1);
	factory3->AddBackgroundTree (tree6,1);
	factory3->AddBackgroundTree (tree7,1);
	factory3->AddBackgroundTree (tree8,1);
	factory3->AddBackgroundTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT1+ AT2+ AT4+ AT5+ AT6+ AT7+ AT8+ AT9;
	
	  
	preselectionCut = "";
	factory3->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT3)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");
	
	
	factory3->BookMethod(TMVA::Types::kBDT, "BDT3","");


	// Train MVAs using the set of training events
	factory3->TrainAllMethods();		

	// ---- Evaluate all MVAs using the set of test events
	factory3->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory3->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 3 is done!" << std::endl;
	
	imethod = factory3->GetMethod("BDT3");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory3;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 4:
	
	
	outfileName = "MulticlassNumbers4.root";			// output file 
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing
	
	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[4] = 1;

	TMVA::Factory *factory4 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )


	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		
		factory4->AddVariable( name,name,"units", 'F' );
		}
	}

	
	//Training and test trees adding to factory1:

	factory4->AddBackgroundTree (tree0,1);
	factory4->AddBackgroundTree (tree1,1);
	factory4->AddBackgroundTree (tree2,1);
	factory4->AddBackgroundTree (tree3,1);
	factory4->AddSignalTree (tree4,1);
	factory4->AddBackgroundTree (tree5,1);
	factory4->AddBackgroundTree (tree6,1);
	factory4->AddBackgroundTree (tree7,1);
	factory4->AddBackgroundTree (tree8,1);
	factory4->AddBackgroundTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT2+ AT3+ AT1+ AT5+ AT6+ AT7+ AT8+ AT9;
	
	preselectionCut = "";
	factory4->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT4)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");
	
	
	factory4->BookMethod(TMVA::Types::kBDT, "BDT4","");


	// Train MVAs using the set of training events
	factory4->TrainAllMethods();				

	// ---- Evaluate all MVAs using the set of test events
	factory4->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory4->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 4 is done!" << std::endl;
	
	imethod = factory4->GetMethod("BDT4");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory4;
	
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 5:
	
	
	
	outfileName = "MulticlassNumbers5.root";			// output file 
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing

	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[5] = 1;

	TMVA::Factory *factory5 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )


	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		
		factory5->AddVariable( name,name,"units", 'F' );
		}
	}

	
	//Training and test trees adding to factory1:

	factory5->AddBackgroundTree (tree0,1);
	factory5->AddBackgroundTree (tree1,1);
	factory5->AddBackgroundTree (tree2,1);
	factory5->AddBackgroundTree (tree3,1);
	factory5->AddBackgroundTree (tree4,1);
	factory5->AddSignalTree (tree5,1);
	factory5->AddBackgroundTree (tree6,1);
	factory5->AddBackgroundTree (tree7,1);
	factory5->AddBackgroundTree (tree8,1);
	factory5->AddBackgroundTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT2+ AT3+ AT4+ AT1+ AT6+ AT7+ AT8+ AT9;
	  
	preselectionCut = "";
	factory5->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT5)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");
	
	
	factory5->BookMethod(TMVA::Types::kBDT, "BDT5","");


	// Train MVAs using the set of training events
	factory5->TrainAllMethods();			

	// ---- Evaluate all MVAs using the set of test events
	factory5->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory5->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 5 is done!" << std::endl;
	
	imethod = factory5->GetMethod("BDT5");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory5;
	
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 6:
	
	
	outfileName = "MulticlassNumbers6.root";			// output file
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing

	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[6] = 1;

	TMVA::Factory *factory6 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )
	

	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		
		factory6->AddVariable( name,name,"units", 'F' );
		}
	}

	
	//Training and test trees adding to factory1:

	factory6->AddBackgroundTree (tree0,1);
	factory6->AddBackgroundTree (tree1,1);
	factory6->AddBackgroundTree (tree2,1);
	factory6->AddBackgroundTree (tree3,1);
	factory6->AddBackgroundTree (tree4,1);
	factory6->AddBackgroundTree (tree5,1);
	factory6->AddSignalTree (tree6,1);
	factory6->AddBackgroundTree (tree7,1);
	factory6->AddBackgroundTree (tree8,1);
	factory6->AddBackgroundTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT2+ AT3+ AT4+ AT5+ AT1+ AT7+ AT8+ AT9;
	  
	preselectionCut = "";
	factory6->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT6)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");

	
	factory6->BookMethod(TMVA::Types::kBDT, "BDT6","");


	// Train MVAs using the set of training events
	factory6->TrainAllMethods();	

	// ---- Evaluate all MVAs using the set of test events
	factory6->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory6->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 6 is done!" << std::endl;
	
	imethod = factory6->GetMethod("BDT6");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory6;
	
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 7:
	
	
	
	outfileName = "MulticlassNumbers7.root";			// output file
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing

	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[7] = 1;
	
	TMVA::Factory *factory7 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )
	


	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		
		factory7->AddVariable( name,name,"units", 'F' );
		}
	}


	
	//Training and test trees adding to factory1:

	factory7->AddBackgroundTree (tree0,1);
	factory7->AddBackgroundTree (tree1,1);
	factory7->AddBackgroundTree (tree2,1);
	factory7->AddBackgroundTree (tree3,1);
	factory7->AddBackgroundTree (tree4,1);
	factory7->AddBackgroundTree (tree5,1);
	factory7->AddBackgroundTree (tree6,1);
	factory7->AddSignalTree (tree7,1);
	factory7->AddBackgroundTree (tree8,1);
	factory7->AddBackgroundTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT2+ AT3+ AT4+ AT5+ AT6+ AT1+ AT8+ AT9;
	
	
	preselectionCut = "";
	factory7->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT7)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");
	
	
	factory7->BookMethod(TMVA::Types::kBDT, "BDT7","");


	// Train MVAs using the set of training events
	factory7->TrainAllMethods();		

	// ---- Evaluate all MVAs using the set of test events
	factory7->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory7->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 7 is done!" << std::endl;
	
	
	imethod = factory7->GetMethod("BDT7");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory7;
	
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 8:
	
	
	outfileName = "MulticlassNumbers8.root";			// output file
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing

	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[8] = 1;

	TMVA::Factory *factory8 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )


	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		factory8->AddVariable( name,name,"units", 'F' );
		}
		
	}

	
	//Training and test trees adding to factory1:

	factory8->AddBackgroundTree (tree0,1);
	factory8->AddBackgroundTree (tree1,1);
	factory8->AddBackgroundTree (tree2,1);
	factory8->AddBackgroundTree (tree3,1);
	factory8->AddBackgroundTree (tree4,1);
	factory8->AddBackgroundTree (tree5,1);
	factory8->AddBackgroundTree (tree6,1);
	factory8->AddBackgroundTree (tree7,1);
	factory8->AddSignalTree (tree8,1);
	factory8->AddBackgroundTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT2+ AT3+ AT4+ AT5+ AT6+ AT7+ AT1+ AT9;
	
	  
	preselectionCut = "";
	factory8->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT8)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");

	
	factory8->BookMethod(TMVA::Types::kBDT, "BDT8","");


	// Train MVAs using the set of training events
	factory8->TrainAllMethods();			

	// ---- Evaluate all MVAs using the set of test events
	factory8->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory8->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 8 is done!" << std::endl;
	
	imethod = factory8->GetMethod("BDT8");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory8;
	
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// number 9:
	
	
	
	outfileName = "MulticlassNumbers9.root";			// output file
	outputFile = TFile::Open( outfileName, "CREATE" );		// open the file for writing
	
	
	if (!outputFile)
	{cuts.push_back(0);}else
	{
	CheckTrain[9] = 1;

	TMVA::Factory *factory9 = new TMVA::Factory( "TMVAMulticlass", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );	// TMVA object
	//( "<JobName>", outputFile, "<options>" )


	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{
		}
		else 
		{
		factory9->AddVariable( name,name,"units", 'F' );
		}
		
	}

	
	//Training and test trees adding to factory1:

	factory9->AddBackgroundTree (tree0,1);
	factory9->AddBackgroundTree (tree1,1);
	factory9->AddBackgroundTree (tree2,1);
	factory9->AddBackgroundTree (tree3,1);
	factory9->AddBackgroundTree (tree4,1);
	factory9->AddBackgroundTree (tree5,1);
	factory9->AddBackgroundTree (tree6,1);
	factory9->AddBackgroundTree (tree7,1);
	factory9->AddBackgroundTree (tree8,1);
	factory9->AddSignalTree (tree9,1);	
	
	nBackgroundTrain = AT0 + AT2+ AT3+ AT4+ AT5+ AT6+ AT7+ AT8+ AT1;
	
	  
	preselectionCut = "";
	factory9->PrepareTrainingAndTestTree( preselectionCut, "nTrain_Signal="+std::to_string(AT9)+":nTrain_Background="+std::to_string(nBackgroundTrain)+":nTest_Signal=0:nTest_Background=0:SplitMode=Block:NormMode=NumEvents");
	
	
	factory9->BookMethod(TMVA::Types::kBDT, "BDT9","");


	// Train MVAs using the set of training events
	factory9->TrainAllMethods();		

	// ---- Evaluate all MVAs using the set of test events
	factory9->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory9->EvaluateAllMethods();

	// --------------------------------------------------------------


	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification 9 is done!" << std::endl;
	
	imethod = factory9->GetMethod("BDT9");
	method = dynamic_cast<TMVA::MethodBase*> (imethod);
	cut = method->GetSignalReferenceCut();
	
	cuts.push_back(cut);
	
	delete outputFile;
	delete factory9;
	
	}
	
	//////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////////////////////////////
		if (CheckTrain[0] == 0)
	{cuts[0] = 0.0053;}
		if (CheckTrain[1] == 0)
	{cuts[1] = -0.0488;}
		if (CheckTrain[2] == 0)
	{cuts[2] = -0.0429;}
		if (CheckTrain[3] == 0)
	{cuts[3] = 0.0237;}
		if (CheckTrain[4] == 0)
	{cuts[4] = 0.109;}
		if (CheckTrain[5] == 0)
	{cuts[5] = -0.0128;}
		if (CheckTrain[6] == 0)
	{cuts[6] = -0.0844;}
		if (CheckTrain[7] == 0)
	{cuts[7] = 0.0651;}
		if (CheckTrain[8] == 0)
	{cuts[8] = 0.0103;}
		if (CheckTrain[9] == 0)
	{cuts[9] = 0.0392;}

	
	/////////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////////
	
		// read the data from the root file:
	

	if (CheckTrain[0] == 0)
	{
	std::string name_str;
	const char * name;
	

	int max = 0;
	for(int i = 0; i < 784; i++) 
	{
		name_str = "pixel" + std::to_string(i);
		name = name_str.c_str();
		
		if (tree0->GetMaximum(name) <= max || tree1->GetMaximum(name) <= max || tree2->GetMaximum(name) <= max || tree3->GetMaximum(name) <= max || tree4->GetMaximum(name) <= max || tree5->GetMaximum(name) <= max || tree6->GetMaximum(name) <= max || tree7->GetMaximum(name) <= max || tree8->GetMaximum(name) <= max || tree9->GetMaximum(name) <= max ) 
		{}
		else 
		{
		UsedPixels.push_back(i);
		}
	}
	}


	////////////////////////////////////////////////////////////////////////////////////
	
		

	vector<float> Data = evaluate(); // training error, validation error, ....


	cout << "TrainingError " << Data.at(0) << '\n' 
	     << "ValidationError " << Data.at(1) << '\n'
  	     << "TruePositive " << Data.at(2) << '\n'
	     << "TrueNegative " << Data.at(3) << '\n'
	     << "FalsePositive " << Data.at(4) << '\n'
	     << "FalseNegative " << Data.at(5) << '\n';


	return Data; 

	}


vector<float> propagateRoot::evaluate()
{
	cout << "Evaluating with " << TestImages.size() << " test images." << endl;

	TrainingError = 0;
	ValidationError = 0;
	float TP = 0;
	float TN = 0;
	float FP = 0;
	float FN = 0;

	vector<float> a;
	vector<float> y;

	//for (size_t i=0; i<TestImages.size(); ++i)
        for (size_t i=0; i<4; ++i)
	{
		a = propagateRoot::Application( TestImages.at(i)->getConcatenatedColumns() );	
		y = propagateRoot::IntToVec(TestImages.at(i)->getRealNumber());	
		ValidationError = ValidationError + propagateRoot::costFunc(a, y);
		
		cout<<"test: "<<i<<endl;

		for (size_t j=0; j<a.size(); ++j)
		{
			if (a.at(j)<cuts.at(j) && y.at(j)==0)
				{ ++TN; }
			else if (a.at(j)<cuts.at(j) && y.at(j)==1)
				{ ++FN; }
			else if (a.at(j)>cuts.at(j) && y.at(j)==0)
				{ ++FP; }
			else
				{ ++TP; }
		}
	}
	
	vector<float> b;
	vector<float> z;
	
	//for (size_t i=0; i<TrainImages.size(); ++i)
        for (size_t i=0; i<4; ++i)
	{
		cout<<"train: "<<i<<endl;
	
		b = propagateRoot::Application( TrainImages.at(i)->getConcatenatedColumns() );
		z = propagateRoot::IntToVec(TrainImages.at(i)->getRealNumber());		
		TrainingError = TrainingError + propagateRoot::costFunc(b, z);	
	}


	TrainingError = TrainingError/TrainImages.size();
	ValidationError = ValidationError/TestImages.size();

	vector<float> Data = {TrainingError, ValidationError, TP, TN, FP, FN};

	return Data;
}

vector<float> propagateRoot::IntToVec(float a)
{
	vector<float>  L(10,0.0);
	L.at(a)=1.0;             //vector begint met element 0.
	return L;
}


float propagateRoot::costFunc(vector<float> estimate,vector<float> result){
	float C = 0;
		for (unsigned int i=0; i<estimate.size(); ++i)
		{
			C = C + pow(result.at(i)-estimate.at(i),2);
		}
	return C/2;
}


tuple<vector<int>,vector<vector<float>>> propagateRoot::evaluateHistogram()
{
    vector<int> listNumbers;
    vector<vector<float>> outputs;
    for (size_t i=0; i<TestImages.size(); ++i)
    {
            outputs.push_back(propagateRoot::Application(TestImages.at(i)->getConcatenatedColumns()));
            listNumbers.push_back(TestImages.at(i)->getRealNumber());
    }
    return make_tuple(listNumbers,outputs);
}


vector <float> propagateRoot::Application(vector<float> image){

	pixel.clear();
	value.clear();
	
	for(unsigned int i = 0; i < UsedPixels.size(); i++) 
	{
		pixel.push_back(image.at(UsedPixels[i]));
	}
	


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// make the reader object for evaluation:
	
	TMVA::Reader* reader0 = new TMVA::Reader( "" );

	// add variables to the reader object with the same names as used in the root file
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
	
		reader0->AddVariable(name, &pixel[i]);
	}
	
		reader0->BookMVA( "BDT0", "weights/TMVAMulticlass_BDT0.weights.xml" );
	
	
	// Classifier response

	value.push_back (reader0->EvaluateMVA( "BDT0" ));
	delete reader0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader1 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader1->AddVariable(name, &pixel[i]);
	}
	
		reader1->BookMVA( "BDT1", "weights/TMVAMulticlass_BDT1.weights.xml" );


	
	// Classifier response
	
	value.push_back (reader1->EvaluateMVA( "BDT1" ));

	delete reader1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader2 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader2->AddVariable(name, &pixel[i]);
	}
	
		reader2->BookMVA( "BDT2", "weights/TMVAMulticlass_BDT2.weights.xml" );

	
	// Classifier response
	
	value.push_back (reader2->EvaluateMVA( "BDT2" ));

	delete reader2;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader3 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader3->AddVariable(name, &pixel[i]);
	}
	
		reader3->BookMVA( "BDT3", "weights/TMVAMulticlass_BDT3.weights.xml" );

	
	// Classifier response
	
	value.push_back (reader3->EvaluateMVA( "BDT3" ));

	delete reader3;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader4 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader4->AddVariable(name, &pixel[i]);
	}
	
		reader4->BookMVA( "BDT4", "weights/TMVAMulticlass_BDT4.weights.xml" );

	
	// Classifier response
	
	value.push_back (reader4->EvaluateMVA( "BDT4" ));


	delete reader4;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader5 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader5->AddVariable(name, &pixel[i]);
	}
	
		reader5->BookMVA( "BDT5", "weights/TMVAMulticlass_BDT5.weights.xml" );


	
	// Classifier response
	
	value.push_back (reader5->EvaluateMVA( "BDT5" ));

	delete reader5;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader6 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader6->AddVariable(name, &pixel[i]);
	}
	
		reader6->BookMVA( "BDT6", "weights/TMVAMulticlass_BDT6.weights.xml" );

	
	// Classifier response
	
	value.push_back (reader6->EvaluateMVA( "BDT6" ));
	

	delete reader6;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader7 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader7->AddVariable(name, &pixel[i]);
	}
	
		reader7->BookMVA( "BDT7", "weights/TMVAMulticlass_BDT7.weights.xml" );

	
	// Classifier response
	
	value.push_back (reader7->EvaluateMVA( "BDT7" ));
	

	delete reader7;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader8 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader8->AddVariable(name, &pixel[i]);
	}
	
		reader8->BookMVA( "BDT8", "weights/TMVAMulticlass_BDT8.weights.xml" );

	
	// Classifier response
	
	value.push_back ( reader8->EvaluateMVA( "BDT8" ));
	

	delete reader8;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	TMVA::Reader* reader9 = new TMVA::Reader( "" );
	
	for(unsigned int i = 0; i < pixel.size(); i++) 
	{
		name_str = "pixel" + std::to_string(UsedPixels[i]);
		name = name_str.c_str();
		reader9->AddVariable(name, &pixel[i]);
	}
	
		reader9->BookMVA( "BDT9", "weights/TMVAMulticlass_BDT9.weights.xml" );


	
	// Classifier response
	
	value.push_back (reader9->EvaluateMVA( "BDT9" ));


	delete reader9;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	cout<<"evaluation 0: "<<value[0]<<endl;
	cout<<"evaluation 1: "<<value[1]<<endl;
	cout<<"evaluation 2: "<<value[2]<<endl;
	cout<<"evaluation 3: "<<value[3]<<endl;
	cout<<"evaluation 4: "<<value[4]<<endl;
	cout<<"evaluation 5: "<<value[5]<<endl;
	cout<<"evaluation 6: "<<value[6]<<endl;
	cout<<"evaluation 7: "<<value[7]<<endl;
	cout<<"evaluation 8: "<<value[8]<<endl;
	cout<<"evaluation 9: "<<value[9]<<endl;
	
	std::cout <<"The computer thinks it is: "<< std::distance(value.begin(), std::max_element(value.begin(), value.end()))<<endl;

	return value;
}

*/


