#include "udeabook.h"

// Rutas de las fotos
const string RUTA_BASE = "/users/udeabook/";
const string CARPETA_ALBUMES = "/albums/";
const string FOTO_PERFIL = "profile.png";
const string EXTENSION = ".png";

// Formato del archivo
const char SEPARADOR = ';';
const char MARCA_SECCION = '#';
const string SECCION_USUARIOS = "#USUARIOS";
const string SECCION_AMISTADES = "#AMISTADES";
const string SECCION_SOLICITUDES = "#SOLICITUDES";
const string SECCION_MENSAJES = "#MENSAJES";
const string SECCION_ALBUMES = "#ALBUMES";
const string LEIDO = "1";

// Valores especiales
const int NO_ENCONTRADO = -1;
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

// Carga, muestra el ingreso y al salir guarda
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
            ingresar();
        } else if (opcion != 0) {
            cout << "Opcion no valida" << endl;
        }
    }

    guardarDatos();
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
            } else if (seccion == SECCION_SOLICITUDES) {
                cargarSolicitud(linea);
            } else if (seccion == SECCION_MENSAJES) {
                cargarMensaje(linea);
            } else if (seccion == SECCION_ALBUMES) {
                cargarAlbum(linea, archivo);
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

// Línea con quién envía y quién recibe la solicitud
void UdeABook::cargarSolicitud(const string &linea)
{
    int posicion = 0;
    int emisor = convertirEntero(tomarCampo(linea, posicion));
    int receptor = convertirEntero(tomarCampo(linea, posicion));
    if (esIndiceValido(emisor) && esIndiceValido(receptor)) {
        usuarios[receptor].agregarSolicitud(emisor);
    }
}

// Línea emisor, receptor, fecha, leído y al final el texto
// El texto va de último para que pueda tener punto y coma
void UdeABook::cargarMensaje(const string &linea)
{
    int posicion = 0;
    int emisor = convertirEntero(tomarCampo(linea, posicion));
    int receptor = convertirEntero(tomarCampo(linea, posicion));
    Fecha fecha;
    fecha.leerTexto(tomarCampo(linea, posicion));
    bool leido = tomarCampo(linea, posicion) == LEIDO;

    string texto = "";
    int largo = linea.length();
    if (posicion < largo) {
        texto = linea.substr(posicion);
    }

    if (esIndiceValido(emisor) && esIndiceValido(receptor)) {
        Mensaje mensaje(usuarios[emisor].getNombreUsuario(), usuarios[receptor].getNombreUsuario(), texto, fecha);
        mensaje.setLeido(leido);
        usuarios[emisor].agregarEnviado(mensaje);
        usuarios[receptor].agregarRecibido(mensaje);
    }
}

// Línea dueño, nombre, privacidad y cantidad de fotos
// Debajo viene una línea por foto con nombre, fecha, tamaño y likes
void UdeABook::cargarAlbum(const string &linea, ifstream &archivo)
{
    int posicion = 0;
    int dueno = convertirEntero(tomarCampo(linea, posicion));
    string nombre = tomarCampo(linea, posicion);
    string privacidad = tomarCampo(linea, posicion);
    int cantidadFotos = convertirEntero(tomarCampo(linea, posicion));

    if (!esIndiceValido(dueno) || privacidad.length() == 0) {
        return;
    }

    string rutaAlbum = rutaBase + usuarios[dueno].getNombreUsuario() + CARPETA_ALBUMES + nombre;
    Album album(nombre, rutaAlbum, privacidad[0]);

    string lineaFoto = "";
    for (int i = 0; i < cantidadFotos; i++) {
        getline(archivo, lineaFoto);
        quitarRetorno(lineaFoto);

        int posicionFoto = 0;
        string nombreFoto = tomarCampo(lineaFoto, posicionFoto);
        Fecha captura;
        captura.leerTexto(tomarCampo(lineaFoto, posicionFoto));
        int tamanio = convertirEntero(tomarCampo(lineaFoto, posicionFoto));
        int likes = convertirEntero(tomarCampo(lineaFoto, posicionFoto));

        Foto foto(rutaAlbum + "/" + nombreFoto + EXTENSION, captura, tamanio, likes);
        album.agregarFoto(foto);
    }

    usuarios[dueno].agregarAlbum(album);
}


// Guardado de datos

// Funcionalidad I, actualización del archivo al salir
// Reescribe todo el archivo con los datos que hay en memoria
void UdeABook::guardarDatos()
{
    ofstream archivo(archivoDatos);
    if (!archivo.is_open()) {
        cout << "No se pudo guardar el archivo " << archivoDatos << endl;
        return;
    }

    int total = usuarios.getCantidad();

    // Usuarios en orden alfabético
    archivo << SECCION_USUARIOS << SEPARADOR << total << "\n";
    for (int i = 0; i < total; i++) {
        Usuario &usuario = usuarios[i];
        archivo << usuario.getNombreUsuario() << SEPARADOR << usuario.getContrasena() << SEPARADOR
                << usuario.getCorreo() << SEPARADOR << usuario.getCiudad() << SEPARADOR
                << usuario.getPais() << SEPARADOR << usuario.getFechaNacimiento() << SEPARADOR
                << usuario.getFechaInscripcion() << "\n";
    }

    // Cada amistad una sola vez, por eso j empieza en i + 1
    archivo << SECCION_AMISTADES << "\n";
    for (int i = 0; i < total; i++) {
        for (int j = i + 1; j < total; j++) {
            if (amistades(i, j)) {
                archivo << i << SEPARADOR << j << "\n";
            }
        }
    }

    // Quien envía y quien recibe
    archivo << SECCION_SOLICITUDES << "\n";
    for (int i = 0; i < total; i++) {
        for (int s = 0; s < usuarios[i].getCantidadSolicitudes(); s++) {
            archivo << usuarios[i].getSolicitud(s) << SEPARADOR << i << "\n";
        }
    }

    // Cada mensaje se escribe una vez, desde los enviados de su emisor
    archivo << SECCION_MENSAJES << "\n";
    for (int i = 0; i < total; i++) {
        for (int m = 0; m < usuarios[i].getCantidadEnviados(); m++) {
            Mensaje &mensaje = usuarios[i].getEnviado(m);
            int receptor = buscarUsuario(mensaje.getReceptor());
            archivo << i << SEPARADOR << receptor << SEPARADOR << mensaje.getFechaEnvio() << SEPARADOR
                    << mensaje.getLeido() << SEPARADOR << mensaje.getTexto() << "\n";
        }
    }

    // Álbumes y debajo sus fotos
    archivo << SECCION_ALBUMES << "\n";
    for (int i = 0; i < total; i++) {
        for (int a = 0; a < usuarios[i].getCantidadAlbumes(); a++) {
            Album &album = usuarios[i].getAlbum(a);
            archivo << i << SEPARADOR << album.getNombre() << SEPARADOR << album.getPrivacidad()
                    << SEPARADOR << album.getCantidadFotos() << "\n";
            for (int f = 0; f < album.getCantidadFotos(); f++) {
                Foto &foto = album[f];
                archivo << foto.getNombre() << SEPARADOR << foto.getFechaCaptura() << SEPARADOR
                        << foto.getTamanio() << SEPARADOR << foto.getLikes() << "\n";
            }
        }
    }

    archivo.close();
    cout << "Datos guardados en " << archivoDatos << endl;
}


// Ingreso a la plataforma

// Busca el usuario y revisa la contraseña
bool UdeABook::iniciarSesion(const string &nombre, const string &contrasena)
{
    int indice = buscarUsuario(nombre);
    if (indice == NO_ENCONTRADO) {
        return false;
    }
    if (!usuarios[indice].verificarContrasena(contrasena)) {
        return false;
    }
    usuarioActual = indice;
    return true;
}

void UdeABook::cerrarSesion()
{
    usuarioActual = SIN_SESION;
}

// Funcionalidad II, ingreso a la plataforma
void UdeABook::ingresar()
{
    cout << "Usuario: ";
    string nombre = leerLinea();
    cout << "Contrasena: ";
    string clave = leerLinea();

    if (!iniciarSesion(nombre, clave)) {
        cout << "Usuario o contrasena incorrectos" << endl;
        return;
    }

    cout << endl << "Bienvenido " << usuarios[usuarioActual].getNombreUsuario() << endl;
    mostrarMenu();
    cerrarSesion();
}


// Menús

// Menú principal después de iniciar sesión
void UdeABook::mostrarMenu()
{
    int opcion = ENTRADA_INVALIDA;
    while (opcion != 0) {
        cout << endl << "===== Menu principal de " << usuarios[usuarioActual].getNombreUsuario() << " =====" << endl;
        cout << "1. Actualizar fotos de amigos (solo una vez)" << endl;
        cout << "2. Administrar amistades" << endl;
        cout << "3. Visitar perfil de un amigo" << endl;
        cout << "4. Ver sugerencias de amistad" << endl;
        cout << "5. Administrar mensajes" << endl;
        cout << "0. Cerrar sesion" << endl;
        cout << "Opcion: ";
        opcion = leerEntero();

        if (opcion >= 1 && opcion <= 5) {
            cout << "Opcion en construccion" << endl;
        } else if (opcion != 0) {
            cout << "Opcion no valida" << endl;
        }
    }
    cout << "Sesion cerrada" << endl;
}


// Búsqueda

// Búsqueda binaria, los usuarios están en orden alfabético
int UdeABook::buscarUsuario(const string &nombre) const
{
    int izquierda = 0;
    int derecha = usuarios.getCantidad() - 1;
    while (izquierda <= derecha) {
        int mitad = (izquierda + derecha) / 2;
        const string &actual = usuarios[mitad].getNombreUsuario();
        if (actual == nombre) {
            return mitad;
        }
        if (actual < nombre) {
            izquierda = mitad + 1;
        } else {
            derecha = mitad - 1;
        }
    }
    return NO_ENCONTRADO;
}

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
