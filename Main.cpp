#include "Matriz.h"
#include <iostream>
#include <stdexcept>

#include "ListaGenerica.h"
#include "Usuario.h"
#include "Administrador.h"
#include "Profesor.h"
#include "Estudiante.h"
using namespace std;

double sumar(double a, double b) {
    return a + b;
}

double restar(double a, double b) {
    return a - b;
}

double multiplicar(double a, double b) {
    return a * b;
}

double dividir(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Division entre cero");
    }
    return a / b;
}

Matriz<double> operarMatrices(const Matriz<double> &a, const Matriz<double> &b, char op) {
    switch (op) {
        case '+': return a.sumar(b);
        case '-': return a.restar(b);
        case '*': return a.multiplicar(b);
        case '/': return a.dividir(b);
        default:
            throw std::invalid_argument("Operacion no valida");
    }
}

int leerEntero(string mensaje) {
    int numero;
    cout << mensaje;
    cin >> numero;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada no valida. Escribe un numero: ";
        cin >> numero;
    }

    cin.ignore(10000, '\n');
    return numero;
}

string leerTexto(string mensaje) {
    string texto;
    cout << mensaje;
    getline(cin, texto);

    while (texto == "") {
        cout << "No puede estar vacio. Escribe de nuevo: ";
        getline(cin, texto);
    }

    return texto;
}

Usuario *buscarUsuario(ListaGenerica<Usuario *> &lista, int id) {
    for (int i = 0; i < lista.length(); i++) {
        Usuario *u = lista.at(i);
        if (u->getId() == id) {
            return u;
        }
    }
    return nullptr;
}

void menuAdministrador(Administrador *admin, ListaGenerica<Usuario *> &usuarios) {
    cout << "Menu del administrador (pendiente)" << endl;
}

void menuProfesor(Profesor *profesor, ListaGenerica<Usuario *> &usuarios) {
    cout << "Menu del profesor (pendiente)" << endl;
}

void menuEstudiante(Estudiante *estudiante) {
    cout << "Menu del estudiante (pendiente)" << endl;
}

int main() {
    ListaGenerica<Usuario *> usuarios;

    Administrador *admin = new Administrador("Admin", "Principal");
    usuarios.add(admin);

    cout << "Administrador creado. Su id es: " << admin->getId() << endl;

    bool salir = false;

    while (salir == false) {
        cout << endl << "===== INSTITUTO =====" << endl;
        int id = leerEntero("Introduce tu id (0 para salir): ");

        if (id == 0) {
            salir = true;
        } else {
            Usuario *u = buscarUsuario(usuarios, id);

            if (u == nullptr) {
                cout << "No existe ningun usuario con ese id." << endl;
            } else {
                cout << "Bienvenido, " << u->getNombre() << " (" << u->getRol() << ")" << endl;

                string rol = u->getRol();

                if (rol == "Administrador") {
                    Administrador *a = static_cast<Administrador *>(u);
                    menuAdministrador(a, usuarios);
                } else if (rol == "Profesor") {
                    Profesor *p = static_cast<Profesor *>(u);
                    menuProfesor(p, usuarios);
                } else if (rol == "Estudiante") {
                    Estudiante *e = static_cast<Estudiante *>(u);
                    menuEstudiante(e);
                }
            }
        }
    }

    // Aqui ira la liberacion de memoria (delete)

    return 0;
}
