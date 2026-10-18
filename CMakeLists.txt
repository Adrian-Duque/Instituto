cmake_minimum_required(VERSION 4.3)
project(Instituto)

set(CMAKE_CXX_STANDARD 23)

add_executable(Instituto Main.cpp
        Matriz.cpp
        Matriz.h
        Administrador.cpp
        Administrador.h
        Profesor.cpp
        Profesor.h
        Usuario.cpp
        Usuario.h
        ListaGenerica.h
        Fichero.cpp
        Fichero.h
        Estudiante.cpp
        Estudiante.h
)

# CLion ejecuta el programa desde la carpeta de compilacion (cmake-build-debug):
# se copia ahi la carpeta ficheros para que "ficheros/actividad1.txt" se encuentre.
add_custom_command(TARGET Instituto POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ficheros $<TARGET_FILE_DIR:Instituto>/ficheros)
