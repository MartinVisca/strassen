#ifndef MATRIZ_H
#define MATRIZ_H

template <typename T>
class Matriz
{
    public:
        Matriz(int k);
        virtual ~Matriz();
        Matriz(const Matriz& other);

        void Inicializar_aleatoriamente ();

        T Devolver_elemento (int fila, int columna) const;

        void Sumar (const Matriz& B, const Matriz& C);
        void Restar (const Matriz& B, const Matriz& C);
        void Strassen_2x2 (const Matriz& B, const Matriz& C);
        void Cargar_submatrices (const Matriz& M11, const Matriz& M12, const Matriz& M21, const Matriz& M22) const;
        void Combinar_submatrices (const Matriz& M11, const Matriz& M12, const Matriz& M21, const Matriz& M22) const;
        void Strassen (const Matriz& B, const Matriz& C);
        void Multiplicar (const Matriz& B, const Matriz& C);

    protected:
    private:
        T ** matriz;
        int filas, columnas, k;
};

#endif // MATRIZ_H
