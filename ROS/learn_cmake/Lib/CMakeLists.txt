cmake_minimum_required(VERSION 3.5)

set(INSTALL_DIR /home/GitHub/Money_Money/ROS/learn_cmake/Lib/install)

project(hello_include)

add_library(my_library SHARED src/hello.cpp)   # 将文件添加到库   .a 是静态库、 .so 是共享库
add_executable(static_lib src/main.cpp)   #可执行文件独立出来

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



install(TARGETS my_library  DESTINATION ${INSTALL_DIR}/lib) # 安装库
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/  DESTINATION ${INSTALL_DIR}/include) #安装头文件
install(FILES test.txt  DESTINATION  ${INSTALL_DIR}/txt)  # 安装其他文件
