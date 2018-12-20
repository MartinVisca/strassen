#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista
{
    public:
        Lista();
        virtual ~Lista();
        Lista(const Lista& other);

        void Agregar_principio (T elem);
        void Agregar_final (T elem);
        void Agregar_posicion (T elem, int pos);
        int Cantidad_elementos () const;
        bool Pertenece (T elem) const;
        bool Es_vacia () const;
        void Eliminar_elemento (int pos);
        void Vaciar_lista ();
        T ObtenerElemento (int pos);

    protected:
    private:
        struct nodo_lista {
            T elemento;
            nodo_lista * sig;
            nodo_lista * ant;
        };

        nodo_lista * primero, * ultimo, * lis;
        int cantidad, posicion;
        void Copiar_lista (nodo_lista * copia);
};

#endif // LISTA_H
