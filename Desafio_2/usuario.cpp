#include "usuario.h"
#include "contador.h"

const int SIN_INDICE = -1;

Usuario::Usuario(){
    nombreUsuario = "";
    contrasena = "";
    correo = "";
    ciudad = "";
    pais = "";
    rutaFotoPerfil = "";
    indice = SIN_INDICE;
}

Usuario::Usuario(const string &nombreUsuario, const string &contrasena, const string &correo,
                 const string &ciudad, const string &pais, const string &rutaFotoPerfil,
                 const Fecha &fechaNacimiento, const Fecha &fechaInscripcion, int indice)
{
    this->nombreUsuario = nombreUsuario;
    this->contrasena = contrasena;
    this->correo = correo;
    this->ciudad = ciudad;
    this->pais = pais;
    this->rutaFotoPerfil = rutaFotoPerfil;
    this->fechaNacimiento = fechaNacimiento;
    this->fechaInscripcion = fechaInscripcion;
    this->indice = indice;
}

// Iteraciones las de Lista operator= de cada lista
Usuario::Usuario(const Usuario &otro){
    nombreUsuario = otro.nombreUsuario;
    contrasena = otro.contrasena;
    correo = otro.correo;
    ciudad = otro.ciudad;
    pais = otro.pais;
    rutaFotoPerfil = otro.rutaFotoPerfil;
    fechaNacimiento = otro.fechaNacimiento;
    fechaInscripcion = otro.fechaInscripcion;
    indice = otro.indice;
    albumes = otro.albumes;
    enviados = otro.enviados;
    recibidos = otro.recibidos;
    solicitudes = otro.solicitudes;
}

Usuario::~Usuario(){
}

const string &Usuario::getNombreUsuario() const{
    return nombreUsuario;
}

const string &Usuario::getContrasena() const{
    return contrasena;
}

const string &Usuario::getCorreo() const{
    return correo;
}

const string &Usuario::getCiudad() const{
    return ciudad;
}

const string &Usuario::getPais() const{
    return pais;
}

const string &Usuario::getRutaFotoPerfil() const{
    return rutaFotoPerfil;
}

const Fecha &Usuario::getFechaNacimiento() const{
    return fechaNacimiento;
}

const Fecha &Usuario::getFechaInscripcion() const{
    return fechaInscripcion;
}

int Usuario::getIndice() const{
    return indice;
}

void Usuario::setNombreUsuario(const string &nombreUsuario){
    this->nombreUsuario = nombreUsuario;
}

void Usuario::setContrasena(const string &contrasena){
    this->contrasena = contrasena;
}

void Usuario::setCorreo(const string &correo){
    this->correo = correo;
}

void Usuario::setCiudad(const string &ciudad){
    this->ciudad = ciudad;
}

void Usuario::setPais(const string &pais){
    this->pais = pais;
}

void Usuario::setRutaFotoPerfil(const string &rutaFotoPerfil){
    this->rutaFotoPerfil = rutaFotoPerfil;
}

void Usuario::setFechaNacimiento(const Fecha &fechaNacimiento){
    this->fechaNacimiento = fechaNacimiento;
}

void Usuario::setFechaInscripcion(const Fecha &fechaInscripcion){
    this->fechaInscripcion = fechaInscripcion;
}

void Usuario::setIndice(int indice){
    this->indice = indice;
}

bool Usuario::verificarContrasena(const string &contrasena) const{
    return this->contrasena == contrasena;
}

// Iteraciones 0, más las de Lista agregar
void Usuario::agregarAlbum(const Album &album){
    albumes.agregar(album);
}

Album &Usuario::getAlbum(int posicion){
    return albumes[posicion];
}

int Usuario::getCantidadAlbumes() const{
    return albumes.getCantidad();
}

// Iteraciones 0 si es el más nuevo, que es lo normal
void Usuario::agregarEnviado(const Mensaje &mensaje){
    int posicion = enviados.getCantidad();
    while (posicion > 0 && mensaje < enviados[posicion - 1]) {
        Contador::sumar();
        posicion--;
    }
    enviados.insertar(posicion, mensaje);
}

// Iteraciones 0 si es el más nuevo
void Usuario::agregarRecibido(const Mensaje &mensaje){
    int posicion = recibidos.getCantidad();
    while (posicion > 0 && mensaje < recibidos[posicion - 1]) {
        Contador::sumar();
        posicion--;
    }
    recibidos.insertar(posicion, mensaje);
}

Mensaje &Usuario::getEnviado(int posicion){
    return enviados[posicion];
}

Mensaje &Usuario::getRecibido(int posicion){
    return recibidos[posicion];
}

int Usuario::getCantidadEnviados() const{
    return enviados.getCantidad();
}

int Usuario::getCantidadRecibidos() const{
    return recibidos.getCantidad();
}

// Iteraciones hasta encontrarlo, como máximo la cantidad de enviados
bool Usuario::marcarEnviadoLeido(const Mensaje &recibido){
    int i = enviados.getCantidad() - 1;
    while (i >= 0) {
        Contador::sumar();
        Mensaje &copia = enviados[i];
        if (!copia.getLeido() && copia.getReceptor() == recibido.getReceptor()
            && copia.getFechaEnvio() == recibido.getFechaEnvio() && copia.getTexto() == recibido.getTexto()) {
            copia.marcarLeido();
            return true;
        }
        i--;
    }
    return false;
}

// Primero búsqueda binaria del primer mensaje desde inicio
// Iteraciones log2(m) más los encontrados, ejemplo 35 en el rango son 42
int Usuario::buscarMensajes(const Fecha &inicio, const Fecha &fin) const{
    int izquierda = 0;
    int derecha = recibidos.getCantidad();
    while (izquierda < derecha) {
        Contador::sumar();
        int mitad = (izquierda + derecha) / 2;
        if (recibidos[mitad].getFechaEnvio() < inicio) {
            izquierda = mitad + 1;
        } else {
            derecha = mitad;
        }
    }

    int encontrados = 0;
    int i = izquierda;
    while (i < recibidos.getCantidad() && recibidos[i].getFechaEnvio() <= fin) {
        Contador::sumar();
        cout << recibidos[i] << endl;
        encontrados++;
        i++;
    }
    return encontrados;
}

// Iteraciones 0, más las de Lista agregar
void Usuario::agregarSolicitud(int emisor){
    solicitudes.agregar(emisor);
}

// Iteraciones las de Lista eliminar
void Usuario::eliminarSolicitud(int posicion){
    solicitudes.eliminar(posicion);
}

// Iteraciones una por solicitud, ejemplo 4 solicitudes son 4
bool Usuario::tieneSolicitudDe(int emisor) const{
    for (int i = 0; i < solicitudes.getCantidad(); i++) {
        Contador::sumar();
        if (solicitudes[i] == emisor) {
            return true;
        }
    }
    return false;
}


int Usuario::getSolicitud(int posicion) const{
    return solicitudes[posicion];
}

int Usuario::getCantidadSolicitudes() const{
    return solicitudes.getCantidad();
}

// Memoria de los arreglos de sus listas y de las fotos de sus álbumes
// Su ciclo no suma iteraciones porque es parte de la medición
long Usuario::memoriaUsada() const{
    long memoria = albumes.memoriaUsada() + enviados.memoriaUsada() + recibidos.memoriaUsada() + solicitudes.memoriaUsada();
    for (int i = 0; i < albumes.getCantidad(); i++) {
        memoria = memoria + albumes[i].memoriaUsada();
    }
    return memoria;
}

bool Usuario::operator==(const Usuario &otro) const{
    return nombreUsuario == otro.nombreUsuario;
}

// Copia otro usuario con todas sus listas
// Iteraciones las de Lista operator= de cada lista
Usuario &Usuario::operator=(const Usuario &otro){
    nombreUsuario = otro.nombreUsuario;
    contrasena = otro.contrasena;
    correo = otro.correo;
    ciudad = otro.ciudad;
    pais = otro.pais;
    rutaFotoPerfil = otro.rutaFotoPerfil;
    fechaNacimiento = otro.fechaNacimiento;
    fechaInscripcion = otro.fechaInscripcion;
    indice = otro.indice;
    albumes = otro.albumes;
    enviados = otro.enviados;
    recibidos = otro.recibidos;
    solicitudes = otro.solicitudes;
    return *this;
}

ostream &operator<<(ostream &salida, const Usuario &usuario){
    salida << "Perfil de " << usuario.nombreUsuario << endl;
    salida << "   Ciudad: " << usuario.ciudad << ", " << usuario.pais << endl;
    salida << "   Correo: " << usuario.correo << endl;
    salida << "   Foto de perfil: " << usuario.rutaFotoPerfil << endl;
    salida << "   En Ude@Book desde " << usuario.fechaInscripcion;
    return salida;
}

