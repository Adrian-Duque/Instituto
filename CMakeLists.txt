cmake_minimum_required(VERSION 4.3)
project(Instituto)

set(CMAKE_CXX_STANDARD 23)

add_executable(Instituto Main.cpp
        Matriz.cpp
        Matriz.h
        Administrador.cpp
        Administrador.h
        Fichero.cpp
        Fichero.h
        Estudiante.cpp
        Estudiante.h
)