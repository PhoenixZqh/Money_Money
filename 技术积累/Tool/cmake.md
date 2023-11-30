# 总览

```cmake

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)                    #设定最小的版本要求
cmake_policy(SET CMP0054 NEW)   

set (PROJECT VERSION 0.0.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
project(PushStream VERSION ${PROJECT_VERSION} LANGUAGES CXX)       #设定项目名称


add_definitions(-DAPI_EXPORTS)                                     #增加预定义的宏
set(CMAKE_BUILD_TYPE "Debug")                                      #设定编译类型 Debug,release

## JETSON, X86_CUDA, X86_INTEL
message(STATUS "System:${CMAKE_HOST_SYSTEM_PROCESSOR}")
if(NOT DEFINED PLATFORM)
  message(FATAL_ERROR "PLATFORM NOT SPECIFIED!")
else()
  message(STATUS "PLATFORM: ${PLATFORM}")
  if(PLATFORM STREQUAL "JETSON")                                   #作用: 该命令用于向列表变量中追加元素。
    add_definitions(-DPLATFORM_JETSON)   
    option(USE_CUDA "BUILD WITH CUDA." ON)                         #选择开启什么选项
    option(USE_GSTREAMER "BUILD WITH GSTREAMER." ON)
  elseif(PLATFORM STREQUAL "X86_CUDA")
    add_definitions(-DPLATFORM_X86_CUDA)
    option(USE_CUDA "BUILD WITH CUDA." ON)
    option(USE_FFMPEG "BUILD WITH FFMPEG." ON)
    # option(USE_GSTREAMER "BUILD WITH GSTREAMER." ON)
  elseif(PLATFORM STREQUAL "X86_INTEL")
    add_definitions(-DPLATFORM_X86_INTEL)
    option(USE_FFMPEG "BUILD WITH FFMPEG." ON)
  else()
    message(FATAL_ERROR "UNSUPPORTED PLATFORM!")
  endif()
endif()


if(USE_CUDA)
  add_definitions(-DWITH_CUDA)
  option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
  find_package(CUDA REQUIRED)
  message(STATUS "CUDA: ON")
endif()


if(USE_GSTREAMER)
  add_definitions(-DWITH_GSTREAMER)
  message(STATUS "GSTREAMER: ON")
endif()

if(USE_FFMPEG)
  add_definitions(-DWITH_FFMPEG)
  find_package(fmt REQUIRED)
  set(FFMPEG_LIBS libavutil.so libavcodec.so libavformat.so libavdevice.so libavfilter.so libswscale.so)
  message(STATUS "WITH_FFMPEG: ON")
endif()

set(cv_bridge_DIR /usr/local/cv_bridge/share/cv_bridge/cmake)  

find_package(catkin REQUIRED COMPONENTS                         #找第三方库
  roscpp
  rospy
  std_msgs
  message_generation
  rosconsole
  cv_bridge
  image_transport
)

find_package(Eigen3 REQUIRED)
add_definitions(-DWITH_OCV470)
find_package(OpenCV 4.7.0 REQUIRED)
find_package(fmt REQUIRED)


include_directories(                                            #包含所需的头文件
  include
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include
  ${EIGEN3_INCLUDE_DIR}
  ${TRT_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
  ${FFMPEG_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/video_io
  ${fmt_INCLUDE_DIRS}
  )

link_directories(                                               #链接到所需要的库
    /usr/local/lib
    /opt/ros/noetic/lib

    # ${TENSORRT_DIR}/lib
)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(USE_GSTREAMER)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/video_io/gstreamer)
  if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    include_directories(
      "/usr/include/gstreamer-1.0"
      "/usr/local/include/gstreamer-1.0"
      "/usr/include/glib-2.0"
      "/usr/lib/aarch64-linux-gnu/glib-2.0/include"
    )
  elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    include_directories(
      "/usr/include/gstreamer-1.0"
      "/usr/local/include/gstreamer-1.0"
      "/usr/include/glib-2.0"
      "/usr/lib/x86_64-linux-gnu/glib-2.0/include"
    )
  endif()
endif()

if(USE_FFMPEG)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/video_io/ffmpeg)
endif()

set (driveSRCS src/push_stream.cpp)                                             #首先选择一个文件
file(GLOB DRV_SV_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/video_io/ffmpeg/*.cpp)        #加入其他文件夹下所有的cpp
list(APPEND driveSRCS ${DRV_SV_SRCS})                                           #append到driveSRCS后面
file(GLOB DRV_SV_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/video_io/gstreamer/*.cpp)
list(APPEND driveSRCS ${DRV_SV_SRCS})
file(GLOB DRV_SV_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/video_io/*.cpp)
list(APPEND driveSRCS ${DRV_SV_SRCS})

set (driverHeaders include/push_stream.h)
file(GLOB DRV_SV_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/video_io/*.h)
list(APPEND driverHeaders ${DRV_SV_INCLUDES})
file(GLOB DRV_SV_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/video_io/ffmpeg/*.h)
list(APPEND driverHeaders ${DRV_SV_INCLUDES})
file(GLOB DRV_SV_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/video_io/gstreamer/*.h)
list(APPEND driverHeaders ${DRV_SV_INCLUDES})

add_library(rtsp_library SHARED ${driveSRCS})                                   #将自己的cpp文件添加到库  
add_executable(rtsp_stream src/push_stream_node.cpp)                            #添加可执行文件
target_include_directories(
    rtsp_library
    PUBLIC
    ${driverHeaders}
)

target_link_libraries(                                                          #将自己的库链接到可执行文件
    rtsp_stream rtsp_library ${OpenCV_LIBS} gstrtspserver-1.0 fmt
)


add_executable(ffmpeg_process src/ffmpeg_process.cpp)
target_link_libraries(ffmpeg_process ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES}) 


add_executable(ros_rtsp src/ros_rtsp.cpp)
target_link_libraries(ros_rtsp rtsp_library fmt ${catkin_LIBRARIES} ${OpenCV_LIBS} ${GST_LIBRARIES}  ${FFMPEG_LIBRARIES}) 
```

# 安装

```cmake
cmake_minimum_required(VERSION 3.5)

set(INSTALL_DIR /home/GitHub/Money_Money/ROS/learn_cmake/Lib/install)

project(hello_include)

add_library(my_library SHARED src/hello.cpp)        # 将文件添加到库   .a 是静态库、 .so 是共享库
add_executable(static_lib src/main.cpp)             #可执行文件独立出来

# 将头文件路径添加到库
target_include_directories(
    my_library
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

#链接到库
target_link_libraries(static_lib  
        PRIVATE 
        my_library
)



install(TARGETS my_library  DESTINATION ${INSTALL_DIR}/lib)                           # 安装库
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/  DESTINATION ${INSTALL_DIR}/include) #安装头文件
install(FILES test.txt  DESTINATION  ${INSTALL_DIR}/txt)                              # 安装其他文件
```

# 变量目录路径说明

/my_project
|-- CMakeLists.txt
|-- README.md
|-- src
|   |-- main.cpp
|   |-- utils
|       |-- utility1.cpp
|       |-- utility2.cpp
|-- include
|   |-- my_project
|       |-- utility1.h
|       |-- utility2.h
|-- tests
|   |-- test_utility1.cpp
|   |-- test_utility2.cpp
|-- docs
|   |-- documentation.md
|-- build (generated during build process)
|-- bin (generated during build process)
|-- lib (generated during build process)

| 变量名                   | 信息                             |
| ------------------------ | -------------------------------- |
| CMAKE_SOURCE_DIR         | 根源码目录，代表my_project       |
| CMAKE_CURRENT_SOURCE_DIR | 当前处理cmakelists.txt所在的目录 |
| PROJECT_SOURCE_DIR       | 表示项目源代码的根目录          |

| CMAKE_CURRENT_SOURCE_DIR |  |
| ------------------------ | - |
