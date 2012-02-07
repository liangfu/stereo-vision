/**
 * @file   utility.h
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Mon Feb  6 21:29:57 2012
 * 
 * @brief  
 * 
 * 
 */

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdio.h>
#include <stdlib.h>

#include "cv.h"

inline bool operator==(CvSize s1, CvSize s2){
	return (s1.height==s2.height) && (s1.width==s2.width);
}

#ifdef __linux__
inline void svShowImage(CvArr * im){
	cvSaveImage("tmp.pgm", im);
	system("display tmp.pgm");
}
#endif

#endif //__UTILITY_H__
