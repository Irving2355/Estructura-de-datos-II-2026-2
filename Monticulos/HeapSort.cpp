#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void imprimir(const vector<int>& datos){
    cout << "[";
    for(int valor: datos){
        cout << valor << " ";
    }
    cout << "]\n";
}

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
        cout << "Ciclo bajar\n";
        imprimir(datos);
    }
}


void heapSort(vector<int>& datos){
    int n = datos.size();
    for(int i=n/2-1; i>=0; i--){
        bajar(datos, i, n);
    }

    //heapSort
    for(int fin=n-1; fin>0; fin--){
        swap(datos[0], datos[fin]);
        cout << "\n\nFin: " << fin << endl;
        imprimir(datos);
        bajar(datos, 0, fin);
    }
}

//BigO(nlogn)

int main(){
    //vector<int> datos = {90,70,80,40,20,30,60};

    srand(time(NULL));
    vector<int> datos(10);
    
    generate(datos.begin(), datos.end(),[](){
        return (rand()%100)+1;
    });

    heapSort(datos);
    cout << "Vector organizado: \n"; 
    imprimir(datos);

}