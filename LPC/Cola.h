#ifndef COLA_H_
#define COLA_H_

#include "Nodo.h"

using namespace std;

template <class Elemento>
class Cola {
private:
    Nodo<Elemento>* frente;
    Nodo<Elemento>* fin;
    int longitud;

public:
    Cola();
    Cola(const Cola<Elemento>& otra);
    ~Cola();
    Cola<Elemento>& operator=(const Cola<Elemento>& otra);
    bool esVacia() const;
    void encolar(Elemento e);
    void desencolar();
    void invertir();
    void vaciar();
    Elemento getFrente() const;
    int getLongitud() const;
    void copiar(const Cola<Elemento>& otra);
};

template <class Elemento>
Cola<Elemento>::Cola() {
    this->frente = nullptr;
    this->fin = nullptr;
    this->longitud = 0;
}

template <class Elemento>
Cola<Elemento>::Cola(const Cola<Elemento>& otra)
    : frente(nullptr), fin(nullptr), longitud(0) {
    copiar(otra);
}

template <class Elemento>
Cola<Elemento>::~Cola() {
    vaciar();
}

template <class Elemento>
Cola<Elemento>& Cola<Elemento>::operator=(const Cola<Elemento>& otra) {
    if (this != &otra) {
        copiar(otra);
    }
    return *this;
}

template <class Elemento>
bool Cola<Elemento>::esVacia() const {
    return this->frente == nullptr;
}

template <class Elemento>
void Cola<Elemento>::encolar(Elemento e) {
    Nodo<Elemento>* nuevo = new Nodo<Elemento>();
    nuevo->setInfo(e);
    nuevo->setProx(nullptr);

    if (this->frente == nullptr) {
        this->frente = nuevo;
        this->fin = nuevo;
        longitud++;
        return;
    }

    this->fin->setProx(nuevo);
    this->fin = nuevo;
    this->longitud++;
}

template <class Elemento>
void Cola<Elemento>::desencolar() {
    if (this->frente == nullptr) return;

    Nodo<Elemento>* actual = this->frente->getProx();
    delete this->frente;
    this->frente = actual;
    if (this->frente == nullptr) {
        this->fin = nullptr;
    }
    this->longitud--;
}

template <class Elemento>
void Cola<Elemento>::invertir() {
    Nodo<Elemento>* anterior = nullptr;
    Nodo<Elemento>* actual = this->frente;
    this->fin = this->frente;

    while (actual != nullptr) {
        Nodo<Elemento>* siguiente = actual->getProx();
        actual->setProx(anterior);
        anterior = actual;
        actual = siguiente;
    }

    this->frente = anterior;
}

template <class Elemento>
void Cola<Elemento>::vaciar() {
    while (this->frente != nullptr) {
        desencolar();
    }
}

template <class Elemento>
Elemento Cola<Elemento>::getFrente() const {
    if (this->frente == nullptr) return Elemento();
    return this->frente->getInfo();
}

template <class Elemento>
int Cola<Elemento>::getLongitud() const {
    return this->longitud;
}

template <class Elemento>
void Cola<Elemento>::copiar(const Cola<Elemento>& otra) {
    if (this == &otra) return;

    vaciar();

    Nodo<Elemento>* actual = otra.frente;
    while (actual != nullptr) {
        encolar(actual->getInfo());
        actual = actual->getProx();
    }
}

#endif