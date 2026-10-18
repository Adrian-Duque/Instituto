//
// Created by Nacho on 10/10/2026.
//

#include "Matriz.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

// Por debajo de este valor un pivote se considera 0 (errores de redondeo de double)
const double TOLERANCIA = 1e-9;

template <typename T>
Matriz<T>::Matriz() : datos(), filas(0), columnas(0) {}

template <typename T>
Matriz<T>::Matriz(int filas, int columnas) : datos(), filas(filas), columnas(columnas) {
    if (filas < 1 || columnas < 1 || filas > MAX_DIM || columnas > MAX_DIM) {
        throw std::invalid_argument("Dimensiones de matriz no validas");
    }
}

template <typename T>
void Matriz<T>::set(int i, int j, T valor) {
    if (i < 0 || i >= filas || j < 0 || j >= columnas) {
        throw std::out_of_range("Posicion fuera de la matriz");
    }
    datos[i][j] = valor;
}

template <typename T>
T Matriz<T>::get(int i, int j) const {
    if (i < 0 || i >= filas || j < 0 || j >= columnas) {
        throw std::out_of_range("Posicion fuera de la matriz");
    }
    return datos[i][j];
}

template <typename T>
int Matriz<T>::getFilas() const {
    return filas;
}

template <typename T>
int Matriz<T>::getColumnas() const {
    return columnas;
}

template <typename T>
void Matriz<T>::imprimir() const {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            std::cout << datos[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

template <typename T>
Matriz<T> Matriz<T>::sumar(const Matriz<T>& otra) const {
    if (filas != otra.filas || columnas != otra.columnas) {
        throw std::invalid_argument("Las matrices deben tener las mismas dimensiones");
    }
    Matriz<T> resultado(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado.datos[i][j] = datos[i][j] + otra.datos[i][j];
        }
    }
    return resultado;
}

template <typename T>
Matriz<T> Matriz<T>::restar(const Matriz<T>& otra) const {
    if (filas != otra.filas || columnas != otra.columnas) {
        throw std::invalid_argument("Las matrices deben tener las mismas dimensiones");
    }
    Matriz<T> resultado(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado.datos[i][j] = datos[i][j] - otra.datos[i][j];
        }
    }
    return resultado;
}

template <typename T>
Matriz<T> Matriz<T>::multiplicar(const Matriz<T>& otra) const {
    if (columnas != otra.filas) {
        throw std::invalid_argument("Columnas de la primera distintas de filas de la segunda");
    }
    Matriz<T> resultado(filas, otra.columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < otra.columnas; j++) {
            T suma = T();
            for (int k = 0; k < columnas; k++) {
                suma = suma + datos[i][k] * otra.datos[k][j];
            }
            resultado.datos[i][j] = suma;
        }
    }
    return resultado;
}

// Division de matrices: this * otra^-1 (otra debe ser cuadrada e invertible)
template <typename T>
Matriz<T> Matriz<T>::dividir(const Matriz<T>& otra) const {
    if (otra.filas != otra.columnas) {
        throw std::invalid_argument("El divisor debe ser una matriz cuadrada");
    }
    if (columnas != otra.filas) {
        throw std::invalid_argument("Dimensiones incompatibles para dividir");
    }
    const int n = otra.filas;

    // Gauss-Jordan sobre [otra | I] para obtener la inversa
    double a[MAX_DIM][2 * MAX_DIM];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = otra.datos[i][j];
            a[i][n + j] = (i == j) ? 1.0 : 0.0;
        }
    }
    for (int c = 0; c < n; c++) {
        // Pivoteo parcial: se usa la fila con el valor mas grande en esta columna.
        // Con decimales un 0 puede quedar como 1e-17, por eso se compara con una tolerancia.
        int pivote = c;
        for (int i = c + 1; i < n; i++) {
            if (std::fabs(a[i][c]) > std::fabs(a[pivote][c])) {
                pivote = i;
            }
        }
        if (std::fabs(a[pivote][c]) < TOLERANCIA) {
            throw std::invalid_argument("La matriz divisor no es invertible");
        }
        for (int j = 0; j < 2 * n; j++) {
            double tmp = a[c][j];
            a[c][j] = a[pivote][j];
            a[pivote][j] = tmp;
        }
        double p = a[c][c];
        for (int j = 0; j < 2 * n; j++) {
            a[c][j] /= p;
        }
        for (int i = 0; i < n; i++) {
            if (i != c) {
                double f = a[i][c];
                for (int j = 0; j < 2 * n; j++) {
                    a[i][j] -= f * a[c][j];
                }
            }
        }
    }

    Matriz<T> inversa(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inversa.datos[i][j] = a[i][n + j];
        }
    }
    return multiplicar(inversa);
}

// Opcional
template <typename T>
Matriz<T> Matriz<T>::traspuesta() const {
    Matriz<T> resultado(columnas, filas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado.datos[j][i] = datos[i][j];
        }
    }
    return resultado;
}

// Opcional: solo para matrices cuadradas
template <typename T>
T Matriz<T>::determinante() const {
    if (filas != columnas) {
        throw std::invalid_argument("El determinante requiere una matriz cuadrada");
    }
    const int n = filas;
    double a[MAX_DIM][MAX_DIM];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = datos[i][j];
        }
    }
    double det = 1.0;
    for (int c = 0; c < n; c++) {
        // Pivoteo parcial, igual que en dividir
        int pivote = c;
        for (int i = c + 1; i < n; i++) {
            if (std::fabs(a[i][c]) > std::fabs(a[pivote][c])) {
                pivote = i;
            }
        }
        if (std::fabs(a[pivote][c]) < TOLERANCIA) {
            return T(); // columna sin pivote: la matriz es singular y su determinante es 0
        }
        if (pivote != c) {
            for (int j = 0; j < n; j++) {
                double tmp = a[c][j];
                a[c][j] = a[pivote][j];
                a[pivote][j] = tmp;
            }
            det = -det;
        }
        det *= a[c][c];
        for (int i = c + 1; i < n; i++) {
            double f = a[i][c] / a[c][c];
            for (int j = c; j < n; j++) {
                a[i][j] -= f * a[c][j];
            }
        }
    }
    return det;
}

// Tipos con los que se puede usar Matriz<T> (al estar la implementacion en el .cpp)
template class Matriz<int>;
template class Matriz<float>;
template class Matriz<double>;
