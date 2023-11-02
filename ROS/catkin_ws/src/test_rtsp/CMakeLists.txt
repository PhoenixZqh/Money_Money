# cmake_minimum_required(VERSION 3.0.2)
# project(test_rtsp)

# ## Compile as C++11, supported in ROS Kinetic and newer
# # add_compile_options(-std=c++11)

# ## Find catkin macros and libraries
# ## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
# ## is used, also find other catkin packages

# SET(CMAKE_BUILD_TYPE "Debug")
# set(cv_bridge_DIR /usr/local/share/cv_bridge/cmake) 
# set(OpenCV_DIR "/usr/local/opencv-4.2.0")
# set(CUDA_BIN_PATH /usr/local/cuda/)

# find_package(catkin REQUIRED COMPONENTS
#   roscpp
#   rospy
#   std_msgs
#   image_transport
#   cv_bridge
# )


# find_package(Eigen3 REQUIRED)
# find_package( OpenCV 4.5.1 REQUIRED )
# find_package(CUDA REQUIRED)


# catkin_package(
# #  INCLUDE_DIRS include
# #  LIBRARIES test_rtsp
# #  CATKIN_DEPENDS roscpp rospy std_msgs
# #  DEPENDS system_lib
# )

# ###########
# ## Build ##
# ###########

# ## Specify additional locations of header files
# ## Your package locations should be listed before other locations
# include_directories(
# # include
#   ${catkin_INCLUDE_DIRS}
#   ${GST_INCLUDE_DIRS}
#   ${FFMPEG_INCLUDE_DIRS}
#   ${OpenCV_INCLUDE_DIRS}
# )


# link_directories(
#     # /usr/local/lib
#     ${CUDA_LIBRARIES}
#     ${OpenCV_LIBS}  
# )


# add_executable(ffmpeg_cpu src/ffmpeg_cpu.cpp)
# target_link_libraries(ffmpeg_cpu ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES} ${CUDA_LIBRARIES}) 

# add_executable(ffmpeg_opencv_rtsp src/ffmpeg_opencv_rtsp.cpp)
# target_link_libraries(ffmpeg_opencv_rtsp ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES} ${CUDA_LIBRARIES} ) 

# add_executable(gst_opencv src/gst_opencv.cpp)
# target_link_libraries(gst_opencv ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES} ${CUDA_LIBRARIES} ) 

# # add_executable(find_problem src/find_problem.cpp)
# # target_link_libraries(find_problem ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES} ${CUDA_LIBRARIES} ) 