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

#include "svutility.h"

using std::vector;
using std::string;

// void createDisparityMapGC(CvArr * img1, CvArr * img2,
// 						  int numberOfDisparities, int maxIters);

int main(int argc, char* argv[])
{
	// StereoCalib("test.txt", 9, 6, 1);
#if 0
	IplImage* img1 = cvLoadImage("../data/test_l.jpg",1);
	IplImage* img2 = cvLoadImage("../data/test_r.jpg",1);
#else
	IplImage* img1 = cvLoadImage("../data/milkbox_test_l.jpg",1);
	IplImage* img2 = cvLoadImage("../data/milkbox_test_r.jpg",1);
#endif
	IplImage * im1_gray = cvCreateImage(cvGetSize(img1), 8, 1);
	IplImage * im2_gray = cvCreateImage(cvGetSize(img2), 8, 1);
	cvCvtColor(img1, im1_gray, CV_RGB2GRAY);
	cvCvtColor(img2, im2_gray, CV_RGB2GRAY);
	
	if (img1==NULL || img2==NULL) {
		printf("Can't read one of the images\n");
		return -1;
	}
	// extractFeatureSURF(im1_gray);
	extractFeatureKLT(im1_gray, im2_gray);

    CvSize imageSize = {0,0};
	imageSize = cvGetSize(im1_gray);
	assert(cvGetSize(img2) == cvGetSize(img1));
    // bool isVerticalStereo = false; //OpenCV can handle left-right
	// int useUncalibrated = 1;

	int numberOfDisparities = 16;
	int maxIters = 2;

	CvMat * (*createDisparityMap)(CvArr * , CvArr * , int , int );
	createDisparityMap = createDisparityMapBM;

	CvMat * left_disparity =
		createDisparityMap(im1_gray, im2_gray, numberOfDisparities, maxIters);
	//cvSaveImage("tmp/disparity.pgm", left_disparity);
	svShowImage(left_disparity);

	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );
	cvReleaseImage( &im1_gray );
	cvReleaseImage( &im2_gray );
	
    // if(1 /* point_cloud_filename */)
    // {
    //     printf("storing the point cloud...");
    //     fflush(stdout);
    //     CvMat xyz; CvMat Q;
    //     // reprojectImageTo3D(disp, xyz, Q, true);
    //     cvReprojectImageTo3D(left_disparity, &xyz, &Q);
	// }
	
	return 0;
}
