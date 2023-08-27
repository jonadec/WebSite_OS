#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int TOTAL_MEMORY = 2000;
int posicion=1, *posicionPtr;
int newPartition=0;


struct Process {
    string name;
    int size;
};

int main() {
    posicionPtr= &posicion;
    system("cls");
    int numPartitions;
    cout << "Memoria total= " << TOTAL_MEMORY << endl;
    cout << "Ingrese la cantidad de particiones: ";
    cin >> numPartitions;
    
    vector<int> partitionSizes(numPartitions);
    int sumatoria = 0;
    
    for (int i = 0; i < numPartitions; ++i) {
        cout << "Ingrese el tamanio de la particion " << i + 1 << ": ";
        cin >> partitionSizes[i];
        
        sumatoria += partitionSizes[i];
        
        if (sumatoria > TOTAL_MEMORY) {
            cout << "El tamanio de las particiones excede la memoria total." << endl;
            return 1;
        }
    }

    vector<Process> memory(numPartitions);
    memory[0].name = "Sistema Operativo";
    memory[0].size = 100;
    int totalMemoryUsed = memory[0].size;

    while (true) {
        cout << endl;

        for (int i = 0; i < numPartitions; ++i) {
            if (memory[i].name.empty()) {
                cout << "Particion " << i + 1 << " (Tamanio: " << partitionSizes[i] << "): Libre" << endl;
            } else {
                cout << "Particion " << i + 1 << " (Tamanio: " << partitionSizes[i] << "): Proceso " << memory[i].name << " (" << memory[i].size << ")" << endl;
            }
        }

        cout << "\n1. Asignar proceso a particion" << endl;
        cout << "2. Liberar particion" << endl;
        cout << "3. Salir" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            if (totalMemoryUsed >= TOTAL_MEMORY) {
                cout << "No hay suficiente memoria disponible para asignar mas procesos." << endl;
                continue;
            }


            Process process;
            cout << "Ingrese el nombre del proceso: ";
            cin >> process.name;

            cout << "Ingrese el tamanio del proceso: ";
            cin >> process.size;

            if (totalMemoryUsed + process.size > TOTAL_MEMORY) {
                cout << "El tamanio del proceso excede la memoria total disponible." << endl;
                continue;
            }

            bool allocated = false;
          
            for (int i = *posicionPtr; i <= numPartitions; i++) {

                 if (i==numPartitions){
                i=0;
                }

                else{
                    if (memory[i].name.empty() && partitionSizes[i] >= process.size) {
                        memory[i] = process;
                        allocated = true;
                        totalMemoryUsed += process.size;
                        newPartition+=partitionSizes[i]-process.size;
                        cout << "Proceso asignado a la particion " << i + 1 << endl;
                        posicion=i;
                        break;
                    }}
                }

            if (!allocated) {
                cout << "No se pudo asignar el proceso a ninguna particion." << endl;
            }
        } 
        
        else if (choice == 2) {
            int partitionIndex;
            cout << "Ingrese el indice de la particion a liberar: ";
            cin >> partitionIndex;

            if (partitionIndex >= 0 && partitionIndex < numPartitions && !memory[partitionIndex].name.empty()) {
                totalMemoryUsed -= memory[partitionIndex].size;
                memory[partitionIndex].name = "";
                memory[partitionIndex].size = 0;
                cout << "Particion liberada." << endl;
            } else {
                cout << "Indice de particion invalido o la particion ya esta libre." << endl;
            }

        } 
        
        else if (choice == 3) {
            cout << "Saliendo del programa." << endl;
            break;
        } else {
            cout << "Opcion invalida." << endl;
        }
    }

    int espacio = TOTAL_MEMORY - totalMemoryUsed;
    cout << "Espacio libre de memoria: " << espacio << " bytes." << endl;
    cout<<"Nueva particion creada con espacio de: "<<newPartition;

    return 0;
}
