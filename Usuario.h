#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "ListaGenerica.h"

// Clase base de los tres roles (Estudiante, Profesor y Administrador).
// Guarda lo que tienen en comun: id, nombre y apellido.
// Los atributos son protected para que las clases hijas puedan usarlos.
class Usuario {
protected:
    int id;
    std::string nombre;
    std::string apellido;
    static ListaGenerica<int> idsEnUso; // Ids ocupados: al dar de baja se libera y se reutiliza
public:
    Usuario(std::string nombre, std::string apellido);
    // Virtual: al hacer delete sobre un Usuario* se ejecuta tambien el destructor de la clase hija
    virtual ~Usuario();

    int getId() const;
    std::string getNombre() const;
    std::string getApellido() const;

    void setNombre(std::string nombre);
    void setApellido(std::string apellido);

    // Virtual: con un Usuario* se ejecuta la version del objeto real (polimorfismo dinamico)
    virtual std::string getRol();
    virtual void mostrarDatos();
};

#endif // USUARIO_H
