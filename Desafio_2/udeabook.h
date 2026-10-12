#ifndef UDEABOOK_H
#define UDEABOOK_H

#include <iostream>
#include <fstream>
#include <string>
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

    // Búsqueda
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

public:
    // Constructor y destructor
    UdeABook(const string &archivoDatos);
    ~UdeABook();

    // Funcionalidades
    void ejecutar();
    bool cargarDatos();

    // Operador
    friend ostream &operator<<(ostream &salida, const UdeABook &plataforma);
};

#endif // UDEABOOK_H
