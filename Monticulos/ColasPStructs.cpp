#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Proceso
{
    int id;
    string nombre;
    int prioridad;
};

struct CompararPrioridad
{
    bool operator()(const Proceso& a,
                    const Proceso& b) const{
        return a.prioridad < b.prioridad; 
    }
};

int main(){
    priority_queue<
        Proceso,
        vector<Proceso>,
        CompararPrioridad
    > procesos;

    procesos.push({1, "Compilador", 3});
    procesos.push({2, "Sistema", 5});
    procesos.push({3, "Navegador", 2});
    procesos.push({4, "Actualizacion", 4});
    procesos.push({5, "Respaldo", 1});

    cout << "Orden de ejecucion: \n";

    while (!procesos.empty())
    {
        Proceso actual = procesos.top();

        cout << "ID: " << actual.id
        << "\nProceso: " << actual.nombre
        << "\nPrioridad: " << actual.prioridad
        << endl;

        procesos.pop();
    }
    

    return 0;
}