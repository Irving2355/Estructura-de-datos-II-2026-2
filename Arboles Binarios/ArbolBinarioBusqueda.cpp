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

bool buscar(
    Nodo* raiz,
    int valor,
    int& comparaciones
){
    if(raiz == nullptr){
        return false;
    }

    comparaciones++;

    if(valor == raiz->dato){
        return true;
    }

    if(valor < raiz->dato){
        return buscar(
            raiz->izquierdo,
            valor,
            comparaciones
        );
    }

    return buscar(
        raiz->derecho,
        valor,
        comparaciones
    );
}

Nodo* minimo(Nodo* raiz){
    if(raiz == nullptr){
        return nullptr;
    }

    while (raiz->izquierdo != nullptr)
    {
        raiz = raiz->izquierdo;
    }
    return raiz;
}

Nodo* maximo(Nodo* raiz){
    if(raiz == nullptr){
        return nullptr;
    }

    while (raiz->derecho != nullptr)
    {
        raiz = raiz->derecho;
    }
    return raiz;
}

Nodo* eliminar(
    Nodo* raiz,
    int valor
){
    if(raiz == nullptr){
        return nullptr;
    }

    if(valor < raiz->dato){
        raiz->izquierdo = eliminar(raiz->izquierdo,valor);
    }else if(valor > raiz->dato){
        raiz->derecho = eliminar(raiz->derecho, valor);
    }else{
        //caso 1 no tiene hijo izq
        if(raiz->izquierdo == nullptr){
            Nodo* temp = raiz->derecho;
            delete raiz;
            return temp;
        }

        //caso 2 solo hijo a la izq
        if(raiz->derecho == nullptr){
            Nodo* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }

        //caso 3 tiene 2 hijos
        Nodo* sucesor = minimo(raiz->derecho);

        raiz->dato = sucesor->dato;
        raiz->derecho = eliminar(
            raiz->derecho,
            sucesor->dato);
    }

    return raiz;
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

    cout << "buscamos un nodo: 90"<< endl;
    int comparaciones;
    bool encontro = buscar(raiz,90,comparaciones);
    if(encontro == true){
        cout << "Si se encontro el 90 despues de " << comparaciones<<endl;
    }else{
        cout << "no se encontro."<<endl;
    }

    cout << "Se elimnina el nodo 90" << endl;
    raiz = eliminar(raiz,90);
    mostrarPorNiveles(raiz);
    return 0;
}