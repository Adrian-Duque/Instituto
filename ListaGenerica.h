#ifndef LISTAGENERICA_H
#define LISTAGENERICA_H

#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class ListaGenerica {
private:
    T almacen[50];
    int count;
public:
    ListaGenerica() {
        count = 0;
    }

    void add(T nuevo) {
        if (count >= 50) {
            throw std::out_of_range("La lista esta llena (maximo 50 elementos).");
        }
        almacen[count] = nuevo;
        count++;
    }

    T remove() {
        if (count == 0) {
            throw std::out_of_range("La lista esta vacia, no se puede eliminar.");
        }
        count--;
        return almacen[count];
    }

    // Eliminar en una posición específica desplazando a la izquierda
    T eliminar(int posicion) {
        if (posicion < 0 || posicion >= count) {
            throw std::out_of_range("Posicion no valida para eliminar.");
        }
        T elementoEliminado = almacen[posicion];
        for (int i = posicion; i < count - 1; i++) {
            almacen[i] = almacen[i + 1];
        }
        count--;
        return elementoEliminado;
    }

    int length() const {
        return count;
    }

    // Consulta sin modificar la lista
    T at(int position) const {
        if (position < 0 || position >= count) {
            throw std::out_of_range("Indice fuera de rango");
        }
        return almacen[position];
    }

    void recorrer() const {
        for (int i = 0; i < count; i++) {
            std::cout << almacen[i] << " ";
        }
        std::cout << std::endl;
    }

    int buscar(T elemento) const {
        for (int i = 0; i < count; i++) {
            if (almacen[i] == elemento) {
                return i;
            }
        }
        return -1;
    }

    void ordenar() {
        std::sort(almacen, almacen + count);
    }
};

#endif // LISTAGENERICA_H