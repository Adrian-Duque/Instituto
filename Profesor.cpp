#include "Profesor.h"
#include "Estudiante.h"
#include <iostream>
#include <stdexcept>

Profesor::Profesor(std::string nombre, std::string apellido) : Usuario(nombre, apellido) {}

std::string Profesor::getRol() {
    return "Profesor";
}

void Profesor::mostrarDatos() {
    std::cout << "Profesor ID: " << id << " - Nombre: " << nombre << " " << apellido << std::endl;
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
        if (e->getid() == id) {
            e->setProfesor(nullptr);
            clase.eliminate(i); // O el método correspondiente para eliminar por posición en tu ListaGenerica
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
        if (e->getid() == id) {
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