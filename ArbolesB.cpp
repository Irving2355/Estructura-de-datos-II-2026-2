#include <iostream>
#include <vector>

using namespace std;

class NodoB{
public:
    vector<int> clave;
    vector<NodoB*> hijos;
    bool hoja;
    
    //grado minimo
    int t;

    NodoB(
        int gradoMinimo,
        bool esHoja
    ): hoja(esHoja),t(gradoMinimo){}

    /*NodoB(int gradoMinimo, bool esHoja){
        this->hoja = esHoja;
        this->t = gradoMinimo;
    }*/

    ~NodoB(){//limpiarMemoria()
        for(NodoB* hijo : hijos){
            delete hijo;
        }
    }

    void recorrer(){
        size_t i = 0;

        for(i = 0; i<clave.size(); i++){
            if(!hoja){
                hijos[i] ->recorrer();
            }
            cout << clave[i] << " ";
        }

        if(!hoja){
            hijos[i]->recorrer();
        }
    }

    NodoB* buscar(int valor, int& accesoBloque){
        accesoBloque++;
        size_t i = 0;
        while (i < clave.size() &&
            valor > clave[i])
        {
            i++;
        }
        
        if(i < clave.size() && clave[i] == valor){
            return this;
        }

        if(hoja){
            return nullptr;
        }

        return hijos[i]->buscar(valor, accesoBloque);
    }

};

int main(){
    return 0;
}