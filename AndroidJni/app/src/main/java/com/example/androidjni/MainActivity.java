package com.example.androidjni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        updateFile("/mnt/sdcard/boys.txt");


    }


    public native String stringFromJNI();

    //    给native传递一个string，这里是打开一个文件，但是需要权限应该会失败
    public native void updateFile(String path);



}
