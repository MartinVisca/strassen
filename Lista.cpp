#include "Lista.h"
#include <cassert>
#include <iostream>

using namespace std;

template <typename T>
Lista<T>::Lista() //Constructor de la clase
{
    primero = nullptr;
    ultimo = nullptr;
    lis = nullptr;
    cantidad = 0;
    posicion = 0;
}

template <typename T>
Lista<T>::~Lista() //Destructor de la clase
{
    while (ultimo != nullptr){
        lis = ultimo;
        ultimo = ultimo->ant;
        delete lis;
    }
}

template <typename T>
void Lista<T>::Copiar_lista (nodo_lista * copia) //Copia la lista; usada en el constructor por copia
{
    while (copia != nullptr){
        Agregar_final (copia->elemento);
        copia = copia->sig;
    }
}

template <typename T>
Lista<T>::Lista(const Lista& L) //Constructor por copia de la clase
{
    nodo_lista * copia = L.primero;
    primero = nullptr;
    ultimo = nullptr;
    lis = nullptr;
    cantidad = 0;
    posicion = 0;
    Copiar_lista(copia);
}

template <typename T>
void Lista<T>::Agregar_principio (T elem) //Agrega un elemento al principio de la lista
{
    nodo_lista * nodo = new nodo_lista;
    nodo->elemento = elem;
    nodo->sig = nullptr;
    nodo->ant = nullptr;

    if (primero == nullptr){
        primero = nodo;
        ultimo = primero;
    }
    else {
        nodo->sig = primero;
        primero->ant = nodo;
        primero = nodo;
    }

    lis = primero;
    posicion = 1;
    cantidad += 1;
}

template <typename T>
void Lista<T>::Agregar_final (T elem) //Agrega un nodo al final de la lista
{
    nodo_lista * nodo = new nodo_lista;
    nodo->elemento = elem;
    nodo->sig = nullptr;

    if (primero == nullptr){
        primero = nodo;
        ultimo = primero;
        nodo->ant = nullptr;
        lis = primero;
    }
    else {
        ultimo->sig = nodo;
        nodo->ant = ultimo;
        ultimo = ultimo->sig;
    }

    cantidad += 1;
    nodo = nullptr;
    delete nodo;
}

template <typename T>
void Lista<T>::Agregar_posicion (T elem, int pos) //Dada una posicion, agrega un nodo en dicho lugar
{
    if ((pos > 1) && (pos <= cantidad + 1)){
        nodo_lista * nodo = new nodo_lista;
        nodo_lista * aux = new nodo_lista;
        aux = primero;
        nodo->elemento = elem;
        nodo->sig = nullptr;

        bool agrego = false;
        int contador = 1;

        while ((aux != nullptr) && (agrego == false)){
            if (contador == pos - 1){
                if (aux->sig == nullptr){
                    nodo->ant = ultimo;
                    ultimo->sig = nodo;
                    ultimo = nodo;
                }
                else{
                    nodo->sig = aux->sig;
                    aux->sig = nodo;
                    nodo->ant = aux;
                }

                agrego = true;
                cantidad += 1;
            }
            else {
                aux = aux->sig;
                contador += 1;
            }
        }
    }
    else if (pos == 1)
        Agregar_principio (elem);
}

template <typename T>
int Lista<T>::Cantidad_elementos () const //Devuelve la cantidad de elementos en la lista
{
    return cantidad;
}

template <typename T>
bool Lista<T>::Pertenece (T elem) const //Determina si un elemento esta o no en la lista
{
    nodo_lista * aux = primero;

    while (aux != nullptr)
        if (aux->elemento == elem)
            return true;
        else
            aux = aux->sig;

    return false;
}

template <typename T>
bool Lista<T>::Es_vacia () const //Determina si una lista es vacia
{
    return (cantidad == 0);
}

template <typename T>
void Lista<T>::Eliminar_elemento (int pos) //Elimina un elemento en una posicion dada
{
    nodo_lista * aux = primero;
    int contador = 1;

    if (contador <= cantidad)
        while (contador < pos){
            aux = aux->sig;
            contador += 1;
        }

        if (aux == primero){
            primero = primero->sig;
            if (primero != nullptr)
                primero->ant = nullptr;
            delete aux;
            cantidad -= 1;
        }
        else if (aux == ultimo){
            ultimo = ultimo->ant;
            ultimo->sig = nullptr;
            delete aux;
            cantidad -= 1;
        }
        else {
            aux->ant->sig = aux->sig;
            aux->sig->ant = aux->ant;
            delete aux;
            cantidad -= 1;
        }

    lis = primero;
    posicion = 1;
}

template <typename T>
void Lista<T>::Vaciar_lista () //Vacia completamente la lista
{
    while (ultimo != nullptr){
        lis = ultimo;
        ultimo = ultimo->sig;
        delete lis;
    }

    cantidad = 0;
    posicion = 0;
    primero = nullptr;
    lis = nullptr;
}

template <typename T>
T Lista<T>::ObtenerElemento(int pos) //Devuelve el elemento que se encuentra en una posicion dada
{
    assert ((!Es_vacia()) && (pos <= cantidad));

    if ((posicion != 0) && (pos <= cantidad) && (pos > 0)){

        while (posicion < pos){
            posicion += 1;
            lis = lis->sig;
        }

        while (posicion > pos){
            posicion -= 1;
            lis = lis->ant;
        }

        return lis->elemento;
    }
}

template class Lista<int>;
template class Lista<float>;
template class Lista<double>;
template class Lista<char>;
template class Lista<string>;
