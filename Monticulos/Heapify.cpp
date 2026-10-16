#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bajar(vector<int>& datos, int posicion, int n){
    while (true)
    {
        int mayor = posicion;
        int izq = 2*posicion+1;
        int der = 2*posicion+2;

        if(izq < n && datos[izq] > datos[mayor]){
            mayor = izq;
        }

        if(der < n && datos[der] > datos[mayor]){
            mayor = der;
        }

        if(mayor == posicion){
            break;
        }

        swap(datos[posicion], datos[mayor]);
        posicion = mayor;
    }
}

void construirHeap(vector<int>& datos){
    int n = datos.size();
    for(int i = n/2-1; i>=0; i--){
        bajar(datos, i, n);
    }
}

void imprimir(const vector<int>& datos){
    cout << "[";
    for(int valor: datos){
        cout << valor << " ";
    }
    cout << "]\n";
}

int main(){
    vector<int> datos = {20,50,10,80,40,70,30};

    cout << "\nMaxHeap:\n";
    construirHeap(datos);
    imprimir(datos);

    return 0;
}