#include <iostream>
#include <vector>
using namespace std;

int padre(int i){
    return (i-1)/2;
}

int hijoIzq(int i){
    return 2*i + 1;
}

int hijoDer(int i){
    return 2*i + 2;
}

int main(){
    vector<int> heap = {90,70,60,40,20,30,10};

    cout << "Contenido del vector:\n";

    for(int i=0; i<heap.size(); i++){
        cout << "[" << i << "] = " << heap[i] << endl; 
    }

    int pos = 3;
    cout << "\nPosicion 3: " << heap[3] << endl;

    if(pos != 0){
        int p = padre(pos);
        cout << "Padre: " << heap[p] <<
        "(indice " << p << ")\n";
    }

    int izq = hijoIzq(pos);
    int der = hijoDer(pos);

    if(izq < heap.size()){
        cout << "Hijo izq: " << heap[izq] <<
        "(indice " << izq << ")\n";
    }

    if(der < heap.size()){
        cout << "Hijo der: " << heap[der] <<
        "(indice " << der << ")\n";
    }
    return 0;
}