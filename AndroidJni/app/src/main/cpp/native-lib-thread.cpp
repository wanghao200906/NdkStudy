#include <jni.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>
//-------------------------调用java普通方法 静态方法-------------------------


//线程数
#define NUMTHREADS 1
//
#define TAG "jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型
//全局变量
static JavaVM *g_jvm = NULL;
static jobject g_obj = NULL;

void *thread_funn(void *arg);

void *thread_fun(void *arg);
//由java调用来建立JNI环境

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_operaitons_ThreadOperationActivity_setJNIEnv(JNIEnv *env,
                                                                         jobject thiz) {

    //保存全局JVM以便在子线程中使用
    env->GetJavaVM(&g_jvm);
    //不能直接赋值(g_obj = obj)
    g_obj = (env)->NewGlobalRef(thiz);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_operaitons_ThreadOperationActivity_mainThread(JNIEnv *env,
                                                                          jobject thiz) {
    int i;
    pthread_t pt[NUMTHREADS];

    for (i = 0; i < NUMTHREADS; i++) {
        //创建子线程
        pthread_create(&pt[i], NULL, &thread_fun, (void *) i);
        pthread_create(&pt[i], NULL, &thread_funn, (void *) i);
    }


}


void *thread_fun(void *arg) {
    JNIEnv *env;
    jclass cls;
    jmethodID mid;


    //Attach主线程
//    让新创建的env指向javavm。这样env才可以使用
    if ((g_jvm)->AttachCurrentThread(&env, NULL) != JNI_OK) {
        LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
        return NULL;
    }
    //找到对应的类
    cls = (env)->GetObjectClass(g_obj);
    if (cls == NULL) {
        LOGE("FindClass() Error.....");
        goto error;
    }
    //再获得类中的方法
    mid = (env)->GetStaticMethodID(cls, "fromJNI", "(I)V");
    if (mid == NULL) {
        LOGE("GetMethodID() Error.....");
        goto error;
    }
//    最后调用java中的静态方法
    (env)->CallStaticVoidMethod(cls, mid,  1);

    error:
    //Detach主线程
    if ((g_jvm)->DetachCurrentThread() != JNI_OK) {
        LOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
    }


    pthread_exit(0);
}


void *thread_funn(void *arg) {
    JNIEnv *env;
    jclass cls;
    jmethodID mid;


    //Attach主线程
    if ((g_jvm)->AttachCurrentThread(&env, NULL) != JNI_OK) {
        LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
        return NULL;
    }
    //找到对应的类
    cls = (env)->GetObjectClass(g_obj);
    if (cls == NULL) {
        LOGE("FindClass() Error.....");
        goto error;
    }
    //再获得类中的方法
    mid = env->GetMethodID(cls, "fromJNI2", "()V");
    if (mid == NULL) {
        LOGE("GetMethodID() Error.....");
        goto error;
    }
//    最后调用java中的静态方法
    env->CallVoidMethod(g_obj, mid);

    error:
    //Detach主线程
    if ((g_jvm)->DetachCurrentThread() != JNI_OK) {
        LOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
    }


    pthread_exit(0);
}


//  为了演示其他代码，所以我这段代码先注释掉。 JNI_OnLoad JNI_OnUnload 指定定义一次
/*
    JNI_OnLoad是在Java层调用System.loadLibrary方法加载共享库到虚拟机时的回调函数，在这里适合做一些初始化处理。
    JNI_OnUnload函数是在共享库被卸载的时候由虚拟机回调，适合做资源释放与内存回收的处理
 */
JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad method call begin");
//    不可以这样直接复制
    JNIEnv *env = NULL;
    jclass cls = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    LOGD("JNI_OnLoad method call end");
    return JNI_VERSION_1_6;
}
/*
    JNI_OnUnload函数是在共享库被卸载的时候由虚拟机回调，适合做资源释放与内存回收的处理
 */

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM
             *vm,
             void *reserved) {
    LOGD("JNI_OnUnload method call begin");
    JNIEnv *env = NULL;
    if (vm->
            GetEnv(
            (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    env->DeleteGlobalRef(g_obj);
}
