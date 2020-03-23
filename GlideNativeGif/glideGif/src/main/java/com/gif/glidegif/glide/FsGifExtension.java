package com.gif.glidegif.glide;

import android.support.rastermill.FrameSequenceDrawable;

import com.bumptech.glide.RequestBuilder;
import com.bumptech.glide.annotation.GlideExtension;
import com.bumptech.glide.annotation.GlideType;
import com.bumptech.glide.request.RequestOptions;

import androidx.annotation.NonNull;

/**
 * Created by Sven.Wong on 2020/3/23
 */

@GlideExtension
public class FsGifExtension {

    private FsGifExtension() {
    }

    @NonNull
    @GlideType(FrameSequenceDrawable.class)
    public static RequestBuilder<FrameSequenceDrawable> asGifFs(RequestBuilder<FrameSequenceDrawable> requestBuilder) {
//        解码的时候要解码为FrameSequenceDrawable类型。
        return requestBuilder.apply(RequestOptions.decodeTypeOf(FrameSequenceDrawable.class));
    }
}
