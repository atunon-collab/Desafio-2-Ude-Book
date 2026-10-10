#ifndef MENSAJE_H
#define MENSAJE_H

#include <iostream>
#include <string>
#include "fecha.h"

using namespace std;

class Mensaje
{
private:
    // Atributos
    string emisor;
    string receptor;
    string texto;
    Fecha fechaEnvio;
    bool leido;

public:
    // Constructores y destructor
    Mensaje();
    Mensaje(const string &emisor, const string &receptor, const string &texto, const Fecha &fechaEnvio);
    Mensaje(const Mensaje &otro);
    ~Mensaje();

    // Getters y setters
    string getEmisor() const;
    string getReceptor() const;
    string getTexto() const;
    Fecha getFechaEnvio() const;
    bool getLeido() const;
    void setEmisor(const string &emisor);
    void setReceptor(const string &receptor);
    void setTexto(const string &texto);
    void setFechaEnvio(const Fecha &fechaEnvio);
    void setLeido(bool leido);
};

#endif // MENSAJE_H
