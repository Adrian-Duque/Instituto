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
    Fichero(const std::string& ruta);

    // Lee el .txt de "ruta" y lo guarda en "contenido".
    // Lanza invalid_argument si la ruta no es un .txt y runtime_error si no se puede abrir.
    void cargar();
    void mostrar() const;
};


#endif //INSTITUTO_FICHERO_H
