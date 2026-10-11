#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <string>

using namespace std;

class Fecha
{
private:
    // Atributos
    int dia;
    int mes;
    int anio;

public:
    // Constructores y destructor
    Fecha();
    Fecha(int dia, int mes, int anio);
    Fecha(const Fecha &otra);
    ~Fecha();

    // Getters y setters
    int getDia() const;
    int getMes() const;
    int getAnio() const;
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    // Consultas
    bool esValida() const;
    int diasDelMes() const;
    int aNumero() const;
    string aTexto() const;

    // Modificación
    bool leerTexto(const string &texto);

    // Fecha de hoy
    static Fecha hoy();

    // Operadores
    bool operator<(const Fecha &otra) const;
    bool operator<=(const Fecha &otra) const;
    bool operator==(const Fecha &otra) const;
    Fecha &operator=(const Fecha &otra);
    friend ostream &operator<<(ostream &salida, const Fecha &fecha);
};

#endif // FECHA_H
