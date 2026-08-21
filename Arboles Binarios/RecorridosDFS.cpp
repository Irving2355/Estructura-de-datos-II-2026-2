#include <iostream>
#include <vector>

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

//raiz izq der
void preorden(
    Nodo* nodo,
    vector<char>& recorrido
){
    if(nodo == nullptr){
        return;
    }

    recorrido.push_back(nodo->dato);

    preorden(
        nodo->izquierdo,
        recorrido
    );

    preorden(
        nodo->derecho,
        recorrido
    );
}

//izq raiz der
void inorden(
    Nodo* nodo,
    vector<char>& recorrido
){
    if(nodo == nullptr){
        return;
    }

    inorden(
        nodo->izquierdo,
        recorrido
    );

    recorrido.push_back(nodo->dato);

    inorden(
        nodo->derecho,
        recorrido
    );
}

//izq der raiz
void postorden(
    Nodo* nodo,
    vector<char>& recorrido
){
    if(nodo == nullptr){
        return;
    }

    postorden(
        nodo->izquierdo,
        recorrido
    );

    postorden(
        nodo->derecho,
        recorrido
    );

    recorrido.push_back(nodo->dato);
}

void mostrarRecorrido(
    const vector<char>& recorrido
){
    for(char dato: recorrido){
        cout << dato << " ";
    }
    cout << endl;
}

int main(){
    Nodo* raiz = crearNodo('A');

    raiz->izquierdo = crearNodo('B');
    raiz->derecho = crearNodo('C');

    raiz->izquierdo->izquierdo = crearNodo('D');
    raiz->derecho->derecho = crearNodo('E');

    vector<char> recorrido;

    cout << "Preorden: " << endl;
    preorden(raiz, recorrido);
    mostrarRecorrido(recorrido);
    recorrido.clear();

    cout << "inorden: " << endl;
    inorden(raiz, recorrido);
    mostrarRecorrido(recorrido);
    recorrido.clear();

    cout << "Postorden: " << endl;
    postorden(raiz, recorrido);
    mostrarRecorrido(recorrido);
    return 0;
}