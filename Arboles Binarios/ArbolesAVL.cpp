#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct NodoAVL
{
    int dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;
};
//suicide linux solo VM
//ls sudo apt install sl

NodoAVL* crearNodo(int dato){
    return new NodoAVL{
        dato,nullptr,nullptr,0
    };
}

int obtenerAltura(NodoAVL* nodo){
    if(nodo == nullptr) return -1;

    return nodo->altura;
}

void actualizarAltura(NodoAVL* nodo){
    if(nodo == nullptr)
        return;
    
    nodo->altura = 1 + max(
        obtenerAltura(nodo->izquierdo),
        obtenerAltura(nodo->derecho)
    );
}

int factorBalance(NodoAVL* nodo){
    if(nodo == nullptr)
        return 0; 
    
    return obtenerAltura(nodo->izquierdo) -
    obtenerAltura(nodo->derecho);
}

int main(){
    return 0;
}