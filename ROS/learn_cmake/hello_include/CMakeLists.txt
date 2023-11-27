cmake_minimum_required(VERSION 3.5)

project(hello_include)
 
# 创建包含源文件的变量
# set(
# SOURCES
# src/hello.cpp
# src/main.cpp
# )

file(GLOB SOURCES src/*.cpp)   #这种方式更加简洁

add_executable(hello_include ${SOURCES})

# 将头文件路径添加到可执行文件
target_include_directories(
    hello_include
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)