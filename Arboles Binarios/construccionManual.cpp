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

int main(){
    Nodo* raiz = crearNodo('A');

    raiz->izquierdo = crearNodo('B');
    raiz->derecho = crearNodo('C');

    raiz->izquierdo->izquierdo = crearNodo('D');
    raiz->derecho->derecho = crearNodo('E');
    //comentario de prueba
    return 0;
}