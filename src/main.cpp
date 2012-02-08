/**
 * @file   main.cpp
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Sat Feb  4 20:13:45 2012
 * 
 * @brief  
 * 
 * 
 */

#include "cv.h"
#include "cxmisc.h"
#include "highgui.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>

#include "svdisparity.h"
#include "svfeature.h"

#include "utility.h"

using std::vector;
using std::string;

// void createDisparityMapGC(CvArr * img1, CvArr * img2,
// 						  int numberOfDisparities, int maxIters);

int main(int argc, char* argv[])
{
	// StereoCalib("test.txt", 9, 6, 1);
	IplImage* img1 = cvLoadImage("../data/test_l.jpg",0);
	IplImage* img2 = cvLoadImage("../data/test_r.jpg",0);
	if (img1==NULL || img2==NULL) {
		printf("Can't read one of the images\n");
		return -1;
	}
	extractFeatureSURF(img1);
	extractFeatureKLT(img1, img2);

    CvSize imageSize = {0,0};
	imageSize = cvGetSize(img1);
	assert(cvGetSize(img2) == cvGetSize(img1));
    // bool isVerticalStereo = false; //OpenCV can handle left-right
	// int useUncalibrated = 1;

	int numberOfDisparities = 16;
	int maxIters = 2;

	void (*createDisparityMap)(CvArr * img1, CvArr * img2,
							   int numberOfDisparities, int maxIters);
	createDisparityMap = createDisparityMapBM;

	createDisparityMap(img1, img2, // imageSize,
					   numberOfDisparities, maxIters);

	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );
	
#ifdef __linux__
	// show dispairty map with external program
	fprintf(stderr, "display: disparity");
	system("display disparity.pgm"); 
#endif //__linux__
	return 0;
}
