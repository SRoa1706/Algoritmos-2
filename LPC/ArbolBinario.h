#ifndef ARBOLBINARIO_H_
#define ARBOLBINARIO_H_

#include "NodoAB.h"

using namespace std;

template <class Elemento>
class ArbolBinario {
private:
    NodoAB<Elemento>* nodoRaiz;
    int peso;

public:
    ArbolBinario();
    ~ArbolBinario();
    bool esNulo() const;
    Elemento raiz() const;
    ArbolBinario<Elemento> hijoDerecho() const;
    ArbolBinario<Elemento> hijoIzquierdo() const;
    void copiar(ArbolBinario<Elemento> a);
    int getPeso() const;
};

template <class Elemento>
Elemento ArbolBinario<Elemento>::raiz() const {
    if (this->nodoRaiz == nullptr) return Elemento();
    return this->nodoRaiz->getInfo();
}

template <class Elemento>
ArbolBinario<Elemento>::ArbolBinario() {
    this->nodoRaiz = nullptr;
    this->peso = 0;
}

template <class Elemento>
ArbolBinario<Elemento>::~ArbolBinario() {
    destruir(this->nodoRaiz);
}

template <class Elemento>
bool ArbolBinario<Elemento>::esNulo() const {
    if(this->nodoRaiz){
        return false;
    }else{
        return true;
    }
}

template <class Elemento>
int ArbolBinario<Elemento>::getPeso() const {
    return this->peso;
}

#endif