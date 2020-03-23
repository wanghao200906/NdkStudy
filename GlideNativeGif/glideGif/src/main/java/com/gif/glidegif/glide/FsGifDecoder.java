package com.gif.glidegif.glide;

import android.graphics.Bitmap;
import android.support.rastermill.FrameSequence;
import android.support.rastermill.FrameSequenceDrawable;

import com.bumptech.glide.load.Options;
import com.bumptech.glide.load.ResourceDecoder;
import com.bumptech.glide.load.engine.Resource;
import com.bumptech.glide.load.engine.bitmap_recycle.BitmapPool;

import java.io.IOException;
import java.io.InputStream;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

/**
 * Created by Sven.Wong on 2020/3/23
 */

public class FsGifDecoder implements ResourceDecoder<InputStream, FrameSequenceDrawable> {
    private BitmapPool mBitmapPool;

    public FsGifDecoder(BitmapPool bitmapPool) {
        this.mBitmapPool = bitmapPool;
    }

    /**
     * @param source
     * @param options
     * @return true 表示能处理这个InputStream
     * false
     * @throws IOException
     */
    @Override
    public boolean handles(@NonNull InputStream source, @NonNull Options options) throws IOException {
        return true;
    }

    @Nullable
    @Override
    public Resource<FrameSequenceDrawable> decode(@NonNull InputStream source, int width, int height, @NonNull Options options) throws IOException {
        FrameSequence frameSequence = FrameSequence.decodeStream(source);
        FrameSequenceDrawable frameSequenceDrawable
                = new FrameSequenceDrawable(frameSequence, new FrameSequenceDrawable.BitmapProvider() {
            @Override
            public Bitmap acquireBitmap(int minWidth, int minHeight) {
                Bitmap bitmap = mBitmapPool.getDirty(minWidth, minHeight, Bitmap.Config.ARGB_8888);
                return bitmap;
            }

            @Override
            public void releaseBitmap(Bitmap bitmap) {
                mBitmapPool.put(bitmap);
            }
        });
        return new FsGifResource(frameSequenceDrawable);
    }
}
