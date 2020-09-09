#include <jni.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>
//-------------------------调用java普通方法 静态方法-------------------------


//
#define TAG "jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

//这个例子运用了 JNI_OnUnload JNI_OnLoad JNINativeMethod的用法

jobjectArray getStrings(JNIEnv *env, jobject obj, jint count, jstring sample) {
    jobjectArray str_array = NULL;
    jclass cls_string = NULL;
    jmethodID mid_string_init;
    jobject obj_str = NULL;
    const char *c_str_sample = NULL;
    char buff[256];
    int i;

    // 保证至少可以创建3个局部引用（str_array，cls_string，obj_str）
    if (env->EnsureLocalCapacity(3) != JNI_OK) {
        return NULL;
    }
//将string转为了char数组
    c_str_sample = env->GetStringUTFChars(sample, NULL);
    if (c_str_sample == NULL) {
        return NULL;
    }
//拿到string的类文件
    cls_string = env->FindClass("java/lang/String");
    if (cls_string == NULL) {
        return NULL;
    }

    // 获取String的构造方法
    mid_string_init = env->GetMethodID(cls_string, "<init>", "()V");
    if (mid_string_init == NULL) {
        env->DeleteLocalRef(cls_string);
        return NULL;
    }
//    创建一个String对象
    obj_str = env->NewObject(cls_string, mid_string_init);
    if (obj_str == NULL) {
        env->DeleteLocalRef(cls_string);
        return NULL;
    }

    // 创建一个字符串数组
    str_array = env->NewObjectArray(count, cls_string, obj_str);
    if (str_array == NULL) {
        env->DeleteLocalRef(cls_string);
        env->DeleteLocalRef(obj_str);
        return NULL;
    }

    // 给数组中每个元素赋值
    for (i = 0; i < count; ++i) {
        memset(buff, 0, sizeof(buff));   // 初始一下缓冲区
        sprintf(buff, c_str_sample, i);
        jstring newStr = env->NewStringUTF(buff);
        env->SetObjectArrayElement(str_array, i, newStr);
        env->DeleteLocalRef(newStr);   // Warning: 这里如果不手动释放局部引用，很有可能造成局部引用表溢出
    }

    // 释放模板字符串所占的内存
    env->ReleaseStringUTFChars(sample, c_str_sample);
    // 释放局部引用所占用的资源
    env->DeleteLocalRef(cls_string);
    env->DeleteLocalRef(obj_str);

    return str_array;
}


const JNINativeMethod g_methods[] = {
        {"getStrings", "(ILjava/lang/String;)[Ljava/lang/String;", (void *) getStrings}
};


static jclass g_cls_MainActivity = NULL;

//  为了演示其他代码，所以我这段代码先注释掉。 JNI_OnLoad JNI_OnUnload 指定定义一次
/*
    JNI_OnLoad是在Java层调用System.loadLibrary方法加载共享库到虚拟机时的回调函数，在这里适合做一些初始化处理。
    JNI_OnUnload函数是在共享库被卸载的时候由虚拟机回调，适合做资源释放与内存回收的处理
 */
//JNIEXPORT jint
//JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
//    LOGD("JNI_OnLoad method call begin");
//    JNIEnv *env = NULL;
//    jclass cls = NULL;
//    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
//        return JNI_ERR;
//    }
//    // 查找要加载的本地方法Class引用
//    cls = env->FindClass("com/example/androidjni/operaitons/ReferenceOperationActivity");
//    if (cls == NULL) {
//        return JNI_ERR;
//    }
//    // 将class的引用缓存到全局变量中
//    g_cls_MainActivity = static_cast<jclass>(env->NewWeakGlobalRef(cls));
//
//    env->DeleteLocalRef(cls);   // 手动删除局部引用是个好习惯
//
//    // 将java中的native方法与本地函数绑定
//    env->RegisterNatives(g_cls_MainActivity, g_methods,
//                         sizeof(g_methods) / sizeof(g_methods[0]));
//    LOGD("JNI_OnLoad method call end");
//    return JNI_VERSION_1_6;
//}
///*
//    JNI_OnUnload函数是在共享库被卸载的时候由虚拟机回调，适合做资源释放与内存回收的处理
// */
//
//JNIEXPORT void JNICALL
//JNI_OnUnload(JavaVM
//             *vm,
//             void *reserved) {
//    LOGD("JNI_OnUnload method call begin");
//    JNIEnv *env = NULL;
//    if (vm->
//            GetEnv(
//            (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
//        return;
//    }
//    env->UnregisterNatives(g_cls_MainActivity); // so被卸载的时候解除注册
//    env->DeleteWeakGlobalRef(g_cls_MainActivity);
//}
