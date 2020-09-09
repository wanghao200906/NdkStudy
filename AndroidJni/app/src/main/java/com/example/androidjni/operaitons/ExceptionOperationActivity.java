package com.example.androidjni.operaitons;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.androidjni.R;
import com.example.androidjni.bean.Hello;

import androidx.appcompat.app.AppCompatActivity;

/**
 * Created by Sven.Wong on 2020/6/11
 */

public class ExceptionOperationActivity extends AppCompatActivity {

    public String name = "test";

    static {
        System.loadLibrary("native-lib-exception");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("jni");

        try {
            callExceptionMethod01();
        } catch (Exception e) {
            Log.d("ExceptionOperationActivity", "error:" + e.getMessage());

        }
        try {
            callExceptionMethod02();
        } catch (Exception e) {
            Log.d("ExceptionOperationActivity", "error:" + e.getMessage());

        }
    }

    public void localMethod1() {
        Log.d("ExceptionOperationActivity", "123");
        String s = null;
        s.toString();
    }

    public native void callExceptionMethod01();

    public native void callExceptionMethod02();
}

