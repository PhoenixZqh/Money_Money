cmake_minimum_required(VERSION 3.0.2)
project(tensorrtStudy)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

set(CUDA_TOOLKIT_ROOT_DIR       "/usr/local/cuda")
set(CUDNN_DIR                   "/usr/local/cuda")
set(TENSORRT_DIR                "/home/zqh/TensorRT-8.2.3.0") #path to yor tensorRT


find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES tensorrtStudy
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include/tensorrtStudy
  ${PROJECT_SOURCE_DIR}/include
  ${CUDA_TOOLKIT_ROOT_DIR}/include
  ${PROJECT_SOURCE_DIR}/onnx_parser

)

link_directories(
    /usr/local/lib
    ${TENSORRT_DIR}/lib
    ${CUDA_TOOLKIT_ROOT_DIR}/lib64
    ${CUDNN_DIR}/lib64
)


file(GLOB_RECURSE trt_srcs ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE trt_cus ${PROJECT_SOURCE_DIR}/*.cu)
file(GLOB_RECURSE trt_include ${PROJECT_SOURCE_DIR}/*.h*)

add_executable(trt_exe src/hello_tensorrt.cpp)
target_link_libraries(trt_exe ${catkin_LIBRARIES} nvinfer nvinfer_plugin)

add_executable(inference src/hello_inference.cpp)
target_link_libraries(inference ${catkin_LIBRARIES} nvinfer nvinfer_plugin cudart)

add_executable(onnx src/onnx_parser.cpp)
target_link_libraries(onnx ${catkin_LIBRARIES} nvinfer nvinfer_plugin cudart nvonnxparser)  #需要添加nvonnxparser

add_executable(ful_cnn_classfier src/ful_cnn_classfier.cpp)
target_link_libraries(ful_cnn_classfier ${catkin_LIBRARIES} ${OpenCV_LIBS} nvinfer nvinfer_plugin cudart nvonnxparser)  #需要添加nvonnxparser


add_executable(int8_cali src/int8_cali.cpp)
target_link_libraries(int8_cali ${catkin_LIBRARIES} ${OpenCV_LIBS} nvinfer nvinfer_plugin cudart nvonnxparser)  #需要添加nvonnxparser
