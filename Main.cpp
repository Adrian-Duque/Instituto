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

double leerDecimal(string mensaje) {
    double numero;
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

Matriz<double> leerMatriz(string nombre) {
    cout << "Matriz " << nombre << endl;
    int filas = leerEntero("Numero de filas: ");
    int columnas = leerEntero("Numero de columnas: ");

    Matriz<double> m(filas, columnas);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << nombre << "[" << i << "][" << j << "] = ";
            double valor = leerDecimal("");
            m.set(i, j, valor);
        }
    }

    return m;
}

void menuCalculadora() {
    bool volver = false;

    while (volver == false) {
        cout << endl << "--- CALCULADORA ---" << endl;
        cout << "1. Sumar" << endl;
        cout << "2. Restar" << endl;
        cout << "3. Multiplicar" << endl;
        cout << "4. Dividir" << endl;
        cout << "5. Operar con matrices" << endl;
        cout << "0. Volver" << endl;

        int opcion = leerEntero("Elige una opcion: ");

        try {
            switch (opcion) {
                case 1: {
                    double a = leerDecimal("Primer numero: ");
                    double b = leerDecimal("Segundo numero: ");
                    cout << "Resultado: " << sumar(a, b) << endl;
                    break;
                }

                case 2: {
                    double a = leerDecimal("Primer numero: ");
                    double b = leerDecimal("Segundo numero: ");
                    cout << "Resultado: " << restar(a, b) << endl;
                    break;
                }

                case 3: {
                    double a = leerDecimal("Primer numero: ");
                    double b = leerDecimal("Segundo numero: ");
                    cout << "Resultado: " << multiplicar(a, b) << endl;
                    break;
                }

                case 4: {
                    double a = leerDecimal("Primer numero: ");
                    double b = leerDecimal("Segundo numero: ");
                    cout << "Resultado: " << dividir(a, b) << endl;
                    break;
                }

                case 5: {
                    Matriz<double> a = leerMatriz("A");
                    Matriz<double> b = leerMatriz("B");

                    cout << "Operacion: 1 = Suma, 2 = Resta, 3 = Multiplicacion, 4 = Division" << endl;
                    int tipo = leerEntero("Operacion: ");

                    char op;
                    if (tipo == 1) {
                        op = '+';
                    } else if (tipo == 2) {
                        op = '-';
                    } else if (tipo == 3) {
                        op = '*';
                    } else if (tipo == 4) {
                        op = '/';
                    } else {
                        op = 'X';
                    }

                    cout << "Resultado:" << endl;
                    operarMatrices(a, b, op).imprimir();
                    break;
                }

                case 0:
                    volver = true;
                    break;

                default:
                    cout << "Opcion no valida." << endl;
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

void menuAdministrador(Administrador *admin, ListaGenerica<Usuario *> &usuarios) {
    bool cerrarSesion = false;

    while (cerrarSesion == false) {
        cout << endl << "--- MENU ADMINISTRADOR ---" << endl;
        cout << "1. Dar de alta un usuario" << endl;
        cout << "2. Dar de baja un usuario" << endl;
        cout << "3. Modificar datos de un usuario" << endl;
        cout << "4. Listar usuarios" << endl;
        cout << "9. Calculadora" << endl;
        cout << "0. Cerrar sesion" << endl;

        int opcion = leerEntero("Elige una opcion: ");

        try {
            switch (opcion) {
                case 1: {
                    cout << "Tipo de usuario: 1 = Estudiante, 2 = Profesor, 3 = Administrador" << endl;
                    int tipo = leerEntero("Tipo: ");

                    char rol;
                    if (tipo == 1) {
                        rol = 'E';
                    } else if (tipo == 2) {
                        rol = 'P';
                    } else if (tipo == 3) {
                        rol = 'A';
                    } else {
                        rol = 'X';
                    }

                    string nombre = leerTexto("Nombre: ");
                    string apellido = leerTexto("Apellido: ");

                    admin->darAlta(usuarios, rol, nombre, apellido);

                    Usuario *nuevo = usuarios.at(usuarios.length() - 1);
                    cout << "Usuario creado con id " << nuevo->getId() << endl;
                    break;
                }

                case 2: {
                    int id = leerEntero("Id del usuario a dar de baja: ");

                    if (id == admin->getId()) {
                        cout << "No puedes darte de baja a ti mismo." << endl;
                    } else {
                        admin->darBaja(usuarios, id);
                        cout << "Usuario dado de baja." << endl;
                    }
                    break;
                }

                case 3: {
                    int id = leerEntero("Id del usuario a modificar: ");
                    string nombre = leerTexto("Nuevo nombre: ");
                    string apellido = leerTexto("Nuevo apellido: ");

                    admin->modificarDatos(usuarios, id, nombre, apellido);
                    cout << "Datos modificados." << endl;
                    break;
                }

                case 4:
                    cout << "Usuarios registrados: " << usuarios.length() << endl;
                    for (int i = 0; i < usuarios.length(); i++) {
                        Usuario *u = usuarios.at(i);
                        cout << u->getId() << " - " << u->getNombre() << " "
                                << u->getApellido() << " (" << u->getRol() << ")" << endl;
                    }
                    break;

                case 9:
                    menuCalculadora();
                    break;

                case 0:
                    cerrarSesion = true;
                    break;

                default:
                    cout << "Opcion no valida." << endl;
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}


void menuProfesor(Profesor *profesor, ListaGenerica<Usuario *> &usuarios) {
    // Interruptor y bucle del menu
    bool cerrarSesion = false;

    while (cerrarSesion == false) {
        // Mostrar opciones y leer la elegida
        cout << endl << "--- MENU PROFESOR ---" << endl;
        cout << "1. Inscribir un estudiante en mi clase" << endl;
        cout << "2. Quitar un estudiante de mi clase" << endl;
        cout << "3. Poner una nota" << endl;
        cout << "4. Ver mi clase" << endl;
        cout << "9. Calculadora" << endl;
        cout << "0. Cerrar sesion" << endl;

        int opcion = leerEntero("Elige una opcion: ");

        try {
            switch (opcion) {
                case 1: {
                    // Inscribir: buscar al estudiante por su id y comprobarlo
                    int id = leerEntero("Id del estudiante: ");
                    Usuario *u = buscarUsuario(usuarios, id);

                    if (u == nullptr) {
                        cout << "No existe ningun usuario con ese id." << endl;
                    } else if (u->getRol() != "Estudiante") {
                        cout << "Ese usuario no es un estudiante." << endl;
                    } else {
                        Estudiante *e = static_cast<Estudiante *>(u);

                        if (e->getProfesor() != nullptr) {
                            cout << "Ese estudiante ya tiene profesor." << endl;
                        } else {
                            profesor->inscribir(e);
                            cout << "Estudiante inscrito." << endl;
                        }
                    }
                    break;
                }

                case 2: {
                    // Quitar un estudiante de la clase
                    int id = leerEntero("Id del estudiante a quitar: ");
                    profesor->desinscribir(id);
                    cout << "Estudiante quitado de la clase." << endl;
                    break;
                }

                case 3: {
                    // Poner una nota a un estudiante de la clase
                    int id = leerEntero("Id del estudiante: ");
                    string asignatura = leerTexto("Asignatura: ");
                    double nota = leerDecimal("Nota (0 a 10): ");

                    profesor->ponerNota(id, asignatura, nota);
                    cout << "Nota guardada." << endl;
                    break;
                }

                case 4:
                    // Ver la clase (numero de inscritos y listado)
                    profesor->verClase();
                    break;

                case 9:
                    menuCalculadora();
                    break;

                case 0:
                    cerrarSesion = true;
                    break;

                default:
                    cout << "Opcion no valida." << endl;
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}


void menuEstudiante(Estudiante *estudiante) {
    // Interruptor y bucle del menu
    bool cerrarSesion = false;

    while (cerrarSesion == false) {
        // Mostrar opciones y leer la elegida
        cout << endl << "--- MENU ESTUDIANTE ---" << endl;
        cout << "1. Cargar un fichero en la mochila" << endl;
        cout << "2. Ver mi mochila" << endl;
        cout << "3. Ver mis datos y notas" << endl;
        cout << "9. Calculadora" << endl;
        cout << "0. Cerrar sesion" << endl;

        int opcion = leerEntero("Elige una opcion: ");

        try {
            switch (opcion) {
                case 1: {
                    // Cargar un fichero .txt en la mochila
                    string ruta = leerTexto("Ruta del fichero: ");
                    estudiante->cargarFichero(ruta);
                    cout << "Fichero cargado en la mochila." << endl;
                    break;
                }

                case 2:
                    // Ver el contenido de la mochila
                    estudiante->verMochila();
                    break;

                case 3:
                    // Ver datos personales y notas
                    estudiante->mostrarDatos();
                    break;

                case 9:
                    menuCalculadora();
                    break;

                case 0:
                    cerrarSesion = true;
                    break;

                default:
                    cout << "Opcion no valida." << endl;
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
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

    // Liberar la memoria de todos los usuarios creados con new
    while (usuarios.length() > 0) {
        Usuario *u = usuarios.remove();
        delete u;
    }

    cout << "Memoria liberada" << endl;

    return 0;
}
