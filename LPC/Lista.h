#ifndef LISTA_H_
#define LISTA_H_

#include "Nodo.h"
#include <iostream>

using namespace std;

template <class Elemento>
class Lista {
private:
    Nodo<Elemento>* cabeza;
    Nodo<Elemento>* cola;
    int longitud;

public:
    Lista();
    Lista(const Lista<Elemento>& otra);
    ~Lista();
    Lista<Elemento>& operator=(const Lista<Elemento>& otra);
    void addElemento(Elemento e);
    int getLongitud();
    bool esVacia();
    void imprimirLista();
    void eliminarUltimo();
    bool existeElemento(Elemento e);
    void addInicio(Elemento e);
    void modificar(int pos, Elemento e);
    void copiar(const Lista<Elemento>& otra);
    Elemento getElemento(int pos);
    void invertir();
    Elemento getUltimo();
    void rightShift(int shift);
    Elemento getPrimero();
    void eliminarPrimero();
    Lista<Elemento> mergeSorted(Lista<Elemento> lista);
    Lista<Elemento> ordenarLista();
};

template <class Elemento>
Lista<Elemento>::Lista() {
    this->cabeza = nullptr;
    this->cola = nullptr;
    this->longitud = 0;
}

template <class Elemento>
Lista<Elemento>::Lista(const Lista<Elemento>& otra)
    : cabeza(nullptr), cola(nullptr), longitud(0) {
    copiar(otra);
}

template <class Elemento>
Lista<Elemento>::~Lista() {
    while (this->cabeza != nullptr) {
        Nodo<Elemento>* temp = this->cabeza;
        this->cabeza = this->cabeza->getProx();
        delete temp;
    }
}

template <class Elemento>
Lista<Elemento>& Lista<Elemento>::operator=(const Lista<Elemento>& otra) {
    if (this != &otra) {
        copiar(otra);
    }
    return *this;
}

template <class Elemento>
void Lista<Elemento>::addElemento(Elemento e) {
    Nodo<Elemento>* nuevo = new Nodo<Elemento>();
    nuevo->setInfo(e);
    nuevo->setProx(nullptr);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
        longitud++;
        return;
    }

    cola->setProx(nuevo);
    cola = nuevo;
    longitud++;
}

template <class Elemento>
int Lista<Elemento>::getLongitud() {
    return this->longitud;
}

template <class Elemento>
bool Lista<Elemento>::esVacia() {
    return cabeza == nullptr;
}

template <class Elemento>
void Lista<Elemento>::imprimirLista() {
    if (cabeza == nullptr) return;

    Nodo<Elemento>* actual = cabeza;
    cout << "[";
    while (actual->getProx() != nullptr) {
        cout << actual->getInfo() << ", ";
        actual = actual->getProx();
    }
    cout << actual->getInfo() << "]" << endl;
}

template <class Elemento>
void Lista<Elemento>::eliminarUltimo() {
    if (cabeza == nullptr) return;

    if (cabeza == cola) {
        delete cabeza;
        cabeza = nullptr;
        cola = nullptr;
        longitud = 0;
        return;
    }

    Nodo<Elemento>* actual = cabeza;
    while (actual->getProx() != cola) {
        actual = actual->getProx();
    }

    delete cola;
    cola = actual;
    actual->setProx(nullptr);
    longitud--;
}

template <class Elemento>
bool Lista<Elemento>::existeElemento(Elemento e) {
    Nodo<Elemento>* actual = cabeza;

    while (actual != nullptr) {
        if (actual->getInfo() == e) return true;
        actual = actual->getProx();
    }
    return false;
}

template <class Elemento>
void Lista<Elemento>::addInicio(Elemento e) {
    Nodo<Elemento>* nuevo = new Nodo<Elemento>();
    nuevo->setInfo(e);
    nuevo->setProx(cabeza);

    cabeza = nuevo;
    if (cola == nullptr) cola = nuevo;
    longitud++;
}

template <class Elemento>
void Lista<Elemento>::modificar(int pos, Elemento e) {
    if (pos >= longitud || pos < 0) return;

    Nodo<Elemento>* actual;
    if (pos == 0) {
        actual = cabeza;
        actual->setInfo(e);
        return;
    } else if (pos == longitud - 1) {
        actual = cola;
        actual->setInfo(e);
        return;
    } else {
        actual = cabeza->getProx();
        for (int i = 1; i < longitud; i++) {
            if (i == pos) {
                actual->setInfo(e);
                return;
            }
            actual = actual->getProx();
        }
    }
}

template <class Elemento>
void Lista<Elemento>::copiar(const Lista<Elemento>& otra) {
    if (this == &otra) return;

    while (this->cabeza != nullptr) {
        Nodo<Elemento>* temp = this->cabeza;
        this->cabeza = this->cabeza->getProx();
        delete temp;
    }

    this->cola = nullptr;
    this->longitud = 0;

    Nodo<Elemento>* actual = otra.cabeza;
    while (actual != nullptr) {
        this->addElemento(actual->getInfo());
        actual = actual->getProx();
    }
}

template <class Elemento>
Elemento Lista<Elemento>::getElemento(int pos) {
    if (pos < 0 || pos >= longitud) return Elemento();

    Nodo<Elemento>* actual = cabeza;
    for (int i = 0; i < pos; i++) {
        actual = actual->getProx();
    }
    return actual->getInfo();
}

template <class Elemento>
void Lista<Elemento>::invertir() {
    Nodo<Elemento>* anterior = nullptr;
    Nodo<Elemento>* actual = this->cabeza;
    this->cola = this->cabeza;

    while (actual != nullptr) {
        Nodo<Elemento>* siguiente = actual->getProx();
        actual->setProx(anterior);
        anterior = actual;
        actual = siguiente;
    }

    this->cabeza = anterior;
}

template <class Elemento>
Elemento Lista<Elemento>::getUltimo() {
    if (cola == nullptr) return Elemento();
    return cola->getInfo();
}

template <class Elemento>
void Lista<Elemento>::rightShift(int shift) {
    int tam = this->longitud;

    for (int i = 0; i < tam - shift; i++) {
        Nodo<Elemento>* actual = this->cabeza;
        Nodo<Elemento>* actualSiguiente = actual->getProx();

        cabeza = actualSiguiente;
        actual->setProx(nullptr);
        cola->setProx(actual);
        cola = actual;
    }
}

template <class Elemento>
Elemento Lista<Elemento>::getPrimero() {
    if (cabeza == nullptr) return Elemento();
    return cabeza->getInfo();
}

template <class Elemento>
void Lista<Elemento>::eliminarPrimero() {
    if (cabeza == nullptr) return;

    Nodo<Elemento>* actual = cabeza;
    cabeza = actual->getProx();
    delete actual;
    longitud--;
}

template <class Elemento>
Lista<Elemento> Lista<Elemento>::mergeSorted(Lista<Elemento> lista) {
    Lista<Elemento> result;
    Nodo<Elemento>* ptrListaA = this->cabeza;
    Nodo<Elemento>* ptrListaB = lista.cabeza;

    while (ptrListaA && ptrListaB) {
        if (ptrListaA->getInfo() <= ptrListaB->getInfo()) {
            result.addElemento(ptrListaA->getInfo());
            ptrListaA = ptrListaA->getProx();
        } else {
            result.addElemento(ptrListaB->getInfo());
            ptrListaB = ptrListaB->getProx();
        }
    }

    while (ptrListaA) {
        result.addElemento(ptrListaA->getInfo());
        ptrListaA = ptrListaA->getProx();
    }

    while (ptrListaB) {
        result.addElemento(ptrListaB->getInfo());
        ptrListaB = ptrListaB->getProx();
    }

    return result;
}

template <class Elemento>
Lista<Elemento> Lista<Elemento>::ordenarLista() {
    for (int i = 0; i < this->longitud; ++i) {
        bool intercambio = false;
        Nodo<Elemento>* actual = this->cabeza;
        for (int j = 0; j < this->longitud - 1 - i; ++j) {
            Nodo<Elemento>* siguiente = actual->getProx();
            if (siguiente == nullptr) {
                break;
            }
            if (actual->getInfo() > siguiente->getInfo()) {
                Elemento temp = actual->getInfo();
                actual->setInfo(siguiente->getInfo());
                siguiente->setInfo(temp);
                intercambio = true;
            }
            actual = siguiente;
        }
        if (!intercambio) {
            break;
        }
    }
    return *this;
}

#endif