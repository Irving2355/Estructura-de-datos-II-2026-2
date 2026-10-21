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
    return 0;
}