/**
 * @file   svdisparity.cpp
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Tue Feb  7 16:37:44 2012
 * 
 * @brief  
 * 
 * 
 */

#include "svdisparity.h"


void createDisparityMapBM(CvArr * img1, CvArr * img2,
						  int numberOfDisparities, int maxIters)
{
	CvSize imageSize = cvGetSize(img1);
	
	CvMat* disp = cvCreateMat( imageSize.height,
							   imageSize.width, CV_16S );

	//Setup for finding stereo corrrespondences
	CvStereoBMState *BMState = cvCreateStereoBMState();
	assert(BMState != 0);
	BMState->preFilterSize=41;
	BMState->preFilterCap=31;

	// window size
	BMState->SADWindowSize=41;

	// depth range 
	// BMState->minDisparity=-64;
	// BMState->numberOfDisparities=128;
	BMState->minDisparity=-16;
	BMState->numberOfDisparities=32;

	BMState->textureThreshold=10;
	BMState->uniquenessRatio=15;

	if( img1 && img2 )
	{
		// CvMat part;
		// void cvRemap( const CvArr* src, CvArr* dst,
		//               const CvArr* mapx, const CvArr* mapy)
		// FUNCTION: dst(x,y)<-src(mapx(x,y),mapy(x,y))

		// cvRemap( img1, img1r, mx1, my1 );
		// cvRemap( img2, img2r, mx2, my2 );

		// if( !isVerticalStereo || useUncalibrated != 0 )
		{
			// When the stereo camera is oriented vertically,
			// useUncalibrated==0 does not transpose the
			// image, so the epipolar lines in the rectified
			// images are vertical. Stereo correspondence
			// function does not support such a case.

			// cvFindStereoCorrespondenceBM( img1r, img2r, disp,
			// 							  BMState);
			cvFindStereoCorrespondenceBM( img1, img2, disp,
										  BMState);

			// cvNormalize( disp, vdisp, 0, 256, CV_MINMAX );
		}
	cvReleaseStereoBMState(&BMState);


	CvMat* disparity_left_visual =
		cvCreateMat( imageSize.height, imageSize.width, CV_8U );
	// because the values in the left disparity images are usually negative
	cvConvertScale( disp, disparity_left_visual, 1 );
	// cvSave( "disparity.pgm", disparity_left_visual );
	cvSaveImage( "disparity.pgm", disparity_left_visual );
	}
}



void createDisparityMapGC(CvArr * img1, CvArr * img2,
						  int numberOfDisparities, int maxIters)
{
	CvSize imageSize = cvGetSize(img1);

	// image_left and image_right are the input 8-bit single-channel images
	// from the left and the right cameras, respectively
	// CvSize size = cvGetSize(image_left);
	CvMat* disparity_left = cvCreateMat( imageSize.height, imageSize.width,
										 CV_16S );
	CvMat* disparity_right = cvCreateMat( imageSize.height, imageSize.width,
										  CV_16S );

	// (int numberOfDisparities, int maxIters)
	CvStereoGCState* state = cvCreateStereoGCState( 16, // numberOfDisparities
													2   //maxIters
													);

	cvFindStereoCorrespondenceGC( img1, img2,
								  disparity_left, disparity_right, state, 0 );
	cvReleaseStereoGCState( &state );

	CvMat* disparity_left_visual =
		cvCreateMat( imageSize.height, imageSize.width, CV_8U );
	// because the values in the left disparity images are usually negative
	cvConvertScale( disparity_left, disparity_left_visual, -16 );
	// cvSave( "disparity.pgm", disparity_left_visual );
	cvSaveImage( "disparity.pgm", disparity_left_visual );
}
