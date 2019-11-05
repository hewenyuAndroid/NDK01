package com.hwy.ndk01;

import android.content.Context;

/**
 * ====================================
 * 作者: hewenyu
 * 日期: 2019/11/4 15:30
 * 说明:
 * ====================================
 */
public class EncryptionUtil {

    static {
        System.loadLibrary("native-lib");
    }

    /**
     * MD5加密
     *
     * @param context
     * @param input
     * @return
     */
    public static native String encryptionMD5(Context context, String input);

    /**
     * MD5加密+异或运算
     *
     * @param context
     * @param key
     * @param input
     * @return
     */
    public static native String encryption(Context context, String key, String input);

}
