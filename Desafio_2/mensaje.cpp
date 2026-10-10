#include "mensaje.h"


// Constructores y destructor

Mensaje::Mensaje()
{
    emisor = "";
    receptor = "";
    texto = "";
    leido = false;
}

// Un mensaje nuevo empieza sin leer
Mensaje::Mensaje(const string &emisor, const string &receptor, const string &texto, const Fecha &fechaEnvio)
{
    this->emisor = emisor;
    this->receptor = receptor;
    this->texto = texto;
    this->fechaEnvio = fechaEnvio;
    leido = false;
}

Mensaje::Mensaje(const Mensaje &otro)
{
    emisor = otro.emisor;
    receptor = otro.receptor;
    texto = otro.texto;
    fechaEnvio = otro.fechaEnvio;
    leido = otro.leido;
}

Mensaje::~Mensaje()
{
}


// Getters y setters

string Mensaje::getEmisor() const
{
    return emisor;
}

string Mensaje::getReceptor() const
{
    return receptor;
}

string Mensaje::getTexto() const
{
    return texto;
}

Fecha Mensaje::getFechaEnvio() const
{
    return fechaEnvio;
}

bool Mensaje::getLeido() const
{
    return leido;
}

void Mensaje::setEmisor(const string &emisor)
{
    this->emisor = emisor;
}

void Mensaje::setReceptor(const string &receptor)
{
    this->receptor = receptor;
}

void Mensaje::setTexto(const string &texto)
{
    this->texto = texto;
}

void Mensaje::setFechaEnvio(const Fecha &fechaEnvio)
{
    this->fechaEnvio = fechaEnvio;
}

void Mensaje::setLeido(bool leido)
{
    this->leido = leido;
}


// Otros métodos

void Mensaje::marcarLeido()
{
    leido = true;
}

void Mensaje::mostrar() const
{
    cout << *this << endl;
}

// Operadores

// Un mensaje es menor si se envió antes
bool Mensaje::operator<(const Mensaje &otro) const
{
    return fechaEnvio < otro.fechaEnvio;
}

// Copia otro mensaje en este
Mensaje &Mensaje::operator=(const Mensaje &otro)
{
    emisor = otro.emisor;
    receptor = otro.receptor;
    texto = otro.texto;
    fechaEnvio = otro.fechaEnvio;
    leido = otro.leido;
    return *this;
}

// Muestra la fecha, quién lo envió, a quién y el texto
ostream &operator<<(ostream &salida, const Mensaje &mensaje)
{
    salida << mensaje.fechaEnvio << " | de " << mensaje.emisor << " para " << mensaje.receptor << endl;
    salida << "   " << mensaje.texto;
    return salida;
}
