#include "usuario.h"

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

bool Usuario::verificarContrasena(const string &contrasena) const
{
    return this->contrasena == contrasena;
}

bool Usuario::operator==(const Usuario &otro) const
{
    return nombreUsuario == otro.nombreUsuario;
}

// Copia otro usuario
Usuario &Usuario::operator=(const Usuario &otro)
{
    nombreUsuario = otro.nombreUsuario;
    contrasena = otro.contrasena;
    correo = otro.correo;
    ciudad = otro.ciudad;
    pais = otro.pais;
    rutaFotoPerfil = otro.rutaFotoPerfil;
    fechaNacimiento = otro.fechaNacimiento;
    fechaInscripcion = otro.fechaInscripcion;
    indice = otro.indice;
    return *this;
}

ostream &operator<<(ostream &salida, const Usuario &usuario)
{
    salida << "Perfil de " << usuario.nombreUsuario << endl;
    salida << "   Ciudad: " << usuario.ciudad << ", " << usuario.pais << endl;
    salida << "   Correo: " << usuario.correo << endl;
    salida << "   Foto de perfil: " << usuario.rutaFotoPerfil << endl;
    salida << "   En Ude@Book desde " << usuario.fechaInscripcion;
    return salida;
}
