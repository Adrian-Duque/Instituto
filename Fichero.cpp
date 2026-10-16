//
// Created by adrian on 15/10/2026.
//

#include "Fichero.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

Fichero::Fichero(const std::string& ruta) {
    this->ruta = ruta;
    contenido = "";
}

void Fichero::cargar() {
    // El enunciado pide ficheros .txt (asi tampoco se puede cargar una carpeta)
    const std::string extension = ".txt";
    if (ruta.length() <= extension.length() ||
        ruta.compare(ruta.length() - extension.length(), extension.length(), extension) != 0) {
        throw std::invalid_argument("Solo se pueden cargar ficheros .txt: " + ruta);
    }

    std::ifstream entrada(ruta);
    if (!entrada.is_open()) {
        throw std::runtime_error("No se ha podido abrir el fichero: " + ruta);
    }

    contenido = "";
    std::string linea;
    while (std::getline(entrada, linea)) {
        contenido += linea + "\n";
    }
    // El ifstream se cierra solo al salir de la funcion (su destructor libera el fichero).
}

void Fichero::mostrar() const {
    std::cout << "--- " << ruta << " ---" << std::endl;
    std::cout << contenido << std::endl;
}