//
// Created by adrian on 15/10/2026.
//

#ifndef INSTITUTO_ESTUDIANTE_H
#define INSTITUTO_ESTUDIANTE_H

#include <string>
#include "Usuario.h"
#include "ListaGenerica.h"
#include "Fichero.h"


// Forward declaration: solo se guarda un puntero a Profesor, no hace falta incluir su .h
// (y se evita la inclusion circular, porque Profesor.h ya conoce a Estudiante).
class Profesor;

class Estudiante : public Usuario {
private:
    // Listas paralelas: la nota de asignaturas.at(i) es notas.at(i).
    ListaGenerica<std::string> asignaturas;
    ListaGenerica<float> notas;

    // Por valor: el estudiante es dueño de sus ficheros (composicion).
    ListaGenerica<Fichero> mochila;

    // Por puntero: el profesor vive en la lista de usuarios, aqui solo se referencia.
    Profesor* profesor;

public:
    Estudiante(const std::string& nombre, const std::string& apellido);

    std::string getRol() override;
    void mostrarDatos() override;

    // Si la asignatura ya existe actualiza su nota; si no, la añade.
    // Lanza invalid_argument si la nota no esta entre 0 y 10.
    void ponerNota(const std::string& asignatura, float nota);

    // Lanza runtime_error si el fichero no se puede abrir.
    void cargarFichero(const std::string& ruta);
    void verMochila();

    Profesor* getProfesor() const;
    void setProfesor(Profesor* p);
};



#endif //INSTITUTO_ESTUDIANTE_H
