cmake_minimum_required(VERSION 3.0.2)
project(learn_gtest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)


add_subdirectory(3rd_party/googletest)


find_package(catkin REQUIRED)
find_package(OpenCV  REQUIRED )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES learn_gtest
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)


include_directories(
    googletest/include
)

enable_testing()


add_executable(
  test1
  src/test1.cpp
)
target_link_libraries(
  test1
  gtest_main
)
include(GoogleTest)
gtest_discover_tests(test1)

add_executable(
  demo1
  src/demo1.cpp
)
target_link_libraries(
  demo1
  ${OpenCV_LIBS}
  gtest_main
)
include(GoogleTest)
gtest_discover_tests(demo1)

add_executable(
  demo2
  src/demo2.cpp
)
target_link_libraries(
  demo2
  ${OpenCV_LIBS}
  gtest_main
)
include(GoogleTest)
gtest_discover_tests(demo2)

add_executable(
  demo3
  src/demo3.cpp
)
target_link_libraries(
  demo3
  ${OpenCV_LIBS}
  gtest_main
)
include(GoogleTest)
gtest_discover_tests(demo3)


