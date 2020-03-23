
cmake_minimum_required(VERSION 3.4.1)


#加载cpp文件到src_files
file(GLOB src_files *.cpp)
#加载c文件到src_giflib
file(GLOB src_giflib giflib/*.c)

#加载头文件
include_directories(${CMAKE_SOURCE_DIR}/giflib)
include_directories(${CMAKE_SOURCE_DIR})


#将生成的 so文件放到 src.main.jniLibs目录下
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

add_library(
        framesequence

        SHARED

        ${src_files}
        ${src_giflib}

)

find_library(
        log-lib

        log)

target_link_libraries(
        framesequence

        log
        android
        jnigraphics)