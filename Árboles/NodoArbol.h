#ifndef NODOARBOL_H_
#define NODOARBOL_H_

template <class Elemento>
class NodoArbol {
    private:
        Elemento info;
        NodoArbol<Elemento>* hijoIzq;
        NodoArbol<Elemento>* hnoDer;

    public:
        NodoArbol();
        NodoArbol(const Elemento& info, NodoArbol<Elemento>* izq = 0, NodoArbol<Elemento>* der = 0);
        Elemento getInfo() const;
        NodoArbol<Elemento>* getHijoIzquierdo() const;
        NodoArbol<Elemento>* getHermanoDerecho() const;
        void setInfo(const Elemento& e);
        void setHijoIzquierdo(NodoArbol<Elemento>* p);
        void setHermanoDerecho(NodoArbol<Elemento>* p);
};

template <class Elemento>
NodoArbol<Elemento>::NodoArbol() 
    : info(Elemento()), hijoIzq(0), hnoDer(0) {}

template <class Elemento>
NodoArbol<Elemento>::NodoArbol(const Elemento& info, NodoArbol<Elemento>* izq, NodoArbol<Elemento>* der)
    : info(info), hijoIzq(izq), hnoDer(der) {}

template <class Elemento>
Elemento NodoArbol<Elemento>::getInfo() const {
    return this->info;
}

template <class Elemento>
NodoArbol<Elemento>* NodoArbol<Elemento>::getHijoIzquierdo() const {
    return this->hijoIzq;
}

template <class Elemento>
NodoArbol<Elemento>* NodoArbol<Elemento>::getHermanoDerecho() const {
    return this->hnoDer;
}

template <class Elemento>
void NodoArbol<Elemento>::setInfo(const Elemento& e) {
    this->info = e;
}

template <class Elemento>
void NodoArbol<Elemento>::setHijoIzquierdo(NodoArbol<Elemento>* p) {
    this->hijoIzq = p;
}

template <class Elemento>
void NodoArbol<Elemento>::setHermanoDerecho(NodoArbol<Elemento>* p) {
    this->hnoDer = p;
}

#endif 