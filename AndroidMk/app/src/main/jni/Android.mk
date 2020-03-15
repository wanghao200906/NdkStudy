LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#LOCAL_MODULE的名称要和之前System.loadLibrary("hello-jni");中的名称一致;
LOCAL_MODULE := hello-jni
LOCAL_SRC_FILES := hello-jni.c add.c mul.c sub.c

#LOCAL_LDLIBS就是天机库用的
# -l 是默认的 log就是log库
# for logging
LOCAL_LDLIBS    += -llog
# for native asset manager
LOCAL_LDLIBS    += -landroid



include $(BUILD_SHARED_LIBRARY)
