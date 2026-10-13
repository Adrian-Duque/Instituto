cmake_minimum_required(VERSION 4.3)
project(Instituto)

set(CMAKE_CXX_STANDARD 23)

add_executable(Instituto main.cpp
        Administrador.cpp
        Administrador.h
        Profesor.cpp
        Profesor.h
        Usuario.cpp
        Usuario.h
        ListaGenerica.h
)
