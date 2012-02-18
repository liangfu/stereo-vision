/**
 * @file   utility.h
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Mon Feb  6 21:29:57 2012
 * 
 * @brief  Utility functions that is commonly used in the project
 * 
 * 
 */

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "cv.h"

#define __SV_NAMESPACE_BEGIN__		namespace sv{
#define __SV_NAMESPACE_END__		};

using std::vector;

inline bool operator==(CvSize s1, CvSize s2){
	return (s1.height==s2.height) && (s1.width==s2.width);
}

inline bool svPrint(const CvArr * _mat, const char* n = NULL){
	if (n!=NULL) {fprintf(stderr, "%s\n", n);}
	CvMat * mat = (CvMat*)_mat;
	for (int i = 0; i < mat->rows; i++){
		for (int j = 0; j < mat->cols; j++){
			fprintf(stderr, "%f ", (float)(mat->data.fl[i*mat->cols+j]));
		}fprintf(stderr, "\n");
	}fprintf(stderr, "\n");
	return 1;
}


#ifdef __linux__
inline void svShowImage(CvArr * im){
	cvSaveImage("tmp/tmp.pgm", im);
	system("display tmp/tmp.pgm");
}
#endif

#endif //__UTILITY_H__
