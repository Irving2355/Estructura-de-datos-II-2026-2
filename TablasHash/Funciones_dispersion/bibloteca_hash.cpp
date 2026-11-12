#include <cstddef>          //std::size_t
#include <functional>       //std::hash funcion de dispercion
#include <iostream>         
#include <map>              //std::map claves ordenadas
#include <string>
#include <unordered_map>    //Clave -> valor con hash
#include <unordered_set>    //Claves unicas con hash

using namespace std;

struct Libro
{
    int codigo;
    string titulo;
    string autor;
};

ostream& operator<<(ostream& salida, const Libro& libro){
    salida << "[" << libro.codigo << "] " << libro.titulo
    << " - " << libro.autor;
    return salida;  
}

struct HashDidactico{
    size_t operator()(int codigo) const noexcept{
        return hash<int>{}(codigo) % 7;
    }
};

class Bibloteca{
private:
    unordered_map<int, Libro, HashDidactico> libros;
    unordered_set<int> socios;
    unordered_map<int, int> prestamos;

    void imprimirLibro(const Libro& libro)const{
        cout << libro;
        auto it = prestamos.find(libro.codigo);
        if(it == prestamos.end()){
            cout << " Disponible\n";
        }else{
            cout << " Prestado al socio " << it->second << endl;
        }
    }

public:
    
};


int main(){
    return 0;
}