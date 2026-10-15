//
// Created by adrian on 15/10/2026.
//

#ifndef INSTITUTO_FICHERO_H
#define INSTITUTO_FICHERO_H
#include <string>

// Documento de la mochila: guarda la ruta de un .txt y el texto leido del disco.
class Fichero {
private:
    std::string ruta;
    std::string contenido;

public:
    // Constructor por defecto: lo necesita el array interno de ListaGenerica<Fichero>.
    Fichero();
    Fichero(const std::string& ruta);

    // Lee el .txt de "ruta" y lo guarda en "contenido".
    // Lanza runtime_error si no se puede abrir.
    void cargar();
    void mostrar() const;
};


#endif //INSTITUTO_FICHERO_H
