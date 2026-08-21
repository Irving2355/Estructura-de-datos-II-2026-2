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

int contarNodos(Nodo* nodo){
    if(nodo == nullptr){
        return 0;
    }

    return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
}

int contarHojas(Nodo* nodo){
    if(nodo == nullptr){
        return 0;
    }

    if(
        nodo->izquierdo == nullptr &&
        nodo->derecho == nullptr
    ){
        return 1;
    }

    return contarHojas(nodo->izquierdo) + contarHojas(nodo->derecho);
}

int altura(Nodo* nodo){
    if(nodo == nullptr)
        return -1;
        //return 0;
    
    int izq = altura(nodo->izquierdo);
    int der = altura(nodo->derecho);

    return 1 + max(izq, der);
}

int main(){
    Nodo* raiz = crearNodo('A');

    raiz->izquierdo = crearNodo('B');
    raiz->derecho = crearNodo('C');

    raiz->izquierdo->izquierdo = crearNodo('D');
    raiz->derecho->derecho = crearNodo('E');
    //comentario de prueba

    cout << "altura: " << altura(raiz) << endl;
    return 0;
}