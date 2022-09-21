cmake_minimum_required(VERSION 3.10)

project(bz2)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} srcs)

add_library(
        ${PROJECT_NAME}
        STATIC
        ${srcs}
)