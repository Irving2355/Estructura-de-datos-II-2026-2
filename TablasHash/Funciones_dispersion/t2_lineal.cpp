#include <iostream>
#include <vector>

using namespace std;

class HashLineal{
private:
    vector<int> claves;
    vector<bool> ocupado;

    size_t indiceInicial(int clave) const{
        const int m = static_cast<int>(claves.size());
        return static_cast<size_t>(((clave % m) + m) % m);
    }
public:
    explicit HashLineal(size_t capacidad)
     :claves(capacidad, 0), ocupado(capacidad, false){}
    
    bool insertar(int clave){
        const size_t inicio = indiceInicial(clave);
        const size_t m = claves.size();

        for(size_t intento=0; intento<m; ++intento){
            const size_t pos = (inicio+intento) % m;
            cout << "Insercion " << clave << " : reviso[" << pos << "]\n";
            if(ocupado[pos] && claves[pos] == clave){
                cout << "Ya esta we\n";
                return false;
            }
            if(!ocupado[pos]){
                claves[pos] = clave;
                ocupado[pos] = true;
                return true;
            }
        }
        cout << "Tabla llena no hay lugar\n";
        return false;
    }

    bool contiene(int clave)const{
        const size_t inicio = indiceInicial(clave);
        const size_t m = claves.size();
        for(size_t intento=0; intento<m; ++intento){
            const size_t pos = (inicio+intento)%m;
            if(!ocupado[pos]){
                return false;
            }
            if(claves[pos] == clave) return true;
        }
        return false;
    }

    void mostrar() const{
        for(size_t i =0; i<claves.size(); ++i){
            cout << "pos i: " << i << " ";
            if(ocupado[i]) cout << claves[i]; 
            else cout << " No hay nada ";
            cout << endl;
        }
    }
};

int main(void){
    HashLineal tabla(7);
    for(int clave : {10,17,26,34}){
        tabla.insertar(clave);
    }
    tabla.mostrar();

    return 0;
}