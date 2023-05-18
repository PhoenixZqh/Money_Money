cmake_minimum_required(VERSION 3.0.2)
project(cudaStudy)

## Compile as C++11, supported in ROS Kinetic and newer
set(CUDA_GEN_CODE "-gencode=arch=compute_86,code=sm_86")  #不同显卡对应不同的代码https://developer.nvidia.com/zh-cn/cuda-gpus#compute
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++11 -O2 -Xcompiler -fPIC -g -w ${CUDA_GEN_CODE}")


add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
set(CUDA_TOOLKIT_ROOT_DIR       "/usr/local/cuda")
set(CUDNN_DIR                   "/usr/local/cuda")

find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cudaStudy
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)



include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${CUDA_TOOLKIT_ROOT_DIR}/include
  ${PROJECT_SOURCE_DIR}/include
)

link_directories(
  /usr/local/lib
  ${TENSORRT_DIR}/lib
  ${CUDA_TOOLKIT_ROOT_DIR}/lib64
  ${CUDNN_DIR}/lib64
)

# file(GLOB_RECURSE cpp_srcs ${PROJECT_SOURCE_DIR}/src/*.cpp)
# file(GLOB_RECURSE c_srcs ${PROJECT_SOURCE_DIR}/src/*.c)
# file(GLOB_RECURSE cuda_srcs ${PROJECT_SOURCE_DIR}/src/*.cu)
# cuda_add_library(cucodes SHARED ${cuda_srcs})


CUDA_ADD_EXECUTABLE(helloWorld 
  src/helloWorld.cu
)

CUDA_ADD_EXECUTABLE(blockIdx_Dim 
  src/blockIdx_Dim.cu
)

CUDA_ADD_EXECUTABLE(grid_block_size 
  src/grid_block_size.cu
)

CUDA_ADD_EXECUTABLE(sumArrays 
  src/sumArrays.cu
)

CUDA_ADD_EXECUTABLE(getThreadId 
  src/getThreadId.cu
)

CUDA_ADD_EXECUTABLE(getGpuInfo 
  src/getGpuInfo.cu
)

CUDA_ADD_EXECUTABLE(check1 
  src/check1.cu
)
target_link_libraries(check1 cuda
)

CUDA_ADD_EXECUTABLE(check2
  src/check2.cu
)
target_link_libraries(check2 cuda
)

CUDA_ADD_EXECUTABLE(context
  src/context.cu
)
target_link_libraries(context cuda
)


CUDA_ADD_EXECUTABLE(memAlloc
  src/memAlloc.cu
)
target_link_libraries(memAlloc cuda
)

CUDA_ADD_EXECUTABLE(learn_cuda1
  src/learn_cuda1.cu
)
target_link_libraries(learn_cuda1 cuda
)


CUDA_ADD_EXECUTABLE(Parallel_efficient
  src/Parallel_efficient.cu
)
target_link_libraries(Parallel_efficient cuda
)


CUDA_ADD_EXECUTABLE(Scanning_parallel
  src/Scanning_parallel.cu
)
target_link_libraries(Scanning_parallel cuda
)

CUDA_ADD_EXECUTABLE(atomic
  src/atomic.cu
)
target_link_libraries(atomic cuda
)

file(GLOB_RECURSE trt_srcs ${PROJECT_SOURCE_DIR}/*.cpp)
# file(GLOB_RECURSE trt_cus ${PROJECT_SOURCE_DIR}/*.cu)
file(GLOB_RECURSE trt_include ${PROJECT_SOURCE_DIR}/*.h*)

add_executable(warp_affine src/affine.cpp)
add_library(trt SHARED ${trt_srcs})
cuda_add_library(trt_plugin SHARED src/affine.cu)

target_link_libraries(warp_affine trt trt_plugin)
target_link_libraries(warp_affine ${OpenCV_LIBS})
target_link_libraries(warp_affine  cuda)

