/* 
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include "cv.h"
// #include "cv.hpp"
#include "cxcore.h"
#include "bmpfmt.h"
#include "test.h"

#define ANDROID_LOG_VERBOSE ANDROID_LOG_DEBUG
#define LOG_TAG "TVReality"

#define LOGV(...) __android_log_print(ANDROID_LOG_SILENT, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#ifdef __cplusplus 
extern "C" {
#endif

// IplImage* pImage = NULL;
// IplImage* loadPixels(int* pixels, int width, int height);
// IplImage* getIplImageFromIntArray(JNIEnv* env, jintArray array_data,
// 		jint width, jint height);

// extern "C" {
// This is just an example of function
// to support both IplImage and cvMat as an input
// CVAPI( void ) cvIamArr( const CvArr* arr )
// {
// 	CV_FUNCNAME( "cvIamArr" );
// 	__BEGIN__;
// 	CvMat matstub, *mat = (CvMat*)arr;
// 	int coi = 0;
// 	CV_ASSERT( mat == NULL );
// 	if( !CV_IS_MAT(mat) )
// 	{
// 		CV_CALL( mat = cvGetMat( mat, &matstub, &coi ) );
// 		if (coi != 0) CV_ERROR_FROM_CODE(CV_BadCOI);
// 	}
// 	// Process as cvMat
// 	__END__;
// }
	
JNIEXPORT void JNICALL Java_com_android_tvr_OpenCVView_FindFeatures(JNIEnv* env, jobject thiz, jint width, jint height, jbyteArray yuv, jintArray bgra) 
{
    jbyte* _yuv  = env->GetByteArrayElements(yuv, 0);
    jint*  _bgra = env->GetIntArrayElements(bgra, 0);

	LOGI("TVReality native function loaded \n");
	// CvMat * myuv = cvCreateMat(height + height/2, width, CV_8UC1);
	// CvMat * mbgra = cvCreateMat(height, width, CV_8UC4);
	// CvMat * mgray = cvCreateMat(height, width, CV_8UC1);
	CvMat myuv = cvMat(height + height/2, width, CV_8UC1, _yuv);
	CvMat mbgra = cvMat(height, width, CV_8UC4, _bgra);
	CvMat mgray = cvMat(height, width, CV_8UC1, _yuv);
	// char s[1024]; sprintf(s, "%d", test2());
	// LOGI(s);

    // CvMat myuv(int(height + height/2), int(width), CV_8UC1, (unsigned char *)_yuv);
    // CvMat mbgra(int(height), int(width), CV_8UC4, (unsigned char *)_bgra);
    // CvMat mgray((int)height, (int)width, CV_8UC1, (unsigned char *)_yuv);

    //Please make attention about BGRA byte order
    //ARGB stored in java as int array becomes BGRA at native level
    // cvtColor(myuv, mbgra, CV_YUV420sp2BGR, 4);
	// cvIamArr(myuv);
	IplImage * t1 = // loadPixels(myuv, width, height);
		cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	IplImage * t2 = // loadPixels(mbgra, width, height);
		cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 4);
	t2 = cvCloneImage(t1);
    cvCvtColor(t1, t2, CV_YCrCb2BGR);

    // vector<KeyPoint> v;

    // FastFeatureDetector detector(50);
    // detector.detect(mgray, v);
    // for( size_t i = 0; i < v.size(); i++ )
    //     circle(mbgra, Point(v[i].pt.x, v[i].pt.y), 10, Scalar(0,0,255,255));

	// cvReleaseMat(&myuv);
    env->ReleaseIntArrayElements(bgra, _bgra, 0);
    env->ReleaseByteArrayElements(yuv, _yuv, 0);
}

// }

// JNIEXPORT void JNICALL
// Java_com_android_tvr_OpenCVView_extractSURFFeature(JNIEnv* env,
// 												   jobject thiz)
// {
// 	IplImage *pWorkImage=cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);
// 	cvCvtColor(pImage,pWorkImage,CV_BGR2GRAY);
// 	CvMemStorage* storage = cvCreateMemStorage(0);
// 	CvSeq *imageKeypoints = 0, *imageDescriptors = 0;
// 	CvSURFParams params = cvSURFParams(2000, 0);
// 	cvExtractSURF( pWorkImage, 0, &imageKeypoints, &imageDescriptors, storage, params );
// 	// show features
// 	for( int i = 0; i < imageKeypoints->total; i++ )
// 	{
// 		CvSURFPoint* r = (CvSURFPoint*)cvGetSeqElem( imageKeypoints, i );
// 		CvPoint center;
// 		int radius;
// 		center.x = cvRound(r->pt.x);
// 		center.y = cvRound(r->pt.y);
// 		radius = cvRound(r->size*1.2/9.*2);
// 		cvCircle( pImage, center, radius, CV_RGB(255,0,0), 1, CV_AA, 0 );
// 	}
// 	cvReleaseImage(&pWorkImage);
// 	cvReleaseMemStorage(&storage);
// }

// JNIEXPORT jboolean JNICALL Java_com_android_tvr_OpenCV_setSourceImage(
// 		JNIEnv* env, jobject thiz, jintArray photo_data, jint width,
// 		jint height) {
// 	if (pImage != NULL) {
// 		cvReleaseImage(&pImage);
// 		pImage = NULL;
// 	}
// 	pImage = getIplImageFromIntArray(env, photo_data, width, height);
// 	if (pImage == NULL) {
// 		return 0;
// 	}
// 	LOGI("Load Image Done.");
// 	return 1;
// }

// JNIEXPORT jbooleanArray JNICALL Java_com_android_tvr_OpenCV_getSourceImage(
// 		JNIEnv* env, jobject thiz) {
// 	if (pImage == NULL) {
// 		LOGE("No source image.");
// 		return 0;
// 	}
// 	cvFlip(pImage);
// 	int width = pImage->width;
// 	int height = pImage->height;
// 	int rowStep = pImage->widthStep;
// 	int headerSize = 54;
// 	int imageSize = rowStep * height;
// 	int fileSize = headerSize + imageSize;
// 	unsigned char* image = new unsigned char[fileSize];
// 	struct bmpfile_header* fileHeader = (struct bmpfile_header*) (image);
// 	fileHeader->magic[0] = 'B';
// 	fileHeader->magic[1] = 'M';
// 	fileHeader->filesz = fileSize;
// 	fileHeader->creator1 = 0;
// 	fileHeader->creator2 = 0;
// 	fileHeader->bmp_offset = 54;
// 	struct bmp_dib_v3_header_t* imageHeader =
// 			(struct bmp_dib_v3_header_t*) (image + 14);
// 	imageHeader->header_sz = 40;
// 	imageHeader->width = width;
// 	imageHeader->height = height;
// 	imageHeader->nplanes = 1;
// 	imageHeader->bitspp = 24;
// 	imageHeader->compress_type = 0;
// 	imageHeader->bmp_bytesz = imageSize;
// 	imageHeader->hres = 0;
// 	imageHeader->vres = 0;
// 	imageHeader->ncolors = 0;
// 	imageHeader->nimpcolors = 0;
// 	memcpy(image + 54, pImage->imageData, imageSize);
// 	jbooleanArray bytes = env->NewBooleanArray(fileSize);
// 	if (bytes == 0) {
// 		LOGE("Error in creating the image.");
// 		delete[] image;
// 		return 0;
// 	}
// 	env->SetBooleanArrayRegion(bytes, 0, fileSize, (jboolean*) image);
// 	delete[] image;
// 	return bytes;
// }

// IplImage* loadPixels(int* pixels, int width, int height) {
// 	int x, y;
// 	IplImage *img = cvCreateImage(cvSize(width, height),
// 								  IPL_DEPTH_8U, 3);
// 	unsigned char* base = (unsigned char*) (img->imageData);
// 	unsigned char* ptr;
// 	for (y = 0; y < height; y++) {
// 		ptr = base + y * img->widthStep;
// 		for (x = 0; x < width; x++) {
// 			// blue
// 			ptr[3 * x] = pixels[x + y * width] & 0xFF;
// 			// green
// 			ptr[3 * x + 1] = pixels[x + y * width] >> 8 & 0xFF;
// 			// blue
// 			ptr[3 * x + 2] = pixels[x + y * width] >> 16 & 0xFF;
// 		}
// 	}
// 	return img;
// }

// IplImage* getIplImageFromIntArray(JNIEnv* env, jintArray array_data,
// 								  jint width, jint height) {
// 	int *pixels = env->GetIntArrayElements(array_data, 0);
// 	if (pixels == 0) {
// 		LOGE("Error getting int array of pixels.");
// 		return 0;
// 	}
// 	IplImage *image = loadPixels(pixels, width, height);
// 	env->ReleaseIntArrayElements(array_data, pixels, 0);
// 	if (image == 0) {
// 		LOGE("Error loading pixel array.");
// 		return 0;
// 	}
// 	return image;
// }

#ifdef __cplusplus
}
#endif

