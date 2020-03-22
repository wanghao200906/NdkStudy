
# Generate one static lib and one shared lib, copy them into
# ${project_dir}/distribution for other indepdendent applications
# to use.
cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

#add_subdirectory添加子目录
#向当前工程添加 子目录的功能
#这里gmath和gperf 文件夹中分别由cmakelist。在这里统一调用就会执行他们的cmakelist。
add_subdirectory(gmath)
add_subdirectory(gperf)
