#!/bin/bash
# 生成apk文件的差分包
# 使用bsdiff实现 https://github.com/mendsley/bsdiff

apk_dir=$1

bsdiff