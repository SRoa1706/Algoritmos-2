#ifndef PILA_H_
#define PILA_H_

#include "Nodo.h"

using namespace std;

template <class Elemento>
class Pila {
private:
    Nodo<Elemento>* top;
    int longitud;

public:
    Pila();
    Pila(const Pila<Elemento>& otra);
    ~Pila();
    Pila<Elemento>& operator=(const Pila<Elemento>& otra);
    void apilar(Elemento e);
    void desapilar();
    Elemento getTop() const;
    int getLongitud() const;
    void vaciar();
    void copiar(const Pila<Elemento>& otra);
};

template <class Elemento>
Pila<Elemento>::Pila() {
    this->top = nullptr;
    this->longitud = 0;
}

template <class Elemento>
Pila<Elemento>::Pila(const Pila<Elemento>& otra)
    : top(nullptr), longitud(0) {
    copiar(otra);
}

template <class Elemento>
Pila<Elemento>::~Pila() {
    vaciar();
}

template <class Elemento>
Pila<Elemento>& Pila<Elemento>::operator=(const Pila<Elemento>& otra) {
    if (this != &otra) {
        copiar(otra);
    }
    return *this;
}

template <class Elemento>
void Pila<Elemento>::apilar(Elemento e) {
    Nodo<Elemento>* nuevo = new Nodo<Elemento>();
    nuevo->setInfo(e);
    nuevo->setProx(this->top);
    this->top = nuevo;
    this->longitud++;
}

template <class Elemento>
void Pila<Elemento>::desapilar() {
    if (this->top == nullptr) return;
    Nodo<Elemento>* actual = top->getProx();
    delete this->top;
    this->top = actual;
    this->longitud--;
}

template <class Elemento>
Elemento Pila<Elemento>::getTop() const {
    if (this->top == nullptr) return Elemento();
    return top->getInfo();
}

template <class Elemento>
int Pila<Elemento>::getLongitud() const {
    return this->longitud;
}

template <class Elemento>
void Pila<Elemento>::vaciar() {
    while (this->top != nullptr) {
        this->desapilar();
    }
}

template <class Elemento>
void Pila<Elemento>::copiar(const Pila<Elemento>& otra) {
    if (this == &otra) return;

    vaciar();
    Nodo<Elemento>* actual = otra.top;
    Nodo<Elemento>* ultimoCopiado = nullptr;

    while (actual != nullptr) {
        Nodo<Elemento>* nuevo = new Nodo<Elemento>();
        nuevo->setInfo(actual->getInfo());
        nuevo->setProx(nullptr);

        if (this->top == nullptr) {
            this->top = nuevo;
        } else {
            ultimoCopiado->setProx(nuevo);
        }
        ultimoCopiado = nuevo;
        this->longitud++;
        actual = actual->getProx();
    }
}

#endif