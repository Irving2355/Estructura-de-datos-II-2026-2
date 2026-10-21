#include <iostream>
#include <queue>

using namespace std;

int main(){
    priority_queue<int> cola;

    cola.push(30);
    cola.push(70);
    cola.push(20);
    cola.push(90);
    cola.push(50);

    cout << "Top: " << cola.top() << endl;

    cout << "Orden de salida: \n";
    while (!cola.empty())
    {
        cout << cola.top() << " ";
        cola.pop();
    }
    cout << "\n\n";
    
    //min-heap

    priority_queue<
    int,
    vector<int>,
    greater<int>> colaMin;

    colaMin.push(30);
    colaMin.push(70);
    colaMin.push(20);
    colaMin.push(90);
    colaMin.push(50);

    cout << "Min-Heap con colas: \n";

    while (!colaMin.empty())
    {
        cout << colaMin.top() << " ";
        colaMin.pop();
    }

    cout << "\n\n";
    

    return 0;
}