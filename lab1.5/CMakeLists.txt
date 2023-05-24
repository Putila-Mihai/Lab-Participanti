cmake_minimum_required(VERSION 3.24)
project(lab2_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2_4 main.c entities.h entities.c service.h entities.c repo.h repo.c service.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-Wall-Wextra")