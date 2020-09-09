package com.example.androidjni;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class MyHandler extends Handler {
    @Override
    public void handleMessage(Message msg) {
        super.handleMessage(msg);
        System.out.println("myhandler");
        Log.d("ThreadOperationActivity", "myhandler");
    }
}
