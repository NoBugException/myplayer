#include <jni.h>
#include <string>
#include "DNFFmpeg.h"

DNFFmpeg *ffmpeg = 0;

JavaVM *javaVm = 0;

int JNI_OnLoad(JavaVM *vm, void *r) {
    javaVm = vm;
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_android_myplayer_MyPlayer_native_1prepare(JNIEnv *env, jobject instance, jstring data_source) {
    const char *dataSource = env->GetStringUTFChars(data_source, 0);
    // 创建播放器
    JavaCallHelper *helper = new JavaCallHelper(javaVm, env, instance);
    ffmpeg = new DNFFmpeg(helper, dataSource);
    ffmpeg->prepare();
    env->ReleaseStringUTFChars(data_source, dataSource);
}