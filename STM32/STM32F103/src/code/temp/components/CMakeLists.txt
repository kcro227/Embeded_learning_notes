cmake_minimum_required(VERSION 3.7)

# 添加组件包含目录
include_directories("led/inc")

# 包含该目录下所有下一级目录的所有.C文件
file(GLOB_RECURSE USR_SRC "./*.c")

add_library(USER_LIB ${USR_SRC})