cmake_minimum_required(VERSION 4.3)
project(Instituto)

set(CMAKE_CXX_STANDARD 23)

add_executable(Instituto Instituto.cpp
        Matriz.cpp
        Matriz.h
        Instituto.h)
