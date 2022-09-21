package com.github.jeffery.patch;

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.gainscha.bspatch.BsPatch;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_patch).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                patchInstall();
            }
        });
    }

    private void patchInstall() {
        File diffFile = new File(getExternalCacheDir(), "diff.apk");
        File installedFile = new File(getCodeCacheDir(), "base.apk");
        File newFile = new File(getExternalCacheDir(), "new.apk");
        if (diffFile.exists() && installedFile.exists()) {
            boolean success = BsPatch.patch(installedFile.getAbsolutePath(), newFile.getAbsolutePath(), diffFile.getAbsolutePath());
            if (success) {
                installApk(newFile);
            } else {
                Toast.makeText(this, "合并增量包失败", Toast.LENGTH_SHORT).show();
            }
        } else {
            Toast.makeText(this, "增量包或应用包不存在", Toast.LENGTH_SHORT).show();
        }
    }

    private void installApk(File apk) {

    }
}