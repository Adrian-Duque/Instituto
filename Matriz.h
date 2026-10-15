//
// Created by Nacho on 10/10/2026.
//

#ifndef INSTITUTO_MATRIZ_H
#define INSTITUTO_MATRIZ_H

const int MAX_DIM = 10;

template <typename T>
class Matriz {
private:
    T datos[MAX_DIM][MAX_DIM];
    int filas;
    int columnas;

public:
    Matriz();
    Matriz(int filas, int columnas);

    void set(int i, int j, T valor);
    T get(int i, int j) const;
    int getFilas() const;
    int getColumnas() const;
    void imprimir() const;
    Matriz<T> sumar(const Matriz<T>& otra) const;
    Matriz<T> restar(const Matriz<T>& otra) const;
    Matriz<T> multiplicar(const Matriz<T>& otra) const;
    Matriz<T> dividir(const Matriz<T>& otra) const;
    Matriz<T> traspuesta() const;
    T determinante() const;
};


#endif //INSTITUTO_MATRIZ_H
