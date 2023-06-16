#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename T>
class nodoAvl
{
public:
    T dato;
    int apariciones;
    int altura;
    nodoAvl *izq;
    nodoAvl *der;

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

    int factorDeBalanceo(nodoAvl<T> *nodo)
    {
        if (nodo == NULL)
        {
            return 0;
        }
        return altura(nodo->der) - altura(nodo->izq);
    }

    int max(int a, int b)
    {
        if (a >= b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

    int altura(nodoAvl<T> *nodo)
    {

        if (nodo == NULL)
        {
            return 0;
        }
        else
        {
            return nodo->altura;
        }
    }

    nodoAvl<T> *rotarIzq(nodoAvl<T> *nodoActual)
    {

        nodoAvl<T> *nuevaRaiz = nodoActual->der; // El del medio es la nueva cabeza
        nodoAvl<T> *aux = nuevaRaiz->izq;        // Guardamos la izquierda de la nueva cabeza para no perderla

        nuevaRaiz->izq = nodoActual; // Re definimos la izquierda de la nueva cabeza
        nodoActual->der = aux;       // Lo colocamos a la der del nodoActual que queriamos rotar

        // Actualizamos las alturas
        nodoActual->altura = 1+ this->max(altura(nodoActual->izq), altura(nodoActual->der));
        nuevaRaiz->altura = 1+ this->max(altura(nuevaRaiz->izq), altura(nuevaRaiz->der));

        return nuevaRaiz;
    }

    nodoAvl<T> *rotarDer(nodoAvl<T> *nodoActual)
    {

        nodoAvl<T> *nuevaRaiz = nodoActual->izq; // El del medio es la nueva cabeza
        nodoAvl<T> *aux = nodoActual->der;       // Guardamos la derecha de la nueva cabeza para no perderla

        nuevaRaiz->der = nodoActual; // Re definimos la derecha de la nueva cabeza
        nodoActual->izq = aux;       // Lo colocamos a la izq del nodoActual que queriamos rotar

        // Actualizamos las alturas de cada nodo
        nodoActual->altura = 1+ this->max(altura(nodoActual->izq), altura(nodoActual->der));
        nuevaRaiz->altura = 1+ this->max(altura(nuevaRaiz->izq), altura(nuevaRaiz->der));

        return nuevaRaiz;
    }

    void insertarRec(nodoAvl<T> *&arbol, T dato)
    {
        if (arbol == NULL)
        {
            arbol = new nodoAvl<T>(dato);
            arbol->apariciones++;
            this->cantElem++;
            return;
        }
        else if (arbol->dato > dato)
        {
            insertarRec(arbol->izq, dato);
            return;
        }
        else if (arbol->dato < dato)
        {
            insertarRec(arbol->der, dato);
            return;
        }
        else
        {
            arbol->apariciones++;
            return;
        }

        // Actualizamos las alturas
        arbol->altura = 1 + this->max(altura(arbol->izq), altura(arbol->der));

         int balance = factorDeBalanceo(arbol);

        if (balance < -1 && dato < arbol->izq->dato)
        {
            arbol = rotarDer(arbol);
            return;
        }

        if (balance > 1 && arbol->der->dato < dato)
        {
            arbol = rotarIzq(arbol);
            return;
        }
        // La segunda condicion es para saber si es una rotacion simple o doble
        // Si pega zigzag es doble y sino es simple eso lo define esto:
        // && arbol->der->dato < dato
        //(ver codigo arriba)

        // Rotacion izquierda-derecha
        if (balance < -1 && dato > arbol->izq->dato)
        {
            arbol->izq = rotarIzq(arbol->izq);
            arbol = rotarDer(arbol);
            return;
        }

        // Rotacion derecha-izquierda
        if (balance > 1 && dato < arbol->der->dato)
        {
            arbol->der = rotarDer(arbol->der);
            arbol = rotarIzq(arbol);
            return;
        }
        
    }
    
public:
    Avl(int largoDado)
    {
        this->arbol = NULL;
        this->largoDado = largoDado;
        this->cantElem = 0;
    }

    void insertar(T dato)
    {
        this->insertarRec(this->arbol, dato);
    }

    nodoAvl<T>* inOrder()
    {
        inOrderRec(this->arbol);
    }
   
    void inOrderRec(nodoAvl<T> *&arbol)
    {
        if (arbol == NULL){
            return;
        }
        inOrderRec(arbol->der);
        cout << arbol->dato << " " << arbol->apariciones << endl;
        inOrderRec(arbol->izq);
    }

    bool esVacio()
    {
        return cantElem == 0;
    }
};
