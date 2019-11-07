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
     * 签名校验+MD5加密
     *
     * @param context    签名校验
     * @param input      需要加密的数据
     * @param resultType 加密的输出类型 0: 默认 1: 大写
     * @return
     */
    public static native String encryptionMD5(Context context, String input, int resultType);

    /**
     * 签名校验+MD5加密+异或运算
     *
     * @param context
     * @param key
     * @param input
     * @return
     */
    public static native String encryption(Context context, String key, String input);

}
