package com.example.androidjni.operaitons;

import android.os.Bundle;
import android.widget.TextView;

import com.example.androidjni.R;

import androidx.appcompat.app.AppCompatActivity;

public class ArrayOperationActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib-array");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("jni");


        methodArray1();

        int[][] arr = initInt2DArray(3);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                System.out.format("arr[%d][%d] = %d\n", i, j, arr[i][j]);
            }
        }

    }

    public void methodArray1() {
        int[] arr = new int[10];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = i;
        }
        int sum = sumArray(arr);
        int sum2 = sumArray2(arr);
        int sum3 = sumArray3(arr);
        System.out.println("sum = " + sum);
        System.out.println("sum2 = " + sum2);
        System.out.println("sum3 = " + sum3);


        int[] ints = updateIntArray(arr);
        for (int anInt : ints) {
            System.out.println("anInt:" + anInt);
        }

        int[] ints2 = updateIntArray2(arr);
        for (int anInt2 : ints2) {
            System.out.println("anInt2:" + anInt2);
        }
    }


    //    传入一个数组，native中进行操作，然后在返回
    public native int[] updateIntArray(int[] data);

    //     传入一个数组，native中进行操作，然后在返回 ，第二种方法
    public native int[] updateIntArray2(int[] data);

    // 在本地代码中求数组中所有元素的和
    private native int sumArray(int[] arr);

    private native int sumArray2(int[] arr);

    private native int sumArray3(int[] arr);

    //    返回一个二维数组
    private native int[][] initInt2DArray(int size);

}
