#ifndef BATCH_H
#define BATCH_H

#include <string>
#include <vector>
#include <memory>

#include "testimage.h"

using namespace std;

class batch
{
public:
	batch(string ImageSetName, string LabelSetName);			// Constructor, takes the filename of the imagefile and the filename of the labels. Assumes these files are in the same folder.
	~batch();								// Destructor.
	void loadBatch(string ImageSetName, string LabelSetName);		// Loads the files. Calls readImageHeader, readLabelHeader, readImages and readLabels.
	vector<shared_ptr<testimage>> getTestImages();				// Getfunction for the TestImages.
	
	
protected:
	vector<int> readImageHeader(string ImageSetName);			// Reads the header of the image file, to get numbers like how many images there are in the file and the size of the images.
	vector<int> readLabelHeader(string LabelSetName);			// Reads the header of the label file, to know how many labels there are in the file.
	vector<vector<uchar>> readImages(string ImageSetName, int Rows, int Cols, int NumberOfImages);	// Reads the images and stores each one of them in a vector. Uses the info provided by readImageHeader. 
	vector<int> readLabels(string LabelSetName, int NumberOfLabels);	// Reads the labels, to be able to link the true number with each image.
	
	vector<shared_ptr<testimage>> TestImages;				// This vector contains the entire batch. Each element of this vector is a shared pointer to a testimage-object. 

private:
	batch(const batch&);							// Copy constructor
};

#endif
