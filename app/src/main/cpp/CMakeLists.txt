# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.18.1)

# 创建一个变量 source_file 它的值就是src/main/cpp/ 所有的.cpp文件
file(GLOB source_file *.cpp)

add_library(
        myplayer
        SHARED
        ${source_file})

include_directories("ffmpeg-include", "include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}")
message("${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}")

target_link_libraries(
        myplayer
        avformat
        avcodec
        avfilter
        avutil
        swresample
        swscale
        log
        z)