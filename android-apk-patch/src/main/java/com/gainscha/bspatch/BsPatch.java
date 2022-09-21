package com.gainscha.bspatch;

public class BsPatch {

    static {
        System.loadLibrary("bspatch-util");
    }

    /**
     * 使用补丁包对旧文件打补丁，生成新文件
     *
     * @param oldFile   旧文件路径
     * @param newFile   新文件路径
     * @param patchFile 补丁文件路径
     * @return 是否成功
     */
    public static native boolean patch(String oldFile, String newFile, String patchFile);
}