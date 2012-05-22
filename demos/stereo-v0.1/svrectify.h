/**
 * @file   svrectify.h
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Tue Feb  7 22:49:43 2012
 * 
 * @brief  
 * 
 * 
 */

#ifndef __SV_RECTIFY_H__
#define __SV_RECTIFY_H__

#include "cv.h"

// CV_IMPL
int
svStereoRectifyUncalibrated(
    const CvMat* _points1, const CvMat* _points2,
    const CvMat* F0, CvSize imgSize, CvMat* _H1, CvMat* _H2, double threshold );

#endif // __SV_RECTIFY_H__
