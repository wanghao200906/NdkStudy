#指定需要CMAKE的最小版本
cmake_minimum_required(VERSION 3.4.1)


#message输出到哪里了呢？
#在这个文件夹下
#/workspaces/MyGitDemo/Android/NdkStudy/AndroidCmake/app/.cxx/cmake/debug/arm64-v8a/build_output.txt
message(${PROJECT_SOURCE_DIR})
message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
# STATUS  WARNING  是各种输出格式，不过在cmake不同的版本在 as上兼容有问题。
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(WARNING "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")


#设置生成的so动态库最后输出的路径
#但是项目会报错 More than one file was found with OS independent path 'lib/armeabi-v7a/libnative-lib.so'
#但是文件确实是输出到指定目录了
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../MySo/${ANDROID_ABI})


# 创建并命名库，将其设置为静态的
# 或共享，并提供其源代码的相对路径。
# 你可以定义多个library库，并使用CMake来构建。
# Gradle会自动将包共享库关联到你的apk程序。
add_library(
        # 设置库的名称
        native-lib

        # 将库设置为共享库。
        SHARED

        # 为源文件提供一个相对路径。
        native-lib.cpp)

#搜索指定预先构建的库和存储路径变量。
#查找系统库，这里查找的是系统日志库，并赋值给变量log-lib
#这个log到底在哪呢？
find_library(
        # 设置path变量的名称
        log-lib

        # 在CMake定位前指定的NDK库名称
        log)

# 指定库CMake应该链接到目标库中，可以链接多个库，比如定义库，构建脚本，预先构建的第三方库或者系统库
target_link_libraries(  # 指定目标库
        native-lib
        # 目标库到日志库的链接 包含在NDK
        ${log-lib})

#其实可以这样写，直接搜索log。就不用 find_library 语句了，但还是尊崇官方思路
#target_link_libraries(  # 指定目标库
#        native-lib
#         目标库到日志库的链接 包含在NDK
#        log)