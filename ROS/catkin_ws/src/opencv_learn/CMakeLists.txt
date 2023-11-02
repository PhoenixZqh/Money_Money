# cmake_minimum_required(VERSION 3.0.2)
# project(opencv_learn)


# find_package(catkin REQUIRED COMPONENTS
#   roscpp
#   rospy
#   std_msgs
# )

# find_package( OpenCV 4.5.1 REQUIRED )


# catkin_package(
# #  INCLUDE_DIRS include
# #  LIBRARIES opencv_learn
# #  CATKIN_DEPENDS roscpp rospy std_msgs
# #  DEPENDS system_lib
# )


# include_directories(
#   ${catkin_INCLUDE_DIRS}
#   ${OpenCV_INCLUDE_DIRS}
#   ${PROJECT_SOURCE_DIR}/include
# )

# link_directories(
#     # /usr/local/lib
#     ${OpenCV_LIBS}  
# )

# set(SRC
#     src/puttext_chinese.cpp
#    )

# add_executable(puttext_chinese ${SRC})
# target_link_libraries(puttext_chinese ${catkin_LIBRARIES} ${OpenCV_LIBS} ${FREETYPE_LIBRARIES}) 