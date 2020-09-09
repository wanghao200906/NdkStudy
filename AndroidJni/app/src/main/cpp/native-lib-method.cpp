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

////调用staticMessage方法
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_bean_Hello_callStaticMethod(JNIEnv *env, jclass clazz, jint i) {
//    1、从classpath路径下搜索com/example/androidjni/bean/Hello这个类，并返回该类的Class对象
    jclass cls_hello = env->FindClass("com/example/androidjni/bean/Hello");
    if (cls_hello == NULL) {
        return;
    }



//    2 从clazz类中查找staticMethod方法
//  cls_hello 是从哪个类找方法
//  staticMessage类的名字
// "(Ljava/lang/String;)V"是方法的签名
    jmethodID mtd_static_method = env->GetStaticMethodID(cls_hello, "staticMethod",
                                                         "(Ljava/lang/String;)V");
    if (mtd_static_method == NULL) {
        return;
    }


//    3 获取一个字符串
    jstring data = env->NewStringUTF("call static method");


//    4 用CallStaticVoidMethod调用clazz类的staticMethod静态方法
//cls_hello调用哪个类的方法
//mtd_static_method方法的引用
//给方法传递的值
    env->CallStaticVoidMethod(cls_hello, mtd_static_method, data);


//   5  删除局部引用
/*
      JVM会自动释放所有局部引用变量所占的内存空间。
      但还是手动释放一下比较安全，因为在JVM中维护着一个引用表，用于存储局部和全局引用变量，
      经测试在Android NDK环境下，这个表的最大存储空间是512个引用，如果超过这个数就会造成引用表溢出，JVM崩溃。
      在PC环境下测试，不管申请多少局部引用也不释放都不会崩，
      我猜可能与JVM和Android Dalvik虚拟机实现方式不一样的原因。
      所以有申请就及时释放是一个好的习惯！

 */


    env->DeleteLocalRef(cls_hello);
    env->DeleteLocalRef(data);

}
////调用Hello的staticMessage方法 并且修改变量
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_bean_Hello_callStaticMethod2(JNIEnv *env, jclass clazz, jint i) {


//    找到方法所在的类 com/example/androidjni/bean/Hello
    jclass cls_hello = env->FindClass("com/example/androidjni/bean/Hello");
    if (cls_hello == NULL) {
        return;
    }
//    找到对应的方法
//  cls_hello 是从哪个类找方法
//  staticMessage类的名字
// "(Ljava/lang/String;)V"是方法的签名
    jmethodID mtd_static_method = env->GetStaticMethodID(cls_hello, "staticMethod",
                                                         "(Ljava/lang/String;)V");
    if (mtd_static_method == NULL) {
        return;
    }
//    拿到静态变量的id
    jfieldID fld_name = env->GetStaticFieldID(cls_hello, "name", "Ljava/lang/String;");
    if (fld_name == NULL) {
        return;
    }

    jstring name = env->NewStringUTF("name name");
//修改静态变量的值
    env->SetStaticObjectField(cls_hello, fld_name, name);

//    获取一个字符串
    jstring data = env->NewStringUTF("call static method");
//    CallStaticVoidMethod调用静态方法
//cls_hello调用哪个类的方法
//mtd_static_method方法的引用
//给方法传递的值
    env->CallStaticVoidMethod(cls_hello, mtd_static_method, data);
    env->DeleteLocalRef(cls_hello);
    env->DeleteLocalRef(data);
    env->DeleteLocalRef(name);
}


////创建Hello实例，调用实例方法
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_bean_Hello_callInstanceMethod(JNIEnv *env, jobject thiz, jlong i) {

    jclass cls_hello = env->FindClass("com/example/androidjni/bean/Hello");
    if (cls_hello == NULL) {
        return;
    }
// 获取方法域的id。
    jmethodID mtd_method = env->GetMethodID(cls_hello, "method", "(Ljava/lang/String;)V");

    if (mtd_method == NULL) {
        return;
    }

//    获取类的构造方法的id ,创建一个类必须得执行构造方法
    jmethodID mtd_construct = env->GetMethodID(cls_hello, "<init>", "()V");
    if (mtd_construct == NULL) {
        return;
    }
//创建cls_hello这个类，这个类创建需要调用构造方法，拿到新创建的类
    jobject hello = env->NewObject(cls_hello, mtd_construct);
    if (hello == NULL) {
        return;
    }
//    创建string
    jstring data = env->NewStringUTF("call instance method");
//    hello 是new出来的类的对象
//    mtd_method 就是method方法
//    data 就是要传入的数据
    env->CallVoidMethod(hello, mtd_method, data);

    env->DeleteLocalRef(data);
    env->DeleteLocalRef(cls_hello);
    env->DeleteLocalRef(hello);

}
////创建Hello实例，调用实例方法，又修改普通变量
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_bean_Hello_callInstanceMethod2(JNIEnv *env, jobject thiz, jlong i) {

//    获取类的对象
    jclass cls_hello = env->FindClass("com/example/androidjni/bean/Hello");
    if (cls_hello == NULL) {
        return;
    }
// 获取方法域的id。
    jmethodID mtd_method = env->GetMethodID(cls_hello, "method", "(Ljava/lang/String;)V");

    if (mtd_method == NULL) {
        return;
    }

//    获取类的构造方法的id
    jmethodID mtd_construct = env->GetMethodID(cls_hello, "<init>", "()V");
    if (mtd_construct == NULL) {
        return;
    }
//创建cls_hello这个类，这个类创建需要调用构造方法，拿到新创建的类
    jobject hello = env->NewObject(cls_hello, mtd_construct);
    if (hello == NULL) {
        return;
    }

    jfieldID jfieldId = env->GetFieldID(cls_hello, "name2", "Ljava/lang/String;");
    if (jfieldId == NULL) {
        return;
    }
    jstring nameData = env->NewStringUTF("new name2");
    env->SetObjectField(hello, jfieldId, nameData);

//    创建string
    jstring data = env->NewStringUTF("call instance method");
//    hello 是new出来的类的对象
//    mtd_method 就是method方法
//    data 就是要传入的数据
    env->CallVoidMethod(hello, mtd_method, data);

    env->DeleteLocalRef(data);
    env->DeleteLocalRef(cls_hello);
    env->DeleteLocalRef(hello);
    env->DeleteLocalRef(nameData);

}


////获取MethodOperationActivity对象直接调用静态方法
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_operaitons_MethodOperationActivity_callStaticMethod(JNIEnv *env,
                                                                                jobject thiz,
                                                                                jint i) {

    jclass cls = env->GetObjectClass(thiz);
    jmethodID mth_static_method = env->GetStaticMethodID(cls, "localMethod",
                                                         "(Ljava/lang/String;)V");
    jstring s1 = env->NewStringUTF("s1");
    env->CallStaticVoidMethod(cls, mth_static_method, s1);
    env->DeleteLocalRef(s1);

}
////获取MethodOperationActivity对象直接调用实例
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_operaitons_MethodOperationActivity_callInstanceMethod(JNIEnv *env,
                                                                                  jobject thiz,
                                                                                  jint i) {

    jclass cls = env->GetObjectClass(thiz);
    jmethodID mth_method = env->GetMethodID(cls, "localMethod",
                                            "(I)V");
    env->CallVoidMethod(thiz, mth_method, 1);
}
////获取MethodOperationActivity对象直接调用普通方法，拿到平普通方法返回值。
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidjni_operaitons_MethodOperationActivity_callInstanceMethod2(JNIEnv *env,
                                                                                   jobject thiz) {

// 获取MainActivity 对象
    jclass _jclass = env->GetObjectClass(thiz);
// 获取方法域的id。
    jmethodID _jmethodID = env->GetMethodID(_jclass, "getName", "()Ljava/lang/String;");
//    jni调用java方法
    jstring result = static_cast<jstring>(env->CallObjectMethod(thiz, _jmethodID));

    //   下面就是打印。很简单。都一样 。

    printf("%#x\n", result);
//    如何转为java 的string   GetStringUTFChars 是string转为char
    char *str = const_cast<char *>(env->GetStringUTFChars(result, NULL));

    char text[20] = "success";
    char *finalresult = strcat(str, text);
    return env->NewStringUTF(finalresult);

}
/////获取MethodOperationActivity对象直接调用普通方法，拿到平普通方法返回特定类型的对象，比如Hello对象
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_operaitons_MethodOperationActivity_callInstanceMethod3(JNIEnv *env,
                                                                                   jobject thiz) {

    jint i = env->GetVersion();
    LOGD("-------i:%x\n", i);
// 获取MainActivity 对象
    jclass _jclass = env->GetObjectClass(thiz);
// 获取方法域的id。
    jmethodID _jmethodID = env->GetMethodID(_jclass, "getName2",
                                            "()Lcom/example/androidjni/bean/Hello;");
//    jni调用java方法
    jobject result = env->CallObjectMethod(thiz, _jmethodID);
    jclass cls_Hello = env->GetObjectClass(result);
    jmethodID jmethodId = env->GetMethodID(cls_Hello, "method", "(Ljava/lang/String;)V");
    jstring s = env->NewStringUTF("sljfaksd");
    env->CallVoidMethod(result, jmethodId, s);
}


/////调用一个类的父类的方法。 Cat extend Animal 调用Animal的方法。
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidjni_bean_Hello_callSuperInstanceMethod(JNIEnv *env, jclass clazz) {
    jclass cls_cat;
    jclass cls_animal;
    jmethodID mid_cat_init;
    jmethodID mid_run;
    jmethodID mid_getName;
    jstring c_str_name;
    jobject obj_cat;
    const char *name = NULL;

    // 1、获取Cat类的class引用
    cls_cat = env->FindClass("com/example/androidjni/bean/Cat");
    if (cls_cat == NULL) {
        return;
    }

    // 2、获取Cat的构造方法ID(构造方法的名统一为：<init>)
    mid_cat_init = env->GetMethodID(cls_cat, "<init>", "(Ljava/lang/String;)V");
    if (mid_cat_init == NULL) {
        return; // 没有找到只有一个参数为String的构造方法
    }

    // 3、创建一个String对象，作为构造方法的参数
    c_str_name = env->NewStringUTF("汤姆猫");
    if (c_str_name == NULL) {
        return; // 创建字符串失败（内存不够）
    }

    //  4、创建Cat对象的实例(调用对象的构造方法并初始化对象)
    obj_cat = env->NewObject(cls_cat, mid_cat_init, c_str_name);
    if (obj_cat == NULL) {
        return;
    }

    //-------------- 5、调用Cat父类Animal的run和getName方法 --------------
    cls_animal = env->FindClass("com/example/androidjni/bean/Animal");
    if (cls_animal == NULL) {
        return;
    }

    // 例1： 调用父类的run方法
    mid_run = env->GetMethodID(cls_animal, "run", "()V");    // 获取父类Animal中run方法的id
    if (mid_run == NULL) {
        return;
    }

    // 注意：obj_cat是Cat的实例，cls_animal是Animal的Class引用，mid_run是Animal类中的方法ID
    env->CallNonvirtualVoidMethod(obj_cat, cls_animal, mid_run);

    // 例2：调用父类的getName方法
    // 获取父类Animal中getName方法的id
    mid_getName = env->GetMethodID(cls_animal, "getName", "()Ljava/lang/String;");
    if (mid_getName == NULL) {
        return;
    }
    c_str_name = static_cast<jstring>(env->CallNonvirtualObjectMethod(obj_cat, cls_animal,
                                                                      mid_getName));
    name = env->GetStringUTFChars(c_str_name, NULL);
    LOGD("In C: Animal Name is %s\n", name);

    // 释放从java层获取到的字符串所分配的内存
    env->ReleaseStringUTFChars(c_str_name, name);

    quit:
    // 删除局部引用（jobject或jobject的子类才属于引用变量），允许VM释放被局部变量所引用的资源
    env->DeleteLocalRef(cls_cat);
    env->DeleteLocalRef(cls_animal);
    env->DeleteLocalRef(c_str_name);
    env->DeleteLocalRef(obj_cat);


}
