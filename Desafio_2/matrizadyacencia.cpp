#include "matrizadyacencia.h"

void MatrizAdyacencia::crear(int tamanio){
    if (tamanio < 0) {
        tamanio = 0;
    }
    this->tamanio = tamanio;
    matriz = new bool *[tamanio];
    for (int i = 0; i < tamanio; i++) {
        matriz[i] = new bool[tamanio];
        for (int j = 0; j < tamanio; j++) {
            matriz[i][j] = false;
        }
    }
}

void MatrizAdyacencia::liberar(){
    if (matriz != nullptr) {
        for (int i = 0; i < tamanio; i++) {
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
        if (matriz[usuario][j]) {
            amigos++;
        }
    }
    return amigos;
}

int MatrizAdyacencia::contarAmigosEnComun(int a, int b) const{
    int comunes = 0;
    for (int k = 0; k < tamanio; k++) {
        if (matriz[a][k] && matriz[b][k]) {
            comunes++;
        }
    }
    return comunes;
}

void MatrizAdyacencia::redimensionar(int tamanio){
    liberar();
    crear(tamanio);
}

void MatrizAdyacencia::agregarAmistad(int a, int b){
    matriz[a][b] = true;
    matriz[b][a] = true;
}
