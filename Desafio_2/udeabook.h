#ifndef UDEABOOK_H
#define UDEABOOK_H

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "lista.h"
#include "usuario.h"
#include "matrizadyacencia.h"
#include "fecha.h"

using namespace std;

class UdeABook
{
private:
    // Atributos
    Lista<Usuario> usuarios;
    MatrizAdyacencia amistades;
    int usuarioActual;
    string rutaBase;
    string archivoDatos;
    Lista<int> fotosMostradas;
    bool fotosActualizadas;
    mt19937 generador;

    // Búsqueda
    int buscarUsuario(const string &nombre) const;
    bool esIndiceValido(int indice) const;

    // Lectura del teclado
    string leerLinea() const;
    int leerEntero() const;
    int convertirEntero(const string &texto) const;

    // Lectura del archivo
    void quitarRetorno(string &linea) const;
    string tomarCampo(const string &linea, int &posicion) const;
    void cargarUsuario(const string &linea);
    void cargarAmistad(const string &linea);
    void cargarSolicitud(const string &linea);
    void cargarMensaje(const string &linea);
    void cargarAlbum(const string &linea, ifstream &archivo);

    // Menús
    void ingresar();
    void mostrarMenu();

    // Partes de las funcionalidades
    void mostrarMejoresAmigos(bool actualizar);
    int calcularPeso(int comunes) const;
    bool fueMostrado(int indice) const;

public:
    // Constructor y destructor
    UdeABook(const string &archivoDatos);
    ~UdeABook();

    // Funcionalidades
    void ejecutar();
    bool cargarDatos();
    void guardarDatos();
    bool iniciarSesion(const string &nombre, const string &contrasena);
    void cerrarSesion();

    // Operador
    friend ostream &operator<<(ostream &salida, const UdeABook &plataforma);
};

#endif // UDEABOOK_H
