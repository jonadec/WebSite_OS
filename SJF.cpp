#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include"jonathan2.h"

using namespace std;

struct Proceso {
    string nombre;
    int tiempoLlegada;
    int tiempoDuracion;
    int indiceInicio;
    int indiceFinal;
    int tiempoEspera;
};

bool compareTiempoLlegada(const Proceso& a, const Proceso& b) {
    return a.tiempoLlegada < b.tiempoLlegada;
}

bool compareDuracion(const Proceso& a, const Proceso& b) {
    return a.tiempoDuracion < b.tiempoDuracion;
}

void planificarSJF(vector<Proceso>& procesos) {
    int tiempoTotal = 0;
    int n = procesos.size();

    // Ordenar los procesos por tiempo de llegada
    sort(procesos.begin(), procesos.end(), compareTiempoLlegada);

    vector<bool> completado(n, false); // Para rastrear los procesos completados

    while (true) {
        int procesoElegido = -1;
        int menorDuracion = INT_MAX;

        // Buscar el proceso más corto que está listo para ejecutar
        for (int i = 0; i < n; i++) {
            if (!completado[i] && procesos[i].tiempoLlegada <= tiempoTotal && procesos[i].tiempoDuracion < menorDuracion) {
                procesoElegido = i;
                menorDuracion = procesos[i].tiempoDuracion;
            }
        }

        if (procesoElegido == -1) {
            // Si no se encontró ningún proceso listo, avanzar en el tiempo hasta el próximo proceso
            int siguienteLlegada = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!completado[i] && procesos[i].tiempoLlegada < siguienteLlegada) {
                    siguienteLlegada = procesos[i].tiempoLlegada;
                }
            }
            tiempoTotal = siguienteLlegada;
        } 
        else {
            Proceso& procesoActual = procesos[procesoElegido];
            procesoActual.indiceInicio = tiempoTotal;
            procesoActual.indiceFinal = tiempoTotal + procesoActual.tiempoDuracion;
            procesoActual.tiempoEspera = procesoActual.indiceInicio - procesoActual.tiempoLlegada;
            tiempoTotal = procesoActual.indiceFinal;
            completado[procesoElegido] = true;

            cout<<"Proceso: " << procesoActual.nombre <<endl;
            cout<<"Proceso completado: " << procesoActual.indiceFinal<<endl;
            //cout<<"Tiempo en servicio: " << procesoActual.indiceFinal-procesoActual.tiempoLlegada <<endl;
          //  cout<<"Tiempo en espera: " << procesoActual.tiempoEspera << endl<<endl;
        }

        
        if (count(completado.begin(), completado.end(), false) == 0) {
            break;
        }
    }
}

int main() {
    system("cls");
    system("color 02");
    int numProcesos=5;
    /*cout << "Ingrese el numero de procesos: ";
    cin >> numProcesos;*/
    system("cls");
    vector<Proceso> procesos;
    Proceso proceso1 = {"A", 2, 9, 0, 0, 0};
    procesos.push_back(proceso1);
    Proceso proceso2 = {"B", 4, 7, 0, 0, 0};
    procesos.push_back(proceso2);
    Proceso proceso3 = {"C", 0, 6, 0, 0, 0};
    procesos.push_back(proceso3);
    Proceso proceso4 = {"D", 3, 2, 0, 0, 0};
    procesos.push_back(proceso4);
    Proceso proceso5 = {"E", 6, 5, 0, 0, 0};
    procesos.push_back(proceso5);
    /*
    for (int i = 0; i < numProcesos; i++) {
        Proceso proceso;
        cout << "Ingrese el nombre del proceso " << i + 1 << ": ";
        cin >> proceso.nombre;
        cout << "Ingrese el tiempo de llegada del proceso " << proceso.nombre << ": ";
        cin >> proceso.tiempoLlegada;
        cout << "Ingrese el tiempo de duracion en CPU del proceso " << proceso.nombre << ": ";
        cin >> proceso.tiempoDuracion;
        procesos.push_back(proceso);
    }*/
    cout<<endl;
    
    planificarSJF(procesos);

    return 0;
}
