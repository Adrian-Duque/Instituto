#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
protected:
    int id;
    std::string nombre;
    std::string apellido;
    static int siguienteId; // Para que el id sea único
public:
    Usuario(std::string nombre, std::string apellido);
    virtual ~Usuario(); // Destructor virtual

    int getId() const;
    std::string getNombre() const;
    std::string getApellido() const;

    void setNombre(std::string nombre);
    void setApellido(std::string apellido);

    virtual std::string getRol() = 0;       // Virtual pura
    virtual void mostrarDatos();            // Virtual
};

#endif // USUARIO_H