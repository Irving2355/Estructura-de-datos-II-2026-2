#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

using Grafo = vector<vector<int>>;

struct ResultadoBFS{
    vector<int> orden;
    vector<int> distancia;
    vector<int> padre;
};

void conectar(Grafo& grafo, int a, int b){
    grafo[a].push_back(b);
    grafo[b].push_back(a);
}

ResultadoBFS bfs(const Grafo& grafo, int origen){
    ResultadoBFS resultado;

    resultado.distancia.assign(grafo.size(), -1);
    resultado.padre.assign(grafo.size(), -1);

    queue<int> pendientes;
    pendientes.push(origen);
    resultado.distancia[origen] = 0;

    while(!pendientes.empty()){
        int actual = pendientes.front();
        pendientes.pop();
        resultado.orden.push_back(actual);

        for(int vecino: grafo[actual]){
            if(resultado.distancia[vecino] != -1) continue;
            resultado.distancia[vecino] = resultado.distancia[actual] + 1;

            resultado.padre[vecino] = actual;
            pendientes.push(vecino);
        }
    }

    return resultado;
}

/*
0 0 1 0
0 0 1 0
0 1 1 0
0 1 0 0
A->C
B->C
C->B,C
D->B*/

vector<int> dfs(const Grafo& grafo, int origen){
    vector<int> orden;
    vector<bool> visitado(grafo.size(), false);
    stack<int> pendientes;
    pendientes.push(origen);

    while(!pendientes.empty()){
        int actual = pendientes.top();
        pendientes.pop();
        if(visitado[actual])continue;
        visitado[actual] = true;
        orden.push_back(actual);
        for(auto it = grafo[actual].rbegin();
        it != grafo[actual].rend(); ++it){
            if(!visitado[*it]) pendientes.push(*it);
        }
    }
    return orden;
}

vector<int> construirCamino(int destino, const vector<int>& padre){
    vector<int> camino;
    for(int v=destino; v!=-1; v=padre[v]){
        camino.push_back(v);
    }
    reverse(camino.begin(), camino.end());
    return camino;
}

void mostrarVertices(const vector<int>& vertices,
const vector<string>& nombres){
    for(size_t i =0; i<vertices.size(); ++i){
        if(i != 0) cout << " -> ";
        cout << nombres[vertices[i]];
    }
    cout << endl;
}

int main(){
    vector<string> nombres={
        "Craft", "Garden", "Billar", "ChuyBombas",
        "PlayaMamitas", "CheveChuy", "OXXO", "C4",
        "Salida"
    };
    Grafo grafo(nombres.size());
    conectar(grafo, 2, 0);
    conectar(grafo, 0, 3);
    conectar(grafo, 0, 2);
    conectar(grafo, 3, 5);
    conectar(grafo, 5, 1);
    conectar(grafo, 1, 4);
    conectar(grafo, 4, 6);
    conectar(grafo, 6, 7);
    conectar(grafo, 7, 8);

    for(auto& vecinos: grafo){
        sort(vecinos.begin(), vecinos.end());
        vecinos.erase(unique(vecinos.begin(), vecinos.end()), vecinos.end());
    }

    cout << "Lista de adyacencia:\n";
    for(size_t v=0; v<grafo.size(); ++v){
        cout << nombres[v] << ": ";
        for(int vecino: grafo[v]){
            cout << nombres[vecino] << " ";
        }
        cout << endl;
    }

    const int origen = 0;
    const int destino = 6;
    ResultadoBFS resultado = bfs(grafo,origen);

    cout << "\nBFS desde Craft\n";
    mostrarVertices(resultado.orden, nombres);
    cout << "\nDFS desde Craft\n";
    mostrarVertices(dfs(grafo,origen), nombres);

    cout << "\nDistancia en numero de caminos BFS\n";
    for(size_t v=0; v<nombres.size(); ++v){
        cout << nombres[v] << ": " << resultado.distancia[v] << endl;
    }

    if(resultado.distancia[destino] != -1){
        cout << "\nCamino con menos pasos hasta CheveChuy\n";
        mostrarVertices(construirCamino(destino,resultado.padre), nombres);
    }else{
        cout << "\nNo existe\n";
    }
    return 0;
}