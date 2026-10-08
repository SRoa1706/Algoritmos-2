#include <iostream>
#include "Lista.h"
#include "Pila.h"
#include "Nodo.h"
#include "Cola.h"
#include <string>
#include <sstream>
using namespace std;
void leerDatos(Cola<Cola<string>> &columnas, Cola<string> &nombres, string &cabecera);
Cola<string> leerColumna(Cola<Cola<string>> &columnas);
string calcularModa(Cola<string> columna);

int main(){
    Cola<Cola<string>> columnas;
    Cola<string> nombres;
    Cola<string> aux;
    string cabecera;
    leerDatos(columnas, nombres, cabecera); 
    for(int i=0;i<4;i++){
        aux = leerColumna(columnas);
        string moda = calcularModa(aux);
        cout << moda;
        cout << ",";
    }
    cout << endl;
    
}

void leerDatos(Cola<Cola<string>> &columnas, Cola<string> &nombres, string &cabecera){
    cin >> cabecera;
    string linea;
    while(cin >> linea){
        stringstream ss(linea);
        string campo;
        while(getline(ss, campo, ',')){
            nombres.encolar(campo);
        }
        columnas.encolar(nombres);
        nombres.vaciar();
    }
}

Cola<string> leerColumna(Cola<Cola<string>> &columnas){
    Cola<string> result;
    int k = columnas.getLongitud();
    for(int i=0;i<k;i++){
        Cola<string> nombres = columnas.getFrente();
        string palabra = nombres.getFrente();
        nombres.desencolar();

        result.encolar(palabra);
        
        columnas.desencolar();
        columnas.encolar(nombres);
    }
    return result;
}

string calcularModa(Cola<string> columna){
    int maxVeces = 0;
    string moda = "";
    int k = columna.getLongitud();

    for(int i=0;i<k;i++){
        
        string palabra = columna.getFrente(); //Guardo en "palabra" el frente de la cola
        int veces = 0;

        for(int j=0;j<k;j++){
            string auxPalabra = columna.getFrente();
            if(palabra == auxPalabra){
                veces++;
                if(veces > maxVeces){
                    maxVeces = veces;
                    moda = palabra;
                }
            }
            columna.desencolar();
            columna.encolar(auxPalabra);

        }
        columna.desencolar();
        columna.encolar(palabra);
    }
    return moda;
}