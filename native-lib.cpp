#include <jni.h>
#include <string>
#include <vector>
#include "skCrypter.h"
#include "xxtea.h"

#define LOG_TAG "NativeXXTEA"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_skypper_kakuluwa_MainActivity_getApiKey(
        JNIEnv* env,
        jobject /* this */) {
    auto apiKey = skCrypt("42 49 7A 62 53 79 42 4C 48 51 42 31 42 69 31 6A 45 56 69 72 7A 6C 61 5A 73 7A 50 55 2D 74 78 55 52 2D 51 68 76 72 6F");
    return env->NewStringUTF(apiKey);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_skypper_kakuluwa_MainActivity_getAppId(
        JNIEnv* env,
        jobject /* this */) {
    auto appId = skCrypt("33 3A 36 34 33 35 32 33 37 32 37 33 37 39 3A 65 6E 64 72 6F 69 64 3A 35 38 39 35 32 31 35 35 36 65 61 63 65 39 39 35 64 33 31 31 61 36");
    return env->NewStringUTF(appId);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_skypper_kakuluwa_MainActivity_getProjectId(
        JNIEnv* env,
        jobject /* this */) {
    auto projectId = skCrypt("6B 61 75 75 75 75 61 2D 36 65 39 36 37");
    return env->NewStringUTF(projectId);
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_skypper_kakuluwa_MainActivity_encryptWithXXTEA(JNIEnv *env, jobject thiz, jbyteArray data) {
    jsize len = env->GetArrayLength(data);
    jbyte* buffer = env->GetByteArrayElements(data, nullptr);

    uint8_t key[16] = { 'z','o','o','o','g','a','n','g','1','2','3','4','5','6','7','8' };
    xxtea_encrypt(reinterpret_cast<uint8_t*>(buffer), len, key);

    jbyteArray encrypted = env->NewByteArray(len);
    env->SetByteArrayRegion(encrypted, 0, len, buffer);
    env->ReleaseByteArrayElements(data, buffer, JNI_ABORT);
    return encrypted;
}

const uint8_t SECRET_KEY[16] = {
        0x12, 0x34, 0x56, 0x78,
        0x9A, 0xBC, 0xDE, 0xF0,
        0x12, 0x34, 0x56, 0x78,
        0x9A, 0xBC, 0xDE, 0xF0
};

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_skypper_kakuluwa_MainActivity_decryptWithXXTEA(JNIEnv *env, jobject, jbyteArray input) {
    jsize len = env->GetArrayLength(input);
    jbyte *buffer = env->GetByteArrayElements(input, nullptr);

    std::vector<uint8_t> data(buffer, buffer + len);
    xxtea_decrypt(data.data(), data.size(), SECRET_KEY);

    jbyteArray result = env->NewByteArray(len);
    env->SetByteArrayRegion(result, 0, len, reinterpret_cast<jbyte *>(data.data()));
    env->ReleaseByteArrayElements(input, buffer, JNI_ABORT);
    return result;
}