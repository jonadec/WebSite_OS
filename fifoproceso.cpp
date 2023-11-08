#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Proceso {
    string nombre;
    int tiempoLlegada;
    int tiempoDuracion;
    int indiceInicio;
    int indiceFinal;
    int tiempoEspera;
};

 float timees=0;
 float timere=0;
 
void planificarFIFO(vector<Proceso>& procesos) {
    int tiempoTotal = 0;

    for (int i = 0; i < procesos.size(); i++) {
        Proceso& procesoActual = procesos[i];

        if (procesoActual.tiempoLlegada > tiempoTotal) {
            tiempoTotal = procesoActual.tiempoLlegada;
        }

        procesoActual.indiceInicio = tiempoTotal;
        procesoActual.indiceFinal = tiempoTotal + procesoActual.tiempoDuracion;
        procesoActual.tiempoEspera = procesoActual.indiceInicio - procesoActual.tiempoLlegada;
        timees+=procesoActual.tiempoEspera;
        timere+=procesoActual.indiceFinal;
        tiempoTotal = procesoActual.indiceFinal;
    }

    for (const Proceso& proceso : procesos) {
        cout<<endl;
        cout << "Proceso: " << proceso.nombre << endl;
        cout << "Inicio: " << proceso.indiceInicio << endl;
        cout << "Fin: " << proceso.indiceFinal-1 << endl;
        cout << "Tiempo de espera: " << proceso.tiempoEspera << endl;
        
    }
}

int main() {
    system("color 02");
     system("cls");
    int numProcesos=5;
    /*cout << "Ingrese el numero de procesos: ";
    cin >> numProcesos;*/
    vector<Proceso> procesos;

    Proceso proceso1 = {"A", 2, 3, 0, 0, 0};
    Proceso proceso2 = {"B", 7, 5, 0, 0, 0};
    Proceso proceso3 = {"C", 0, 4, 0, 0, 0};
    Proceso proceso4 = {"D", 3, 7, 0, 0, 0};
    Proceso proceso5 = {"E", 4, 5, 0, 0, 0};
    procesos.push_back(proceso1);
    procesos.push_back(proceso2);
    procesos.push_back(proceso3);
    procesos.push_back(proceso4);
    procesos.push_back(proceso5);
/*
    for (int i = 0; i < numProcesos; i++) {
        Proceso proceso;
        cout << "Ingrese el nombre del proceso " << i << ": ";
        cin >> proceso.nombre;
        cout << "Ingrese el tiempo de llegada del proceso " << proceso.nombre << ": ";
        cin >> proceso.tiempoLlegada;
        cout << "Ingrese el tiempo de duracion en CPU del proceso " << proceso.nombre << ": ";
        cin >> proceso.tiempoDuracion;
        procesos.push_back(proceso);
    }*/

    // Ordenar los procesos por tiempo de llegada
    sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
        return a.tiempoLlegada < b.tiempoLlegada;
    });

    // Llama a la función de planificación FIFO
    system("cls");
    planificarFIFO(procesos);
    cout<<endl;
    cout<<"TE: "<<timees/numProcesos<<endl;
    cout<<"TR: "<<(timere/numProcesos)-1<<endl;
    return 0;
}

