#include "Profesor.h"
#include "Estudiante.h"
#include <iostream>
#include <stdexcept>

Profesor::Profesor(std::string nombre, std::string apellido) : Usuario(nombre, apellido) {}

Profesor::~Profesor() {
    // El profesor no es dueño de sus estudiantes: no se borran, solo se quedan sin clase
    for (int i = 0; i < clase.length(); i++) {
        clase.at(i)->setProfesor(nullptr);
    }
}

std::string Profesor::getRol() {
    return "Profesor";
}

void Profesor::mostrarDatos() {
    std::cout << "[Profesor] "<< std::endl;
    Usuario::mostrarDatos();
}

void Profesor::inscribir(Estudiante* e) {
    if (e == nullptr) {
        throw std::invalid_argument("El estudiante no puede ser nulo.");
    }
    // Comprobar si ya tiene profesor asignado
    if (e->getProfesor() != nullptr) {
        throw std::runtime_error("El estudiante ya esta inscrito en otra clase.");
    }

    clase.add(e);
    e->setProfesor(this);
}

void Profesor::desinscribir(int id) {
    bool encontrado = false;
    for (int i = 0; i < clase.length(); i++) {
        Estudiante* e = clase.at(i);
        if (e->getId() == id) {
            e->setProfesor(nullptr);
            clase.eliminar(i);
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        throw std::out_of_range("Estudiante no encontrado en esta clase.");
    }
}

void Profesor::ponerNota(int id, std::string asignatura, float nota) {
    bool encontrado = false;
    for (int i = 0; i < clase.length(); i++) {
        Estudiante* e = clase.at(i);
        if (e->getId() == id) {
            e->ponerNota(asignatura, nota); 
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        throw std::out_of_range("Estudiante no encontrado para poner la nota.");
    }
}

void Profesor::verClase() {
    std::cout << "Numero de inscritos en la clase: " << clase.length() << std::endl;
    std::cout << "Listado de estudiantes:" << std::endl;
    for (int i = 0; i < clase.length(); i++) {
        Estudiante* e = clase.at(i);
        e->mostrarDatos(); // Muestra nombre, apellido y notas
    }
}