package com.gif.glidegif.glide;

import android.support.rastermill.FrameSequenceDrawable;

import com.bumptech.glide.load.resource.drawable.DrawableResource;

import androidx.annotation.NonNull;

/**
 * Created by Sven.Wong on 2020/3/23
 */

public class FsGifResource extends DrawableResource<FrameSequenceDrawable> {
    public FsGifResource(FrameSequenceDrawable drawable) {
        super(drawable);
    }

    @NonNull
    @Override
    public Class<FrameSequenceDrawable> getResourceClass() {
        return FrameSequenceDrawable.class;
    }

    @Override
    public int getSize() {
        return drawable.getIntrinsicHeight() * drawable.getIntrinsicHeight();
    }

    @Override
    public void recycle() {
        drawable.stop();
        drawable.destroy();
    }
}
