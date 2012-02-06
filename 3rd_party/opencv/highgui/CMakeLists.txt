cmake_minimum_required(VERSION 2.8)

include_directories(include ../cxcore/include ../cv/include)
file(GLOB highgui_src src/*.cpp)
add_library(highgui STATIC ${highgui_src})

# target_link_libraries(highgui cv cxcore)