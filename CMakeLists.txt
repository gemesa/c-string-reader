cmake_minimum_required(VERSION 3.24)
project(c_string_reader C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET (CMAKE_C_COMPILER "/usr/bin/clang")
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

file(MAKE_DIRECTORY artifacts)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/artifacts)

add_executable(c-string-reader
        main.c
        modules/config.h
        modules/reader/reader.c
        modules/reader/reader.h
        modules/argparser/argparser.c
        modules/argparser/argparser.h)

