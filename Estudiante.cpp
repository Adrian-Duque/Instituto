//
// Created by adrian on 15/10/2026.
//

#include "Estudiante.h"
#include "Profesor.h" // en el .cpp si se necesita la clase completa para llamar a desinscribir
#include <iostream>
#include <stdexcept>

Estudiante::Estudiante(const std::string& nombre, const std::string& apellido)
    : Usuario(nombre, apellido) {
    profesor = nullptr; // Al darse de alta todavia no esta en ninguna clase
    mochila = new ListaGenerica<Fichero*>();
}

Estudiante::~Estudiante() {
    // Si esta en una clase, se quita de ella para que el profesor no se quede
    // con un puntero a un estudiante que ya no existe (puntero colgante).
    // profesor != nullptr solo cuando esta inscrito, asi que desinscribir siempre lo encuentra.
    if (profesor != nullptr) {
        profesor->desinscribir(id);
    }

    // Se libera cada fichero y despues la propia mochila
    while (mochila->length() > 0) {
        delete mochila->remove();
    }
    delete mochila;
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
    Fichero* nuevo = new Fichero(ruta);
    try {
        nuevo->cargar();    // Si falla lanza la excepcion y no se añade nada a la mochila
        mochila->add(nuevo);
    } catch (...) {
        delete nuevo;       // no se ha guardado: se libera para que no haya fuga
        throw;
    }
}

void Estudiante::quitarFichero(int posicion) {
    Fichero* quitado = mochila->eliminar(posicion - 1);
    delete quitado;
}

void Estudiante::verMochila() {
    std::cout << "Mochila de " << nombre << " " << apellido
              << " (" << mochila->length() << " ficheros)" << std::endl;

    if (mochila->length() == 0) {
        std::cout << "  La mochila esta vacia" << std::endl;
        return;
    }
    for (int i = 0; i < mochila->length(); i++) {
        std::cout << "[" << i + 1 << "] ";
        mochila->at(i)->mostrar();
    }
}

Profesor* Estudiante::getProfesor() const {
    return profesor;
}

void Estudiante::setProfesor(Profesor* p) {
    profesor = p;
}
