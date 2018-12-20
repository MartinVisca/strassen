#include "Arreglo.h"
#include <iostream>

using namespace std;

template <typename T>
Arreglo<T>::Arreglo(unsigned int longitud)
{
    posicion = 0;
    capacidad = longitud;

    arreglo = new T [capacidad];
}

template <typename T>
Arreglo<T>::~Arreglo()
{
    delete [] arreglo;
    arreglo = nullptr;
    capacidad = 0;
    posicion = 0;
}

template <typename T>
void Arreglo<T>::Copiar_arreglo (T * arr)
{
    unsigned int pos = 0;

    while (pos < capacidad){
        Agregar_elemento (arreglo[pos]);
        pos += 1;
    }
}

template <typename T>
Arreglo<T>::Arreglo(const Arreglo& arr)
{
    posicion = 0;
    capacidad = 0;
    arreglo = new T [capacidad];
    Copiar_arreglo(arreglo);
}

template <typename T>
void Arreglo<T>::Agregar_capacidad ()
{
    int capacidad_anterior = capacidad;
    capacidad = capacidad * 2;

    T * arr = new T [capacidad];
    for (int i = 0; i < capacidad_anterior; i++)
        arr[i] = arreglo[i];

    arreglo = arr;

    delete [] arr;
    arr = nullptr;
}

template <typename T>
void Arreglo<T>::Agregar_elemento (T elem)
{
    if (posicion < capacidad)
        arreglo[posicion] = elem;

    else{
        Agregar_capacidad();
        arreglo[posicion] = elem;
    }

    posicion += 1;
}

template <typename T>
void Arreglo<T>::Agregar_posicion (T elem, unsigned int pos)
{
    T aux = arreglo[pos - 1];
    T aux2;
    arreglo[pos - 1] = elem;

    while (pos < capacidad){
            aux2 = arreglo[pos];
            arreglo[pos] = aux;
            aux = aux2;
            pos += 1;
        }
}

template <typename T>
T Arreglo<T>::Recuperar_elemento (unsigned int pos)
{
    return arreglo[pos];
}

template <typename T>
int Arreglo<T>::Capacidad () const
{
    return capacidad;
}

template class Arreglo<int>;
template class Arreglo<float>;
template class Arreglo<double>;
template class Arreglo<char>;
template class Arreglo<string>;
