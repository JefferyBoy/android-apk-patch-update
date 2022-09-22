#include <jni.h>
#include <string>
#include "android/log.h"
#include "file_patcher.h"

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_gainscha_bspatch_BsPatch_patch(JNIEnv *env, jclass clazz, jstring old_file,
                                        jstring new_file, jstring patch_file) {
    int ret = -1;
    jboolean is_copy;
    const char *old_file_ptr = env->GetStringUTFChars(old_file, &is_copy);
    const char *patch_file_ptr = env->GetStringUTFChars(patch_file, &is_copy);
    const char *new_file_ptr = env->GetStringUTFChars(new_file, &is_copy);
    if (old_file_ptr != nullptr
        && patch_file_ptr != nullptr
        && new_file_ptr != nullptr
        && strlen(old_file_ptr) > 0
        && strlen(new_file_ptr) > 0
        && strlen(patch_file_ptr) > 0) {
        ret = bspatch_file(old_file_ptr, new_file_ptr, patch_file_ptr);
    }
    env->ReleaseStringUTFChars(old_file, old_file_ptr);
    env->ReleaseStringUTFChars(new_file, new_file_ptr);
    env->ReleaseStringUTFChars(patch_file, patch_file_ptr);
    return ret;
}