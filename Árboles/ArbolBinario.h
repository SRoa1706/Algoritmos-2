#ifndef ARBOLBINARIO_H_
#define ARBOLBINARIO_H_

#include <vector>
#include "NodoAB.h"
#include <cmath>
#include <queue>
#include <stdexcept>

using namespace std;

template <class Elemento>
class ArbolBinario {
    private:
        NodoAB<Elemento>* nodoRaiz;
        int peso;
        static NodoAB<Elemento>* copiarNodos(const NodoAB<Elemento>* p);
        static void destruirNodos(NodoAB<Elemento>* p);
        static NodoAB<Elemento>* construirNodos(const vector<Elemento>& inorden, int inicioInorden,
            int finInorden, const vector<Elemento>& postorden, int inicioPostorden, int finPostorden,
            bool& valido
        );
        static NodoAB<Elemento>* construirNodosInordenPreorden(const vector<Elemento>& inorden, int inicioInorden,
            int finInorden, const vector<Elemento>& preorden, int inicioPreorden,
            int finPreorden, bool& valido
        );

        //recorridos
        void preorden(vector<Elemento> &preorden, NodoAB<Elemento>* p);
        void inorden(vector<Elemento> &inorden, NodoAB<Elemento>* p);
        void postorden(vector<Elemento> &postorden, NodoAB<Elemento>* p);

        //Ejercicios
        int contarHojas(NodoAB<Elemento>* p);
        int distanciaNivel(Elemento a, Elemento b, NodoAB<Elemento>* p);
        int profundidad(NodoAB<Elemento>* p, const Elemento& valor, int nivel) const;
        NodoAB<Elemento>* getLCA(NodoAB<Elemento>* p, Elemento a, Elemento b);
        
    public:
        ArbolBinario();
        ArbolBinario(const ArbolBinario<Elemento>& arbol);
        ~ArbolBinario();
        ArbolBinario<Elemento>& operator=(const ArbolBinario<Elemento>& arbol);
        void copiar(const ArbolBinario<Elemento>& arbol);
        bool esNulo() const;
        Elemento raiz() const;
        int getPeso() const;
        ArbolBinario<Elemento> getHijoIzquierdo();
        ArbolBinario<Elemento> getHijoDerecho();
        int distanciaEntreNodos(Elemento a, Elemento b);

        //Recorridos

        vector<Elemento> inorden();
        vector<Elemento> postorden();
        vector<Elemento> preorden();

        //Ejercicios
        int contarHojas();
        int distanciaNivel(Elemento a, Elemento b);
        void construirDesdeInordenPostorden(const vector<Elemento>& inorden, const vector<Elemento>& postorden);
        void construirDesdeInordenPreorden(const vector<Elemento>& inorden, const vector<Elemento>& preorden);
};

template <class Elemento>
Elemento ArbolBinario<Elemento>::raiz() const {
    if (this->nodoRaiz == 0) return Elemento();
    return this->nodoRaiz->getInfo();
}

template <class Elemento>
ArbolBinario<Elemento>::ArbolBinario() {
    this->nodoRaiz = 0;
    this->peso = 0;
}

template <class Elemento>
ArbolBinario<Elemento>::ArbolBinario(const ArbolBinario<Elemento>& arbol)
    : nodoRaiz(copiarNodos(arbol.nodoRaiz)), peso(arbol.peso) {}

template <class Elemento>
ArbolBinario<Elemento>::~ArbolBinario() {
    destruirNodos(this->nodoRaiz);
}

template <class Elemento>
ArbolBinario<Elemento>& ArbolBinario<Elemento>::operator=(const ArbolBinario<Elemento>& arbol) {
    if (this != &arbol) {
        copiar(arbol);
    }
    return *this;
}

template <class Elemento>
void ArbolBinario<Elemento>::copiar(const ArbolBinario<Elemento>& arbol) {
    if (this != &arbol) {
        NodoAB<Elemento>* nuevaRaiz = copiarNodos(arbol.nodoRaiz);
        destruirNodos(this->nodoRaiz);
        this->nodoRaiz = nuevaRaiz;
        this->peso = arbol.peso;
    }
}

template <class Elemento>
NodoAB<Elemento>* ArbolBinario<Elemento>::copiarNodos(const NodoAB<Elemento>* p) {
    if (p == 0) {
        return 0;
    }

    NodoAB<Elemento>* nuevo = new NodoAB<Elemento>();
    nuevo->setInfo(p->getInfo());
    nuevo->setHijoIzquierdo(copiarNodos(p->getHijoIzquierdo()));
    nuevo->setHijoDerecho(copiarNodos(p->getHijoDerecho()));
    return nuevo;
}

template <class Elemento>
void ArbolBinario<Elemento>::destruirNodos(NodoAB<Elemento>* p) {
    if (p == 0) {
        return;
    }
    destruirNodos(p->getHijoIzquierdo());
    destruirNodos(p->getHijoDerecho());
    delete p;
}

template <class Elemento>
NodoAB<Elemento>* ArbolBinario<Elemento>::construirNodos(
    const vector<Elemento>& inorden,
    int inicioInorden,
    int finInorden,
    const vector<Elemento>& postorden,
    int inicioPostorden,
    int finPostorden,
    bool& valido
) {
    if (inicioInorden > finInorden) {
        return 0;
    }

    if (!valido || finInorden - inicioInorden != finPostorden - inicioPostorden) {
        valido = false;
        return 0;
    }

    const Elemento& valorRaiz = postorden[finPostorden];
    int posicionRaiz = inicioInorden;
    while (posicionRaiz <= finInorden && inorden[posicionRaiz] != valorRaiz) {
        ++posicionRaiz;
    }
    if (posicionRaiz > finInorden) {
        valido = false;
        return 0;
    }

    int cantidadIzquierda = posicionRaiz - inicioInorden;
    NodoAB<Elemento>* nuevo = new NodoAB<Elemento>();
    nuevo->setInfo(valorRaiz);
    nuevo->setHijoIzquierdo(construirNodos(
        inorden,
        inicioInorden,
        posicionRaiz - 1,
        postorden,
        inicioPostorden,
        inicioPostorden + cantidadIzquierda - 1,
        valido
    ));
    if (!valido) {
        destruirNodos(nuevo);
        return 0;
    }

    nuevo->setHijoDerecho(construirNodos(
        inorden,
        posicionRaiz + 1,
        finInorden,
        postorden,
        inicioPostorden + cantidadIzquierda,
        finPostorden - 1,
        valido
    ));
    if (!valido) {
        destruirNodos(nuevo);
        return 0;
    }

    return nuevo;
}

template <class Elemento>
NodoAB<Elemento>* ArbolBinario<Elemento>::construirNodosInordenPreorden(
    const vector<Elemento>& inorden,
    int inicioInorden,
    int finInorden,
    const vector<Elemento>& preorden,
    int inicioPreorden,
    int finPreorden,
    bool& valido
) {
    if (inicioInorden > finInorden) {
        return 0;
    }

    if (!valido || finInorden - inicioInorden != finPreorden - inicioPreorden) {
        valido = false;
        return 0;
    }

    const Elemento& valorRaiz = preorden[inicioPreorden];
    int posicionRaiz = inicioInorden;
    while (posicionRaiz <= finInorden && inorden[posicionRaiz] != valorRaiz) {
        ++posicionRaiz;
    }
    if (posicionRaiz > finInorden) {
        valido = false;
        return 0;
    }

    int cantidadIzquierda = posicionRaiz - inicioInorden;
    NodoAB<Elemento>* nuevo = new NodoAB<Elemento>();
    nuevo->setInfo(valorRaiz);
    nuevo->setHijoIzquierdo(construirNodosInordenPreorden(
        inorden,
        inicioInorden,
        posicionRaiz - 1,
        preorden,
        inicioPreorden + 1,
        inicioPreorden + cantidadIzquierda,
        valido
    ));
    if (!valido) {
        destruirNodos(nuevo);
        return 0;
    }

    nuevo->setHijoDerecho(construirNodosInordenPreorden(
        inorden,
        posicionRaiz + 1,
        finInorden,
        preorden,
        inicioPreorden + cantidadIzquierda + 1,
        finPreorden,
        valido
    ));
    if (!valido) {
        destruirNodos(nuevo);
        return 0;
    }

    return nuevo;
}

template <class Elemento>
void ArbolBinario<Elemento>::construirDesdeInordenPostorden(
    const vector<Elemento>& inorden,
    const vector<Elemento>& postorden
) {
    if (inorden.size() != postorden.size()) {
        throw invalid_argument("Los recorridos deben tener la misma cantidad de elementos");
    }

    for (unsigned int i = 0; i < inorden.size(); ++i) {
        for (unsigned int j = i + 1; j < inorden.size(); ++j) {
            if (inorden[i] == inorden[j] || postorden[i] == postorden[j]) {
                throw invalid_argument("Los recorridos deben contener elementos unicos");
            }
        }
    }

    bool valido = true;
    NodoAB<Elemento>* nuevaRaiz = construirNodos(
        inorden,
        0,
        static_cast<int>(inorden.size()) - 1,
        postorden,
        0,
        static_cast<int>(postorden.size()) - 1,
        valido
    );
    if (!valido) {
        throw invalid_argument("Los vectores no representan recorridos del mismo arbol");
    }

    destruirNodos(this->nodoRaiz);
    this->nodoRaiz = nuevaRaiz;
    this->peso = static_cast<int>(inorden.size());
}

template <class Elemento>
void ArbolBinario<Elemento>::construirDesdeInordenPreorden(
    const vector<Elemento>& inorden,
    const vector<Elemento>& preorden
) {
    if (inorden.size() != preorden.size()) {
        throw invalid_argument("Los recorridos deben tener la misma cantidad de elementos");
    }

    for (unsigned int i = 0; i < inorden.size(); ++i) {
        for (unsigned int j = i + 1; j < inorden.size(); ++j) {
            if (inorden[i] == inorden[j] || preorden[i] == preorden[j]) {
                throw invalid_argument("Los recorridos deben contener elementos unicos");
            }
        }
    }

    bool valido = true;
    NodoAB<Elemento>* nuevaRaiz = construirNodosInordenPreorden(
        inorden,
        0,
        static_cast<int>(inorden.size()) - 1,
        preorden,
        0,
        static_cast<int>(preorden.size()) - 1,
        valido
    );
    if (!valido) {
        throw invalid_argument("Los vectores no representan recorridos del mismo arbol");
    }

    destruirNodos(this->nodoRaiz);
    this->nodoRaiz = nuevaRaiz;
    this->peso = static_cast<int>(inorden.size());
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

template <class Elemento>
ArbolBinario<Elemento> ArbolBinario<Elemento>::getHijoIzquierdo() {
    ArbolBinario<Elemento> hijo;
    hijo.nodoRaiz = copiarNodos(this->nodoRaiz == 0 ? 0 : this->nodoRaiz->getHijoIzquierdo());
    hijo.peso = 0;
    return hijo;
}

template <class Elemento>
ArbolBinario<Elemento> ArbolBinario<Elemento>::getHijoDerecho() {
    ArbolBinario<Elemento> hijo;
    hijo.nodoRaiz = copiarNodos(this->nodoRaiz == 0 ? 0 : this->nodoRaiz->getHijoDerecho());
    hijo.peso = 0;
    return hijo;
}

//Recorridos

template <class Elemento>
vector<Elemento> ArbolBinario<Elemento>::inorden(){
    vector<Elemento> inorden;
    this->inorden(inorden, this->nodoRaiz);
    return inorden;
}

template <class Elemento>
void ArbolBinario<Elemento>::inorden(vector<Elemento> &inorden, NodoAB<Elemento>* p){
    if(p != 0){
        this->inorden(inorden, p->getHijoIzquierdo());
        inorden.push_back(p->getInfo());
        this->inorden(inorden, p->getHijoDerecho());
    }
}

template <class Elemento>
vector<Elemento> ArbolBinario<Elemento>::postorden(){
    vector<Elemento> postorden;
    this->postorden(postorden, this->nodoRaiz);
    return postorden;
}

template <class Elemento>
void ArbolBinario<Elemento>::postorden(vector<Elemento> &postorden, NodoAB<Elemento>* p){
    if(p != 0){
        this->postorden(postorden, p->getHijoIzquierdo());
        this->postorden(postorden, p->getHijoDerecho());
        postorden.push_back(p->getInfo());
    }
}

template <class Elemento>
vector<Elemento> ArbolBinario<Elemento>::preorden(){
    vector<Elemento> preorden;
    this->preorden(preorden, this->nodoRaiz);
    return preorden;
}

template <class Elemento>
void ArbolBinario<Elemento>::preorden(vector<Elemento> &preorden, NodoAB<Elemento>* p){
    if(p != 0){
        preorden.push_back(p->getInfo());
        this->preorden(preorden, p->getHijoIzquierdo());
        this->preorden(preorden, p->getHijoDerecho());
    }
}

//Ejercicios para volverme un master

//contar Hojas
template <class Elemento>
int ArbolBinario<Elemento>::contarHojas(){
    return contarHojas(this->nodoRaiz);    
}

template <class Elemento>
int ArbolBinario<Elemento>::contarHojas(NodoAB<Elemento>* p){
    if(p == 0){
        return 0;
    }
    if(p->getHijoIzquierdo() == 0 && p->getHijoDerecho() == 0){
        return 1;
    }
    return contarHojas(p->getHijoIzquierdo()) + contarHojas(p->getHijoDerecho());
}

template <class Elemento>
int ArbolBinario<Elemento>::distanciaNivel(Elemento a, Elemento b){
    return distanciaNivel(a, b, nodoRaiz);
}

template <class Elemento>
int ArbolBinario<Elemento>::distanciaNivel(Elemento a, Elemento b, NodoAB<Elemento>* p) {
    if (p == 0) {
        return -1; // Árbol vacío
    }

    queue<NodoAB<Elemento>*> cola;
    cola.push(p);

    int nivelActual = 0;
    int nivelA = -1;
    int nivelB = -1;
    while (!cola.empty()) {
        int tamNivel = cola.size();

        while (tamNivel > 0) {
            NodoAB<Elemento>* actual = cola.front();
            cola.pop();

            // Verificar si el nodo actual coincide con a o b
            if (actual->getInfo() == a && nivelA == -1){
                nivelA = nivelActual;
            }
            if (actual->getInfo() == b && nivelB == -1){
                nivelB = nivelActual;
            }

            // La distancia entre niveles es la diferencia absoluta de sus niveles.
            if (nivelA != -1 && nivelB != -1){
                int diferencia = nivelA > nivelB
                    ? nivelA - nivelB
                    : nivelB - nivelA;
                return diferencia;
            }

            // Encolar hijos si existen
            if (actual->getHijoIzquierdo() != 0){
                cola.push(actual->getHijoIzquierdo());
            }
            if (actual->getHijoDerecho() != 0){
                cola.push(actual->getHijoDerecho());
            }

            tamNivel--;
        }

        nivelActual++;
    }

    // Retorna -1 si uno o ambos elementos no existen en el árbol
    return -1;
} 

template <class Elemento>
NodoAB<Elemento>* ArbolBinario<Elemento>::getLCA(NodoAB<Elemento>* p, Elemento a, Elemento b) {
    if (p == 0) {
        return 0;
    }

    if (p->getInfo() == a || p->getInfo() == b) {
        return p;
    }

    NodoAB<Elemento>* lcaIzq = getLCA(p->getHijoIzquierdo(), a, b);
    NodoAB<Elemento>* lcaDer = getLCA(p->getHijoDerecho(), a, b);

    if (lcaIzq != 0 && lcaDer != 0) {
        return p;
    }

    return lcaIzq != 0 ? lcaIzq : lcaDer;
}

template <class Elemento>
int ArbolBinario<Elemento>::profundidad(NodoAB<Elemento>* p, const Elemento& valor, int nivel) const {
    if (p == 0) {
        return -1;
    }
    if (p->getInfo() == valor) {
        return nivel;
    }

    int izq = profundidad(p->getHijoIzquierdo(), valor, nivel + 1);
    if (izq != -1) {
        return izq;
    }

    return profundidad(p->getHijoDerecho(), valor, nivel + 1);
}

template <class Elemento>
int ArbolBinario<Elemento>::distanciaEntreNodos(Elemento a, Elemento b) {
    if (this->nodoRaiz == 0) {
        return -1;
    }
    if (a == b) {
        return 0;
    }

    int profundidadA = profundidad(this->nodoRaiz, a, 0);
    int profundidadB = profundidad(this->nodoRaiz, b, 0);
    if (profundidadA == -1 || profundidadB == -1) {
        return -1;
    }

    NodoAB<Elemento>* lca = getLCA(this->nodoRaiz, a, b);
    if (lca == 0) {
        return -1;
    }

    int profundidadLCA = profundidad(this->nodoRaiz, lca->getInfo(), 0);
    return profundidadA + profundidadB - 2 * profundidadLCA;
}

#endif