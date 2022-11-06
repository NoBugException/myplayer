# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.18.1)

add_library(
        myplayer
        SHARED
        native-lib.cpp)

include_directories("ffmpeg-include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}")
message("${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}")

target_link_libraries(
        myplayer
        avcodec
        avfilter
        avformat
        avutil
        swresample
        swscale
        log)