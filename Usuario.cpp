#include "Usuario.h"
#include <iostream>

int Usuario::siguienteId = 1;

Usuario::Usuario(std::string nombre, std::string apellido) {
    this->id = siguienteId++; // Asigna el ID actual y lo incrementa para el siguiente
    this->nombre = nombre;
    this->apellido = apellido;
}

Usuario::~Usuario() {
    // Destructor virtual por defecto
}

int Usuario::getId() const {
    return id;
}

std::string Usuario::getNombre() const {
    return nombre;
}

std::string Usuario::getApellido() const {
    return apellido;
}

void Usuario::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void Usuario::setApellido(std::string apellido) {
    this->apellido = apellido;
}

void Usuario::mostrarDatos() {
    std::cout << "ID: " << id << " | Nombre: " << nombre << " " << apellido << std::endl;
}