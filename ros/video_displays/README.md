# video_displays

##  git clone地址
    git clone http://10.88.13.31:9080/yangnianshun/video_displays.git

## 环境搭建

### mqtt环境搭建

####基础环境搭建
    sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui
    
    sudo apt-get install fakeroot devscripts dh-make lsb-release
    
    sudo apt-get install libssl-dev
    
    sudo apt-get install doxygen graphviz

#### Paho C安装
    git clone https://github.com/eclipse/paho.mqtt.c.git
    cd paho.mqtt.c
    git checkout v1.3.8
    
    cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
    
    sudo cmake --build build/ --target install
    
    sudo ldconfig

#### Paho C++安装
    git clone https://github.com/eclipse/paho.mqtt.c.git
    cd paho.mqtt.c
    git checkout v1.3.8
    
    cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
    
    sudo cmake --build build/ --target install
    
    sudo ldconfig

### websocket++环境搭建 （本项目使用的0.8.1版本）
    前置依赖：
    dpkg -s libboost-dev   #查看libboost-dev是否安装成功
    sudo apt-get install libboost-dev

    命令行安装：
    sudo apt install libwebsocketpp-dev #安装命令
    sudo apt install libwebsocketpp-dev #卸载命令

    源码安装0.8.1版本命令：

        下载的源码地址：https://github.com/zaphoyd/websocketpp/releases/tag/0.8.1
        mkdir build
        cd build
        cmake ..
        make
        sudo make install

### openssl版本为1.1.1l版本

### opencv版本为3.4.6

## 模拟三架无人机飞行用例

    rosbag play -l drone_1_2023-03-20-19-10-18.bag /camera/color/image_raw/compressed:=/drone_1/camera/color/image_raw/compressed  /camera/depth/image_rect_raw:=/drone_1/camera/depth/image_rect_raw
    
    rosbag play -l drone_2_2023-03-20-19-33-42.bag /camera/color/image_raw/compressed:=/drone_2/camera/color/image_raw/compressed  /camera/depth/image_rect_raw:=/drone_2/camera/depth/image_rect_raw
    
    rosbag play -l drone_3_2023-03-20-19-34-43.bag /camera/color/image_raw/compressed:=/drone_3/camera/color/image_raw/compressed  /camera/depth/image_rect_raw:=/drone_3/camera/depth/image_rect_raw


##运行
### 修改launch文件参数
    <node pkg="websocket_video_package" name="websocket_video_package_node" type="websocket_video_package_node" output="screen">
        <param name="address" value="tcp://10.88.105.20:1883" />  //修改mqtt的服务器地址 
        <param name="clientid" value="drone_video"/>
    </node>
### 运行命令
    roslaunch websocket_video_package videonode.launch
