////
//// Created by 王浩 on 2020/3/15.
////

#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include "head.h"

#define TAG "jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

/*
 * Class:     com_androidmk_example_MainActivity
 * Method:    nativeTestAdd
 * Signature: (II)I
 */
jint Java_com_androidmk_example_MainActivity_nativeTestAdd
        (JNIEnv *env, jobject this, jint a, jint b) {
    LOGD("my test");
    return 1;
}
//
///*
// * Class:     com_androidmk_example_MainActivity
// * Method:    nativeTestMul
// * Signature: (II)I
// */
//JNIEXPORT jint JNICALL Java_com_androidmk_example_MainActivity_nativeTestMul
//        (JNIEnv *env, jobject this, jint a, jint b) {
//    return mul(a, b);
//}
//
///*
// * Class:     com_androidmk_example_MainActivity
// * Method:    nativeTestSub
// * Signature: (II)I
// */
//JNIEXPORT jint JNICALL Java_com_androidmk_example_MainActivity_nativeTestSub
//        (JNIEnv *env, jobject this, jint a, jint b) {
//    return sub(a, b);
//}
