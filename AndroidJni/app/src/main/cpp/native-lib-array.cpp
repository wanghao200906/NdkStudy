#include <jni.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>


//
#define TAG "jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

//-------------------------数组操作-------------------------
//使用 GetIntArrayRegion SetIntArrayRegion
extern "C" JNIEXPORT jintArray JNICALL Java_com_example_androidjni_operaitons_ArrayOperationActivity_updateIntArray(JNIEnv *env,
                                                                             jobject thiz,
                                                                             jintArray data) {
    jint nativeArray[5];//直接在栈上分配的。
//    将data的数组从 0 到5，赋值到nativeArray中
    env->GetIntArrayRegion(data, 0, 5, nativeArray);

    int j;
    for (j = 0; j < 5; j++) {
        nativeArray[j] += 5;
        LOGD("updateIntArra from c int %d\n", nativeArray[j]);
    }
//    将nativeArray数组的数据 从0到5，拷贝到data中。
    env->SetIntArrayRegion(data, 0, 5, nativeArray);
    return data;
}
/*
 * 使用 GetIntArrayElements ReleaseIntArrayElements
 * 数组在栈上
 */
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_androidjni_operaitons_ArrayOperationActivity_updateIntArray2(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jintArray data) {
//   获取java层传过来的数组data的数据，转为一个jint数组
    jint *array = env->GetIntArrayElements(data, NULL);
//    获取数组长度
    jsize size = env->GetArrayLength(data);
    int j;
    for (j = 0; j < size; j++) {
        array[j] += 3;
        LOGD("updateIntArra2 from c int %d\n", array[j]);
    }

//   释放data array资源
    env->ReleaseIntArrayElements(data, array, 0);
    return data;
}
/*
 * 使用 GetIntArrayRegion
 * 创建了缓冲区
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_androidjni_operaitons_ArrayOperationActivity_sumArray(JNIEnv *env, jobject thiz,
                                                                       jintArray arr) {
    jint i, sum = 0;
    jint *c_array;
    jint arr_len;
    //1. 获取数组长度
    arr_len = env->GetArrayLength(arr);
    //2. 根据数组长度和数组元素的数据类型申请存放java数组元素的缓冲区
    c_array = (jint *) malloc(sizeof(jint) * arr_len);
    //3. 初始化缓冲区
    memset(c_array, 0, sizeof(jint) * arr_len);
    printf("arr_len = %d ", arr_len);
    //4. 拷贝Java数组中的所有元素到缓冲区中
    env->GetIntArrayRegion(arr, 0, arr_len, c_array);
    for (i = 0; i < arr_len; i++) {
        sum += c_array[i];  //5. 累加数组元素的和
    }
    free(c_array);  //6. 释放存储数组元素的缓冲区
    LOGD("sum:%d\n", sum);
    return sum;
}
//使用 GetIntArrayRegion SetIntArrayRegion ReleaseIntArrayElements
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_androidjni_operaitons_ArrayOperationActivity_sumArray2(JNIEnv *env, jobject thiz,
                                                                        jintArray arr) {

    jint i, sum = 0;
    jint *c_array;
    jint arr_len;
    // 可能数组中的元素在内存中是不连续的，JVM可能会复制所有原始数据到缓冲区，然后返回这个缓冲区的指针
//    isCopy 表示返回的数组指针是原始数组，还是拷贝原始数据到临时缓冲区的指针，如果是JNI_TRUE：表示临时缓冲区数组指针，JNI_FALSE：表示临时原始数组指针。开发当中，我们并不关心它从哪里返回的数组指针，这个参数填NULL即可
    c_array = env->GetIntArrayElements(arr, NULL);
//    但在获取到的指针必须做校验，因为当原始数据在内存当中不是连续存放的情况下，JVM会复制所有原始数据到一个临时缓冲区，并返回这个临时缓冲区的指针。有可能在申请开辟临时缓冲区内存空间时，会内存不足导致申请失败，这时会返回NULL。
    if (c_array == NULL) {
        return 0;   // JVM复制原始数据到缓冲区失败
    }
    arr_len = env->GetArrayLength(arr);
    printf("arr_len = %d\n", arr_len);
    for (i = 0; i < arr_len; i++) {
        sum += c_array[i];
    }
    env->ReleaseIntArrayElements(arr, c_array, 0); // 释放可能复制的缓冲区
    return sum;

}
/*
 *  Get/ReleasePrimitiveArrayCritical
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_androidjni_operaitons_ArrayOperationActivity_sumArray3(JNIEnv *env, jobject thiz,
                                                                        jintArray arr) {
    jint i, sum = 0;
    jint *c_array;
    jint arr_len;
    jboolean isCopy;
    c_array = static_cast<jint *>(env->GetPrimitiveArrayCritical(arr, &isCopy));
    LOGD("isCopy: %d \n", isCopy);
    if (c_array == NULL) {
        return 0;
    }
    arr_len = env->GetArrayLength(arr);
    LOGD("arr_len = %d\n", arr_len);
    for (i = 0; i < arr_len; i++) {
        sum += c_array[i];
    }
    env->ReleasePrimitiveArrayCritical(arr, c_array, 0);
    return sum;

}
/*
1、对于小量的、固定大小的数组，应该选择Get/SetArrayRegion函数来操作数组元素是效率最高的。
 因为这对函数要求提前分配一个C临时缓冲区来存储数组元素，你可以直接在Stack（栈）上或用malloc在堆上来动态申请，当然在栈上申请是最快的。
 有童鞋可能会认为，访问数组元素还需要将原始数据全部拷贝一份到临时缓冲区才能访问而觉得效率低？
 我想告诉你的是，像这种复制少量数组元素的代价是很小的，几乎可以忽略。这对函数的另外一个优点就是，
 允许你传入一个开始索引和长度来实现对子数组元素的访问和操作（SetArrayRegion函数可以修改数组），
 不过传入的索引和长度不要越界，函数会进行检查，如果越界了会抛出ArrayIndexOutOfBoundsException异常。

2、如果不想预先分配C缓冲区，并且原始数组长度也不确定，而本地代码又不想在获取数组元素指针时被阻塞的话，
 使用Get/ReleasePrimitiveArrayCritical函数对，就像Get/ReleaseStringCritical函数对一样，
 使用这对函数要非常小心，以免死锁。

3、Get/Release<type>ArrayElements系列函数永远是安全的，JVM会选择性的返回一个指针，
 这个指针可能指向原始数据，也可能指向原始数据的复制。

 */

/*

 JNI提供了两个函数来访问对象数组，GetObjectArrayElement返回数组中指定位置的元素，
 SetObjectArrayElement修改数组中指定位置的元素。与基本类型不同的是，
 我们不能一次得到数据中的所有对象元素或者一次复制多个对象元素到缓冲区。
 因为字符串和数组都是引用类型，只能通过Get/SetObjectArrayElement这样的JNI函数来访问字符串数组或者数组中的数组元素。
 下面的例子通过调用一个本地方法来创建一个二维的int数组，然后打印这个二维数组的内容：

 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_androidjni_operaitons_ArrayOperationActivity_initInt2DArray(JNIEnv *env,
                                                                             jobject thiz,
                                                                             jint size) {
    jobjectArray result;
    jclass clsIntArray;
    jint i, j;
    // 1.获得一个int型二维数组类的引用  int[] 类型
    clsIntArray = env->FindClass("[I");
    if (clsIntArray == NULL) {
        return NULL;
    }
    // 2.创建一个数组对象（里面每个元素用clsIntArray表示）
//    NewObjectArray创建一个新的数组，这个数组里面的元素类型用intArrCls(int[])类型来表示 ，这样resule就是一个二维数组了
    result = env->NewObjectArray(size, clsIntArray, NULL);
    if (result == NULL) {
        return NULL;
    }

    // 3.为数组元素赋值
    for (i = 0; i < size; ++i) {
        jint buff[256];
//       用NewIntArray创建一个JNI的int数组，并为每个数组元素分配空间
        jintArray intArr = env->NewIntArray(size);
        if (intArr == NULL) {
            return NULL;
        }
//        给buff数组分配元素
        for (j = 0; j < size; j++) {
            buff[j] = i + j;
        }
//        用SetIntArrayRegion把buff[]缓冲中的内容复制到新分配的一维数组中去
        env->SetIntArrayRegion(intArr, 0, size, buff);
//        用SetObjectArrayElement把intArr数组中的的内容复制到新分配的一维数组中去
        env->SetObjectArrayElement(result, i, intArr);
//        为了避免在循环内创建大量的JNI局部引用，造成JNI引用表溢出
//        DeleteLocalRef将新创建的jintArray引用从引用表中移除
//        在JNI中，只有jobject以及子类属于引用变量，会占用引用表的空间，jint，jfloat，jboolean等都是基本类型变量，
//        不会占用引用表空间，即不需要释放。引用表最大空间为512个，如果超出这个范围，JVM就会挂掉。
        env->DeleteLocalRef(intArr);
    }
    return result;

}