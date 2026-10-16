#include "Administrador.h"
#include "Estudiante.h"
#include "Profesor.h"
#include <stdexcept>

Administrador::Administrador(const std::string& nombre, const std::string& apellido)
    : Usuario(nombre, apellido) {}

std::string Administrador::getRol() {
    return "Administrador";
}

void Administrador::darAlta(ListaGenerica<Usuario*>& lista, char rol,
                            const std::string& nombre, const std::string& apellido) {
    Usuario* nuevo = nullptr;

    if (rol == 'E') {
        nuevo = new Estudiante(nombre, apellido);
    } else if (rol == 'P') {
        nuevo = new Profesor(nombre, apellido);
    } else if (rol == 'A') {
        nuevo = new Administrador(nombre, apellido);
    } else {
        throw std::runtime_error("Rol no valido");
    }

    try {
        lista.add(nuevo);
    } catch (...) {
        delete nuevo;  // lista llena: no queda fuga
        throw;
    }
}

void Administrador::darBaja(ListaGenerica<Usuario*>& lista, int id) {
    int pos = -1;
    for (int i = 0; i < lista.length(); i++) {
        if (lista.at(i)->getId() == id) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        throw std::runtime_error("El id no existe");
    }

    // Se saca de la lista y se elimina de memoria. Al ser el destructor virtual, delete ejecuta
    // el de la clase real: ~Estudiante o ~Profesor deshacen la relacion profesor-alumno
    // y despues ~Usuario deja libre el id.
    Usuario* u = lista.eliminar(pos);
    delete u;
}

void Administrador::modificarDatos(ListaGenerica<Usuario*>& lista, int id,
                                   const std::string& nombre, const std::string& apellido) {
    for (int i = 0; i < lista.length(); i++) {
        if (lista.at(i)->getId() == id) {
            lista.at(i)->setNombre(nombre);
            lista.at(i)->setApellido(apellido);
            return;
        }
    }
    throw std::runtime_error("El id no existe");
}