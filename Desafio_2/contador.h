#ifndef CONTADOR_H
#define CONTADOR_H

class Contador
{
private:
    // Atributo static, hay uno solo para todo el programa
    static long iteraciones;

public:
    // Métodos static, se usan sin crear objetos
    static void sumar();
    static void reiniciar();
    static long getIteraciones();
};

#endif // CONTADOR_H
