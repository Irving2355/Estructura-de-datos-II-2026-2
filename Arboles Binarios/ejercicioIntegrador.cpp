#include <iostream>
#include <vector>
#include <string>

using namespace std;

//escrituraCamelUsandoMayus
struct Nodo
{
    string dato;
    Nodo* izquierdo;
    Nodo* derecho;
};

Nodo* crearNodo(string dato){
    Nodo* nuevo = new Nodo;

    nuevo->dato = dato;
    nuevo->izquierdo = nullptr;
    nuevo->derecho = nullptr;
    return nuevo;
}

int main(){
    return 0;
}