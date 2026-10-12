#include "udeabook.h"

// Rutas de las fotos
const string RUTA_BASE = "/users/udeabook/";

// Valores especiales
const int SIN_SESION = -1;
const int ENTRADA_INVALIDA = -1;
const int MAX_CIFRAS = 9;



// Constructor y destructor

UdeABook::UdeABook(const string &archivoDatos)
{
    this->archivoDatos = archivoDatos;
    rutaBase = RUTA_BASE;
    usuarioActual = SIN_SESION;
}

// Las listas y la matriz se liberan solas con sus destructores
UdeABook::~UdeABook()
{
}


// Programa principal

// Muestra el menú de ingreso
void UdeABook::ejecutar()
{
    cout << *this << endl;

    int opcion = ENTRADA_INVALIDA;
    while (opcion != 0) {
        cout << endl << "========== Ude@Book ==========" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        opcion = leerEntero();

        if (opcion == 1) {
            cout << "Inicio de sesion en construccion" << endl;
        } else if (opcion != 0) {
            cout << "Opcion no valida" << endl;
        }
    }

    cout << "Hasta pronto" << endl;
}


// Lectura del teclado

// Si se acaba la entrada devuelve 0 para salir de los menús
string UdeABook::leerLinea() const
{
    string linea = "";
    if (!getline(cin, linea)) {
        return "0";
    }
    return linea;
}

int UdeABook::leerEntero() const
{
    return convertirEntero(leerLinea());
}

// Convierte un texto de dígitos en número, si no se puede devuelve -1
int UdeABook::convertirEntero(const string &texto) const
{
    int largo = texto.length();
    if (largo == 0 || largo > MAX_CIFRAS) {
        return ENTRADA_INVALIDA;
    }

    int numero = 0;
    for (int i = 0; i < largo; i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return ENTRADA_INVALIDA;
        }
        numero = numero * 10 + (texto[i] - '0');
    }
    return numero;
}


// Operador

// Muestra cuántos usuarios hay en la plataforma
ostream &operator<<(ostream &salida, const UdeABook &plataforma)
{
    salida << "Ude@Book tiene " << plataforma.usuarios.getCantidad() << " usuarios registrados";
    return salida;
}
