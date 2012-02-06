CMAKE_MINIMUM_REQUIRED(VERSION 2.8)



include_directories(include)
file(GLOB cxcore_src src/*.cpp)
add_library(cxcore STATIC ${cxcore_src})

# target_link_libraries(cxcore dl)