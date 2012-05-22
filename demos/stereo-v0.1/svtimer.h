// modified by Liangfu Chen, 2011~2012

// StopWatch.h
// Stopwatch class for high resolution timing.
// Code by Richard S. Wright Jr.
// March 23, 1999
// 
// This function uses the High performance counter on Win32 and
// gettimeofday on Mac OS X/Linux. gettimeofday is actually pretty
// good on the Mac (about 10ms).

#ifndef __SV_TIMER_H__
#define __SV_TIMER_H__

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


class timer
{
public:
	void start()	// Constructor
	{
#ifdef WIN32
		QueryPerformanceFrequency(&m_CounterFrequency);
		QueryPerformanceCounter(&m_LastCount);
#else
		gettimeofday(&m_LastCount, 0);
#endif
	}
	
	// Resets timer (difference) to zero
	inline void restart() 
	{
#ifdef WIN32
		QueryPerformanceCounter(&m_LastCount);
#else
		gettimeofday(&m_LastCount, 0);
#endif
	}					
	
	// Get elapsed time in seconds
	float elapsed()
	{
		// Get the current count
#ifdef WIN32
		LARGE_INTEGER lCurrent;
		QueryPerformanceCounter(&lCurrent);
		
		return float((lCurrent.QuadPart - m_LastCount.QuadPart) /
					 double(m_CounterFrequency.QuadPart));
#else
		timeval lcurrent;
		gettimeofday(&lcurrent, 0);
		float fSeconds = (float)(lcurrent.tv_sec - m_LastCount.tv_sec);
		float fFraction = (float)(lcurrent.tv_usec - m_LastCount.tv_usec) * 0.000001f;
		return fSeconds + fFraction;
#endif
	}	
	
protected:
#ifdef WIN32
	LARGE_INTEGER m_CounterFrequency;
	LARGE_INTEGER m_LastCount;
#else
	timeval m_LastCount;
#endif
};


#endif // __SV_TIMER_H__
