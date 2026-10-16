#include "Usuario.h"
#include <iostream>

ListaGenerica<int> Usuario::idsEnUso;

Usuario::Usuario(std::string nombre, std::string apellido) {
    // Se asigna el menor id libre (empezando en 1, el 0 es "salir"), asi se reutilizan los de las bajas.
    // Si ya hay 50 usuarios, add lanza out_of_range y el objeto no llega a crearse.
    int candidato = 1;
    while (idsEnUso.buscar(candidato) != -1) {
        candidato++;
    }
    idsEnUso.add(candidato);

    this->id = candidato;
    this->nombre = nombre;
    this->apellido = apellido;
}

Usuario::~Usuario() {
    // Al destruir el usuario su id queda libre para la siguiente alta
    int pos = idsEnUso.buscar(id);
    if (pos != -1) {
        idsEnUso.eliminar(pos);
    }
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
std::string Usuario::getRol() {
    return "Usuario";
}
void Usuario::mostrarDatos() {
    std::cout << "ID: " << id << " | Nombre: " << nombre << " " << apellido << std::endl;
}