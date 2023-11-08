#include <iostream>
#include <cstdlib>

using namespace std;

struct listaNodo {
    int dato;
    struct listaNodo* next;
    struct listaNodo* before;
};

typedef struct listaNodo LISTANODO;
typedef LISTANODO* apuntador_LISTANODO;

void insertar_doble(apuntador_LISTANODO*, int);

int main() {
    apuntador_LISTANODO lista = NULL;
    int num = 0, frames = 0;
    int page=0;
    float pageFaults=0, hit=0;
    int numelementos = 0;
    float pagemiss=0, hitRatio=0;
    system("cls");
    system("color 02");

    cout << "Ingrese el numero de elementos del string" << endl;
    cin >> numelementos;
    for (int i = 0; i < numelementos; i++) {
        system("cls");
        cout << "Ingrese el elemento " << i << ": ";
        cin >> num;
        insertar_doble(&lista, num);
    }
    cout << "Ingrese la cantidad de frames" << endl;
    cin >> frames;
    int memoria[frames];
    for (int i = 0; i < frames; i++) {
        memoria[i] = -1;
    }


    apuntador_LISTANODO actual = lista;

    int indiceReemplazo=0;

    while (actual != NULL) {
        int paginaActual = actual->dato;
        bool pageFault = true;
        for (int i = 0; i < frames; i++) {
            if (memoria[i] == paginaActual) {
                pageFault = false;
                hit++;
            }
        }

        if (pageFault) {
            pageFaults++;
            memoria[indiceReemplazo] = paginaActual;
            indiceReemplazo = (indiceReemplazo + 1) % frames; 
        }
        
       /* cout <<"Pagina "<<page<<": ";
        for (int i = 0; i < frames; i++) {
            cout << memoria[i] << " ";
            }
            cout << endl;
            page++;*/

        actual = actual->next;
    }
           cout <<"Pagina "<<page<<": ";
        for (int i = 0; i < frames; i++) {
            cout << memoria[i] << " ";
            }
            cout << endl;
            
    pagemiss=(pageFaults/numelementos)*100;
    hitRatio=(hit/numelementos)*100;
    cout<<"En total son: "<<pageFaults<<" page faults"<<endl;
    cout<<"En total son: "<<hit<<" hits"<<endl;
    cout<<"Page miss: "<<pagemiss<<endl;
    cout<<"Hit Ratio: "<<hitRatio<<endl;

    return 0;
}

void insertar_doble(apuntador_LISTANODO* inicio, int valor) {
    apuntador_LISTANODO nuevo, actual;
    nuevo = new LISTANODO();
    if (nuevo != NULL) {
        nuevo->dato = valor;
        nuevo->next = NULL;
        nuevo->before = NULL;
        actual = *inicio;

        if (actual == NULL) {
            
            *inicio = nuevo;
        } else {
      
            while (actual->next != NULL) {
                actual = actual->next;
            }
            actual->next = nuevo;
            nuevo->before = actual;
        }
    } else {
        cout << valor << " No insertado" << endl;
    }
}


