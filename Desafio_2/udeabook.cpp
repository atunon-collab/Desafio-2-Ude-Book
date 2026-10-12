#include "udeabook.h"

// Rutas de las fotos
const string RUTA_BASE = "/users/udeabook/";
const string CARPETA_ALBUMES = "/albums/";
const string FOTO_PERFIL = "profile.png";

// Formato del archivo
const char SEPARADOR = ';';
const char MARCA_SECCION = '#';
const string SECCION_USUARIOS = "#USUARIOS";
const string SECCION_AMISTADES = "#AMISTADES";

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

// Carga los datos y muestra el ingreso
void UdeABook::ejecutar()
{
    cout << "Cargando datos..." << endl;
    if (!cargarDatos()) {
        return;
    }
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


// Carga de datos

// Funcionalidad I, carga de datos
bool UdeABook::cargarDatos()
{
    ifstream archivo(archivoDatos);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << archivoDatos << endl;
        return false;
    }

    string linea = "";
    string seccion = "";
    while (getline(archivo, linea)) {
        quitarRetorno(linea);

        if (linea.length() > 0 && linea[0] == MARCA_SECCION) {
            // Encabezado de una sección
            int posicion = 0;
            seccion = tomarCampo(linea, posicion);
            if (seccion == SECCION_USUARIOS) {
                // El encabezado trae N para crear la matriz
                int total = convertirEntero(tomarCampo(linea, posicion));
                amistades.redimensionar(total);
            }
        } else if (linea.length() > 0) {
            if (seccion == SECCION_USUARIOS) {
                cargarUsuario(linea);
            } else if (seccion == SECCION_AMISTADES) {
                cargarAmistad(linea);
            }
        }
    }
    archivo.close();

    cout << "Datos cargados de " << archivoDatos << endl;
    return true;
}

// Quita el fin de línea de Windows si quedó
void UdeABook::quitarRetorno(string &linea) const
{
    if (linea.length() > 0 && linea[linea.length() - 1] == '\r') {
        linea.erase(linea.length() - 1);
    }
}

// Saca el texto que hay hasta el siguiente separador y avanza la posición
string UdeABook::tomarCampo(const string &linea, int &posicion) const
{
    string campo = "";
    int largo = linea.length();
    while (posicion < largo && linea[posicion] != SEPARADOR) {
        campo = campo + linea[posicion];
        posicion++;
    }
    // Salta el separador
    posicion++;
    return campo;
}

// Línea usuario, contraseña, correo, ciudad, país, nacimiento, inscripción
void UdeABook::cargarUsuario(const string &linea)
{
    int posicion = 0;
    string nombre = tomarCampo(linea, posicion);
    string contrasena = tomarCampo(linea, posicion);
    string correo = tomarCampo(linea, posicion);
    string ciudad = tomarCampo(linea, posicion);
    string pais = tomarCampo(linea, posicion);
    Fecha nacimiento;
    nacimiento.leerTexto(tomarCampo(linea, posicion));
    Fecha inscripcion;
    inscripcion.leerTexto(tomarCampo(linea, posicion));

    // La ruta se arma, no se guarda en el archivo
    string rutaFoto = rutaBase + nombre + CARPETA_ALBUMES + FOTO_PERFIL;
    Usuario nuevo(nombre, contrasena, correo, ciudad, pais, rutaFoto, nacimiento, inscripcion, usuarios.getCantidad());
    usuarios.agregar(nuevo);
}

// Línea con los índices de dos amigos
void UdeABook::cargarAmistad(const string &linea)
{
    int posicion = 0;
    int a = convertirEntero(tomarCampo(linea, posicion));
    int b = convertirEntero(tomarCampo(linea, posicion));
    if (esIndiceValido(a) && esIndiceValido(b)) {
        amistades.agregarAmistad(a, b);
    }
}


// Búsqueda

bool UdeABook::esIndiceValido(int indice) const
{
    return indice >= 0 && indice < usuarios.getCantidad() && indice < amistades.getTamanio();
}


// Lectura del teclado

// Si se acaba la entrada devuelve 0 para salir de los menús
string UdeABook::leerLinea() const
{
    string linea = "";
    if (!getline(cin, linea)) {
        return "0";
    }
    quitarRetorno(linea);
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
