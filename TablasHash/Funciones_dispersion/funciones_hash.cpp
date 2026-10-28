#include <iostream>
#include <stdexcept>
#include <string>

int hashModular(int clave, int m){
    if(m <= 0) throw std::invalid_argument("m debe de ser positivo");

    //(rand() + 1) % 100; 
    return ((clave % m) + m) % m;
}

//12345678 12+34+56+78=180
int hashPlegamiento(long long clave,int m){
    if(m <= 0 || clave < 0){
        throw std::invalid_argument("Datos invalidos");
    }

    std::string digitos = std::to_string(clave);

    if(digitos.size() % 2 != 0) digitos.insert(0, "0");

    long long suma = 0;
    for(std::size_t i=0; i<digitos.size(); i+=2){
        suma += std::stoi(digitos.substr(i,2));
    }

    return static_cast<int>(suma % m);
}

int hashMitadCuadrado(int clave, int m){
    if(m <= 0 || clave < 10 || clave > 99){
        throw std::invalid_argument("Use claves de 2 cifras y m > 0");
    }

    const int cuadrado = clave * clave;
    std::string digitos = std::to_string(cuadrado);
    while (digitos.size() < 4)
    {
        digitos.insert(0,"0");
    }

    const int centro = std::stoi(digitos.substr(1,2));
    return centro % m;
}

int hashCadena(const std::string& texto, int m){
    if(m <= 0){
        throw std::invalid_argument("m debe de ser positivo");
    }

    long long acumulador = 0;
    for(unsigned char c : texto){
        acumulador = (31 * acumulador + c) % m;
    }
    return static_cast<int>(acumulador);
}

int main(){
    std::cout << "Modular: " << hashModular(-9,0) << "\n";
    return 0;
}