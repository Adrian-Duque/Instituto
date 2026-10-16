#ifndef INSTITUTO_PROFESOR_H
#define INSTITUTO_PROFESOR_H

#include "Usuario.h"
#include "ListaGenerica.h"
#include <string>

class Estudiante;

class Profesor : public Usuario {
private:
    ListaGenerica<Estudiante*> clase; // Punteros: el profesor no es dueño de los estudiantes

public:
    // Constructor
    Profesor(std::string nombre, std::string apellido);

    // Métodos heredados de Usuario
    std::string getRol();
    void mostrarDatos();

    // Métodos de profesor 
    void inscribir(Estudiante* e);
    void desinscribir(int id);
    void ponerNota(int id, std::string asignatura, float nota);
    void verClase();
};

#endif //INSTITUTO_PROFESOR_H