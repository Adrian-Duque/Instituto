//
// Created by Nacho on 10/10/2026.
//

#include "Calculadora.h"

#include <stdexcept>

double Calculadora::sumar(double a, double b) {
    return a + b;
}

double Calculadora::restar(double a, double b) {
    return a - b;
}

double Calculadora::multiplicar(double a, double b) {
    return a * b;
}

double Calculadora::dividir(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("No se puede dividir entre cero");
    }
    return a / b;
}

Matriz<double> Calculadora::operarMatrices(const Matriz<double>& a, const Matriz<double>& b, char op) {
    switch (op) {
        case '+':
            return a.sumar(b);
        case '-':
            return a.restar(b);
        case '*':
            return a.multiplicar(b);
        case '/':
            return a.dividir(b);
        default:
            throw std::invalid_argument("Operacion de matrices no valida");
    }
}
