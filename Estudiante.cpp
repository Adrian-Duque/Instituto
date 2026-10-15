//
// Created by adrian on 15/10/2026.
//

#include "Estudiante.h"
#include <iostream>
#include <stdexcept>

Estudiante::Estudiante(const std::string& nombre, const std::string& apellido)
    : Usuario(nombre, apellido) {
    profesor = nullptr; // Al darse de alta todavia no esta en ninguna clase
}

std::string Estudiante::getRol() {
    return "Estudiante";
}

void Estudiante::mostrarDatos() {
    std::cout << "[Estudiante] " << std::endl;
    Usuario::mostrarDatos();

    if (notas.length() == 0) {
        std::cout << "  Sin notas todavia" << std::endl;
        return;
    }
    for (int i = 0; i < notas.length(); i++) {
        std::cout << "  " << asignaturas.at(i) << ": " << notas.at(i) << std::endl;
    }
}

void Estudiante::ponerNota(const std::string& asignatura, float nota) {
    if (nota < 0 || nota > 10) {
        throw std::invalid_argument("La nota debe estar entre 0 y 10.");
    }

    // ListaGenerica no permite modificar una posicion: si la asignatura ya existe,
    // se quita de las dos listas a la vez para que sigan emparejadas y se vuelve a añadir.
    int pos = asignaturas.buscar(asignatura);
    if (pos != -1) {
        asignaturas.eliminar(pos);
        notas.eliminar(pos);
    }

    asignaturas.add(asignatura);
    notas.add(nota);
}

void Estudiante::cargarFichero(const std::string& ruta) {
    Fichero nuevo(ruta);
    nuevo.cargar();    // Si falla lanza la excepcion y no se añade nada a la mochila
    mochila.add(nuevo);
}

void Estudiante::verMochila() {
    std::cout << "Mochila de " << nombre << " " << apellido
              << " (" << mochila.length() << " ficheros)" << std::endl;

    if (mochila.length() == 0) {
        std::cout << "  La mochila esta vacia" << std::endl;
        return;
    }
    for (int i = 0; i < mochila.length(); i++) {
        mochila.at(i).mostrar();
    }
}

Profesor* Estudiante::getProfesor() const {
    return profesor;
}

void Estudiante::setProfesor(Profesor* p) {
    profesor = p;
}
