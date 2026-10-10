#ifndef FECHA_H
#define FECHA_H
#include <iostream>
using namespace std;

class Fecha
{
private:
    int dia, mes, anio;
public:
    Fecha();
    ~Fecha();
    Fecha(int d, int m, int a);
    Fecha(const Fecha & f);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    bool setDia(int d);
    bool setMes(int m);
    bool setAnio(int a);

    bool esValida() const;
    bool operator<(const Fecha & f) const;
    bool operator<=(const Fecha & f) const;
    bool operator==(const Fecha & f) const;
    Fecha &operator=(const Fecha &f);
    friend ostream & operator<<(ostream &os, const Fecha &f);
    static Fecha hoy();
};

#endif // FECHA_H
