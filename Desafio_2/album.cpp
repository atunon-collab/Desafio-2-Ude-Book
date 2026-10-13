#include "album.h"

// Opciones del carrusel
const string SIGUIENTE = "1";
const string PREVIA = "2";
const string LIKE = "3";
const string SALIR = "0";


// Constructores y destructor

Album::Album()
{
    nombre = "";
    ruta = "";
    privacidad = PRIVADO;
}

Album::Album(const string &nombre, const string &ruta, char privacidad)
{
    this->nombre = nombre;
    this->ruta = ruta;
    this->privacidad = privacidad;
}

// Copia el álbum con todas sus fotos
Album::Album(const Album &otro)
{
    nombre = otro.nombre;
    ruta = otro.ruta;
    privacidad = otro.privacidad;
    fotos = otro.fotos;
}

// La lista de fotos se libera sola con su destructor
Album::~Album()
{
}


// Getters y setters

const string &Album::getNombre() const
{
    return nombre;
}

const string &Album::getRuta() const
{
    return ruta;
}

char Album::getPrivacidad() const
{
    return privacidad;
}

void Album::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

void Album::setRuta(const string &ruta)
{
    this->ruta = ruta;
}

void Album::setPrivacidad(char privacidad)
{
    this->privacidad = privacidad;
}


// Fotos

void Album::agregarFoto(const Foto &foto)
{
    fotos.agregar(foto);
}

Foto &Album::getFoto(int posicion)
{
    return fotos[posicion];
}

int Album::getCantidadFotos() const
{
    return fotos.getCantidad();
}


// Otros métodos

// Público lo ve cualquiera, amigos solo los amigos, privado nadie más
bool Album::esVisible(bool esAmigo) const
{
    if (privacidad == PUBLICO) {
        return true;
    }
    if (privacidad == AMIGOS) {
        return esAmigo;
    }
    return false;
}

// Muestra las fotos una tras otra en círculo
void Album::verCarrusel()
{
    int cantidad = fotos.getCantidad();
    if (cantidad == 0) {
        cout << "El album no tiene fotos" << endl;
        return;
    }

    // Guarda si en esta visita ya se le dio like a cada foto
    bool *conLike = new bool[cantidad];
    for (int i = 0; i < cantidad; i++) {
        conLike[i] = false;
    }

    int posicion = 0;
    string opcion = "";
    while (opcion != SALIR) {
        cout << endl << "Album " << nombre << " - foto " << posicion + 1 << " de " << cantidad << endl;
        cout << fotos[posicion] << endl;
        cout << "1. Siguiente   2. Previa   3. Dar o quitar like   0. Salir del album" << endl;
        cout << "Opcion: ";
        if (!getline(cin, opcion)) {
            opcion = SALIR;
        }

        if (opcion == SIGUIENTE) {
            // Después de la última vuelve a la primera
            posicion = (posicion + 1) % cantidad;
        } else if (opcion == PREVIA) {
            // Antes de la primera va a la última
            posicion = (posicion - 1 + cantidad) % cantidad;
        } else if (opcion == LIKE) {
            if (conLike[posicion]) {
                --fotos[posicion];
                conLike[posicion] = false;
                cout << "Like quitado" << endl;
            } else {
                ++fotos[posicion];
                conLike[posicion] = true;
                cout << "Like dado" << endl;
            }
        } else if (opcion != SALIR) {
            cout << "Opcion no valida" << endl;
        }
    }

    delete[] conLike;
}


// Operadores

// album[i] devuelve la foto i
Foto &Album::operator[](int posicion)
{
    return fotos[posicion];
}

// Copia otro álbum con sus fotos
Album &Album::operator=(const Album &otro)
{
    nombre = otro.nombre;
    ruta = otro.ruta;
    privacidad = otro.privacidad;
    fotos = otro.fotos;
    return *this;
}

// Muestra el nombre, la privacidad y cuántas fotos tiene
ostream &operator<<(ostream &salida, const Album &album)
{
    salida << album.nombre << " (";
    if (album.privacidad == Album::PUBLICO) {
        salida << "publico";
    } else if (album.privacidad == Album::AMIGOS) {
        salida << "amigos";
    } else {
        salida << "privado";
    }
    salida << ", " << album.fotos.getCantidad() << " fotos)";
    return salida;
}
