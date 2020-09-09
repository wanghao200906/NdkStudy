package com.example.androidjni.bean;

import android.util.Log;

/**
 * Created by Sven.Wong on 2020/6/11
 */

public class Hello {
    static {
        System.loadLibrary("native-lib-method");
    }

    private static String name = "MethodOperationActivity";
    private String name2 = "MethodOperationActivity";


    public static void logMethod(String data) {
        Log.d("MethodOperationActivity", data);
    }

    //    native调用静态方法
    public static void staticMethod(String data) {
        logMethod(data);
        logMethod(name);
    }

    //    native调用普通方法
    public void method(String data) {
        logMethod(data);
        logMethod(name2);

    }

//调用实例方法
    public native void callInstanceMethod(long i);
    //调用实例方法 并且修改    name2
    public native void callInstanceMethod2(long i);
//调用静态方法
    public static native void callStaticMethod(int i);
//调用静态方法 并且修改    name
    public static native void callStaticMethod2(int i);
//调用一个类的父类方法
    public native static void callSuperInstanceMethod();
}
