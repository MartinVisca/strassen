#include <iostream>
#include "Matriz.h"

using namespace std;

int main()
{
    Matriz<int> A(1);
    Matriz<int> B(1);
    Matriz<int> C(1);

    A.Inicializar_aleatoriamente();
    B.Inicializar_aleatoriamente();

    A.Multiplicar(B, C);

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++)
            cout << A.Devolver_elemento(i, j) << " ";
        cout << endl;
    } cout << endl;

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++)
            cout << B.Devolver_elemento(i, j) << " ";
        cout << endl;
    } cout << endl;

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++)
            cout << C.Devolver_elemento(i, j) << " ";
        cout << endl;
    } cout << endl;

    //cout << C.Devolver_elemento(0, 1);

    return 0;
}
