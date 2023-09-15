cmake_minimum_required(VERSION 3.0.2)
project(track8yolo)

add_compile_options(-std=c++11)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  message_generation
  dynamic_reconfigure
)

find_package(Eigen3 REQUIRED)
find_package(OpenCV  REQUIRED)
include_directories(include ${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

find_package(Boost REQUIRED COMPONENTS thread)
find_package(Threads REQUIRED)
find_package(Eigen3 REQUIRED)

set(CUDA_TOOLKIT_ROOT_DIR       "/usr/local/cuda")
set(CUDNN_DIR                   "/usr/local/cuda")
set(TENSORRT_DIR                "/home/zqh/TensorRT-8.2.3.0") #path to yor tensorRT


add_message_files(
  FILES
  BoundingBox.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

generate_dynamic_reconfigure_options(
  cfg/param_pid.cfg
)

catkin_package(
  CATKIN_DEPENDS
  message_runtime
  
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
  ${NLOPT_INCLUDE_DIRS}
  ${CUDA_TOOLKIT_ROOT_DIR}/include
  ${TENSORRT_DIR}/include
  /usr/include/eigen3
  ${CMAKE_CURRENT_SOURCE_DIR}
  /home/zqh/trackUav_ws/src/track8yolo/include/track8yolo
 
 )

link_directories(
  /usr/local/lib
  ${TENSORRT_DIR}/lib
  ${CUDA_TOOLKIT_ROOT_DIR}/lib64
  ${CUDNN_DIR}/lib64                
)

link_directories("./so/")

# tensorrt
# include_directories("~/atools/TensorRT-7.2.2.3/include")
# link_directories("~/atools/TensorRT-7.2.2.3/lib")





add_executable(tracknode
  src/tracknode.cpp
  src/uav_track.cpp
  src/pidTrack.cpp
)

add_executable(imagepub
  src/imagepub.cpp
  src/detect_yolo.cpp
)

add_dependencies(tracknode
  ${PROJECT_NAME}_gencfg
)

target_link_libraries(tracknode ${catkin_LIBRARIES} )
target_link_libraries(imagepub ${catkin_LIBRARIES} ${OpenCV_LIBS} nvinfer cudart myplugins YoloV5_TensorRT pthread )

