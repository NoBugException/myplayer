package com.android.myplayer;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class SurfacePreview extends SurfaceView implements SurfaceHolder.Callback {

    public SurfacePreview(Context context) {
        this(context, null);
    }

    public SurfacePreview(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public SurfacePreview(Context context, AttributeSet attrs, int defStyleAttr) {
        this(context, attrs, defStyleAttr, 0);
    }

    public SurfacePreview(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }

    /**
     * 每次初始化预览界面时
     *
     * @param holder
     */
    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    /**
     * 当预览界面布局发生改变时执行一次
     * SurfaceView在初始化时就会执行， 与TextureView不同，TextureView再初始化时不执行
     *
     * @param holder
     * @param format
     * @param width
     * @param height
     */
    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    /**
     * 当预览界面切入后台或者Activity销毁时执行
     *
     * @param holder
     */
    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}