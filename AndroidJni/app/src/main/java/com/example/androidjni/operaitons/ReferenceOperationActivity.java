package com.example.androidjni.operaitons;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.example.androidjni.R;
import com.example.androidjni.bean.Hello;

import androidx.appcompat.app.AppCompatActivity;

/**
 * Created by Sven.Wong on 2020/6/11
 */

public class ReferenceOperationActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native-lib-reference");
    }

    EditText mEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        mEditText = (EditText) findViewById(R.id.str_count);
    }

    public void onTestLocalRefOverflow(View view) {
        String[] strings = getStrings(Integer.parseInt(mEditText.getText().toString()), "I Love You %d Year！！！");
        for (String string : strings) {
            Log.d("ReferenceOperationActivity", string);
        }
    }

    // 返回count个sample相同的字符串数组，并用编号标识，如：sample1，sample2...
    public native String[] getStrings(int count, String sample);

}

