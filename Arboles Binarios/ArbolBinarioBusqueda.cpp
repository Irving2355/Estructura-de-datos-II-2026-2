#include <iostream>
#include <locale.h>
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
        dato,nullptr,nullptr
    };
}

Nodo* insertar(
    Nodo *raiz,
    int valor
){
    if(raiz == nullptr){
        return crearNodo(valor);
    }

    if(valor < raiz->dato){
        raiz->izquierdo = insertar(
            raiz->izquierdo,
            valor
        );
    }else if(valor > raiz->dato){
        raiz->derecho = insertar(
            raiz->derecho,
            valor
        );
    }
    return raiz;
}

Nodo* construirBTS(
    const vector<int>& datos
){
    Nodo* raiz = nullptr;

    for(int valor: datos){
        raiz = insertar(
            raiz,
            valor
        );
    }

    return raiz;
}

void mostrarPorNiveles(
    Nodo* raiz
){
    if(raiz == nullptr){
        return;
    }

    queue<Nodo*> cola;

    cola.push(raiz);

    int nivel = 0;

    while(!cola.empty()){
        int cantidad = cola.size();
        cout << "Nivel " << nivel << ": ";
        for(int i=0; i<cantidad; i++){
            Nodo* actual = cola.front();
            cola.pop();

            cout << actual->dato << "\t";
            if(actual->izquierdo != nullptr){
                cola.push(actual->izquierdo);
            }

            if(actual->derecho != nullptr){
                cola.push(actual->derecho);
            }
        }//fin for
        cout << endl;
        nivel++;
    }//fin del while
}

int main(){
    setlocale(LC_ALL, "spanish");
    cout << "ñóáéú";

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

    Nodo* raiz = construirBTS(datos);

    cout << "Arbol original: " << endl;
    mostrarPorNiveles(raiz);
    cout << endl << endl;
    return 0;
}