#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include "batch.h"
#include "testimage.h"

using namespace std;

batch::batch(string ImageSetName, string LabelSetName)				// Takes the filenames of the image-file and the file with the labels, and calls "loadBatch".
{
	loadBatch(ImageSetName, LabelSetName);
	cout << "Batch with images at " << ImageSetName << " and labels at " << LabelSetName << " was loaded correctly." << endl; 
}

batch::~batch()									// Destructor.
{ }

void batch::loadBatch(string ImageSetName, string LabelSetName)
{
	vector<int> ImageHeaderData=readImageHeader(ImageSetName);		// Get the data (e.g. how many images, how many columns and how many rows) from the header from the imagefiles.
	vector<int> LabelHeaderData=readLabelHeader(LabelSetName);		// Get the data (most useful is the number of labels) from the header from the imagefiles.

	vector<vector<uchar>> ImageVec = readImages(ImageSetName, ImageHeaderData.at(2), ImageHeaderData.at(3), ImageHeaderData.at(1));		//Actual loading of the images happens here.
	vector<int> LabelVec = readLabels(LabelSetName, LabelHeaderData.at(1));	// The reading of the labels themselves is done by this function.

	TestImages.resize(ImageHeaderData.at(1));				// Resize TestImages to preallocate memory. This is done as soon as the length needed to contain the images is known.

	for(int i=0; i<ImageHeaderData.at(1); i++)				// For-loop to fill TestImages with testimages.
	{	
		// We chose for smart pointers because they allow for more robust memory management, especially with the amount of testimages we're dealing with. 	
		shared_ptr<testimage> ImagePtr(new testimage(ImageVec.at(i),LabelVec.at(i)));
		TestImages.at(i)=ImagePtr;
	}
}

vector<shared_ptr<testimage>> batch::getTestImages()				// getfunction for TestImages.
{
	return TestImages;
}

vector<int> batch::readImageHeader(string ImageSetName)				// Reading in the header of the image file.
{
	// Function to flip the bytes of the header. For more documentation on why this needs to be done, we refer
	// to the documentation on the MNIST database, and the report on this section. For this, we used code from Jürgen Brauer (for full references, see report).

	auto reverseInt = [](int i) 						
	{
	unsigned char c1, c2, c3, c4;
	c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
  	};

	vector<int> ImageHeaderData(4);						// Preallocate space for the vector containing the data of the images.

	ifstream file(ImageSetName, ios::binary);				// Here, we say that the file is in binary.
 
	if (file.is_open()) 
	{
	int MagicNumber = 0;							// Initialize the integers which will contain the data. This is needed because the 'read' function, called on a file, 
	int NumberOfImages = 0;							// needs an existing variable to store the read data to.
	int Rows = 0;
	int Cols = 0;

	file.read((char *)&MagicNumber, sizeof(MagicNumber));			// Read the first number, the so-called 'magic number'. If this equals 2051, then it is indeed a file containing images.
	ImageHeaderData.at(0) = reverseInt(MagicNumber);			// Reverse the number and save it to the first element of the ImageHeaderData-vector.

	if (ImageHeaderData.at(0) != 2051)					// Check whether this is indeed a file of MNIST images. This is also a check to make sure the data is being read correctly.
	{
		cerr << "This is not a MNIST image file!" << endl;
		exit(1);
	}

	file.read((char *)&NumberOfImages, sizeof(NumberOfImages));		// Read the next data-elements from the file.
	file.read((char *)&Rows, sizeof(Rows));
	file.read((char *)&Cols, sizeof(Cols));

	ImageHeaderData.at(1) = reverseInt(NumberOfImages);			// Reverse the bytes for these values, and put them in the other slots of the ImageHeaderData-vector.
	ImageHeaderData.at(2) = reverseInt(Rows);
	ImageHeaderData.at(3) = reverseInt(Cols);

	return ImageHeaderData;							// Return all the info from the image file header, so it can be used in next functions.
	
	}
	else									// If anything goes wrong with opening the file, a error is given. The most likely explanation for this to happen is 
	{									// that the MNIST datafiles are not present in the folder, or the name of the file has been entered wrong.
		cerr << "Could not open file" << endl;
		exit(1);
	}

}

vector<int> batch::readLabelHeader(string LabelSetName)				// Reading in the header of the label file.
{
	// Function to flip the bytes of the header. For more documentation on why this needs to be done, we refer
	// to the documentation on the MNIST database, and the report on this section. For this, we used code from Jürgen Brauer (for full references, see report).
	auto reverseInt = [](int i) 
	{
	unsigned char c1, c2, c3, c4;
	c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
  	};

	vector<int> LabelHeaderData(2);						// Preallocate space for the vector containing the data of the labels.

	ifstream file(LabelSetName, ios::binary);				// Here, we say that the file is in binary.
 
	if (file.is_open()) 
	{
	int MagicNumber = 0;							// Initialize the integers which will contain the data. This is needed because the 'read' function, called on a file,
	int NumberOfLabels = 0;							// needs an existing variable to store the read data to.

	file.read((char *)&MagicNumber, sizeof(MagicNumber));			// Read the first number, the so-called 'magic number'. If this equals 2049, then it is indeed a file containing labels.
	LabelHeaderData.at(0) = reverseInt(MagicNumber);			// Reverse the number and save it to the first element of the LabelHeaderData-vector.

	if (LabelHeaderData.at(0) != 2049)					// Check whether this is indeed a file of MNIST labels. This is also a check to make sure the data is being read correctly.
	{
		cerr << "This is not a MNIST label file!" << endl;
		exit(1);
	}

	file.read((char *)&NumberOfLabels, sizeof(NumberOfLabels));		// Read the other data-element from the file.

	LabelHeaderData.at(1) = reverseInt(NumberOfLabels);			// Reverse the bytes, and put them in the other slot of the LabelHeaderData-vector.

	return LabelHeaderData;							// Return all the info from the label file header, so it can be used in next functions.
	
	}
	else									// If anything goes wrong with opening the file, a error is given. The most likely explanation for this to happen is 
	{									// that the MNIST datafiles are not present in the folder, or the name of the file has been entered wrong.
		cerr << "Could not open file" << endl;
		exit(1);
	}
}

vector<vector<uchar>> batch::readImages(string ImageSetName, int Rows, int Cols, int NumberOfImages)
{
	ifstream file(ImageSetName, ios::binary);				// Tell the system we are dealing with a binary file.
 
	if (file.is_open()) 
	{
		// Since uchars are 1 byte variables, and the pixels are as well, we chose to initially store the pixels as uchars, to reduce memory usage.
		vector<uchar> Image(Cols*Rows);					// Preallocate memory to contain the data.
		vector<vector<uchar>> Images(NumberOfImages,Image);
		
		// Since the first 4 numbers of the file, with 4 bytes for each number, have been read already, the cursor 
		// to read the file is set to start reading at the 17th byte, which is the first pixelvalue.
		file.seekg(16);
		
		for (int i = 0; i < NumberOfImages; i++)			// Loop over all the images in the file.
		{
			for (int n = 0; n < Rows*Cols; n++)			// Loop in every image over the pixels of this image.
  			{
				file.read((char*)&(Images.at(i).at(n)), 1);	// Read the values of the pixels, and store them in the right place.
			}
		}
	return Images;								// Return the vector containing the pixels for each image. 
	}
	else									// If anything goes wrong with opening the file, a error is given. The most likely explanation for this to happen is 
	{									// that the MNIST datafiles are not present in the folder, or the name of the file has been entered wrong.
		cerr << "Could not open file" << endl;
		exit(1);
	}
}

vector<int> batch::readLabels(string LabelSetName, int NumberOfLabels)
{
	ifstream file(LabelSetName, ios::binary);				// Tell the system we are dealing with a binary file.
 
	if (file.is_open()) 
	{
		vector<int> Labels(NumberOfLabels,0);				// Preallocate memory to contain the data.

		// Since the first 4 numbers of the file, with 4 bytes for each number, have been read already, the cursor 
		// to read the file is set to start reading at the 17th byte, which is the first pixelvalue.
		file.seekg(8);

		for (int i = 0; i < NumberOfLabels; i++)			// Loop over all the labels in the file.
		{
			file.read((char*)&(Labels.at(i)), 1);			// Read the values of the labels, and store them in the right place.
		}
	return Labels;								// Return the vector containing the value for each label. 
	}
	else									// If anything goes wrong with opening the file, a error is given. The most likely explanation for this to happen is 
	{									// that the MNIST datafiles are not present in the folder, or the name of the file has been entered wrong.
		cerr << "Could not open file" << endl;
		exit(1);
	}
}
