#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <string>
#include "Usuario.h"
#include "ListaGenerica.h"

class Administrador : public Usuario {
public:
    Administrador(const std::string& nombre, const std::string& apellido);

    std::string getRol() override;

    // rol: 'E' = Estudiante, 'P' = Profesor, 'A' = Administrador
    // Lanza runtime_error si el rol no es válido
    void darAlta(ListaGenerica<Usuario*>& lista, char rol,
                 const std::string& nombre, const std::string& apellido);

    // Lanza runtime_error si el id no existe
    void darBaja(ListaGenerica<Usuario*>& lista, int id);

    // Lanza runtime_error si el id no existe
    void modificarDatos(ListaGenerica<Usuario*>& lista, int id,
                        const std::string& nombre, const std::string& apellido);
};

#endif