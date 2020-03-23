package com.gif.glidegif.glide;

import android.content.Context;
import android.support.rastermill.FrameSequenceDrawable;

import com.bumptech.glide.Glide;
import com.bumptech.glide.Registry;
import com.bumptech.glide.annotation.GlideModule;
import com.bumptech.glide.module.AppGlideModule;

import java.io.InputStream;

import androidx.annotation.NonNull;

/**
 * Created by Sven.Wong on 2020/3/23
 */

@GlideModule
public class GifGlideModule extends AppGlideModule {
    @Override
    public void registerComponents(@NonNull Context context, @NonNull Glide glide, @NonNull Registry registry) {
        super.registerComponents(context, glide, registry);
//注册自定义解码组件，用于将InputStream转为FsDrawable
        registry.append(
                Registry.BUCKET_GIF,
                InputStream.class,
                FrameSequenceDrawable.class,
                new FsGifDecoder(glide.getBitmapPool())
        );
    }
}
