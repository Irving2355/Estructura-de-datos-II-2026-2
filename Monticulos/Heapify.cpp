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
    }
    
}

int main(){

    return 0;
}