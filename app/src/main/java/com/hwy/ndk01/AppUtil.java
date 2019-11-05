package com.hwy.ndk01;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * ====================================
 * 作者: hewenyu
 * 日期: 2019/11/5 9:18
 * 说明:
 * ====================================
 */
public class AppUtil {

    /**
     * 获取应用签名
     *
     * @param context
     * @param packageName
     * @return
     */
    public static String getSign(Context context, String packageName) {
        try {
            PackageInfo info = context.getPackageManager().getPackageInfo(packageName, PackageManager.GET_SIGNATURES);
            byte[] bytes = info.signatures[0].toByteArray();
            return byte2hex(bytes);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "";
    }

    /**
     * 获取签名的MD5值
     *
     * @param context
     * @param packageName
     * @return
     */
    public static String getSignMD5(Context context, String packageName) {
        try {
            PackageInfo info = context.getPackageManager().getPackageInfo(packageName, PackageManager.GET_SIGNATURES);
            byte[] bytes = info.signatures[0].toByteArray();
            return encryptionMD5(bytes);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "";
    }

    private static String encryptionMD5(byte[] byteStr) {
        MessageDigest messageDigest = null;
        StringBuffer md5StrBuff = new StringBuffer();
        try {
            messageDigest = MessageDigest.getInstance("MD5");
            messageDigest.reset();
            messageDigest.update(byteStr);
            byte[] byteArray = messageDigest.digest();
            for (int i = 0; i < byteArray.length; i++) {
                if (Integer.toHexString(0xFF & byteArray[i]).length() == 1) {
                    md5StrBuff.append("0").append(Integer.toHexString(0xFF & byteArray[i]));
                } else {
                    md5StrBuff.append(Integer.toHexString(0xFF & byteArray[i]));
                }
            }
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return md5StrBuff.toString();
    }

    private static String byte2hex(byte[] bytes) {
        String hs = "";
        String tmp = "";
        for (int i = 0; i < bytes.length; i++) {
            tmp = (Integer.toHexString(bytes[i] & 0XFF));
            if (tmp.length() == 1)
                hs = hs + "0" + tmp;
            else
                hs = hs + tmp;
        }
        return hs.toUpperCase();
    }

}
