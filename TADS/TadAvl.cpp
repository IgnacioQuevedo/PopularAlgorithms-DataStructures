#include <iostream>
using namespace std;

template <typename T>
class nodoAvl
{
public:
    T dato;
    int apariciones;
    nodoAvl *izq;
    nodoAvl *der;
    int altura; 

    nodoAvl(T dato)
    {
        this->dato = dato;
        this->izq = NULL;
        this->der = NULL;
        this->apariciones = 0;
        this->altura = 0;
    }
};

template <typename T>

class Avl
{

private:
    nodoAvl<T> *arbol;
    int cantElem;
    int largoDado;


    nodoAvl<T>* rotarIzq(nodoAvl<T>* nodo){

    }

    nodoAvl<T>* rotarDer(nodoAvl<T>* nodo){

        nodoAvl<T>* nuevaRaiz = nodo->izq;
        nodoAvl<T>* temporal = nodo->der;

        nuevaRaiz->der = nodo;

    }

public:
    Avl(int largoDado)
    {
        this->arbol = NULL;
        this->largoDado = largoDado;
        this->cantElem = 0;
    }

    nodoAvl<T>* insertar(nodoAvl<T>* arbol, T dato){
        
    
    
    
    }

    



};

int main(int argc, char const *argv[])
{

    return 0;
}
