#include "Matriz.h"
#include <iostream>
#include <stdexcept>

class Calculadora {
public:
    double sumar(double a, double b);
    double restar(double a, double b);
    double multiplicar(double a, double b);
    double dividir(double a, double b); // lanza runtime_error si b == 0

    Matriz<double> operarMatrices(const Matriz<double>& a, const Matriz<double>& b, char op);
};

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
        throw std::runtime_error("Division entre cero");
    }
    return a / b;
}

Matriz<double> Calculadora::operarMatrices(const Matriz<double>& a, const Matriz<double>& b, char op) {
    switch (op) {
        case '+': return a.sumar(b);
        case '-': return a.restar(b);
        case '*': return a.multiplicar(b);
        case '/': return a.dividir(b);
        default:
            throw std::invalid_argument("Operacion no valida");
    }
}

int main() {
    Calculadora calculadora;

    try {
        std::cout << "5 + 3 = " << calculadora.sumar(5, 3) << std::endl;
        std::cout << "5 - 3 = " << calculadora.restar(5, 3) << std::endl;
        std::cout << "5 * 3 = " << calculadora.multiplicar(5, 3) << std::endl;
        std::cout << "6 / 3 = " << calculadora.dividir(6, 3) << std::endl;

        Matriz<double> a(2, 2);
        Matriz<double> b(2, 2);
        a.set(0, 0, 1); a.set(0, 1, 2);
        a.set(1, 0, 3); a.set(1, 1, 4);
        b.set(0, 0, 5); b.set(0, 1, 6);
        b.set(1, 0, 7); b.set(1, 1, 8);

        std::cout << "A + B:" << std::endl;
        calculadora.operarMatrices(a, b, '+').imprimir();
        std::cout << "A * B:" << std::endl;
        calculadora.operarMatrices(a, b, '*').imprimir();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
