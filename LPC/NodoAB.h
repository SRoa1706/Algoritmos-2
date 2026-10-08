#ifndef NODOAB_H_
#define NODOAB_H_

#include <iostream>

using namespace std;

template <class Elemento>
class NodoAB {
private:
    NodoAB<Elemento>* hijoIzq;
    NodoAB<Elemento>* hijoDer;
    Elemento info;

public:
    NodoAB();
    void setInfo(Elemento e);
    void setHijoDerecho(NodoAB<Elemento>* s);
    void setHijoIzquierdo(NodoAB<Elemento>* s);
    Elemento getInfo() const;
    NodoAB<Elemento>* getHijoIzquierdo() const;
    NodoAB<Elemento>* getHijoDerecho() const;
};

template <class Elemento>
NodoAB<Elemento>::NodoAB() : hijoIzq(nullptr), hijoDer(nullptr), info(Elemento()) {}

template <class Elemento>
void NodoAB<Elemento>::setInfo(Elemento e) {
    this->info = e;
}

template <class Elemento>
void NodoAB<Elemento>::setHijoIzquierdo(NodoAB<Elemento>* s) {
    this->hijoIzq = s;
}

template <class Elemento>
void NodoAB<Elemento>::setHijoDerecho(NodoAB<Elemento>* s) {
    this->hijoDer = s;
}

template <class Elemento>
Elemento NodoAB<Elemento>::getInfo() const {
    return this->info;
}

template <class Elemento>
NodoAB<Elemento>* NodoAB<Elemento>::getHijoIzquierdo() const {
    return this->hijoIzq;
}

template <class Elemento>
NodoAB<Elemento>* NodoAB<Elemento>::getHijoDerecho() const {
    return this->hijoDer;
}

#endif