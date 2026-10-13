#include "Instituto.h"
#include <stdexcept>

double Instituto::sumar(double a, double b) {
    return a + b;
}

double Instituto::restar(double a, double b) {
    return a - b;
}

double Instituto::multiplicar(double a, double b) {
    return a * b;
}

double Instituto::dividir(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Division entre cero");
    }
    return a / b;
}

Matriz<double> Instituto::operarMatrices(const Matriz<double>& a, const Matriz<double>& b, char op) {
    switch (op) {
        case '+': return a.sumar(b);
        case '-': return a.restar(b);
        case '*': return a.multiplicar(b);
        case '/': return a.dividir(b);
        default:
            throw std::invalid_argument("Operacion no valida");
    }
}