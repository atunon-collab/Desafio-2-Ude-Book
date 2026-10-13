#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <string>
#include "lista.h"
#include "foto.h"

using namespace std;

class Album
{
private:
    // Atributos
    string nombre;
    string ruta;
    char privacidad;
    Lista<Foto> fotos;

public:
    // Tipos de privacidad
    static const char PUBLICO = 'P';
    static const char AMIGOS = 'A';
    static const char PRIVADO = 'R';

    // Constructores y destructor
    Album();
    Album(const string &nombre, const string &ruta, char privacidad);
    Album(const Album &otro);
    ~Album();

    // Getters y setters
    const string &getNombre() const;
    const string &getRuta() const;
    char getPrivacidad() const;
    void setNombre(const string &nombre);
    void setRuta(const string &ruta);
    void setPrivacidad(char privacidad);

    // Fotos
    void agregarFoto(const Foto &foto);
    Foto &getFoto(int posicion);
    int getCantidadFotos() const;

    // Otros métodos
    bool esVisible(bool esAmigo) const;
    void verCarrusel();
    long memoriaUsada() const;

    // Operadores
    Foto &operator[](int posicion);
    Album &operator=(const Album &otro);
    friend ostream &operator<<(ostream &salida, const Album &album);
};

#endif // ALBUM_H
