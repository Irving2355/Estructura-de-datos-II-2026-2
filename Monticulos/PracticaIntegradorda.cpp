/*
Situación
Se desea desarrollar un simulador sencillo para administrar pacientes de un área de urgencias.
Cada paciente tendrá:

-número de registro;
-nombre;
-edad;
-nivel de urgencia;
-turno de llegada.

Los niveles serán:
5 Crítico
4 Muy urgente
3 Urgente
2 Poco urgente
1 No urgente

8.2. Reglas de prioridad
El sistema deberá seleccionar primero al paciente con:
1. mayor nivel de urgencia;
2. si dos pacientes tienen la misma urgencia, deberá atenderse primero al que llegó antes.

Por ejemplo:
Paciente Urgencia Llegada
Ana     3       1
Luis    5       2
Pedro   3       3
María   5       4

El orden esperado sería:
Luis -> Maria -> Ana -> Pedro

Menu:

====================================
SISTEMA DE URGENCIAS
====================================
1. Registrar paciente
2. Consultar siguiente paciente
3. Atender siguiente paciente
4. Mostrar pacientes pendientes
5. Mostrar cantidad de pacientes
6. Salir
Seleccione una opcion:

*/
#include <iostream>

using namespace std;

struct Paciente
{
    int registro;
    string nombre;
    int edad;
    int urgencia;
    int llegada;
};


int main(){
    return 0;
}