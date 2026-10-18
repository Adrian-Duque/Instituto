#include "Matriz.h"
#include <iostream>
#include <stdexcept>

#include "ListaGenerica.h"
#include "Usuario.h"
#include "Administrador.h"
#include "Profesor.h"
#include "Estudiante.h"
using namespace std;

// ---- Calculadora: operaciones basicas ----
// Son funciones sueltas y no una clase: la calculadora no guarda estado y solo
// habria un objeto, asi que una clase no aportaria nada.
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

// El resultado se guarda en el free store; quien llama debe liberarlo con delete
Matriz<double> *operarMatrices(const Matriz<double> &a, const Matriz<double> &b, char op) {
    switch (op) {
        case '+': return new Matriz<double>(a.sumar(b));
        case '-': return new Matriz<double>(a.restar(b));
        case '*': return new Matriz<double>(a.multiplicar(b));
        case '/': return new Matriz<double>(a.dividir(b));
        default:
            throw std::invalid_argument("Operacion no valida");
    }
}

// ---- Lectura validada de datos ----
// Si el usuario escribe letras donde se espera un numero, cin queda en estado de error:
// se limpia (clear), se descarta la linea (ignore) y se vuelve a pedir.
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

// Devuelve el usuario con ese id o nullptr si no existe
Usuario *buscarUsuario(ListaGenerica<Usuario *> &lista, int id) {
    for (int i = 0; i < lista.length(); i++) {
        Usuario *u = lista.at(i);
        if (u->getId() == id) {
            return u;
        }
    }
    return nullptr;
}

// La matriz se crea en el free store; quien llama debe liberarla con delete
Matriz<double> *leerMatriz(string nombre) {
    cout << "Matriz " << nombre << endl;
    int filas = leerEntero("Numero de filas: ");
    int columnas = leerEntero("Numero de columnas: ");

    // Si las dimensiones no son validas el constructor lanza y new libera la memoria solo
    Matriz<double> *m = new Matriz<double>(filas, columnas);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << nombre << "[" << i << "][" << j << "] = ";
            double valor = leerDecimal("");
            m->set(i, j, valor);
        }
    }

    return m;
}

// Menu de la calculadora (disponible para los tres roles con la opcion 9)
void menuCalculadora() {
    bool volver = false;

    while (volver == false) {
        cout << endl << "--- CALCULADORA ---" << endl;
        cout << "1. Sumar" << endl;
        cout << "2. Restar" << endl;
        cout << "3. Multiplicar" << endl;
        cout << "4. Dividir" << endl;
        cout << "5. Operar con matrices" << endl;
        cout << "6. Traspuesta de una matriz" << endl;
        cout << "7. Determinante de una matriz" << endl;
        cout << "0. Volver" << endl;

        int opcion = leerEntero("Elige una opcion: ");

        // Cualquier excepcion de una opcion se muestra y se vuelve al menu,
        // asi un error no cierra el programa
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
                    // Se elige la operacion antes de pedir las matrices
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
                        throw std::invalid_argument("Operacion no valida");
                    }

                    // Matrices y resultado en el free store. Si algo lanza una excepcion
                    // se libera lo que ya se habia creado antes de relanzarla.
                    Matriz<double> *a = nullptr;
                    Matriz<double> *b = nullptr;
                    Matriz<double> *resultado = nullptr;
                    try {
                        a = leerMatriz("A");
                        b = leerMatriz("B");
                        resultado = operarMatrices(*a, *b, op);
                        cout << "Resultado:" << endl;
                        resultado->imprimir();
                    } catch (...) {
                        delete resultado;
                        delete b;
                        delete a;
                        throw;
                    }
                    delete resultado;
                    delete b;
                    delete a;
                    break;
                }

                case 6: {
                    Matriz<double> *a = nullptr;
                    Matriz<double> *traspuesta = nullptr;
                    try {
                        a = leerMatriz("A");
                        traspuesta = new Matriz<double>(a->traspuesta());
                        cout << "Traspuesta:" << endl;
                        traspuesta->imprimir();
                    } catch (...) {
                        delete traspuesta;
                        delete a;
                        throw;
                    }
                    delete traspuesta;
                    delete a;
                    break;
                }

                case 7: {
                    Matriz<double> *a = nullptr;
                    try {
                        a = leerMatriz("A");
                        // Lanza invalid_argument si la matriz no es cuadrada
                        double determinante = a->determinante();
                        cout << "Determinante: " << determinante << endl;
                    } catch (...) {
                        delete a;
                        throw;
                    }
                    delete a;
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
        cout << "3. Eliminar un fichero de la mochila" << endl;
        cout << "4. Ver mis datos y notas" << endl;
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

                case 3: {
                    // Eliminar un fichero: se muestra la mochila numerada y se elige cual quitar
                    estudiante->verMochila();
                    int posicion = leerEntero("Numero del fichero a eliminar: ");
                    estudiante->quitarFichero(posicion);
                    cout << "Fichero eliminado de la mochila." << endl;
                    break;
                }

                case 4:
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
    // Lista de todos los usuarios. Guarda punteros (Usuario*) para poder tener
    // estudiantes, profesores y administradores en la misma lista (polimorfismo).
    // La lista vive en la pila de main; los usuarios, en el free store.
    ListaGenerica<Usuario *> usuarios;

    // Primer administrador, para poder entrar y dar de alta al resto (recibe el id 1)
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

                // getRol es virtual: devuelve el rol del objeto real. Con el rol ya se sabe
                // que tipo es, y static_cast convierte el Usuario* al puntero de su clase.
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

    // Liberar la memoria de todos los usuarios creados con new.
    // delete ejecuta el destructor de cada clase (virtual) y no queda ninguna fuga.
    while (usuarios.length() > 0) {
        Usuario *u = usuarios.remove();
        delete u;
    }

    cout << "Memoria liberada" << endl;

    return 0;
}
