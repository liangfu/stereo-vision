src = main.cpp svdisparity.cpp svfeature.cpp

extern_inc = -I../3rd_party/opencv/cv/include \
	-I../3rd_party/opencv/cxcore/include \
	-I../3rd_party/opencv/highgui/include 
extern_lib = -L../3rd_party/opencv/cv \
	-L../3rd_party/opencv/cxcore \
	-L../3rd_party/opencv/highgui \
	-lcv -lhighgui -lcxcore \
	-ldl # -lpthread

first:
	g++ -Wall -g $(src) -o stereovision $(extern_lib) $(extern_inc)
	./stereovision

