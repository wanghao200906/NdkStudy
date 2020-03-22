
# Build one shared lib. When we build, we set the bin to $user/tmp, and
# remove it after build complete, so only the distribution place could be
# used for application linking.
cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

add_library(gperf SHARED src/gperf.c)

# copy out the lib binary and remove generated files
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../app3_C)
set_target_properties(gperf
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY
        "${distribution_DIR}/gperf/lib/${ANDROID_ABI}")
add_custom_command(TARGET gperf POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E
        copy "${CMAKE_CURRENT_SOURCE_DIR}/src/gperf.h"
        "${distribution_DIR}/gperf/include/gperf.h"
        COMMENT "Copying gperf to output directory")