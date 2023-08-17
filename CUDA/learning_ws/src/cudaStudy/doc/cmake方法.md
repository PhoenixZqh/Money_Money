```cmake
cmake_minimum_required(VERSION 2.6)
project(pro)
add_definitions(-std=c++11)  # CmakeList支持c++11的方式有两种：
                             # SET(CMAKE_CXX_FLAGS "-std=c++11")
                             # add_definitions(-std=c++11)

option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/workspace)

set(CUDA_GEN_CODE "-gencode=arch=compute_75,code=sm_75")

set(OpenCV_DIR   "/data/datav/expstation/lean/opencv4.2.0/lib/cmake/opencv4/")

set(CUDA_DIR     "/data/sxai/lean/cuda-10.2")
set(CUDNN_DIR    "/data/sxai/lean/cudnn8.2.2.26")
set(TENSORRT_DIR "/data/sxai/lean/TensorRT-8.0.1.6-cuda10.2-cudnn8.2")



find_package(CUDA REQUIRED)
find_package(OpenCV)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${OpenCV_INCLUDE_DIRS}
    ${CUDA_DIR}/include
    ${TENSORRT_DIR}/include
    ${CUDNN_DIR}/include
)


link_directories(
    ${TENSORRT_DIR}/lib
    ${CUDA_DIR}/lib64
    ${CUDNN_DIR}/lib
)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O0 -Wfatal-errors -pthread -w -g")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++11 -O0 -Xcompiler -fPIC -g -w ${CUDA_GEN_CODE}")
file(GLOB_RECURSE cpp_srcs ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE c_srcs ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE cuda_srcs ${PROJECT_SOURCE_DIR}/src/*.cu)
cuda_add_library(cucodes SHARED ${cuda_srcs})

add_executable(pro ${cpp_srcs} ${c_srcs})


target_link_libraries(cucodes nvinfer nvonnxparser)
target_link_libraries(cucodes cuda cublas cudart cudnn)
target_link_libraries(pro ${OpenCV_LIBS})
target_link_libraries(pro cucodes)

add_custom_target(
    run
    DEPENDS pro
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/workspace
    COMMAND ./pro
)


```