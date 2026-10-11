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


// Otros métodos

// Público lo ve cualquiera, amigos solo los amigos, privado nadie más
bool Album::esVisible(bool esAmigo) const
{
    if (privacidad == PUBLICO) {
        return true;
    }
    if (privacidad == AMIGOS) {
        return esAmigo;
    }
    return false;
}


// Operadores

// album[i] devuelve la foto i
Foto &Album::operator[](int posicion)
{
    return fotos[posicion];
}

// Copia otro álbum con sus fotos
Album &Album::operator=(const Album &otro)
{
    nombre = otro.nombre;
    ruta = otro.ruta;
    privacidad = otro.privacidad;
    fotos = otro.fotos;
    return *this;
}

// Muestra el nombre, la privacidad y cuántas fotos tiene
ostream &operator<<(ostream &salida, const Album &album)
{
    salida << album.nombre << " (";
    if (album.privacidad == Album::PUBLICO) {
        salida << "publico";
    } else if (album.privacidad == Album::AMIGOS) {
        salida << "amigos";
    } else {
        salida << "privado";
    }
    salida << ", " << album.fotos.getCantidad() << " fotos)";
    return salida;
}
