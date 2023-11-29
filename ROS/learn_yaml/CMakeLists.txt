cmake_minimum_required(VERSION 3.5)
project(yaml_learn)

add_compile_options(-std=c++11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

find_package(yaml-cpp REQUIRED)

include_directories(
  include
  ${catkin_INCLUDE_DIRS} 
  ${PROJECT_SOURCE_DIR}/include
)
 

add_executable(yaml_learn 
                src/yaml_learn.cpp
                src/yaml_learn_node.cpp)   #可执行文件独立出来


target_link_libraries(yaml_learn yaml-cpp ${catkin_LIBRARIES})



