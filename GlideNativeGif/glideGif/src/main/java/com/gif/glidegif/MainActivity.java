package com.gif.glidegif;

import android.os.Bundle;
import android.widget.ImageView;

import com.bumptech.glide.Glide;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity {


    private int mResourceId;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mResourceId = getIntent().getIntExtra("resourceId", R.raw.demo);

        setContentView(R.layout.activity_main);
        ImageView ivGif = findViewById(R.id.iv_gif);
        InputStream is = getResources().openRawResource(mResourceId);
        byte[] bytes = new byte[0];
        try {
            bytes = input2byte(is);
        } catch (IOException e) {
            e.printStackTrace();
        }

        Glide.with(this)
                .load(bytes)
//                .load("http://hiphotos.baidu.com/feed/pic/item/ac4bd11373f082025e367b9f47fbfbedaa641bed.gif")
                .placeholder(R.drawable.ic_launcher_background)
                .error(R.drawable.ic_launcher_foreground)
                .into(ivGif);


    }

    // 将输入流解析成字节数组
    public static final byte[] input2byte(InputStream inStream)
            throws IOException {
        ByteArrayOutputStream swapStream = new ByteArrayOutputStream();
        byte[] buff = new byte[100];
        int rc = 0;
        while ((rc = inStream.read(buff, 0, 100)) > 0) {
            swapStream.write(buff, 0, rc);
        }
        byte[] in2b = swapStream.toByteArray();
        return in2b;
    }
}
