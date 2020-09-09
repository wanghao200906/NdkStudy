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

//调用普通方法，静态方法
public class MethodOperationActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native-lib-method");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("jni");

        Hello.callStaticMethod(1);
        Hello.callStaticMethod2(2);
        new Hello().callInstanceMethod(2);
        new Hello().callInstanceMethod2(2);

        callInstanceMethod(1);
        callStaticMethod(1);
        Log.d("MethodOperationActivity", callInstanceMethod2());
        callInstanceMethod3();

        Hello.callSuperInstanceMethod();
    }

    public String getName() {
        return "1234";
    }

    public Hello getName2() {
        return new Hello();
    }

    public void localMethod(int i) {
        Log.d("MethodOperationActivity", "instance localMethod——" + i);
    }

    public static void localMethod(String i) {
        Log.d("MethodOperationActivity", "static localMethod——" + i);
    }

    public native void callStaticMethod(int i);

    public native void callInstanceMethod(int i);

    public native String callInstanceMethod2();

    public native void callInstanceMethod3();
}

