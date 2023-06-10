#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class nodoHeap
{

    // LO QUE VA A TENER MI NODO HEAP
public:
    int prioridad; // Sera el nivel
    T dato;        // Sera el nodoDobleDato con -->EL T vertice, y la int cantAristas

    // LLAMO AL CONSTRUCTOR

    nodoHeap(float prioridad, T dato)
    {
        this->prioridad = prioridad; // THIS->PRIORIDAD ("LA PRIO DEL HEAP SERÁ LA QUE ME PASEN POR PARAMETRO")
        this->dato = dato;
    }
};

template <class T>
class HeapOT
{

private:
    int maxElem; // MAXIMA CANTIDAD POSIBLE
    int tope;    // CANT DE ELEMENTOS
    nodoHeap<T> **vecNodoHeap;

    void flotar(int pos)
    {

        if (pos == 0 || (this->vecNodoHeap[pos]->prioridad) > (this->vecNodoHeap[(pos - 1) / 2]->prioridad))
        { // Si el hijo es mas grande esta Ok.
            return;
        }
        else if ((this->vecNodoHeap[pos]->dato->cantAristas > this->vecNodoHeap[(pos - 1) / 2]->dato->cantAristas) || (this->vecNodoHeap[pos]->dato->valor > this->vecNodoHeap[(pos - 1) / 2]->dato->valor))
        {
            // SWAP
            nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[(pos - 1) / 2]->prioridad, this->vecNodoHeap[(pos - 1) / 2]->dato); // Me guardo el padre
            delete this->vecNodoHeap[(pos - 1) / 2];
            this->vecNodoHeap[(pos - 1) / 2] = this->vecNodoHeap[pos]; // el padre es el nuevo hijo
            this->vecNodoHeap[pos] = aux;                              // el hijo pasa a ser el padre
            aux = NULL;
            delete aux;
            flotar((pos - 1) / 2); // Repito con el nuevo padre.
        }
    }
}

int minOT(int posIzq, int posDer)
{
    if (this->vecNodoHeap[posIzq]->prioridad < this->vecNodoHeap[posDer]->prioridad)
    {
        return posIzq;
    }
    if (this->vecNodoHeap[posIzq]->prioridad == this->vecNodoHeap[posDer]->prioridad)
    {
        if (this->vecNodoHeap[posIzq]->dato->cantAristas > this->vecNodoHeap[posIzq]->dato->cantAristas)
        {
            return posIzq;
        }
        else if (this->vecNodoHeap[posIzq]->dato->cantAristas < this->vecNodoHeap[posIzq]->dato->cantAristas)
        {
            return posDer;
        }
        else
        {
            if (this->vecNodoHeap[posIzq]->dato->valor <= this->vecNodoHeap[posDer]->dato->valor)
            {
                return posIzq;
            }
            else
            {
                return posDer;
            }
        }
    }
    
    else
    {
        return posDer;
    }
}

void hundir(int pos)
{
    bool swap = false;

    if (this->tope == pos)
    { // SI LLEGASTE AL FINAL
        return;
    }
    else
    {
        //Si no tenes elemento derecho.
        if (this->tope == pos * 2 + 2)
        { 
            if (this->vecNodoHeap[pos]->prioridad > this->vecNodoHeap[pos * 2 + 1]->prioridad) 
            {
                swap = true;
            }

            else if (this->vecNodoHeap[pos]->dato->cantAristas < this->vecNodoHeap[pos * 2 + 1]->dato->cantAristas)
            {
                swap = true;
            }
            else if (this->vecNodoHeap[pos]->dato->valor > this->vecNodoHeap[pos * 2 + 1]->dato->valor)
            {
                swap = true;
            }
            if (swap)
            {
                nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[pos]->prioridad, this->vecNodoHeap[pos]->dato);
                delete this->vecNodoHeap[pos];
                this->vecNodoHeap[pos] = this->vecNodoHeap[posHijoChico];
                this->vecNodoHeap[posHijoChico] = aux;
                aux = NULL;
                delete aux;
                hundir(posHijoChico); // LLAMAS A LA RECURSION
            }
            if
            
            else
            {
                return;
            }
        }

        else
        { // ES PORQUE TIENE HIJO DER Y IZQ -> ME FIJO CUAL ES MAS CHICO PARA EL SWAP
            if (2 * pos + 1 >= this->tope && 2 * pos + 2 >= this->tope)
            {
                return;
            }
            int posHijoChico = this->min(2 * pos + 1, 2 * pos + 2); // Me guardo el elemento mas chico de mis hijos.

            if (this->vecNodoHeap[pos]->prioridad > this->vecNodoHeap[posHijoChico]->prioridad)
            {
               swap = true; 
            }
            else
            {
                if(this->vecNodoHeap[pos]->prioridad == this->vecNodoHeap[posHijoChico]->prioridad){
                    if((this->vecNodoHeap[pos]->dato->cantAristas < this->vecNodoHeap[posHijoChico]->dato->cantAristas)){
                        swap = true;
                    }
                    else if()
                }
            }

            if(swap){
                nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[pos]->prioridad, this->vecNodoHeap[pos]->dato);
                delete this->vecNodoHeap[pos];
                this->vecNodoHeap[pos] = this->vecNodoHeap[posHijoChico];
                this->vecNodoHeap[posHijoChico] = aux;
                aux = NULL;
                delete aux;
                hundir(posHijoChico); 
            }
        }
    }
}

public:
// CREO EL HEAP

HeapOT(int maxElem, bool esMinHeap)
{
    this->maxElem = maxElem;
    this->tope = 0;
    this->vecNodoHeap = new nodoHeap<T> *[maxElem];
    this->esMinHeap = esMinHeap;
    for (int i = 0; i <= maxElem; i++)
    {
        this->vecNodoHeap[i] = NULL;
    }
}

void encolar(int prioridad, T dato)
{
    this->vecNodoHeap[tope] = new nodoHeap<T>(prioridad, dato); // TOPE = LA POS siguiente al ultimo eleme
    if (esMinHeap)
    {
        if (this->tope <= this->maxElem)
        {
            flotarMin(this->tope);
        }
    }
    else
    {
        if (this->tope <= this->maxElem)
        {
            flotarMax(this->tope);
        }
    }
    this->tope = tope + 1; // El tope aumenta porque añadi un elemento
}

void desencolar()
{
    if (tope == 0)
    {
        return;
    }
    else
    {

        nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[tope - 1]->prioridad, this->vecNodoHeap[tope - 1]->dato);
        delete this->vecNodoHeap[0];
        this->vecNodoHeap[0] = aux;
        delete this->vecNodoHeap[tope - 1];
        this->vecNodoHeap[tope - 1] = NULL;
        this->tope--;
        if (this->esMinHeap)
        {
            hundirMin(0);
        }
        else
        {
            hundirMax(0);
        }
    }
}

void destruir()
{

    for (int i = 0; i < this->tope; i++)
    {
        delete this->vecNodoHeap[i];
    }

    delete[] this->vecNodoHeap;
}

float prioridadTope()
{
    return (this->vecNodoHeap[0])->prioridad;
}

T topDato()
{
    return (this->vecNodoHeap[0]->dato);
}

bool esVacia()
{
    return this->tope == 0;
}

int largo()
{
    return this->tope;
}

bool chequearHeap()
{
    for (int i = 0; i < this->tope; i++)
    {
        float b = this->vecNodoHeap[i]->prioridad;
        if (b <= 0.1 && b != 0)
        {
            return true;
        }
    }
    return false;
}
}
;
