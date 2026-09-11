#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

struct Alumnos
{
    int matricula;
    string nombre;
    string carrera;
};

void mostrarAlumno(
    const Alumnos& alumno
){
    cout << alumno.matricula 
    << " | " 
    << alumno.nombre
    << " | "
    << alumno.carrera << endl;
}

int main(){
    vector<Alumnos> datos = {
        {
            1045, "Ana", "ISC"
        },
        {
            1080, "Juan", "ISC"
        },
        {
            1010, "Omar", "ISC"
        },
        {
            1001, "Ivan", "ISC"
        },
        {
            1035, "Josue", "ISC"
        },
        {
            1052, "Brian", "ISC"
        }
    };

    map<int, Alumnos> indice;

    set<int> matriculas;

    for(
        const Alumnos& alumno : datos
    ){
        auto resultado = matriculas.insert(alumno.matricula);

        if(!resultado.second){
            cout << "Matricula repetida: "
            << alumno.matricula << endl;
            continue;
        }
        
        indice[alumno.matricula] = alumno;
    }

    cout << "Alumnos ordenados por matricula" <<endl;
    for(const auto& elemento : indice){
        mostrarAlumno(elemento.second);
    }

    int buscada = 1060;
    cout << "\nBuscar matricula "  << buscada << endl;
    
    auto encontrado = indice.find(buscada);

    if(encontrado != indice.end()){
        mostrarAlumno(encontrado->second);
    }else{
        cout << "\nNo se encontro\n";
    }

    cout << "\nRango 1020-1060\n";
    auto inicio = indice.lower_bound(1020);
    auto fin = indice.upper_bound(1060);

    for(auto it = inicio; it != fin; ++it){
        mostrarAlumno(it->second);
    }

    int eliminar = 1035;
    cout << "\nEliminando " << eliminar << endl;
    indice.erase(eliminar);
    matriculas.erase(eliminar);

    cout << "Alumnos actualizados" <<endl;
    for(const auto& elemento : indice){
        mostrarAlumno(elemento.second);
    }
    return 0;
}