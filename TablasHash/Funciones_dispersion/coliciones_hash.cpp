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
};



int main(){
    return 0;
}