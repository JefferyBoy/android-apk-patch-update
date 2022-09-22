#!/bin/bash
# 批量生成apk文件的差分包，一次性生成新版本对所有旧版本的差分包
# 使用bsdiff实现 https://github.com/mendsley/bsdiff
# 使用方式：./diff.sh /path/to/old/apk /path/to/new/apk

old_apk_dir=$1
if [[ -f $old_apk_dir ]]; then
  old_apk_dir=${1%/*}
  old_apk_list=${1##*/} 
else
  old_apk_list=`ls -l $old_apk_dir | grep ".apk$" | awk '{print $9}'`
fi
new_apk=$2
new_apk_patch_dir="${new_apk%.*}-patch"

if [[ ! -f $new_apk ]]; then
  echo "new apk not exist" >&2
  exit 1
fi
if [[ ! -e $old_apk_dir ]]; then
  echo "old apk dir not exist" >&2
  exit 1
fi
if [[ ! -d $new_apk_patch_dir ]]; then
  mkdir $new_apk_patch_dir
fi

index=1
for apk in $old_apk_list
do
  apk="${old_apk_dir}/$apk"
  if [[ $apk != ${new_apk} ]]; then
    old_apk_name_without_ext=${apk##*/}
    old_apk_name_without_ext=${old_apk_name_without_ext%.*}
    new_apk_name_without_ext=${new_apk##*/}
    new_apk_name_without_ext=${new_apk_name_without_ext%.*}
    patch_apk="${new_apk_patch_dir}/${old_apk_name_without_ext}-patch.apk"
    echo "${index}. paching: ${apk##*/}"
    bsdiff $apk $new_apk $patch_apk
    if [[ $? -eq 0 ]]; then
      echo "  success. " $(ls -lhs ${patch_apk} | cut -d ' ' -f1)
    else
      echo "  failed"
    fi
    index=$(($index+1))
  fi
done


