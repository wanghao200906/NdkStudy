package com.androidcmake.example;

/**
 * Created by Sven.Wong on 2020/3/21
 */

public class NdkUtils {

    public static native String getStringJni();

    static {
        System.loadLibrary("hello-libs");
    }
}
