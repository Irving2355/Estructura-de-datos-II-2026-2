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

NodoAVL* rotacionDerecha(
    NodoAVL* y
){
    cout << "Rotacion derecha sobre "
    << y->dato << endl;

    NodoAVL* x = y->izquierdo;

    NodoAVL* subArbolTemporal = x->derecho;

    //realizamos la rotacion
    x->derecho = y;
    y->izquierdo = subArbolTemporal;

    //actualizar alturas
    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

NodoAVL* rotacionIzquierda(
    NodoAVL* x
){
    cout << "Rotacion izquierda sobre "
    << x->dato << endl;
    
    NodoAVL* y = x->derecho;
    NodoAVL* subArbolTemporal = y->izquierdo;

    //rotacion
    y->izquierdo = x;
    x->derecho = subArbolTemporal;

    actualizarAltura(x);
    actualizarAltura(y);
    return y;
}

NodoAVL* insertarAVL(
    NodoAVL* raiz,
    int valor
){
    if(raiz == nullptr){
        cout << "insertando " << valor << endl;
        return crearNodo(valor);
    }

    if(valor < raiz->dato){
        raiz->izquierdo = insertarAVL(
            raiz->izquierdo,
            valor);
    }else if(valor > raiz->dato){
        raiz->derecho = insertarAVL(
            raiz->derecho,
            valor
        );
    }else{
        return raiz;
    }

    //actualizar su altura
    actualizarAltura(raiz);

    //revisar el balance
    int balance = factorBalance(raiz);
    //caso LL
    if(balance > 1 &&
    valor < raiz->izquierdo->dato){
        cout << "Caso LL " << raiz->dato << endl;
        return rotacionDerecha(raiz);
    }

    //caso RR
    if(balance < -1 &&
    valor > raiz->derecho->dato){
        cout << "Caso RR " << raiz->dato << endl;
        return rotacionIzquierda(raiz);
    }

    //caso LR
    if(balance > 1 &&
    valor > raiz->izquierdo->dato){
        cout << "Caso LR " << raiz->dato << endl;
        raiz->izquierdo = rotacionIzquierda(raiz->izquierdo);
        return rotacionDerecha(raiz);
    }

    //caso RL
    if(balance < -1 &&
    valor < raiz->derecho->dato){
        cout << "Caso RL " << raiz->dato << endl;
        raiz->derecho = rotacionDerecha(raiz->derecho);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

NodoAVL* construirAVL(
    const vector<int>& datos
){
    NodoAVL* raiz = nullptr;
    for(int valor : datos){
        raiz = insertarAVL(raiz,valor);
        cout << endl;
    }
    return raiz;
}

void mostrarPorNiveles(
    NodoAVL* raiz
){
    if(raiz == nullptr){
        return;
    }

    queue<NodoAVL*> cola;

    cola.push(raiz);

    int nivel = 0;

    while(!cola.empty()){
        int cantidad = cola.size();
        cout << "Nivel " << nivel << ": ";
        for(int i=0; i<cantidad; i++){
            NodoAVL* actual = cola.front();
            cola.pop();

            cout << actual->dato << "(h= "
            << actual->altura << ". FB= "
            << factorBalance(actual) << ")";

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

    vector<int> datos = {1,2,3,4,5,6,7,8};
    NodoAVL* avl = construirAVL(datos);
    cout << "Arbol AVL:" << endl;
    mostrarPorNiveles(avl);
    return 0;
}