package com.example.androidjni.operaitons;

import android.content.res.ColorStateList;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import com.example.androidjni.MyHandler;
import com.example.androidjni.R;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatImageButton;
import androidx.core.content.ContextCompat;

/**
 * Created by Sven.Wong on 2020/6/11
 */

public class ThreadOperationActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native-lib-thread");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setJNIEnv();
//调用JNI中的函数来启动JNI中的线程
        mainThread();
    }

    private native void setJNIEnv();

    private native void mainThread();

    MyHandler mMyHandler = new MyHandler();

    //由JNI中的线程回调
    private static void fromJNI(int i) {
        Log.v("ThreadOperationActivity", Thread.currentThread().getName() + " i:" + i);

    }

    //由JNI中的线程回调
    private void fromJNI2() {
        Log.v("ThreadOperationActivity", Thread.currentThread().getName());
//        mHandler.obtainMessage().sendToTarget();
        mMyHandler.obtainMessage().sendToTarget();

    }

}

