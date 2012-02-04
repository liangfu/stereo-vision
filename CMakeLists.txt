cmake_minimum_required(VERSION 2.8)
project(stereovision)

set(CMAKE_CXX_FLAGS "-Wall -g")

# ADD_LIBRARY(OpenCV 3rd_party)
include_directories(3rd_party/opencv/cxcore/include 
  3rd_party/opencv/cv/include)
add_subdirectory(3rd_party/opencv/cxcore/)
add_subdirectory(3rd_party/opencv/cv/)

add_executable(stereovision src/main.cpp)
target_link_libraries(stereovision cv cxcore)