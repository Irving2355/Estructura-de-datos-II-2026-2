#include <cstddef>          //size_t
#include <functional>       //hash funcion de dispercion
#include <iostream>         
#include <map>              //map claves ordenadas
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

class Biblioteca{
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
    Biblioteca(){
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
        if(libros.find(codigo) == libros.end()) return false;
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

    void mostrarEstadoHash() const{
        cout << "Libros registrados: " << libros.size() << endl;
        cout << "Cubetas: " << libros.bucket_count() << endl;
        cout << "Factor de carga " << libros.load_factor() << endl;
        cout << "Factor maximo de carga " << libros.max_load_factor() << endl;
    }

    void reservarCapacidad(size_t cantidad){
        libros.reserve(cantidad);
    }

    void redistribuir(){
        libros.rehash(libros.bucket_count() * 2 + 1);
    }
};


int main() {
    Biblioteca biblioteca;

    // Datos de arranque del MISMO sistema (no son miniprogramas separados).
    biblioteca.registrarSocio(501);
    biblioteca.registrarSocio(502);
    biblioteca.agregarLibro(10, "Estructuras de datos", "Autor A");
    biblioteca.agregarLibro(17, "Algoritmos", "Autor B");
    biblioteca.agregarLibro(24, "Programacion en C++", "Autor C");
    // 10, 17 y 24 causan colision con HashDidactico.

    int opcion;
    do {
        cout << "\nBIBLIOTECA / TABLAS HASH\n"
                  << "1. Registrar socio\n"
                  << "2. Agregar libro\n"
                  << "3. Actualizar libro\n"
                  << "4. Buscar libro\n"
                  << "5. Prestar libro\n"
                  << "6. Devolver libro\n"
                  << "7. Eliminar libro\n"
                  << "8. Mostrar catalogo (unordered_map)\n"
                  << "9. Mostrar catalogo ordenado (map)\n"
                  << "10. Ver cubetas y factor de carga\n"
                  << "11. Reservar capacidad (reserve)\n"
                  << "12. Redistribuir cubetas (rehash)\n"
                  << "0. Salir\nOpcion: ";
        if (!(cin >> opcion)) break;

        int codigo;
        int matricula;
        string titulo;
        string autor;

        switch (opcion) {
            case 1:
                cout << "Matricula: ";
                cin >> matricula;
                cout << (biblioteca.registrarSocio(matricula)
                                  ? "Socio registrado.\n" : "No se registro (duplicado o invalido).\n");
                break;
            case 2:
            case 3:
                cout << "Codigo: ";
                cin >> codigo;
                // ws descarta el salto de linea antes de leer un titulo con espacios.
                cout << "Titulo: ";
                getline(cin >> ws, titulo);
                cout << "Autor: ";
                getline(cin, autor);
                if (opcion == 2)
                    cout << (biblioteca.agregarLibro(codigo, titulo, autor)
                                      ? "Libro agregado.\n" : "No se pudo agregar.\n");
                else
                    cout << (biblioteca.actualizarLibro(codigo, titulo, autor)
                                      ? "Libro actualizado.\n" : "No se pudo actualizar.\n");
                break;
            case 4:
                cout << "Codigo: ";
                cin >> codigo;
                biblioteca.buscarLibro(codigo);
                break;
            case 5:
                cout << "Codigo del libro: ";
                cin >> codigo;
                cout << "Matricula del socio: ";
                cin >> matricula;
                cout << (biblioteca.prestarLibro(codigo, matricula)
                                  ? "Prestamo realizado.\n" : "Prestamo rechazado.\n");
                break;
            case 6:
                cout << "Codigo: ";
                cin >> codigo;
                cout << (biblioteca.devolverLibro(codigo)
                                  ? "Libro devuelto.\n" : "No existe prestamo.\n");
                break;
            case 7:
                cout << "Codigo: ";
                cin >> codigo;
                cout << (biblioteca.eliminarLibro(codigo)
                                  ? "Libro eliminado.\n" : "No existe o esta prestado.\n");
                break;
            case 8:
                biblioteca.mostrarCatalogo();
                break;
            case 9:
                biblioteca.mostrarCatalogoOrdenado();
                break;
            case 10:
                biblioteca.mostrarEstadoHash();
                break;
            case 11: {
                size_t cantidad;
                cout << "Capacidad estimada de libros: ";
                cin >> cantidad;
                biblioteca.reservarCapacidad(cantidad);
                biblioteca.mostrarEstadoHash();
                break;
            }
            case 12:
                biblioteca.redistribuir();
                biblioteca.mostrarEstadoHash();
                break;
            case 0:
                cout << "Hasta luego.\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}