#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista
{
private:
    // Atributos
    T *datos;
    int cantidad;
    int capacidad;

    static const int CAPACIDAD_INICIAL = 4;

    // Métodos privados
    void redimensionar();

public:
    // Constructores y destructor
    Lista();
    Lista(int capacidadInicial);
    Lista(const Lista<T> &otra);
    ~Lista();

    // Consultas
    bool estaVacia() const;
    int getCantidad() const;
    int getCapacidad() const;
    long memoriaUsada() const;

    // Modificación
    void agregar(const T &elemento);
    bool insertar(int posicion, const T &elemento);
    bool eliminar(int posicion);

    // Operadores
    T &operator[](int posicion);
    const T &operator[](int posicion) const;
    Lista<T> &operator=(const Lista<T> &otra);
};


// Constructores y destructor

template <typename T>
Lista<T>::Lista()
{
    capacidad = CAPACIDAD_INICIAL;
    cantidad = 0;
    datos = new T[capacidad];
}

template <typename T>
Lista<T>::Lista(int capacidadInicial)
{
    if (capacidadInicial < 1) {
        capacidadInicial = 1;
    }
    capacidad = capacidadInicial;
    cantidad = 0;
    datos = new T[capacidad];
}

template <typename T>
Lista<T>::Lista(const Lista<T> &otra)
{
    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    datos = new T[capacidad];

    for (int i = 0; i < cantidad; i++) {
        datos[i] = otra.datos[i];
    }
}

template <typename T>
Lista<T>::~Lista()
{
    delete[] datos;
}


// Consultas

template <typename T>
bool Lista<T>::estaVacia() const
{
    return cantidad == 0;
}

template <typename T>
int Lista<T>::getCantidad() const
{
    return cantidad;
}

template <typename T>
int Lista<T>::getCapacidad() const
{
    return capacidad;
}

template <typename T>
long Lista<T>::memoriaUsada() const
{
    return sizeof(Lista<T>) + capacidad * sizeof(T);
}


// Métodos privados

template <typename T>
void Lista<T>::redimensionar()
{
    int nuevaCapacidad = capacidad * 2;
    T *nuevo = new T[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++) {
        nuevo[i] = datos[i];
    }

    delete[] datos;
    datos = nuevo;
    capacidad = nuevaCapacidad;
}


// Modificación

template <typename T>
void Lista<T>::agregar(const T &elemento)
{
    if (cantidad == capacidad) {
        redimensionar();
    }
    datos[cantidad] = elemento;
    cantidad++;
}

template <typename T>
bool Lista<T>::insertar(int posicion, const T &elemento)
{
    if (posicion < 0 || posicion > cantidad) {
        return false;
    }
    if (cantidad == capacidad) {
        redimensionar();
    }

    for (int i = cantidad; i > posicion; i--) {
        datos[i] = datos[i - 1];
    }

    datos[posicion] = elemento;
    cantidad++;
    return true;
}

template <typename T>
bool Lista<T>::eliminar(int posicion)
{
    if (posicion < 0 || posicion >= cantidad) {
        return false;
    }

    for (int i = posicion; i < cantidad - 1; i++) {
        datos[i] = datos[i + 1];
    }

    cantidad--;
    return true;
}


// Operadores

template <typename T>
T &Lista<T>::operator[](int posicion)
{
    return datos[posicion];
}

template <typename T>
const T &Lista<T>::operator[](int posicion) const
{
    return datos[posicion];
}

template <typename T>
Lista<T> &Lista<T>::operator=(const Lista<T> &otra)
{
    if (this == &otra) {
        return *this;
    }

    delete[] datos;

    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    datos = new T[capacidad];

    for (int i = 0; i < cantidad; i++) {
        datos[i] = otra.datos[i];
    }

    return *this;
}

#endif // LISTA_H
