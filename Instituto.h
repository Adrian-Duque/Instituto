
#ifndef INSTITUTO_H
#define INSTITUTO_H
 
#include "Matriz.h"
 
class Instituto {
public:
    double sumar(double a, double b);
    double restar(double a, double b);
    double multiplicar(double a, double b);
    double dividir(double a, double b); // lanza runtime_error si b == 0
 
    Matriz<double> operarMatrices(const Matriz<double>& a, const Matriz<double>& b, char op);
};
 
#endif