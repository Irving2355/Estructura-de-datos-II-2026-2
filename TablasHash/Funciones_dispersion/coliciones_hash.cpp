#include <algorithm> //std::find
#include <iostream>
#include <iomanip>  //std::setprecision
#include <stdexcept>
#include <string>
#include <vector>

struct Registro
{
    int clave;
    std::string nombre;
};

bool operator==(const Registro& a, const Registro& b){
    return a.clave == b.clave;
}

std::ostream& operator<<(std::ostream& salida, const Registro& r){
    salida << "[ " << r.clave << ": " << r.nombre << " ]";
    return salida;
}

class Laboratorio
{
private:
    int m;
    std::vector<int> frecuencia;
    std::vector<Registro> datos;
    int colisiones = 0;

    int indice(int clave){
        return ((clave % m) + m) % m;
    }
public:
    explicit Laboratorio(int capacidad)
        :m(capacidad),
        frecuencia(capacidad > 0 ? capacidad : 0, 0){
            if(m <= 0) throw std::invalid_argument("m debe de ser positivo");
        }
    
    void registrar(const Registro& nuevo){
        auto it = std::find(datos.begin(), datos.end(), nuevo);
        if(it != datos.end()){
            *it = nuevo;
            std::cout << "Actualizacion: " << nuevo << "\n";
            return;
        }

        const int pos = indice(nuevo.clave);
        if(frecuencia[pos] > 0){
            ++colisiones;
            std::cout << "Colision en indice " << pos << "\n";
        }

        ++frecuencia[pos];
        datos.push_back(nuevo);
        std::cout << "Nueva clave: " << nuevo  << "\n";
    }

    void mostrar() const{
        std::cout << "\nCubeta: cantidad de claves\n";
        for(int i=0; i<m; i++){
            std::cout << i << ": " << frecuencia[i] << "\n";
        }

        std::cout << "Elementos: " << datos.size() << "\n";
        std::cout << "Factor de carga: " << std::fixed
            << std::setprecision(3)
            <<static_cast<double>(datos.size())/m << "\n";
        std::cout << "Evidencia de colision: " << colisiones<< "\n";
    }
};



int main(){
    Laboratorio nombres(7);
    nombres.registrar({0, "Pedro"});
    nombres.registrar({18, "Isai"});
    nombres.registrar({34, "Horacio"});
    nombres.registrar({9, "Pancho"});
    nombres.registrar({32, "Prime"});
    nombres.mostrar();
    return 0;
}