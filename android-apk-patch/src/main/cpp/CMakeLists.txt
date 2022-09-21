cmake_minimum_required(VERSION 3.10)

project("bspatch-util")

include_directories(
        bspatch
        bz2
)

add_subdirectory(bz2)
add_subdirectory(bspatch)

add_library(
        ${PROJECT_NAME}
        SHARED
        file_patcher.c
        com_gainscha_bspatch_jni.cpp
)

find_library(
        log-lib
        log
)

target_link_libraries(
        ${PROJECT_NAME}
        bspatch
        bz2
        ${log-lib}
)