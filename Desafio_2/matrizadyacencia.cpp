#include "matrizadyacencia.h"
#include "contador.h"

void MatrizAdyacencia::crear(int tamanio){
    if (tamanio < 0) {
        tamanio = 0;
    }
    this->tamanio = tamanio;
    matriz = new bool *[tamanio];
    for (int i = 0; i < tamanio; i++) {
        Contador::sumar();
        matriz[i] = new bool[tamanio];
        for (int j = 0; j < tamanio; j++) {
            Contador::sumar();
            matriz[i][j] = false;
        }
    }
}

void MatrizAdyacencia::liberar(){
    if (matriz != nullptr) {
        for (int i = 0; i < tamanio; i++) {
            Contador::sumar();
            delete[] matriz[i];
        }
        delete[] matriz;
    }
    matriz = nullptr;
    tamanio = 0;
}

MatrizAdyacencia::MatrizAdyacencia(){
    matriz = nullptr;
    tamanio = 0;
}

MatrizAdyacencia::MatrizAdyacencia(int tamanio){
    matriz = nullptr;
    crear(tamanio);
}

MatrizAdyacencia::MatrizAdyacencia(const MatrizAdyacencia &otra){
    matriz = nullptr;
    crear(otra.tamanio);
    for (int i = 0; i < tamanio; i++) {
        for (int j = 0; j < tamanio; j++) {
            Contador::sumar();
            matriz[i][j] = otra.matriz[i][j];
        }
    }
}

MatrizAdyacencia::~MatrizAdyacencia(){
    liberar();
}

int MatrizAdyacencia::getTamanio() const{
    return tamanio;
}

bool MatrizAdyacencia::sonAmigos(int a, int b) const{
    return matriz[a][b];
}

int MatrizAdyacencia::contarAmigos(int usuario) const{
    int amigos = 0;
    for (int j = 0; j < tamanio; j++) {
        Contador::sumar();
        if (matriz[usuario][j]) {
            amigos++;
        }
    }
    return amigos;
}

int MatrizAdyacencia::contarAmigosEnComun(int a, int b) const{
    int comunes = 0;
    for (int k = 0; k < tamanio; k++) {
        Contador::sumar();
        if (matriz[a][k] && matriz[b][k]) {
            comunes++;
        }
    }
    return comunes;
}

long MatrizAdyacencia::memoriaUsada() const{
    return tamanio * sizeof(bool *) + tamanio * tamanio * sizeof(bool);
}

void MatrizAdyacencia::redimensionar(int tamanio){
    liberar();
    crear(tamanio);
}

void MatrizAdyacencia::agregarAmistad(int a, int b){
    if (a == b) {
        return;
    }
    matriz[a][b] = true;
    matriz[b][a] = true;
}

bool MatrizAdyacencia::operator()(int a, int b) const{
    return sonAmigos(a, b);
}

MatrizAdyacencia &MatrizAdyacencia::operator=(const MatrizAdyacencia &otra){
    if (this == &otra) {
        return *this;
    }
    liberar();
    crear(otra.tamanio);
    for (int i = 0; i < tamanio; i++) {
        for (int j = 0; j < tamanio; j++) {
            Contador::sumar();
            matriz[i][j] = otra.matriz[i][j];
        }
    }
    return *this;
}