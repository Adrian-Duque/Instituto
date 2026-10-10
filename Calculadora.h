//
// Created by Nacho on 10/10/2026.
//

#ifndef INSTITUTO_CALCULADORA_H
#define INSTITUTO_CALCULADORA_H

#include "Matriz.h"

class Calculadora {
public:
    double sumar(double a, double b);
    double restar(double a, double b);
    double multiplicar(double a, double b);
    // Lanza std::invalid_argument si b == 0
    double dividir(double a, double b);
    // op: '+', '-', '*' o '/'. Lanza std::invalid_argument si op no es valida
    Matriz<double> operarMatrices(const Matriz<double>& a, const Matriz<double>& b, char op);
};


#endif //INSTITUTO_CALCULADORA_H
