#include "contador.h"

long Contador::iteraciones = 0;

// Suma una vuelta de ciclo
void Contador::sumar()
{
    iteraciones++;
}

// Pone el contador en cero
void Contador::reiniciar()
{
    iteraciones = 0;
}

long Contador::getIteraciones()
{
    return iteraciones;
}
