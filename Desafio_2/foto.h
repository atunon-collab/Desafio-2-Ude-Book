#ifndef FOTO_H
#define FOTO_H

#include <iostream>
#include <string>
#include "fecha.h"

using namespace std;

class Foto
{
private:
    // Atributos
    string ruta;
    Fecha fechaCaptura;
    int tamanio;
    int likes;

public:
    // Constructores y destructor
    Foto();
    Foto(const string &ruta, const Fecha &fechaCaptura, int tamanio, int likes);
    Foto(const Foto &otra);
    ~Foto();

    // Getters y setters
    string getRuta() const;
    Fecha getFechaCaptura() const;
    int getTamanio() const;
    int getLikes() const;
    void setRuta(const string &ruta);
    void setFechaCaptura(const Fecha &fechaCaptura);
    void setTamanio(int tamanio);
    void setLikes(int likes);

    // Otros métodos
    void darLike();
    void quitarLike();
    void mostrar() const;

    // Operadores
    Foto &operator++();
    Foto &operator--();
    Foto &operator=(const Foto &otra);
    friend ostream &operator<<(ostream &salida, const Foto &foto);
};

#endif // FOTO_H
