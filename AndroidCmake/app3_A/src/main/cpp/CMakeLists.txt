
cmake_minimum_required(VERSION 3.4.1)

# 获取资源的目录
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../app3_C)

#生成lib_gmath.so文件
add_library(
        lib_gmath
        STATIC
#        代码在静态库里面，所以要导入这里使用IMPORTED
        IMPORTED)
#给lib_gmath库导入libgmath.a文件。
#意思就是使用libgmath.a文件生成了lib_gmath.a文件。
set_target_properties(lib_gmath PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/gmath/lib/${ANDROID_ABI}/libgmath.a)

# 生成 so库。也是用IMPORTED进行导入
add_library(lib_gperf SHARED IMPORTED)
set_target_properties(lib_gperf PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/gperf/lib/${ANDROID_ABI}/libgperf.so)


# 给c++编译器支持 c++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


#生成 hello-libs.so库
add_library(hello-libs SHARED
        hello-libs.cpp)


#引用指定目录的头文件
target_include_directories(hello-libs PRIVATE
        ${distribution_DIR}/gmath/include
        ${distribution_DIR}/gperf/include)

#这里要应用 lib_gmath和lib_gperf
target_link_libraries(hello-libs
        android
        lib_gmath
        lib_gperf
        log)