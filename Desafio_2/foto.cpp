#include "foto.h"

// Constructores y destructor

Foto::Foto()
{
    ruta = "";
    tamanio = 0;
    likes = 0;
}

Foto::Foto(const string &ruta, const Fecha &fechaCaptura, int tamanio, int likes)
{
    this->ruta = ruta;
    this->fechaCaptura = fechaCaptura;
    this->tamanio = tamanio;
    this->likes = likes;
}

Foto::Foto(const Foto &otra)
{
    ruta = otra.ruta;
    fechaCaptura = otra.fechaCaptura;
    tamanio = otra.tamanio;
    likes = otra.likes;
}

Foto::~Foto()
{
}


// Getters y setters

string Foto::getRuta() const
{
    return ruta;
}

Fecha Foto::getFechaCaptura() const
{
    return fechaCaptura;
}

int Foto::getTamanio() const
{
    return tamanio;
}

int Foto::getLikes() const
{
    return likes;
}

void Foto::setRuta(const string &ruta)
{
    this->ruta = ruta;
}

void Foto::setFechaCaptura(const Fecha &fechaCaptura)
{
    this->fechaCaptura = fechaCaptura;
}

void Foto::setTamanio(int tamanio)
{
    this->tamanio = tamanio;
}

void Foto::setLikes(int likes)
{
    this->likes = likes;
}


// Otros métodos

void Foto::darLike()
{
    likes++;
}

void Foto::quitarLike()
{
    if (likes > 0) {
        likes--;
    }
}

void Foto::mostrar() const
{
    cout << *this << endl;
}

// Operadores

// ++foto da un like
Foto &Foto::operator++()
{
    darLike();
    return *this;
}

// --foto quita un like
Foto &Foto::operator--()
{
    quitarLike();
    return *this;
}

// Copia otra foto en esta
Foto &Foto::operator=(const Foto &otra)
{
    ruta = otra.ruta;
    fechaCaptura = otra.fechaCaptura;
    tamanio = otra.tamanio;
    likes = otra.likes;
    return *this;
}

// Muestra la ruta y los datos de la foto
ostream &operator<<(ostream &salida, const Foto &foto)
{
    salida << foto.ruta << endl;
    salida << "   Capturada " << foto.fechaCaptura << " | " << foto.tamanio << " KB | " << foto.likes << " likes";
    return salida;
}