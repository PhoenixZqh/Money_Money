cmake_minimum_required(VERSION 2.8)

project(demo)

set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall -fopenmp")

find_package(OpenCV 4.5 REQUIRED )


include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(demo main.cpp)

target_link_libraries(
    demo
    ${OpenCV_LIBS}
)