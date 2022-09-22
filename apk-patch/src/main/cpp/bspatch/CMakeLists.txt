cmake_minimum_required(VERSION 3.10)

project(bspatch)

add_library(
        ${PROJECT_NAME}
        STATIC
        bspatch.c
)

add_dependencies(${PROJECT_NAME} bz2)