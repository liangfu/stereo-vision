/**
 * @file   svdisparity.h
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Tue Feb  7 16:35:28 2012
 * 
 * @brief  
 * 
 * 
 */

#ifndef __SV_DISPARITY_H__
#define __SV_DISPARITY_H__

#include "cv.h"
#include "highgui.h"

// namespace sv{

void createDisparityMapBM(CvArr * img1, CvArr * img2,
						  int numberOfDisparities, int maxIters);
void createDisparityMapGC(CvArr * img1, CvArr * img2,
						  int numberOfDisparities, int maxIters);

// }

#endif // __SV_DISPARITY_H__
