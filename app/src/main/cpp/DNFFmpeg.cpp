//
// Created by Administrator on 2018/9/5.
//

#include <cstring>
#include <pthread.h>
#include "DNFFmpeg.h"
#include "macro.h"

void* task_prepare(void *args){
    DNFFmpeg *ffmpeg = static_cast<DNFFmpeg *>(args);
    ffmpeg->_prepare();
    return 0;
}

DNFFmpeg::DNFFmpeg(JavaCallHelper *callHelper,const char *dataSource) {
    this->callHelper = callHelper;
    //防止 dataSource参数 指向的内存被释放
    this->dataSource = new char[strlen(dataSource)];
    strcpy(this->dataSource,dataSource);
}

DNFFmpeg::~DNFFmpeg() {
    //释放
    DELETE(dataSource);
    DELETE(callHelper);
}


void DNFFmpeg::prepare(){
    //创建一个线程
    pthread_create(&pid,0,task_prepare,this);
}

void DNFFmpeg::_prepare(){
    // 初始化网络 让ffmpeg能够使用网络
    avformat_network_init();
    //1、打开媒体地址(文件地址、直播地址)
    // AVFormatContext  包含了 视频的 信息(宽、高等)
    formatContext = NULL;
    //文件路径不对 手机没网
    int ret = avformat_open_input(&formatContext,dataSource,0,0);
    //ret不为0表示 打开媒体失败
    if(ret != 0){
        LOGE("打开媒体失败:%s",av_err2str(ret));
        callHelper->onError(THREAD_CHILD,FFMPEG_CAN_NOT_OPEN_URL);
        return;
    }
    //2、查找媒体中的 音视频流 (给 contxt里的 streams等成员赋)
    ret =  avformat_find_stream_info(formatContext,0);
    // 小于0 则失败
    if (ret < 0){
        LOGE("查找流失败:%s",av_err2str(ret));
        callHelper->onError(THREAD_CHILD,FFMPEG_CAN_NOT_FIND_STREAMS);
        return;
    }
    //nb_streams :几个流(几段视频/音频)
    for (int i = 0; i < formatContext->nb_streams; ++i) {
        //可能代表是一个视频 也可能代表是一个音频
        AVStream *stream = formatContext->streams[i];
        //包含了 解码 这段流 的各种参数信息(宽、高、码率、帧率)
        AVCodecParameters  *codecpar =  stream->codecpar;

        //无论视频还是音频都需要干的一些事情（获得解码器）
        // 1、通过 当前流 使用的 编码方式，查找解码器
        const AVCodec *dec = avcodec_find_decoder(codecpar->codec_id);
        if(dec == NULL){
            LOGE("查找解码器失败:%s",av_err2str(ret));
            callHelper->onError(THREAD_CHILD,FFMPEG_FIND_DECODER_FAIL);
            return;
        }
        //2、获得解码器上下文
        AVCodecContext *context = avcodec_alloc_context3(dec);
        if(context == NULL){
            LOGE("创建解码上下文失败:%s",av_err2str(ret));
            callHelper->onError(THREAD_CHILD,FFMPEG_ALLOC_CODEC_CONTEXT_FAIL);
            return;
        }
        //3、设置上下文内的一些参数 (context->width)
//        context->width = codecpar->width;
//        context->height = codecpar->height;
        ret = avcodec_parameters_to_context(context,codecpar);
        //失败
        if(ret < 0){
            LOGE("设置解码上下文参数失败:%s",av_err2str(ret));
            callHelper->onError(THREAD_CHILD,FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL);
            return;
        }
        // 4、打开解码器
        ret = avcodec_open2(context,dec,0);
        if (ret != 0){
            LOGE("打开解码器失败:%s",av_err2str(ret));
            callHelper->onError(THREAD_CHILD,FFMPEG_OPEN_DECODER_FAIL);
            return;
        }
        //音频
        if (codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
            audioChannel = new AudioChannel;
        } else if(codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            videoChannel = new VideoChannel;
        }
    }
    //没有音视频  (很少见)
    if(!audioChannel && !videoChannel){
        LOGE("没有音视频");
        callHelper->onError(THREAD_CHILD,FFMPEG_NOMEDIA);
        return;
    }
    // 准备完了 通知java 你随时可以开始播放
    callHelper->onPrepare(THREAD_CHILD);
};