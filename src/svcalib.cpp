/**
 * @file   svcalib.cpp
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Tue Feb  7 22:45:16 2012
 * 
 * @brief  
 * 
 * 
 */

#include "svcalib.h"



#if 0
// ARRAY AND VECTOR STORAGE:
double M1[3][3], M2[3][3], D1[5], D2[5];
double R[3][3], T[3], E[3][3], F[3][3];
CvMat _M1 = cvMat(3, 3, CV_64F, M1 );
CvMat _M2 = cvMat(3, 3, CV_64F, M2 );
CvMat _D1 = cvMat(1, 5, CV_64F, D1 );
CvMat _D2 = cvMat(1, 5, CV_64F, D2 );
CvMat _R = cvMat(3, 3, CV_64F, R );
CvMat _T = cvMat(3, 1, CV_64F, T );
CvMat _E = cvMat(3, 3, CV_64F, E );
CvMat _F = cvMat(3, 3, CV_64F, F );

vector<CvPoint2D32f> points[2];
CvMat _imagePoints1 = cvMat(1, N, CV_32FC2, &points[0][0] );
CvMat _imagePoints2 = cvMat(1, N, CV_32FC2, &points[1][0] );

#endif	
	
#if 0
CvMat* mx1 = cvCreateMat( imageSize.height,
						  imageSize.width, CV_32F );
CvMat* my1 = cvCreateMat( imageSize.height,
						  imageSize.width, CV_32F );
CvMat* mx2 = cvCreateMat( imageSize.height,
						  imageSize.width, CV_32F );
CvMat* my2 = cvCreateMat( imageSize.height,
						  imageSize.width, CV_32F );

CvMat* img1r = cvCreateMat( imageSize.height,
							imageSize.width, CV_8U );
CvMat* img2r = cvCreateMat( imageSize.height,
							imageSize.width, CV_8U );

CvMat* vdisp = cvCreateMat( imageSize.height,
							imageSize.width, CV_8U );
CvMat* pair;
double R1[3][3], R2[3][3], P1[3][4], P2[3][4];
CvMat _R1 = cvMat(3, 3, CV_64F, R1);
CvMat _R2 = cvMat(3, 3, CV_64F, R2);
#endif

#if 0
cvReleaseMat( &mx1 );
cvReleaseMat( &my1 );
cvReleaseMat( &mx2 );
cvReleaseMat( &my2 );
cvReleaseMat( &img1r );
cvReleaseMat( &img2r );
cvReleaseMat( &disp );
#endif
	
#if 0
// HARTLEY'S METHOD
// use intrinsic parameters of each camera, but
// compute the rectification transformation directly
// from the fundamental matrix
if( useUncalibrated == 1 )
 {
	 double H1[3][3], H2[3][3], iM[3][3];
	 CvMat _H1 = cvMat(3, 3, CV_64F, H1);
	 CvMat _H2 = cvMat(3, 3, CV_64F, H2);
	 CvMat _iM = cvMat(3, 3, CV_64F, iM);
	 //Just to show you could have independently used F
	 if( useUncalibrated == 2 ){
		 cvFindFundamentalMat( &_imagePoints1,
							   &_imagePoints2, &_F);
	 }
	 cvStereoRectifyUncalibrated( &_imagePoints1,
								  &_imagePoints2, &_F,
								  imageSize,
								  &_H1, &_H2, 3);
	 cvInvert(&_M1, &_iM);
	 cvMatMul(&_H1, &_M1, &_R1);
	 cvMatMul(&_iM, &_R1, &_R1);
	 cvInvert(&_M2, &_iM);
	 cvMatMul(&_H2, &_M2, &_R2);
	 cvMatMul(&_iM, &_R2, &_R2);
	 //Precompute map for cvRemap()
	 cvInitUndistortRectifyMap(&_M1,&_D1,&_R1,&_M1,mx1,my1);

	 cvInitUndistortRectifyMap(&_M2,&_D1,&_R2,&_M2,mx2,my2);
 }
#endif 
