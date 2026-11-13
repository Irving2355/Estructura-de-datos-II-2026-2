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
    Bibloteca(){
        libros.max_load_factor(0.75f);
        libros.rehash(11);
    }

    bool registrarSocio(int matricula){
        if(matricula <= 0) return false;
        return socios.insert(matricula).second;
    }

    bool agregarLibro(int codigo, const string& titulo, const string& autor){
        if(codigo <= 0 || titulo.empty() || autor.empty()) return false;

        return libros.try_emplace(codigo, Libro{codigo,titulo,autor}).second;
    }

    bool actualizarLibro(int codigo, const string& titulo, const string& autor){
        if(titulo.empty()) return false;
        auto it = libros.find(codigo);
        if(it == libros.end()) return false;

        it->second.titulo = titulo;
        it->second.autor = autor;
        return true;
    }

    void buscarLibro(int codigo)const{
        auto it = libros.find(codigo);
        if(it == libros.end()){
            cout << "No esta we\n";
            return;
        }
        imprimirLibro(it->second);
    }

    bool prestarLibro(int codigo, int matricula){
        if(socios.find(matricula) == socios.end()) return false;
        if(codigo.find(codigo) == codigo.end()) return false;
        if(prestamos.find(codigo) != prestamos.end()) return false;

        prestamos[codigo] = matricula;
        return true;
    }

    bool devolverLibro(int codigo){
        return prestamos.erase(codigo) == 1;
    }

    bool eliminarLibro(int codigo){
        if(prestamos.find(codigo) != prestamos.end()) return false;
        return libros.erase(codigo) == 1;
    }

    void mostrarCatalogo() const{
        if(libros.empty()){
            cout << "No hay libros\n";
            return;
        }
        for(const auto& par : libros){
            imprimirLibro(par.second);
        }
    }

    void mostrarCatalogoOrdenado() const{
        map<int,Libro> ordenados(libros.begin(), libros.end());
        for(const auto& [codigo,libro]: ordenados){
            imprimirLibro(libro);
        }
    }
};


int main(){
    return 0;
}