cmake_minimum_required(VERSION 3.29)
project(pr9 C)

set(CMAKE_C_STANDARD 11)

add_executable(pr9 main.c
        src/io.c
        src/include/io.h
        src/misc.c
        src/include/misc.h)
