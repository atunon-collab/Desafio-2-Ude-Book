#include "Fecha.h"
#include <iostream>
#include <chrono>

using namespace std;


Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

Fecha::Fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;

    if (!esValida()) {
        dia = 1;
        mes = 1;
        anio = 2000;
    }
}

Fecha::Fecha(const Fecha &f) {
    dia = f.dia;
    mes = f.mes;
    anio = f.anio;
}

Fecha::~Fecha() {
}

bool Fecha::esValida() const {
    if (mes < 1 || mes > 12 || dia < 1) {
        return false;
    }

    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    if (esBisiesto) {
        diasPorMes[1] = 29;
    }

    return dia <= diasPorMes[mes - 1];
}

int Fecha::getDia() const  { return dia; }
int Fecha::getMes() const  { return mes; }
int Fecha::getAnio() const { return anio; }

bool Fecha::setDia(int d) {
    int anterior = dia;
    dia = d;
    if (!esValida()) {
        dia = anterior;
        return false;
    }
    return true;
}

bool Fecha::setMes(int m) {
    int anterior = mes;
    mes = m;
    if (!esValida()) {
        mes = anterior;
        return false;
    }
    return true;
}

bool Fecha::setAnio(int a) {
    int anterior = anio;
    anio = a;
    if (!esValida()) {
        anio = anterior;
        return false;
    }
    return true;
}

bool Fecha::operator<(const Fecha &f) const {
    if (anio != f.anio) return anio < f.anio;
    if (mes != f.mes)   return mes < f.mes;
    return dia < f.dia;
}

bool Fecha::operator==(const Fecha &f) const {
    return anio == f.anio && mes == f.mes && dia == f.dia;
}

bool Fecha::operator<=(const Fecha &f) const {
    return (*this < f) || (*this == f);
}

Fecha &Fecha::operator=(const Fecha &f) {
    if (this != &f) {
        dia = f.dia;
        mes = f.mes;
        anio = f.anio;
    }
    return *this;
}

// Imprime en formato dd/mm/aaaa
ostream &operator<<(ostream &os, const Fecha &f) {
    if (f.dia < 10) os << '0';
    os << f.dia << '/';
    if (f.mes < 10) os << '0';
    os << f.mes << '/' << f.anio;
    return os;
}

const int HORAS_COLOMBIA = 5;

Fecha Fecha::hoy()
{
    chrono::system_clock::time_point ahora = chrono::system_clock::now();
    ahora = ahora - chrono::hours(HORAS_COLOMBIA);

    // Se pasa a días y luego a día, mes y año
    chrono::year_month_day calendario = chrono::year_month_day(chrono::floor<chrono::days>(ahora));

    int diaHoy = static_cast<unsigned>(calendario.day());
    int mesHoy = static_cast<unsigned>(calendario.month());
    int anioHoy = static_cast<int>(calendario.year());

    Fecha resultado(diaHoy, mesHoy, anioHoy);
    return resultado;
}