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

vector<vector<int>> obtenerNiveles(
    Nodo* raiz
){
    vector<vector<int>> niveles;

    if(raiz == nullptr){
        return niveles;
    }

    queue<Nodo*> cola;

    cola.push(raiz);

    while (!cola.empty())
    {
        int cantidadNivel = cola.size();

        vector<int> nivel;

        for(int i=0; i<cantidadNivel; i++){
            Nodo* actual = cola.front();

            cola.pop();

            nivel.push_back(
                actual->dato
            );

            if(actual->izquierdo != nullptr){
                cola.push(actual->izquierdo);
            }

            if(actual->derecho != nullptr){
                cola.push(actual->derecho);
            }
        }//fin for
        niveles.push_back(nivel);
    }//fin while
    return niveles;
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