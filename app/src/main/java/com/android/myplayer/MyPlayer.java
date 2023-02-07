package com.android.myplayer;

import android.view.SurfaceHolder;

/**
 * 提供java进行播放、停止 等函数
 */
public class MyPlayer {

    static {
        System.loadLibrary("myplayer");
    }

    private String dataSource;
    private OnPrepareListener listener;

    /**
     * 设置播放的文件 或 直播地址
     * @param dataSource
     */
    public void setDataSource(String dataSource) {
        this.dataSource = dataSource;
    }

    public void onError(int errorCode){
        System.out.println("Java接到回调:"+errorCode);
    }

    public void setOnPrepareListener(OnPrepareListener listener){
        this.listener = listener;
    }

    public void onPrepare(){
        if (null != listener){
            listener.onPrepare();
        }
    }

    /**
     * 准备好 要播放的视频
     */
    public void prepare() {
        native_prepare(dataSource);
    }

    /**
     * 开始播放
     */
    public void start() {

    }

    /**
     * 停止播放
     */
    public void stop() {

    }

    native void native_prepare(String dataSource);

}
