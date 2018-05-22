#include <vector>
#include "opencv2/opencv.hpp"

#include "testimage.h"

using namespace std;
using namespace cv;

testimage::testimage(vector<uchar> ImageVec, int RN)				// Constructor. Takes a vector<uchar> containing pixels, and the real number.
{
	RealNumber=RN;
	ImageMat=convertToMat(ImageVec);
}

testimage::~testimage()								// Destructor.
{ }

int testimage::getRealNumber()							// Gertfunction for real number.
{
	return RealNumber;
}

vector<float> testimage::getConcatenatedColumns()				// Getfunction to create a vector<float> from the Mat.
{
	// Preallocate memory for two vectors, one with uchars, and one with floats. This is done because the input is in uchar, but the output needs to be floats.
	vector<uchar> ImageVec(784);
	vector<float> ImageVecF(784);

	int counter=0;								// Counter to access vector at the right place.
	for(int i=0;i<ImageMat.rows;i++)					// Loop over rows and columns of the Matrix.
	{
		for(int j=0;j<ImageMat.cols;j++)
		{
			ImageVec.at(counter)=ImageMat.at<uchar>(j, i);		// Fill vector with uchars. Immediate conversion to floats here was not possible.
			counter++;
		}
	}
		
	for (int i = 0; i < 784; i++)
	{
		ImageVecF.at(i) = (float)ImageVec.at(i);			// Convert uchar to float.
	}

	
	return ImageVecF;							// Return the vector<float>.
}

Mat testimage::getMat()								// Getfunction for the matrix containing the image.
{
	return ImageMat;
}

Mat testimage::convertToMat(vector<uchar> ImageVec)				// Convert the vector to a matrix. This is done in uchar to minimize memory usage.
{
	Mat MatImage = Mat::zeros(Size(28, 28), CV_8UC1);			// Initiate a 28 x 28 matrix taking uchars.
	int counter=0;								// Counter to access vector at the right place.
	for (int col=0; col<28; col++)						// Loop over rows and columns. 
	{
		for (int row=0; row<28; row++)
		{
			MatImage.at<uchar>(col, row) = ImageVec.at(counter);	// Fill matrix with elements of the vector.
			counter++;
		}
	}

	return MatImage;							// Return the matrix. 
}
