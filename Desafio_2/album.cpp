#include "album.h"

// Constructores y destructor

Album::Album()
{
    nombre = "";
    ruta = "";
    privacidad = PRIVADO;
}

Album::Album(const string &nombre, const string &ruta, char privacidad)
{
    this->nombre = nombre;
    this->ruta = ruta;
    this->privacidad = privacidad;
}

// Copia el álbum con todas sus fotos
Album::Album(const Album &otro)
{
    nombre = otro.nombre;
    ruta = otro.ruta;
    privacidad = otro.privacidad;
    fotos = otro.fotos;
}

// La lista de fotos se libera sola con su destructor
Album::~Album()
{
}


// Getters y setters

const string &Album::getNombre() const
{
    return nombre;
}

const string &Album::getRuta() const
{
    return ruta;
}

char Album::getPrivacidad() const
{
    return privacidad;
}

void Album::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

void Album::setRuta(const string &ruta)
{
    this->ruta = ruta;
}

void Album::setPrivacidad(char privacidad)
{
    this->privacidad = privacidad;
}


// Fotos

void Album::agregarFoto(const Foto &foto)
{
    fotos.agregar(foto);
}

Foto &Album::getFoto(int posicion)
{
    return fotos[posicion];
}

int Album::getCantidadFotos() const
{
    return fotos.getCantidad();
}
