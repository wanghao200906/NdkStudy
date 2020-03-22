
# Build a static lib and copy it into distribution place for independent app to use
# we could not delete the bin directory is because android studio would error out
# when it checks target's existance. Only distribution place is used as import to app

cmake_minimum_required(VERSION 3.4.1)

#显示详细的原始编译信息，主要用于定位一些链接错误，看看库路径什么的是否配置对。
set(CMAKE_VERBOSE_MAKEFILE on)

#STATIC 是生成 静态库 就是生成 libgmath.a
add_library(gmath STATIC src/gmath.c)
#这样不写STATIC或者SHARED默认的是STATIC
#add_library(gmath   src/gmath.c)

# 将生成的库文件 放到一个 文件夹下。这里是app3_C文件夹
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../app3_C)


#set_target_properties 就是给库配置一些参数
set_target_properties(
        #
        gmath
        #固定的就是PROPERTIES
        PROPERTIES
        #        可以传入多个 key  value的参数。空格隔开
        #        key                          value
        ARCHIVE_OUTPUT_DIRECTORY "${distribution_DIR}/gmath/lib/${ANDROID_ABI}"
        #        将生成的库的名字改为hello
#        OUTPUT_NAME "hello"
)

#add_custom_command 是自定义命令 暂时没有理解透彻。
#这个功能的意思就是将 头文件 复制到 特定的目录中取
add_custom_command(
        # TARGET是模板，必须写的第一个参数
        TARGET
        # gmath是要操作的库
        gmath
        #  POST_BUILD这个位置有三个参数
        #  PRE_BUILD - 命令将会在其他依赖项执行前执行
        #  PRE_LINK - 命令将会在其他依赖项执行完后执行
        #  POST_BUILD - 命令将会在目标构建完后执行。
        POST_BUILD
#
        COMMAND "${CMAKE_COMMAND}" -E
        copy "${CMAKE_CURRENT_SOURCE_DIR}/src/gmath.h"
        "${distribution_DIR}/gmath/include/gmath.h"
        #                   **** the following 2 lines are for potential future debug purpose ****
        #                   COMMAND "${CMAKE_COMMAND}" -E
        #                   remove_directory "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Copying gmath to output directory")


#一些打印信息
message("CMAKE_SOURCE_DIR：${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR：${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_LIST_DIR：${CMAKE_CURRENT_LIST_DIR}")

#get_target_property和set_target_properties是对应的。一个是设置一个是获取
get_target_property(OUTPUT_VALUE gmath OUTPUT_NAME)
get_target_property(OUTPUT_VALUE2 gmath ARCHIVE_OUTPUT_DIRECTORY)

MESSAGE(STATUS "This is the hello OUTPUT_NAME: " ${OUTPUT_VALUE})
MESSAGE(STATUS "This is the hello ARCHIVE_OUTPUT_DIRECTORY: " ${OUTPUT_VALUE2})