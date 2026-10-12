#ifndef MATRIZADYACENCIA_H
#define MATRIZADYACENCIA_H

class MatrizAdyacencia
{
private:
    // Atributos
    bool **matriz;
    int tamanio;

    // Métodos privados
    void crear(int tamanio);
    void liberar();

public:
    // Constructores y destructor
    MatrizAdyacencia();
    MatrizAdyacencia(int tamanio);
    ~MatrizAdyacencia();

    // Consultas
    int getTamanio() const;
    bool sonAmigos(int a, int b) const;
    int contarAmigos(int usuario) const;
    int contarAmigosEnComun(int a, int b) const;

    // Modificación
    void redimensionar(int tamanio);
    void agregarAmistad(int a, int b);
};

#endif // MATRIZADYACENCIA_H
