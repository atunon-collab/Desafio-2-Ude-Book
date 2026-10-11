#include "fecha.h"
#include "contador.h"
#include <chrono>

const int DIA_INICIAL = 1;
const int MES_INICIAL = 1;
const int ANIO_INICIAL = 2000;

const int MESES = 12;
const int FEBRERO = 2;
const int ABRIL = 4;
const int JUNIO = 6;
const int SEPTIEMBRE = 9;
const int NOVIEMBRE = 11;
const int DIAS_FEBRERO = 28;
const int DIAS_FEBRERO_BISIESTO = 29;
const int DIAS_MES_CORTO = 30;
const int DIAS_MES_LARGO = 31;

// Formato dd/mm/aaaa
const int LARGO_TEXTO = 10;
const int POSICION_BARRA_1 = 2;
const int POSICION_BARRA_2 = 5;
const char BARRA = '/';

const int HORAS_COLOMBIA = 5;

Fecha::Fecha(){
    dia = DIA_INICIAL;
    mes = MES_INICIAL;
    anio = ANIO_INICIAL;
}

Fecha::Fecha(int dia, int mes, int anio){
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

Fecha::Fecha(const Fecha &otra){
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
}

Fecha::~Fecha(){
}

int Fecha::getDia() const{
    return dia;
}

int Fecha::getMes() const{
    return mes;
}

int Fecha::getAnio() const{
    return anio;
}

void Fecha::setDia(int dia){
    this->dia = dia;
}

void Fecha::setMes(int mes){
    this->mes = mes;
}

void Fecha::setAnio(int anio){
    this->anio = anio;
}

int Fecha::diasDelMes() const{
    if (mes == FEBRERO) {
        if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
            return DIAS_FEBRERO_BISIESTO;
        }
        return DIAS_FEBRERO;
    }
    if (mes == ABRIL || mes == JUNIO || mes == SEPTIEMBRE || mes == NOVIEMBRE) {
        return DIAS_MES_CORTO;
    }
    return DIAS_MES_LARGO;
}

bool Fecha::esValida() const{
    if (anio < 1 || mes < 1 || mes > MESES) {
        return false;
    }
    return dia >= 1 && dia <= diasDelMes();
}

int Fecha::aNumero() const{
    return anio * 10000 + mes * 100 + dia;
}

string Fecha::aTexto() const{
    string texto = "";
    if (dia < 10) {
        texto = texto + "0";
    }
    texto = texto + to_string(dia) + BARRA;
    if (mes < 10) {
        texto = texto + "0";
    }
    texto = texto + to_string(mes) + BARRA + to_string(anio);
    return texto;
}

bool Fecha::leerTexto(const string &texto){
    int largo = texto.length();
    if (largo != LARGO_TEXTO) {
        return false;
    }

    for (int i = 0; i < LARGO_TEXTO; i++) {
        Contador::sumar();
        if (i == POSICION_BARRA_1 || i == POSICION_BARRA_2) {
            if (texto[i] != BARRA) {
                return false;
            }
        } else if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }

    int nuevoDia = (texto[0] - '0') * 10 + (texto[1] - '0');
    int nuevoMes = (texto[3] - '0') * 10 + (texto[4] - '0');
    int nuevoAnio = (texto[6] - '0') * 1000 + (texto[7] - '0') * 100 + (texto[8] - '0') * 10 + (texto[9] - '0');

    Fecha nueva(nuevoDia, nuevoMes, nuevoAnio);
    if (!nueva.esValida()) {
        return false;
    }

    dia = nuevoDia;
    mes = nuevoMes;
    anio = nuevoAnio;
    return true;
}

Fecha Fecha::hoy(){
    chrono::system_clock::time_point ahora = chrono::system_clock::now();
    ahora = ahora - chrono::hours(HORAS_COLOMBIA);

    chrono::year_month_day calendario = chrono::year_month_day(chrono::floor<chrono::days>(ahora));

    int diaHoy = static_cast<unsigned>(calendario.day());
    int mesHoy = static_cast<unsigned>(calendario.month());
    int anioHoy = static_cast<int>(calendario.year());

    Fecha resultado(diaHoy, mesHoy, anioHoy);
    return resultado;
}

bool Fecha::operator<(const Fecha &otra) const{
    return aNumero() < otra.aNumero();
}

bool Fecha::operator<=(const Fecha &otra) const{
    return aNumero() <= otra.aNumero();
}

bool Fecha::operator==(const Fecha &otra) const{
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

Fecha &Fecha::operator=(const Fecha &otra){
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
    return *this;
}

ostream &operator<<(ostream &salida, const Fecha &fecha){
    salida << fecha.aTexto();
    return salida;
}
