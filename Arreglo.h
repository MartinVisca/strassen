#ifndef ARREGLO_H
#define ARREGLO_H

template <typename T>
class Arreglo
{
    public:
        Arreglo(unsigned int longitud);
        virtual ~Arreglo();
        Arreglo(const Arreglo& other);

        void Agregar_elemento (T elem);
        void Agregar_capacidad ();
        void Agregar_posicion (T elem, unsigned int pos);
        int Capacidad () const;
        T Recuperar_elemento (unsigned int pos);

    protected:
    private:
        unsigned int capacidad, posicion;
        T * arreglo;
        void Copiar_arreglo(T * arreglo);
};

#endif // ARREGLO_H
