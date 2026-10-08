#include <iostream>
#include "Lista.h"
#include "Pila.h"
#include "Nodo.h"
#include "Cola.h"
#include <string>
#include <sstream>
using namespace std;
void leerDatos(Lista<Cola<string>> &columnas, Cola<string> &nombres, Lista<int> &repeticiones, int &n);
Cola<string> leerColumna(Lista<Cola<string>> &columnas);
string papaSeQuema(Cola<string> jugadores, int k);

int main(){
    Lista<Cola<string>> columnas;
    Cola<string> nombres;
    Cola<string> aux;
    string ganador;
    int n;
    Lista<int> repeticiones;
    leerDatos(columnas, nombres, repeticiones, n);
    for(int i=0;i<n;i++){
        aux = leerColumna(columnas);
        int k = repeticiones.getElemento(i);
        ganador = papaSeQuema(aux, k);
        cout << ganador <<endl;
    }
    return 0;
}

void leerDatos(Lista<Cola<string>> &columnas, Cola<string> &nombres, Lista<int> &repeticiones, int &n){
    string linea, palabra;
    cin >> n;
    for(int i=0;i<n;i++){
        int k;
        cin >> k;
        repeticiones.addElemento(k);
    }
    cin.ignore(); //Limpiar Buffer
    while(getline(cin, linea)){
        stringstream ss(linea);

        while(ss >> palabra){
            nombres.encolar(palabra);
        }
        columnas.addElemento(nombres);
        nombres.vaciar();

    }
}

Cola<string> leerColumna(Lista<Cola<string>> &columnas){
    int n = columnas.getLongitud();
    Cola<string> result;
    for(int i=0;i<n;i++){
        Cola<string> nombres;
        string palabra;
        nombres = columnas.getElemento(i);
        palabra = nombres.getFrente();
        result.encolar(palabra);
        nombres.desencolar();
        columnas.modificar(i,nombres);
    }
    return result;
}

string papaSeQuema(Cola<string> jugadores, int k){
    int cont = 0;
    k = k % jugadores.getLongitud();
    string jugador;
    while(jugadores.getLongitud() > 1){
        if(cont == k){
            jugadores.desencolar();
            cont = 0;
            jugadores.invertir();
        }else{
            jugador = jugadores.getFrente();
            jugadores.desencolar();
            jugadores.encolar(jugador);
            cont++;
        }
    }
    return jugadores.getFrente();
}
    
