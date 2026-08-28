#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Nodo
{
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;
};

Nodo* crearNodo(int dato){
    return new Nodo{
        dato,
        nullptr,
        nullptr
    };
}

Nodo* construirDesdeVector(
    const vector<int>& datos,
    size_t i
){
    if(i >= datos.size()){
        return nullptr;
    }

    Nodo* nodo = crearNodo(datos[i]);

    nodo->izquierdo = construirDesdeVector(
        datos,
        2 * i + 1
    );

    nodo->derecho = construirDesdeVector(
        datos,
        2 * i + 2
    );

    return nodo;
}


int main(){
    vector<int> datos = {
        50,
        90,
        20,
        10,
        80,
        30,
        70,
        5,
        15
    };
    Nodo* raiz = construirDesdeVector(datos,0);
    return 0;
}