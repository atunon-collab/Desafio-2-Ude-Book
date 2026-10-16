#include "udeabook.h"

// CMake pone la ruta del archivo de datos
// Si no la pone se busca junto al programa
#ifndef RUTA_DATOS
#define RUTA_DATOS "udeabook.txt"
#endif

// Crea la plataforma y la ejecuta
// Iteraciones las de todas las funcionalidades que se usen
int main()
{
    UdeABook plataforma(RUTA_DATOS);
    plataforma.ejecutar();
    return 0;
}
