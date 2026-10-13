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

    Usuario* u = lista.at(pos);

    if (u->getRol() == "Estudiante") {
        Estudiante* e = static_cast<Estudiante*>(u);
        if (e->getProfesor() != nullptr) {
            e->getProfesor()->desinscribir(id);
        }
    } else if (u->getRol() == "Profesor") {
        Profesor* p = static_cast<Profesor*>(u);
        for (int i = 0; i < lista.length(); i++) {
            if (lista.at(i)->getRol() == "Estudiante") {
                Estudiante* e = static_cast<Estudiante*>(lista.at(i));
                if (e->getProfesor() == p) {
                    e->setProfesor(nullptr);
                }
            }
        }
    }

    delete u;
    lista.eliminar(pos);
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