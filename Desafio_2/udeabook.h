#ifndef UDEABOOK_H
#define UDEABOOK_H

#include <iostream>
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

    // Lectura del teclado
    string leerLinea() const;
    int leerEntero() const;
    int convertirEntero(const string &texto) const;

public:
    // Constructor y destructor
    UdeABook(const string &archivoDatos);
    ~UdeABook();

    // Funcionalidades
    void ejecutar();

    // Operador
    friend ostream &operator<<(ostream &salida, const UdeABook &plataforma);
};

#endif // UDEABOOK_H
