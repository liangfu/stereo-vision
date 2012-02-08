/**
 * @file   svfeature.cpp
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Tue Feb  7 17:02:55 2012
 * 
 * @brief  
 * 
 * 
 */

#include "svfeature.h"

#include "utility.h"

const int MAX_CORNERS = 500;

void extractFeatureSURF(CvArr * pImage, bool saveImage)
{
	IplImage * pWorkImage = cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

	// cvCvtColor(pImage,pWorkImage,CV_BGR2GRAY);
	pWorkImage = cvCloneImage((IplImage*)pImage);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq *imageKeypoints = 0, *imageDescriptors = 0;
	CvSURFParams params = cvSURFParams(2000, 0);
	cvExtractSURF( pWorkImage, 0, &imageKeypoints, &imageDescriptors,
				   storage, params );
	// show features
	for( int i = 0; i < imageKeypoints->total; i++ )
	{
		CvSURFPoint* r = (CvSURFPoint*)cvGetSeqElem( imageKeypoints, i );
		CvPoint center;
		int radius;
		center.x = cvRound(r->pt.x);
		center.y = cvRound(r->pt.y);
		radius = cvRound(r->size*1.2/9.*2);
		cvCircle( pWorkImage, center, radius, CV_RGB(255,0,0), 1, CV_AA, 0 );
	}
	if (saveImage) // svShowImage(pWorkImage);
	{cvSaveImage("feature.pgm", pWorkImage);}
	
	cvReleaseImage(&pWorkImage);
	cvReleaseMemStorage(&storage);
}

void extractFeatureKLT(const CvArr * imgA, const CvArr * imgB,
					   const bool saveImage)
{
	// Load two images and allocate other structures
	// IplImage* imgA = cvLoadImage("image0.png", CV_LOAD_IMAGE_GRAYSCALE);
	// IplImage* imgB = cvLoadImage("image1.png", CV_LOAD_IMAGE_GRAYSCALE);

	CvSize img_sz = cvGetSize( imgA );
	int win_size = 15;

	IplImage* imgC;// = cvLoadImage("OpticalFlow1.png", CV_LOAD_IMAGE_UNCHANGED);

	// Get the features for tracking
	IplImage* eig_image = cvCreateImage( img_sz, IPL_DEPTH_32F, 1 );
	IplImage* tmp_image = cvCreateImage( img_sz, IPL_DEPTH_32F, 1 );

	int corner_count = MAX_CORNERS;
	CvPoint2D32f* cornersA = new CvPoint2D32f[ MAX_CORNERS ];

	cvGoodFeaturesToTrack( imgA, eig_image, tmp_image, cornersA, 
						   &corner_count,
						   0.05, 5.0, 0, 3, 0, 0.04 );

	cvFindCornerSubPix( imgA, cornersA, corner_count, 
						cvSize( win_size, win_size ),
						cvSize( -1, -1 ), 
						cvTermCriteria( CV_TERMCRIT_ITER | 
										CV_TERMCRIT_EPS, 20, 0.03 ) );

	// Call Lucas Kanade algorithm
	char features_found[ MAX_CORNERS ];
	float feature_errors[ MAX_CORNERS ];

	// CvSize pyr_sz = cvSize( imgA->width+8, imgB->height/3 );
	CvSize pyr_sz = cvSize( cvGetSize(imgA).width+8,
							cvGetSize(imgB).height/3 );

	IplImage* pyrA = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
	IplImage* pyrB = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );

	CvPoint2D32f* cornersB = new CvPoint2D32f[ MAX_CORNERS ];

	cvCalcOpticalFlowPyrLK( imgA, imgB, pyrA, pyrB, 
							cornersA, cornersB, corner_count, 
							cvSize( win_size, win_size ), 5, 
							features_found, feature_errors,
							cvTermCriteria( CV_TERMCRIT_ITER | 
											CV_TERMCRIT_EPS, 20, 0.3 ), 0 );

	// Make an image of the results
	// imgC->origin = ((IplImage*)imgB)->origin;

	// cvAddWeighted : dst(I)=src1(I)*alpha+src2(I)*beta+gamma
	imgC = cvCloneImage((IplImage*)imgB);
	float alpha = 0.5f;
	cvAddWeighted(imgC, alpha, imgA, 1.0f-alpha, 0.0, imgC);
	//cvAddWeighted(imgC, alpha, imgB, 1.0f-alpha, 0.0, imgC);

	for( int k,i = k = 0; i < corner_count; i++ )
	{
		// if( add_remove_pt )
		// {
		// double dx = pt.x - cornersB[i].x;
		// double dy = pt.y - cornersB[i].y;

		// if ( dx*dx + dy*dy <= 25 ) {
		// 	add_remove_pt = 0;
		// 	continue;
		// }
		// }
                
		if( !features_found[i] ){ continue; }
                
		// cornersB[k++] = cornersB[i];
		// cvCircle( imgC, cvPointFrom32f(cornersB[i]),
		// 		  3, CV_RGB(0,255,0), -1, 8, 0);
		CvPoint p0 = cvPoint( cvRound( cornersA[i].x ),
							  cvRound( cornersA[i].y ) );
		CvPoint p1 = cvPoint( cvRound( cornersB[i].x ),
							  cvRound( cornersB[i].y ) );
		cvLine( imgC, p0, p1, CV_RGB(255,0,0), 1 );
	}
	// for( int i=0; i < corner_count; i++ ){
	// 	// if (feature_errors[i]>0){
	// 	// 	printf("Error is %f/n", feature_errors[i]);
	// 	// 	continue;
	// 	// }
	// 	printf("Got it/n");
	// 	CvPoint p0 = cvPoint( cvRound( cornersA[i].x ),
	// 						  cvRound( cornersA[i].y ) );
	// 	CvPoint p1 = cvPoint( cvRound( cornersB[i].x ),
	// 						  cvRound( cornersB[i].y ) );
	// 	cvLine( imgC, p0, p1, CV_RGB(255,0,0), 2 );
	// }
	if (saveImage) {svShowImage(imgC);}
}
