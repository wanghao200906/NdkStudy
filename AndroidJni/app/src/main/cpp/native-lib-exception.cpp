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
static jclass g_cls_MainActivity = NULL;

void JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg);

//native调用java代码，java代码报错，直接把异常跑出给java
void callExceptionMethod01(JNIEnv *env, jobject obj) {
    jclass cls = env->GetObjectClass(obj);
    jmethodID mth_static_method = env->GetMethodID(cls, "localMethod1", "()V");
    env->CallVoidMethod(obj, mth_static_method);
//    调用CallVoidMethod会发生异常，但是jni并不会停止会执行下面的代码
//    ExceptionOccurred 和  ExceptionCheck都可以做判断
//ExceptionCheck返回 jboolean
//ExceptionOccurred 返回 jthrowable
//    if (env->ExceptionOccurred()) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe(); //打印这个异常的堆栈信息
        env->ExceptionClear();//清除异常堆栈信息的缓冲区（如果不清除，后面调用ThrowNew抛出的异常堆栈信息会覆盖前面的异常信息）
        jclass cls_exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(cls_exception,
                      "call localMethod1 method ndk error");//调用ThrowNew函数手动抛出一个java.lang.Exception异常。
        return;
    }
    env->DeleteLocalRef(cls);
}

//使用ExceptionOccurred来检测异常
void callExceptionMethod02(JNIEnv *env, jobject obj) {
    jclass _jcalsss = env->GetObjectClass(obj);
//  1 会报错   java.lang.NoSuchFieldError: no type "Ljava/lang/String" found and so no field "name2" could be found in class "Lcom/example/practise14_ndkjni/MainActivity;" or its superclasses
    jfieldID _jfieldID = env->GetFieldID(_jcalsss, "name2", "Ljava/lang/String;");
//  2  检测异常
    jthrowable _jthrowable = env->ExceptionOccurred();
    if (_jthrowable != NULL) {
//  3    为了保证java的代码能继续执行，清除异常
        env->ExceptionClear();
        _jfieldID = env->GetFieldID(_jcalsss, "name", "Ljava/lang/String;");
    }
//  4  转化
    jstring _jstring = static_cast<jstring>(env->GetObjectField(obj, _jfieldID));
    char *str = const_cast<char *>(env->GetStringUTFChars(_jstring, NULL));

    //假使c++有异常，java层面如何try
    //int strcmp(const char* _Nonnull, const char* _Nonnull) __attribute_pure__;
    if (strcmp(str, "www") != 0) {
        //抛出异常（java的异常
        // ）
//        jclass newThrow = env->FindClass("java/lang/IllegalArgumentException");
//        env->ThrowNew(newThrow, "非法参数");
        JNU_ThrowByName(env, "java/lang/IllegalArgumentException", "非法参数");
    }

}

//写一个抛出异常的工具类
void JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg) {
    // 查找异常类
    jclass cls = env->FindClass(name);
    /* 如果这个异常类没有找到，VM会抛出一个NowClassDefFoundError异常 */
    if (cls != NULL) {
        env->ThrowNew(cls, msg);  // 抛出指定名字的异常
    }
    /* 释放局部引用 */
    env->DeleteLocalRef(cls);
}

const JNINativeMethod methods[] = {
        {"callExceptionMethod01", "()V", (void *) callExceptionMethod01},
        {"callExceptionMethod02", "()V", (void *) callExceptionMethod02}
};
//  为了演示其他代码，所以我这段代码先注释掉。 JNI_OnLoad JNI_OnUnload 指定定义一次
//
///*
//    JNI_OnLoad是在Java层调用System.loadLibrary方法加载共享库到虚拟机时的回调函数，在这里适合做一些初始化处理。
//    JNI_OnUnload函数是在共享库被卸载的时候由虚拟机回调，适合做资源释放与内存回收的处理
// */
//JNIEXPORT jint
//JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
//    LOGD("JNI_OnLoad method call begin");
//    JNIEnv *env = NULL;
//    jclass cls = NULL;
//    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
//        return JNI_ERR;
//    }
//    // 查找要加载的本地方法Class引用
//    cls = env->FindClass("com/example/androidjni/operaitons/ExceptionOperationActivity");
//    if (cls == NULL) {
//        return JNI_ERR;
//    }
//    // 将class的引用缓存到全局变量中
//    g_cls_MainActivity = static_cast<jclass>(env->NewWeakGlobalRef(cls));
//    env->DeleteLocalRef(cls);   // 手动删除局部引用是个好习惯
//
//    // 将java中的native方法与本地函数绑定
//    env->RegisterNatives(g_cls_MainActivity, methods,
//                         sizeof(methods) / sizeof(methods[0]));
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
//