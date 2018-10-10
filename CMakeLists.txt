cmake_minimum_required(VERSION 2.8)
project(EasyJSONC C)

set(CMAKE_C_STANDARD 11)

add_executable(EasyJSONC
        main.c slog.h EasyJSON.h slog.c EasyJSON.c)
