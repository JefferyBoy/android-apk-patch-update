//
// Created by mxlei on 2022/9/11.
//
#include "file_patcher.h"
#include "iostream"

int main(int argc, char *args[]) {
    char *old_file = "/media/mxlei/workspace/DevLibrary/gprinter/app/gprinter/release/gprinter-release-v5.2.5.apk";
    char *new_file = "/media/mxlei/workspace/DevLibrary/gprinter/app/gprinter/release/new.apk";
    char *patch_file = "/media/mxlei/workspace/DevLibrary/gprinter/app/gprinter/release/patch.apk";
    int ret = bspatch_file(old_file, new_file, patch_file);
    if (ret == 0) {
        std::cout << "patch ok" << std::endl;
    }
}

