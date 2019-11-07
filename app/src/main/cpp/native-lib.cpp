#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>
#include "MD5.h"

#define LOG_TAG "TAG_C"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;

// 预设的包名
static const char *PACKAGE_NAME = "com.hwy.ndk01";
// 预设的签名MD5值
static const char *APP_SIGNATURE_MD5 = "22f65cc4f98cbdb4fc33f02d0efae0ee";
// 22F65CC4F98CBDB4FC33F02D0EFAE0EE
// 预设的签名
const char *APP_SIGNATURE = "308202eb308201d3a003020102020427e0a549300d06092a864886f70d01010b050030263111300f060355040b130874657374556e69743111300f06035504031308746573744e616d65301e170d3139313130353031323932345a170d3434313032393031323932345a30263111300f060355040b130874657374556e69743111300f06035504031308746573744e616d6530820122300d06092a864886f70d01010105000382010f003082010a02820101008c0d4146f43b2d21546818dffa238af5cccde2ab81ad576ecb810b99f8d3de2316ed7cdc335f4da27ff26bc5e0f84fc3c28a9c547e4aaa9663728f057ea6d9e0e4f9d2668c7d0f300f1cef386003ac4394a97499d14543b1eb7f461bc20aea9fb9e2a301067a1cb574355f393c57fbe3371b7fe91928a5ae6d10e0974792454e3a5e8078dd4f69d38829459bd48fc86e2ed92146a3add854fbe827d87ccb935f247cbfd3164aedfa13cee59238f36ac99230d19d0a992f06ab5cc6704544d385a6edaa0d057d159b0a47301f1639a17f3aa72a10e10808ef20df4bd5298967e64a31ec7cc87fde9be1fb8fe9a4298f059673976fcec38e6c8b20c488231f4b690203010001a321301f301d0603551d0e04160414f5372b469502bbc9201cb44f9baab9c48619e11d300d06092a864886f70d01010b05000382010100305eb51ed1b0e2";

extern "C" {

JNIEXPORT jstring JNICALL
Java_com_hwy_ndk01_EncryptionUtil_encryptionMD5(JNIEnv *env, jclass j_clz, jobject j_context,
                                                jstring j_input, jint j_result_type) {
    if (!j_context) {   // 上下文判空
        return env->NewStringUTF("error content");
    }

    if (!j_input) { // 字符串判空
        return env->NewStringUTF("error input string");
    }

    // region ----------------------- 包名校验 -----------------------

    // 获取上下文的 Class
    jclass j_context_clz = env->GetObjectClass(j_context);
    // 获取 getPackageName 方法的方法签名
    jmethodID j_mid = env->GetMethodID(j_context_clz, "getPackageName", "()Ljava/lang/String;");
    // 获取包名
    jstring j_package_name = static_cast<jstring>(env->CallObjectMethod(j_context, j_mid));
    const char *c_package_name = env->GetStringUTFChars(j_package_name, NULL);
    LOGD("input package name --> %s ", c_package_name);
    if (strcmp(c_package_name, PACKAGE_NAME) != 0) {    // 包名不一致
        return env->NewStringUTF("error_package");
    }

    // endregion -----------------------------------------------------

    // region ----------------------- 签名校验 -----------------------

    // 获取方法签名
    j_mid = env->GetMethodID(j_context_clz, "getPackageManager",
                             "()Landroid/content/pm/PackageManager;");
    // PackageManager
    jobject j_package_manager = env->CallObjectMethod(j_context, j_mid);
    // 获取PackageInfo
    jclass j_package_manager_clz = env->GetObjectClass(j_package_manager);
    j_mid = env->GetMethodID(j_package_manager_clz, "getPackageInfo",
                             "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    // 获取 PackageInfo 对象
    jobject j_package_info = env->CallObjectMethod(j_package_manager, j_mid, j_package_name,
                                                   0x00000040);
    //获取签名数组
    j_clz = env->GetObjectClass(j_package_info);
    jfieldID j_signature_id = env->GetFieldID(j_clz, "signatures",
                                              "[Landroid/content/pm/Signature;");
    jobjectArray signature_array = static_cast<jobjectArray>(env->GetObjectField(j_package_info,
                                                                                 j_signature_id));
    // 获取数组的第一个元素
    jobject signature_first = env->GetObjectArrayElement(signature_array, 0);

    j_clz = env->GetObjectClass(signature_first);
    j_mid = env->GetMethodID(j_clz, "toCharsString", "()Ljava/lang/String;");
    jstring j_signature = static_cast<jstring>(env->CallObjectMethod(signature_first, j_mid));
    const char *c_signature = env->GetStringUTFChars(j_signature, NULL);
    LOGD("input signature1 = %s", c_signature);

    if (strncmp(c_signature, APP_SIGNATURE, strlen(APP_SIGNATURE)) != 0) {  // 签名不一致
        return env->NewStringUTF("error_signature");
    }

    // endregion -----------------------------------------------------

    // 获取需要加密的数据
    const char *c_input = env->GetStringUTFChars(j_input, NULL);

    // 此处可以对需要加密的数据进行加密前的处理，增加破解难度

    MD5 md5_input;
    md5_input.update(c_input);
    string result = md5_input.bytesToHexString(md5_input.digest(), 16);

    if (j_result_type == 1) {
        // 转大写
        transform(result.begin(), result.end(), result.begin(), ::toupper);
    }

    return env->NewStringUTF(result.c_str());
}


JNIEXPORT jstring JNICALL
Java_com_hwy_ndk01_EncryptionUtil_encryption(JNIEnv *env, jclass j_clz, jobject j_context,
                                             jstring j_key, jstring j_input) {

    return env->NewStringUTF("");
}

}
