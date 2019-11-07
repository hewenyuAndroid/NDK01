package com.hwy.ndk01;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.e("TAG", "-->" + AppUtil.getSign(this, getPackageName()));
        Log.e("TAG", "==>" + AppUtil.getSignMD5(this, getPackageName()));

    }

    public void encryption(View view) {

    }

    public void encryptionMD5(View view) {
        Log.e("TAG", "--->" + EncryptionUtil.encryptionMD5(this, "123456", 0));
    }

}
