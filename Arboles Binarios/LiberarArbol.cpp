#include <iostream>
using namespace std;

struct Nodo{
    char dato;
    Nodo* izquierdo;
    Nodo* derecho;
};

Nodo* crearNodo(char dato){
    Nodo* nuevo = new Nodo;

    nuevo->dato = dato;

    nuevo->izquierdo = nullptr;
    nuevo->derecho = nullptr;

    return nuevo;
}

void liberarMemoria(Nodo* nodo){
    if(nodo == nullptr){
        return;
    }

    liberarMemoria(nodo->izquierdo);
    liberarMemoria(nodo->derecho);

    cout << "Liberando nodo: "
         << nodo->dato
         << endl;
    delete nodo;
}

int main(){
    Nodo* raiz = crearNodo('A');

    raiz->izquierdo = crearNodo('B');
    raiz->derecho = crearNodo('C');

    raiz->izquierdo->izquierdo = crearNodo('D');
    raiz->derecho->derecho = crearNodo('E');
    
    return 0;
}