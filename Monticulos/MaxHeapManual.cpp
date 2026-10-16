#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MaxHeap{
private:
    vector<int> datos;

    int padre(int i){
        return (i-1)/2;
    }
public:
    void insertar(int valor){
        //el nuevo elemento siempre al final
        datos.push_back(valor);

        //subimos mientreas el elemento sea mayor
        int actual = datos.size() - 1;
        while (actual > 0)
        {
            int p = padre(actual);

            if(datos[p] >= datos[actual]){
                break;
            }

            swap(datos[p], datos[actual]);

            actual = p;
        }
    }

    void imprimir(){
        //for(int i=0; i<datos.size(); i++)
        for(int valor : datos){
            cout << valor << " ";
        }
        cout << endl;
    }
};

int main(){
    MaxHeap heap;
    vector<int> datos = {20,50,10,80,40,70,30};
    for(int valor:datos){
        heap.insertar(valor);
    }

    heap.imprimir();
    return 0;
}