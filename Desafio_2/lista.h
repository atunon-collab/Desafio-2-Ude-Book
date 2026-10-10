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

public:
    // Constructores y destructor
    Lista();
    Lista(int capacidadInicial);
    ~Lista();

    // Consultas
    bool estaVacia() const;
    int getCantidad() const;
    int getCapacidad() const;
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


#endif // LISTA_H
