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

    //que tan grande el vector de claves para dividir
    //2t - 1 
    void dividirHijo(int indice, NodoB* lleno){
        NodoB* nuevo = new NodoB(
            lleno->t,
            lleno->hoja
        );

        int mediana = lleno->clave[t-1];

        //copiar la mitad derecha
        for(int j=0; j<t-1; j++){
            nuevo->clave
            .push_back(lleno->clave[j+t]);
        }

        if(!lleno->hoja){
            for(int j=0; j<t; j++){
                nuevo->hijos
                .push_back(lleno->hijos[j+t]);
            }
        }

        //el nodo original conserve la parte izq
        lleno->clave.resize(t-1);

        if(!lleno->hoja){
            lleno->hijos.resize(t);
        }

        hijos.insert(
            hijos.begin() + indice + 1,
            nuevo
        );

        //subimos la mediana al padre
        clave.insert(
            clave.begin() + indice,
            mediana
        );
    }

    void insertarNoLleno(int valor){
        int i = static_cast<int>(clave.size())-1;

        if(hoja){
            clave.push_back(0);

            while (i >= 0 && valor<clave[i])
            {
                clave[i+1] = clave[i];
                i--;
            }

            clave[i+1]=valor;
            
        }else{
            while (i>=0 && valor<clave[i])
            {
                i--;
            }
            i++;

            if(hijos[i]->clave.size() == 
            static_cast<size_t>(2*t -1)){
                dividirHijo(i,hijos[i]);

                if(valor > clave[i]){
                    i++;
                }
            }

            hijos[i]->insertarNoLleno(valor);
        }
    }

};

int main(){
    return 0;
}