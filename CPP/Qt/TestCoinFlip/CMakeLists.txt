cmake_minimum_required(VERSION 3.5)

project(TestCoinFlip LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)

if(ANDROID)
  add_library(TestCoinFlip SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    res.qrc
    mypushbutton.cpp
    mypushbutton.h
    choosescene.cpp
    choosescene.h
    playscene.cpp
    playscene.h
    mycoin.cpp
    mycoin.h
    dataconfig.cpp
    dataconfig.h
    zqh.qrc
    res.qrc
  )
else()
  add_executable(TestCoinFlip
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    res.qrc
    mypushbutton.cpp
    mypushbutton.h
    choosescene.cpp
    choosescene.h
    playscene.cpp
    playscene.h
    mycoin.cpp
    mycoin.h
    dataconfig.cpp
    dataconfig.h
    zqh.qrc
    res/
  )
endif()

target_link_libraries(TestCoinFlip PRIVATE Qt5::Widgets)
