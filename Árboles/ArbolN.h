#ifndef ARBOLN_H_
#define ARBOLN_H_
#include <iostream>
#include <vector>
#include <queue>
#include "NodoArbol.h"

using namespace std;

template <class Elemento>
class ArbolN {
    private:
        NodoArbol<Elemento>* nodoRaiz;
        static NodoArbol<Elemento>* copiarNodos(NodoArbol<Elemento>* p);
        static void destruirNodos(NodoArbol<Elemento>* p);

        //Recorridos
        void inorden(vector<Elemento> &inorden, NodoArbol<Elemento>* p);
        void preorden(vector<Elemento> &preorden, NodoArbol<Elemento>* p);
        void postorden(vector<Elemento> &postorden, NodoArbol<Elemento>* p);

        //Ejecicios
        int altura(NodoArbol<Elemento>* p) const;
        bool buscarNodo(NodoArbol<Elemento>* p, const Elemento& e) const;
        void ArbolN<Element>::mapearNiveles(const NodoN<Element> *pNodo, map<Element, int> &niveles, int nivel);
        map<Element, int> ArbolN<Element>::mapearNiveles() const;
        
    public:
        
        ArbolN();
        ArbolN(const ArbolN<Elemento>& arbol);
        ArbolN(Elemento e, const vector<ArbolN<Elemento> > &hijos);
        ~ArbolN();
        ArbolN<Elemento>& operator=(const ArbolN<Elemento>& arbol);
        void copiar(const ArbolN<Elemento> &arbol);
        bool esNulo();
        Elemento raiz();
        vector<ArbolN<Elemento> > getHijos();
        void insertarSubarbol(const ArbolN<Elemento> &arbol);
        void eliminarSubarbol(int pos);

        //Recorridos
        vector<Elemento> inorden();
        vector<Elemento> preorden();
        vector<Elemento> postorden();
        
        //Ejercicios
        bool buscarNodo(const Elemento& e) const;
        int altura() const;
        vector<Elemento> recorridoPorNiveles() const;

};

template <class Elemento>
ArbolN<Elemento>::ArbolN() : nodoRaiz(0) {}

template <class Elemento>
ArbolN<Elemento>::ArbolN(const ArbolN<Elemento>& arbol)
    : nodoRaiz(copiarNodos(arbol.nodoRaiz)) {}

template <class Elemento>
ArbolN<Elemento>::ArbolN(Elemento e, const vector<ArbolN<Elemento> > &hijos){
    nodoRaiz = new NodoArbol<Elemento>(e, 0, 0);

    NodoArbol<Elemento>* ultimoHijo = 0;
    for (typename vector<ArbolN<Elemento> >::const_iterator hijo = hijos.begin();
         hijo != hijos.end(); ++hijo) {
        NodoArbol<Elemento>* nuevoHijo = copiarNodos(hijo->nodoRaiz);
        if (ultimoHijo == 0) {
            nodoRaiz->setHijoIzquierdo(nuevoHijo);
        } else {
            ultimoHijo->setHermanoDerecho(nuevoHijo);
        }
        ultimoHijo = nuevoHijo;
    }
}

template <class Elemento>
ArbolN<Elemento>::~ArbolN(){
    destruirNodos(this->nodoRaiz);
}

template <class Elemento>
ArbolN<Elemento>& ArbolN<Elemento>::operator=(const ArbolN<Elemento>& arbol){
    if (this != &arbol) {
        NodoArbol<Elemento>* nuevaRaiz = copiarNodos(arbol.nodoRaiz);
        destruirNodos(this->nodoRaiz);
        this->nodoRaiz = nuevaRaiz;
    }
    return *this;
}

template <class Elemento>
NodoArbol<Elemento>* ArbolN<Elemento>::copiarNodos(NodoArbol<Elemento>* p){
    if(p == 0){
        return 0;
    }

    NodoArbol<Elemento>* nuevoHijoIzq = copiarNodos(p->getHijoIzquierdo());
    NodoArbol<Elemento>* nuevoHnoDer  = copiarNodos(p->getHermanoDerecho());

    NodoArbol<Elemento>* nuevoNodo = new NodoArbol<Elemento>(p->getInfo(), nuevoHijoIzq, nuevoHnoDer);

    return nuevoNodo;
}

template <class Elemento>
void ArbolN<Elemento>::destruirNodos(NodoArbol<Elemento>* p){
    if (p == 0) {
        return;
    }
    destruirNodos(p->getHijoIzquierdo());
    destruirNodos(p->getHermanoDerecho());
    delete p;
}

template <class Elemento>
bool ArbolN<Elemento>::esNulo(){
    return this->nodoRaiz == 0;
}

template <class Elemento>
void ArbolN<Elemento>::copiar(const ArbolN<Elemento> &arbol){
    if (this != &arbol) {
        destruirNodos(this->nodoRaiz);
        this->nodoRaiz = copiarNodos(arbol.nodoRaiz);
    }
}

template <class Elemento>
Elemento ArbolN<Elemento>::raiz(){
    if (this->nodoRaiz == 0) {
        return Elemento();
    }
    return this->nodoRaiz->getInfo();
}

template <class Elemento>
vector<ArbolN<Elemento> > ArbolN<Elemento>::getHijos(){
    vector<ArbolN<Elemento> > resultado;
    if (this->nodoRaiz == 0) {
        return resultado;
    }

    NodoArbol<Elemento>* actual = this->nodoRaiz->getHijoIzquierdo();
    while (actual != 0) {
        ArbolN<Elemento> hijo;
        hijo.nodoRaiz = new NodoArbol<Elemento>(
            actual->getInfo(),
            copiarNodos(actual->getHijoIzquierdo()),
            0
        );
        resultado.push_back(hijo);
        actual = actual->getHermanoDerecho();
    }
    return resultado;
}

template <class Elemento>
void ArbolN<Elemento>::insertarSubarbol(const ArbolN<Elemento> &arbol){
    if (arbol.nodoRaiz == 0) {
        return;
    }
    if (this->nodoRaiz == 0) {
        this->nodoRaiz = copiarNodos(arbol.nodoRaiz);
        return;
    }

    NodoArbol<Elemento>* nuevoHijo = new NodoArbol<Elemento>(
        arbol.nodoRaiz->getInfo(),
        copiarNodos(arbol.nodoRaiz->getHijoIzquierdo()),
        0
    );

    NodoArbol<Elemento>* ultimoHijo = this->nodoRaiz->getHijoIzquierdo();
    if (ultimoHijo == 0) {
        this->nodoRaiz->setHijoIzquierdo(nuevoHijo);
        return;
    }
    while (ultimoHijo->getHermanoDerecho() != 0) {
        ultimoHijo = ultimoHijo->getHermanoDerecho();
    }
    ultimoHijo->setHermanoDerecho(nuevoHijo);
}

template <class Elemento>
void ArbolN<Elemento>::eliminarSubarbol(int pos){
    if (this->nodoRaiz == 0 || pos < 0) {
        return;
    }

    NodoArbol<Elemento>* anterior = 0;
    NodoArbol<Elemento>* actual = this->nodoRaiz->getHijoIzquierdo();
    for (int i = 0; actual != 0 && i < pos; ++i) {
        anterior = actual;
        actual = actual->getHermanoDerecho();
    }
    if (actual == 0) {
        return;
    }

    NodoArbol<Elemento>* siguiente = actual->getHermanoDerecho();
    actual->setHermanoDerecho(0);
    if (anterior == 0) {
        this->nodoRaiz->setHijoIzquierdo(siguiente);
    } else {
        anterior->setHermanoDerecho(siguiente);
    }
    destruirNodos(actual);
}

//Recorridos

template <class Elemento>
vector<Elemento> ArbolN<Elemento>::inorden(){
    vector<Elemento> inorden;
    this->inorden(inorden,this->nodoRaiz);
    return inorden;
}

template <class Elemento>
void ArbolN<Elemento>::inorden(vector<Elemento> &inorden, NodoArbol<Elemento>* p){
    if(p != 0){
        this->inorden(inorden,p->getHijoIzquierdo());
        inorden.push_back(p->getInfo());
        NodoArbol<Elemento>* aux = p->getHijoIzquierdo();
        while(aux != 0){
            aux = aux->getHermanoDerecho();
            this->inorden(inorden, aux);
        }
    }
}

template <class Elemento>
vector<Elemento> ArbolN<Elemento>::preorden(){
    vector<Elemento> preorden;
    this->preorden(preorden,this->nodoRaiz);
    return preorden;
}

template <class Elemento>
void ArbolN<Elemento>::preorden(vector<Elemento> &preorden, NodoArbol<Elemento>* p){
    NodoArbol<Elemento>* aux;
    if(p != 0){
        preorden.push_back(p->getInfo());
        aux = p->getHijoIzquierdo();
        while(aux != 0){
            this->preorden(preorden, aux);
            aux = aux->getHermanoDerecho();
        }
    }
}

template <class Elemento>
vector<Elemento> ArbolN<Elemento>::postorden(){
    vector<Elemento> postorden;
    this->postorden(postorden,this->nodoRaiz);
    return postorden;
}

template <class Elemento>
void ArbolN<Elemento>::postorden(vector<Elemento> &postorden, NodoArbol<Elemento>* p){
    if(p != 0){
        NodoArbol<Elemento>* aux = p->getHijoIzquierdo();
        while(aux != 0){
            this->postorden(postorden,aux);
            aux = aux->getHermanoDerecho();
        }
        postorden.push_back(p->getInfo());
    }
}

//Ejercicios para volverme un Pro

template <class Elemento>
bool ArbolN<Elemento>::buscarNodo(const Elemento& e) const{
    return buscarNodo(this->nodoRaiz, e);
}

template <class Elemento>
bool ArbolN<Elemento>::buscarNodo(NodoArbol<Elemento>* p, const Elemento& e) const{
    if(p == 0) return false;
    if(p->getInfo() == e) return true;

    NodoArbol<Elemento>* aux;
    aux = p->getHijoIzquierdo();
    while(aux != 0){
        if(buscarNodo(aux, e)) return true;
        aux = aux->getHermanoDerecho();
    }
    return false;
}

//Altura de un arbol
template <class Elemento>
int ArbolN<Elemento>::altura() const{
    return altura(this->nodoRaiz);
}

template <class Elemento>
int ArbolN<Elemento>::altura(NodoArbol<Elemento>* p) const{
    if(p == 0) return 0;

    int alturaMax = 0;
    NodoArbol<Elemento>* aux = p->getHijoIzquierdo();
    while(aux != 0){
        int alturaHijos = altura(aux);

        if (alturaHijos > alturaMax){
            alturaMax = alturaHijos;
        }

        aux = aux->getHermanoDerecho();
    }
    return 1 + alturaMax;

}

//Recorrido por niveles
template <class Elemento>
vector<Elemento> ArbolN<Elemento>::recorridoPorNiveles() const{
    vector<Elemento> recorrido;
    if (this->nodoRaiz == 0) {
        return recorrido;
    }

    queue<NodoArbol<Elemento>*> cola;
    cola.push(this->nodoRaiz);

    while (!cola.empty()) {
        NodoArbol<Elemento>* actual = cola.front();
        cola.pop();
        recorrido.push_back(actual->getInfo());

        NodoArbol<Elemento>* hijo = actual->getHijoIzquierdo();
        while (hijo != 0) {
            cola.push(hijo);
            hijo = hijo->getHermanoDerecho();
        }
    }

    return recorrido;
}

template<class Element>
map<Element, int> ArbolN<Element>::mapearNiveles() const{
    map<Element, int> result;

    if(pRaiz){
        mapearNiveles(this->pRaiz, result, 0);
    }

    return result;
}

template<class Element>
void ArbolN<Element>::mapearNiveles(const NodoN<Element> *pNodo, map<Element, int> &niveles, int nivel){
    if(!pNodo){
        return;
    }

    niveles[pNodo->getInfo()] = nivel;
    const NodoN<Element> *aux = pNodo->getHijoIzq();

    while(aux){
        mapearNiveles(aux, niveles, nivel+1);
        aux = aux->getHermanoDer();
    }
}

#endif
