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

double evaluar(Nodo* nodo){
    if(
        nodo->izquierdo == nullptr &&
        nodo->derecho == nullptr
    ){
        return stod(nodo->dato);
    }

    double izq = evaluar(nodo->izquierdo);
    double der = evaluar(nodo->derecho);

    if(nodo->dato == "+"){
        return izq + der;
    }

    if(nodo->dato == "-"){
        return izq - der;
    }

    if(nodo->dato == "*"){
        return izq * der;
    }

    if(nodo->dato == "/"){
        return izq / der;
    }

    return 0;

    /*switch(nodo->dato){
        case '+': return izq + der;
                  break;
    }*/
}

void mostrar(
    const vector<string>& datos
){
    for(const string& dato: datos){
        cout << dato << " ";
    }
    cout << endl;
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

    Nodo* raiz = crearNodo("*");
    raiz->izquierdo = crearNodo("+");
    raiz->derecho = crearNodo("-");
    raiz->izquierdo->izquierdo = crearNodo("8");
    raiz->izquierdo->derecho = crearNodo("4");

    raiz->derecho->izquierdo = crearNodo("10");
    raiz->derecho->derecho = crearNodo("6");

    vector<string> prefija;
    generarPrefija(raiz,prefija);

    vector<string> postfija;
    generarPostfija(raiz,postfija);

    string infija = generarInfija(raiz);

    cout << "Expresion original: "<< endl;
    cout << infija << endl;

    cout << "Notacion prefija: " << endl;
    mostrar(prefija);

    cout << "Notacion postfija: " << endl;
    mostrar(postfija);

    double res = evaluar(raiz);

    cout << "Resultado de la expresion: "<<endl;
    cout << res << endl;

    liberarMemoria(raiz);
    raiz = nullptr;
    return 0;
}