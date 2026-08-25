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

bool esOperador(const string& dato){
    return dato == "+" ||
           dato == "-" ||
           dato == "*" ||
           dato == "/";
}

//preorden generar notacion prefija
/*
(8+4)*(10-6)
*,+,8,4,-,10,6
*/
void generarPrefija(
    Nodo* nodo,
    vector<string>& expresion
){
    if(nodo == nullptr){
        return;
    }

    expresion.push_back(nodo->dato);

    generarPrefija(
        nodo->izquierdo,
        expresion
    );

    generarPrefija(
        nodo->derecho,
        expresion
    );
}

/*
Inorden
izq raiz der
8,+,4,*,10,-,6
*/

string generarInfija(Nodo* nodo){
    if(nodo == nullptr){
        return "";
    }

    //si es una hoja 
    if(
        nodo->izquierdo == nullptr &&
        nodo->derecho == nullptr
    ){
        return nodo->dato;
    }

    string izquierda = generarInfija(nodo->izquierdo);
    string derecha = generarInfija(nodo->derecho);

    return "(" +
        izquierda +
        " " +
        nodo->dato +
        " " +
        derecha +
        ")";
}

/*
Postorden
izq der raiz
8,4,+,10,6,-,*
*/
void generarPostfija(
    Nodo* nodo,
    vector<string>& expresion
){
    if(nodo == nullptr){
        return;
    }

    generarPostfija(
        nodo->izquierdo,
        expresion
    );

    generarPostfija(
        nodo->derecho,
        expresion
    );

    expresion.push_back(nodo->dato);
}

int main(){
    return 0;
}