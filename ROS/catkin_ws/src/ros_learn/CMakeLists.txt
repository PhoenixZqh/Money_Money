cmake_minimum_required(VERSION 3.0.2)
project(ros_learn)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
SET(CMAKE_BUILD_TYPE "Debug")
# set(OpenCV_DIR "/usr/local/opencv-4.5.1")
set(CUDA_BIN_PATH /usr/local/cuda/)
# set(cv_bridge_DIR /usr/local/share/cv_bridge/cmake) 

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  rosconsole
  # cv_bridge
  image_transport
  rosbag
  
)

find_package(Eigen3 REQUIRED)
find_package(OpenCV 4.2 REQUIRED )
# find_package(CUDA REQUIRED)


message(STATUS "Found OpenCV version ${OpenCV_VERSION}")

## Generate services in the 'srv' folder
add_service_files(
  FILES
  add.srv
)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_learn
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
  
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  # /usr/local/include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${GST_INCLUDE_DIRS}
  ${FFMPEG_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

link_directories(
    # /usr/local/lib
    # ${CUDA_LIBRARIES}
    ${OpenCV_LIBS}  
)

# add_executable(turtle_spawn src/rosclient.cpp)
# target_link_libraries(turtle_spawn ${catkin_LIBRARIES})

# add_executable(turtle_command_server src/rosservice.cpp)
# target_link_libraries(turtle_command_server ${catkin_LIBRARIES})  

# add_executable(add_server src/add_server.cpp)
# target_link_libraries(add_server ${catkin_LIBRARIES})  
# add_dependencies(add_server ros_learn_gencpp)

# add_executable(add_client src/add_client.cpp)
# target_link_libraries(add_client ${catkin_LIBRARIES})  
# add_dependencies(add_client ros_learn_gencpp)

# add_executable(eigen src/eigen.cpp)
# target_link_libraries(eigen ${catkin_LIBRARIES}) 


# add_executable(ros_rtsp src/ros_rtsp.cpp)
# target_link_libraries(ros_rtsp ${catkin_LIBRARIES}) 

# add_executable(rtsp_sub src/rtsp_sub.cpp)
# target_link_libraries(rtsp_sub ${catkin_LIBRARIES} ${OpenCV_LIBS}) 

# add_executable(rtsp_pub src/rtsp_pub.cpp)
# target_link_libraries(rtsp_pub ${catkin_LIBRARIES} ${OpenCV_LIBS}) 

# add_executable(web_pub src/web_pub.cpp)
# target_link_libraries(web_pub ${catkin_LIBRARIES} ${OpenCV_LIBS}) 

# add_executable(web_sub src/web_sub.cpp)
# target_link_libraries(web_sub ${catkin_LIBRARIES} ${OpenCV_LIBS}) 

# add_executable(pid_control src/pid_control.cpp)
# target_link_libraries(pid_control ${catkin_LIBRARIES} ${OpenCV_LIBS}) 

# add_executable(udp_sub src/udp_sub.cpp)
# target_link_libraries(udp_sub ${catkin_LIBRARIES} ${OpenCV_LIBS}) 

# add_executable(udp_pub src/udp_pub.cpp)
# target_link_libraries(udp_pub ${catkin_LIBRARIES} ${OpenCV_LIBS}) 

add_executable(test_rtsp src/test_rtsp.cpp)
target_link_libraries(test_rtsp ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES}) 

# add_executable(image_2_bag src/image_2_bag.cpp)
# target_link_libraries(image_2_bag ${catkin_LIBRARIES} ${OpenCV_LIBS})  

add_executable(gstreamer_rtsp src/gstreamer_rtsp.cpp)
target_link_libraries(gstreamer_rtsp ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES} ${CUDA_LIBRARIES}) 

add_executable(opencv_push_rtsp src/opencv_push_rtsp.cpp)
target_link_libraries(opencv_push_rtsp ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES} ${CUDA_LIBRARIES}) 

add_executable(get_cali src/get_cali.cpp)
target_link_libraries(get_cali ${catkin_LIBRARIES} ${OpenCV_LIBS} ) 