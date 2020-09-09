#include <jni.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>


//使用命名空间可以不用了。
using namespace std;

/*
    因为native-lib.cpp 后缀是cpp。所以里面调用的方法都是c++的调用方式

    JNI中针对C++的代码是：
                 jstring NewStringUTF(const char* bytes)
                { return functions->NewStringUTF(this, bytes); }

   C++中调用方式
            JNIEXPORT jstring JNICALL Java_cn_itcast_cpp_DemoActivity_helloInC (JNIEnv * env, jobject obj){
                    return  env->NewStringUTF("haha from c");
            }


    JNI中针对C的代码是：
            　jstring     (*NewStringUTF)(JNIEnv*, const char*);
    C中调用方式：
            　　(*env)->NewStringUTF(env,"haha from c");

 */

//
#define TAG "jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

//-------------------------字符串操作-------------------------

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_androidjni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    auto b = 1;
    printf("%d", b);
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_MainActivity_updateFile(JNIEnv *env, jobject thiz, jstring path) {
    //    生成native的char类型的指针
    const char *file_path = env->GetStringUTFChars(path, NULL);
    if (file_path != NULL) {
        LOGD("from c file_path %s\n", file_path);
    }
//    打开一个文件
    FILE *file = fopen(file_path, "a+");
    if (file != NULL) {
        LOGD("from c open file success");
    } else {
        LOGD("from c failed open file success");
        //释放 资源
        env->ReleaseStringUTFChars(path, file_path);
        return;
    }
//    写入的数据
    char data[] = "I AM A BOY";
//    data是写入的数据
//     strlen(data)是写入数据有多长
//      1 代表写几次
//    file代表往哪里写数据
    int count = fwrite(data, strlen(data), 1, file);
    if (count > 0) {
        LOGD("from c write file success");
    }
    if (file != NULL) {
        //关闭文件
        fclose(file);
    }
    //释放 资源
    env->ReleaseStringUTFChars(path, file_path);
}