# 安卓增量更新

## 1. 使用过程

1. 对新版apk生成每个旧版对应的差分包 执行diff.sh脚本生成新apk对每个旧apk的差分包

```shell
# 生成差分包
# 第一个参数是旧版apk文件路径或者旧版apk文件所在文件夹（对文件夹下所有apk都执行差分）
# 第二个参数是新版apk文件路径
./diff.sh /path/to/old/apk /path/to/new/apk
```

![](https://fastly.jsdelivr.net/gh/JefferyBoy/pictures@master/2022/16637761725121663776171587.png)

2. 服务器下发差分包 服务期根据app请求接口中提供的app版本号下发不同的差分包给app
3. app拿到差分包，对当前安装的apk进行合并差分，得到新版apk app下载差分包后，执行差分包和合并

```java
// 合并差分包
boolean success=BsPatch.patch(installedFile.getAbsolutePath(),newFile.getAbsolutePath(),diffFile.getAbsolutePath());
```

4. 安装新版apk

## 2. 库引入

```groovy
repositories {
    maven { url 'https://jitpack.io' }
}

dependencies {
    implementation 'com.github.JefferyBoy:android-apk-patch-update:1.0.2'
}
```