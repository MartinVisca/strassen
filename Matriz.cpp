#include "Matriz.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

template <typename T>
Matriz<T>::Matriz(int k)
//Constructor de la clase. Este metodo construye matrices cuadradas.
{
    this->k = k;
    filas = columnas = pow (2, k);
    matriz = new T *[filas];
    for (int i = 0; i < filas; i++)
        matriz[i] = new T [columnas];
}

template <typename T>
Matriz<T>::~Matriz()
//Destructor de la clase
{
    for (int i = 0; i < filas; i++)
        delete matriz [i];
    delete [] matriz;
}

template <typename T>
Matriz<T>::Matriz(const Matriz& mat)
//Constructor por copia de la clase
{
    *this = mat;
}

template <typename T>
void Matriz<T>::Inicializar_aleatoriamente ()
//Como su nombre lo indica, carga las matriz con valores aleatorios
{
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            matriz[i][j] = rand () % 10;

    srand (time (NULL));
}

template <typename T>
void Matriz<T>::Sumar (const Matriz& B, const Matriz& C)
//Suma y resta (abajo) implementadas con la extension de funcionalidad de los operadores + y -
{
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            C.matriz[i][j] = matriz[i][j] + B.matriz[i][j];
}

template <typename T>
void Matriz<T>::Restar (const Matriz& B, const Matriz& C)
{
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            C.matriz[i][j] = matriz[i][j] - B.matriz[i][j];
}

template <typename T>
void Matriz<T>::Strassen_2x2 (const Matriz& B, const Matriz& C)
//Aplico el algoritmo de Strassen al minimo caso (matriz de 2x2)
{
    T a, b, c, d, e, f, g;

    a = (matriz[0][0] + matriz[1][1]) * (B.matriz[0][0] + B.matriz[1][1]);
    b = (matriz[1][0] + matriz[1][1]) * B.matriz[0][0];
    c = matriz[0][0] * (B.matriz[0][1] - B.matriz[1][1]);
    d = matriz[1][1] * (B.matriz[1][0] - B.matriz[0][0]);
    e = (matriz[0][0] + matriz[0][1]) * B.matriz[1][1];
    f = (matriz[1][0] - matriz[0][0]) * (B.matriz[0][0] + B.matriz[0][1]);
    g = (matriz[0][1] - matriz[1][1]) * (B.matriz[1][0] + B.matriz[1][1]);

    C.matriz[0][0] = a + d - e + g;
    C.matriz[0][1] = c + e;
    C.matriz[1][0] = b + d;
    C.matriz[1][1] = a + c - b + f;
}

template <typename T>
void Matriz<T>::Cargar_submatrices (const Matriz& M11, const Matriz& M12, const Matriz& M21, const Matriz& M22) const
//Cargo las submatrices definidas previamente con los valores de la matriz original
{
    int n = filas;
    for (int i = 0; i < n/2; i++)
        for (int j = 0; j < n/2; j++){
            M11.matriz[i][j] = matriz[i][j];
            M12.matriz[i][j] = matriz[i][j + n/2];
            M21.matriz[i][j] = matriz[i + n/2][j];
            M22.matriz[i][j] = matriz[i + n/2][j + n/2];
        }
}

template <typename T>
void Matriz<T>::Combinar_submatrices (const Matriz& M11, const Matriz& M12, const Matriz& M21, const Matriz& M22) const
//Metodo que combina las submatrices en la matriz final
{
    int n = filas;
    for (int i = 0; i < n/2; i++)
        for (int j = 0; j < n/2; j++){
            matriz[i][j] = M11.matriz[i][j];
            matriz[i][j + n/2] = M12.matriz[i][j];
            matriz[i + n/2][j] = M21.matriz[i][j];
            matriz[i + n/2][j + n/2] = M22.matriz[i][j];
        }
}

template <typename T>
void Matriz<T>::Strassen (const Matriz& B, const Matriz& C)
//Metodo del que derivan los anteriores. Aplica Strassen a la multiplicacion de matrices
{
    Matriz A11(k-1); Matriz A12(k-1); Matriz A21(k-1); Matriz A22(k-1); Matriz B11(k-1); Matriz B12(k-1); Matriz B21(k-1);
    Matriz B22(k-1); Matriz C11(k-1); Matriz C12(k-1); Matriz C21(k-1); Matriz C22(k-1); //Definicion de submatrices

    Matriz I(k-1); Matriz II(k-1); Matriz III(k-1); Matriz IV(k-1); Matriz V(k-1); Matriz VI(k-1); Matriz VII(k-1); //Matrices necesarias para las operaciones de Strassen
    Matriz RA(k-1); Matriz RB(k-1); //Matrices auxiliares para guardar resultados de las operaciones anteriores

    if (k == 1)
        Strassen_2x2 (B, C); //Strassen aplicado a matrices de 2x2

    else {
        //Cargo las submatrices con los valores de las matrices originales
        Cargar_submatrices(A11, A12, A21, A22);
        B.Cargar_submatrices(B11, B12, B21, B22);

        //Resuelvo las operaciones de Strassen
        A11.Sumar(A22, RA);
        B11.Sumar(B22, RB);
        RA.Strassen (RB, I); //Primera operacion de Strassen-> (A11 + A22)(B11 + B22)

        A21.Sumar(A22, RA);
        RA.Strassen (B11, II); //Segunda operacion-> (A21 + A22)B11

        B12.Restar(B22, RB);
        A11.Strassen (RB, III); //Tercera operacion-> A11(B12 - B22)

        B21.Restar(B11, RB);
        A22.Strassen (RB, IV); //Cuarta operacion-> A22(B21 - B11)

        A11.Sumar(A12, RA);
        RA.Strassen (B22, V); //Quinta operacion-> (A11 + A12)B22

        A21.Restar(A11, RA);
        B11.Sumar(B12, RB);
        RA.Strassen (RB, VI); //Sexta operacion-> (A21 - A11)(B11 + B12)

        A12.Restar(A22, RA);
        B21.Sumar(B22, RB);
        RA.Strassen (RB, VII); //Septima operacion-> (A12 - A22)(B21 + B22)

        //Operaciones de Strassen que arman la matriz resultado
        I.Sumar(IV, RA);
        RA.Restar(V, RB);
        RB.Sumar(VII, C11); //C11 = I + IV - V + VII

        III.Sumar(V, C12); //C12 = III + V;

        II.Sumar(IV, C21); //C21 = II + IV;

        I.Sumar(III, RA);
        RA.Restar(II, RB);
        RB.Sumar(VI, C22); //C22 = I + III - II + VI

        C.Combinar_submatrices (C11, C12, C21, C22);
    }
}

template <typename T>
void Matriz<T>::Multiplicar (const Matriz& B, const Matriz& C)
{
    if (k == B.k && k == C.k)
        Strassen (B, C);
    else
        //En esta parte podrian agregarse filas y/o columnas de ceros para completar una o las dos matrices implicadas y poder
        //realizar la multiplicacion normalmente
        cout << "Las matrices no se pueden multiplicar por tener dimensiones diferentes" << endl;
}

template <typename T>
T Matriz<T>::Devolver_elemento (int fila, int columna) const
{
    return matriz[fila][columna];
}

template class Matriz<int>;
template class Matriz<float>;
template class Matriz<double>;
template class Matriz<char>;


