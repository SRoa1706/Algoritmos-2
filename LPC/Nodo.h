#ifndef NODO_H_
#define NODO_H_

#include <iostream>

using namespace std;

template <class Elemento>
class Nodo {
private:
    Nodo<Elemento>* prox;
    Elemento info;

public:
    Nodo();
    void setInfo(Elemento e);
    void setProx(Nodo<Elemento>* s);
    Elemento getInfo() const;
    Nodo<Elemento>* getProx() const;
};

template <class Elemento>
Nodo<Elemento>::Nodo() : prox(nullptr), info(Elemento()) {}

template <class Elemento>
void Nodo<Elemento>::setInfo(Elemento e) {
    this->info = e;
}

template <class Elemento>
void Nodo<Elemento>::setProx(Nodo<Elemento>* s) {
    this->prox = s;
}

template <class Elemento>
Elemento Nodo<Elemento>::getInfo() const {
    return this->info;
}

template <class Elemento>
Nodo<Elemento>* Nodo<Elemento>::getProx() const {
    return this->prox;
}

#endif