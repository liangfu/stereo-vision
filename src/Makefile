# Makefile for stereo vision project 
# by Liangfu Chen, 2011~2012

release-flags = -O2
debug-flags = -Wall -g

src = main.cpp svdisparity.cpp svfeature.cpp svcalib.cpp svrectify.cpp

extern_inc = -I../3rd_party/opencv/cv/include \
	-I../3rd_party/opencv/cxcore/include \
	-I../3rd_party/opencv/highgui/include 
extern_lib = -L../3rd_party/opencv/cv \
	-L../3rd_party/opencv/cxcore \
	-L../3rd_party/opencv/highgui \
	-lcv -lhighgui -lcxcore \
	-ldl # -lpthread

first:.misc tmp
	g++ $(debug-flags) $(src) -o stereovision $(extern_lib) $(extern_inc)
	./stereovision

.misc:
	mkdir .misc

tmp:
	mkdir tmp