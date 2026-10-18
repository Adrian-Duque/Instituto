#ifndef LISTAGENERICA_H
#define LISTAGENERICA_H

#include <iostream>
#include <algorithm>
#include <stdexcept>

// Contenedor generico (TAD lista) que usan todas las colecciones del proyecto:
// usuarios, alumnos de una clase, asignaturas, notas, mochila e ids en uso.
// Es una plantilla, asi que el cuerpo de los metodos tiene que estar en el .h:
// el compilador genera el codigo para cada tipo concreto (ListaGenerica<int>,
// ListaGenerica<Usuario*>...) en el sitio donde se usa.
//
// Invariante: las posiciones validas son 0..count-1 y count esta entre 0 y 50.
// Requisitos sobre T: tener constructor por defecto y poder copiarse (array interno),
// == para buscar y << para recorrer.
template <typename T>
class ListaGenerica {
private:
    T almacen[50];   // tamaño fijo: los elementos quedan contiguos en memoria
    int count;       // numero de posiciones ocupadas
public:
    // Constructora: deja la lista en un estado valido (vacia)
    ListaGenerica() {
        count = 0;
    }

    // Modificadora: añade al final. Lanza out_of_range si la lista esta llena
    void add(T nuevo) {
        if (count >= 50) {
            throw std::out_of_range("La lista esta llena (maximo 50 elementos).");
        }
        almacen[count] = nuevo;
        count++;
    }

    // Modificadora: saca y devuelve el ultimo elemento
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

    // Consultoras (const): no modifican la lista
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

    // Busqueda lineal: devuelve la posicion del elemento o -1 si no esta
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