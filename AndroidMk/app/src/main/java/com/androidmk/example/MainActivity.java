package com.androidmk.example;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    {
        System.loadLibrary("hello-jni");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        System.out.println("nativeTestAdd:" + nativeTestAdd(1, 2));
        System.out.println("nativeTestMul:" + nativeTestMul(1, 2));
        System.out.println("nativeTestSub:" + nativeTestSub(1, 2));
    }

    public static native int nativeTestAdd(int a, int b);

    native int nativeTestMul(int a, int b);

    native int nativeTestSub(int a, int b);
}
