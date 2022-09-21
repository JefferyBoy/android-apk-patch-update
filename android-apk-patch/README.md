# APP增量更新合并增量包

```java
public void test(){
    // 当前安装应用的apk
    String oldFile="/path/to/oldApkFile";
    // 合并增量后生产的新apk
    String newFile="/path/to/newApkFile";
    // 增量包文件（一般是从服务器下发的增量包）
    String patchFile="/path/to/patchFile";
    int r = BsPatch.patch(String oldFile,String newFile,String patchFile);
    if ( r == 0 ) {
        // 成功
    } else {
        // 失败
    }
}
```