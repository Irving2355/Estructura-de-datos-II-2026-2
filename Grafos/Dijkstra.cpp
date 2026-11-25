#include <algorithm>
#include <functional>
#include <limits>
#include <utility>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

using Arista = pair<int, int>;
using Grafo = vector<vector<Arista>>;
using Estado = pair<long long, int>; //distancia,vertices

struct Resultado
{
    vector<long long> distancia;
    vector<int> padre;
};

void conectar(Grafo& grafo,int a,int b, int costo){
    grafo[a].push_back({b, costo});
    grafo[b].push_back({a, costo});
}

Resultado dijkstra(const Grafo& grafo, int origen){
    const long long INF = numeric_limits<long long>::max()/4;
    Resultado resultado{
        vector<long long>(grafo.size(), INF),
        vector<int>(grafo.size(), -1)
    };

    priority_queue<Estado, vector<Estado>,
        greater<Estado>> pendientes;
    
    resultado.distancia[origen] = 0;
    pendientes.push({0, origen});

    while (!pendientes.empty())
    {
        auto [distanciaActual, actual] = pendientes.top();
        pendientes.pop();
        
        if(distanciaActual != resultado.distancia[actual]) continue;

        for(const auto& [vecino, costo] : grafo[actual]){
            long long nueva = distanciaActual + costo;
            if(nueva < resultado.distancia[vecino]){
                resultado.distancia[vecino] = nueva;
                resultado.padre[vecino] = actual;
                pendientes.push({nueva, vecino});
            }
        }
    }
    return resultado;
}

vector<int> construirCamino(int destino, 
    const vector<int>& padre){
    
    vector<int> camino;
    for(int v=destino; v!=-1; v=padre[v]){
        camino.push_back(v);
    }

    reverse(camino.begin(), camino.end());
    return camino;
}

void bloquearConexion(Grafo& grafo, int a, int b){
    auto quitar = [](vector<Arista>& lista, int destino){
        lista.erase(
            remove_if(lista.begin(), lista.end(),
                [destino](const Arista& arista){
                    return arista.first == destino;
                }),
            lista.end()
        );
    };

    quitar(grafo[a], b);
    quitar(grafo[b], a);
}

void mostrarRuta(const Grafo& grafo, int origen, int destino, const vector<string>& nombres){
    const long long INF = numeric_limits<long long>::max()/4;
    Resultado resultado = dijkstra(grafo,origen);

    if(resultado.distancia[destino] == INF){
        cout << "\nNo existe el camino\n";
        return;
    }

    vector<int> camino = construirCamino(destino,resultado.padre);

    cout << "Ruta: ";
    for(size_t i=0; i<camino.size(); ++i){
        if(i>0) cout << " -> ";
        cout << nombres[camino[i]];
    }
    cout << "\n\nCosto total: " << resultado.distancia[destino] << "\n";
}

int main(){
    vector<string> nombres={
        "Craft", "Garden", "Billar", "ChuyBombas",
        "PlayaMamitas", "CheveChuy", "OXXO", "C4",
        "Salida"
    };
    Grafo grafo(nombres.size());
    conectar(grafo, 0, 3, 2);
    conectar(grafo, 4, 1, 4);
    conectar(grafo, 0, 8, 4);
    conectar(grafo, 3, 5, 1);
    conectar(grafo, 3, 1, 7);
    conectar(grafo, 1, 4, 3);
    conectar(grafo, 4, 5, 5);
    conectar(grafo, 6, 7, 0);
    conectar(grafo, 6, 8, 8);

    cout << "Original\n";
    mostrarRuta(grafo,0,8,nombres);

    cout << "\nPrueba Craft a PlayaMamitas\n";
    mostrarRuta(grafo, 0, 4, nombres);

    bloquearConexion(grafo, 3, 5);
    cout << "\nModificado\n";
    mostrarRuta(grafo,0,8,nombres);
    cout << "\nPrueba Craft a PlayaMamitas\n";
    mostrarRuta(grafo, 0, 4, nombres);

    return 0;
}