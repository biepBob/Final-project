#ifndef TESTIMAGE_H
#define TESTIMAGE_H

#include <vector>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class testimage
{
public:
	testimage(vector<uchar> Image, int RN);				// Constructor. Takes a vector<uchar> containing the pixel values, and the real number that is written. 
	~testimage();							// Destructor.
	int getRealNumber();						// Getfunction for the real number.
	vector<float> getConcatenatedColumns();				// Getfunction for a vector containing the pixelvalues in floats.
	Mat getMat();							// Getfunction for the matrix.

protected:
	Mat convertToMat(vector<uchar> ImageVec);			// Converts the vector<uchar> to a Mat object.

	int RealNumber;							// The real number that is depicted.
	Mat ImageMat;							// The matrix of the image.
	

private:
	testimage(const testimage&);					// Copy constructor.
};

#endif
