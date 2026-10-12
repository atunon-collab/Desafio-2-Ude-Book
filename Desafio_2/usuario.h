#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include "fecha.h"

using namespace std;

class Usuario
{
private:
    // Atributos
    string nombreUsuario;
    string contrasena;
    string correo;
    string ciudad;
    string pais;
    string rutaFotoPerfil;
    Fecha fechaNacimiento;
    Fecha fechaInscripcion;
    int indice;

public:
    // Constructores y destructor
    Usuario();
    Usuario(const string &nombreUsuario, const string &contrasena, const string &correo,
            const string &ciudad, const string &pais, const string &rutaFotoPerfil,
            const Fecha &fechaNacimiento, const Fecha &fechaInscripcion, int indice);
    Usuario(const Usuario &otro);
    ~Usuario();

    // Getters y setters
    const string &getNombreUsuario() const;
    const string &getContrasena() const;
    const string &getCorreo() const;
    const string &getCiudad() const;
    const string &getPais() const;
    const string &getRutaFotoPerfil() const;
    const Fecha &getFechaNacimiento() const;
    const Fecha &getFechaInscripcion() const;
    int getIndice() const;
    void setNombreUsuario(const string &nombreUsuario);
    void setContrasena(const string &contrasena);
    void setCorreo(const string &correo);
    void setCiudad(const string &ciudad);
    void setPais(const string &pais);
    void setRutaFotoPerfil(const string &rutaFotoPerfil);
    void setFechaNacimiento(const Fecha &fechaNacimiento);
    void setFechaInscripcion(const Fecha &fechaInscripcion);
    void setIndice(int indice);

    // Sesión
    bool verificarContrasena(const string &contrasena) const;

    // Operadores
    bool operator==(const Usuario &otro) const;
    Usuario &operator=(const Usuario &otro);
    friend ostream &operator<<(ostream &salida, const Usuario &usuario);
};

#endif // USUARIO_H
