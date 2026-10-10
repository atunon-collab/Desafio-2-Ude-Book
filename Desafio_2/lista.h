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


#endif // LISTA_H
