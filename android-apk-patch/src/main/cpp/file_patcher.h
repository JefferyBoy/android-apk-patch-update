//
// Created by mxlei on 2022/9/11.
//

#ifndef PRINTER_SDK_ANDROID_FILE_PATCHER_H
#define PRINTER_SDK_ANDROID_FILE_PATCHER_H

#ifdef __cplusplus
extern "C" {
#endif

int bspatch_file(const char *old_file, const char *new_file, const char *patch_file);

#ifdef __cplusplus
};
#endif

#endif //PRINTER_SDK_ANDROID_FILE_PATCHER_H
