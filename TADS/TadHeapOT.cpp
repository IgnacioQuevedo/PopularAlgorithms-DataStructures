#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class nodoDobleDato
{

public:
    int cantAristas;
    T vertice;

    nodoDobleDato(int cantAristas, T vertice)
    {
        this->cantAristas = cantAristas;
        this->vertice = vertice;
    }
};

template <class T>
class nodoHeap
{

    // LO QUE VA A TENER MI NODO HEAP
public:
    int prioridad; // es la cantidad de incidencias del nodo
    nodoDobleDato<T>* dato;

    // LLAMO AL CONSTRUCTOR

    nodoHeap(int prioridad, nodoDobleDato<T> *dato)
    {
        this->prioridad = prioridad; // THIS->PRIORIDAD ("LA PRIO DEL HEAP SERÁ LA QUE ME PASEN POR PARAMETRO")
        this->dato = dato;
    }
};

template <class T>
class Heap
{

private:
    int maxElem; // MAXIMA CANTIDAD POSIBLE
    int tope;    // CANT DE ELEMENTOS
    nodoHeap<T> **vecNodoHeap;

    void flotar(int pos)
    {
        bool swap = false;

        if (pos == 0 || (this->vecNodoHeap[pos]->prioridad) > (this->vecNodoHeap[(pos - 1) / 2]->prioridad))
        { // Si el hijo es mas grande esta Ok.
            return;
        }
        else if ((this->vecNodoHeap[pos]->prioridad) < (this->vecNodoHeap[(pos - 1) / 2]->prioridad)) // hago Swap
        {
            swap = true;
        }
        else
        { // LAS PRIORIDADES SON IGUALES
            if (this->vecNodoHeap[pos]->dato->cantAristas > this->vecNodoHeap[(pos - 1) / 2]->dato->cantAristas)
            {
                swap = true;
            }
            else if (this->vecNodoHeap[pos]->dato->cantAristas == this->vecNodoHeap[(pos - 1) / 2]->dato->cantAristas)
            {
                if (this->vecNodoHeap[pos]->dato->vertice < this->vecNodoHeap[(pos - 1) / 2]->dato->vertice)
                {
                    swap = true;
                }
            }
        }

        if (swap)
        {
            nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[(pos - 1) / 2]->prioridad, this->vecNodoHeap[(pos - 1) / 2]->dato); // Me guardo el padre
            delete this->vecNodoHeap[(pos - 1) / 2];
            this->vecNodoHeap[(pos - 1) / 2] = this->vecNodoHeap[pos]; // el padre es el nuevo hijo
            this->vecNodoHeap[pos] = aux;                              // el hijo pasa a ser el padre
            aux = NULL;
            delete aux;
            flotar((pos - 1) / 2); // Repito con el nuevo padre.
        }
    }

    int min(int posIzq, int posDer)
    {
        if (this->vecNodoHeap[posIzq]->prioridad < this->vecNodoHeap[posDer]->prioridad)
        {
            return posIzq;
        }
        else if (this->vecNodoHeap[posIzq]->prioridad == this->vecNodoHeap[posDer]->prioridad)
        {
            if (this->vecNodoHeap[posIzq]->dato->cantAristas > this->vecNodoHeap[posDer]->dato->cantAristas)
            {
                return posIzq;
            }
            else if (this->vecNodoHeap[posIzq]->dato->cantAristas < this->vecNodoHeap[posDer]->dato->cantAristas)
            {
                return posDer;
            }
            else
            {
                if (this->vecNodoHeap[posIzq]->dato->vertice < this->vecNodoHeap[posDer]->dato->vertice)
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
            // Si no tenes elemento derecho.
            if (this->tope == pos * 2 + 2)
            {
                if (this->vecNodoHeap[pos]->prioridad > this->vecNodoHeap[pos * 2 + 1]->prioridad)
                {
                    swap = true;
                }
                else if (this->vecNodoHeap[pos]->prioridad == this->vecNodoHeap[pos * 2 + 1]->prioridad)
                {
                    if (this->vecNodoHeap[pos]->dato->cantAristas < this->vecNodoHeap[pos * 2 + 1]->dato->cantAristas)
                    {
                        swap = true;
                    }
                    else if (this->vecNodoHeap[pos]->dato->cantAristas > this->vecNodoHeap[pos * 2 + 1]->dato->cantAristas)
                    {
                        return;
                    }
                    else{
                        if(this->vecNodoHeap[pos]->dato->vertice > this->vecNodoHeap[pos * 2 + 1]->dato->vertice){
                            swap = true;
                        }
                        else{
                            return;
                        }
                    }
                    if (swap)
                    {
                        nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[pos]->prioridad, this->vecNodoHeap[pos]->dato);
                        delete this->vecNodoHeap[pos];
                        this->vecNodoHeap[pos] = this->vecNodoHeap[pos*2+1];
                        this->vecNodoHeap[pos*2+1] = aux;
                        aux = NULL;
                        delete aux;
                        hundir(pos*2+1); // LLAMAS A LA RECURSION
                    }
                }
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
                    if (this->vecNodoHeap[pos]->prioridad == this->vecNodoHeap[posHijoChico]->prioridad)
                    {
                        if ((this->vecNodoHeap[pos]->dato->cantAristas < this->vecNodoHeap[posHijoChico]->dato->cantAristas))
                        {
                            swap = true;
                        }
                        else if (this->vecNodoHeap[pos]->dato->cantAristas == this->vecNodoHeap[posHijoChico]->dato->cantAristas){
                            if(this->vecNodoHeap[pos]->dato->vertice > this->vecNodoHeap[posHijoChico]->dato->vertice){
                                swap = true;
                            }
                            else{
                                return;
                            }
                        }
                    }
                }
                if (swap)
                {
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
    Heap(int maxElem)
    {
        this->maxElem = maxElem;
        this->tope = 0;
        this->vecNodoHeap = new nodoHeap<T> *[maxElem];
        for (int i = 0; i <= maxElem; i++)
        {
            this->vecNodoHeap[i] = NULL;
        }
    }

    void encolar(int prioridad, nodoDobleDato<T> *dato)
    {
        this->vecNodoHeap[tope] = new nodoHeap<T>(prioridad, dato); // TOPE = LA POS siguiente al ultimo eleme

        if (this->tope <= this->maxElem)
        {
            flotar(this->tope);
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
            hundir(0);
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

    int prioridadTope()
    {
        return (this->vecNodoHeap[0])->prioridad;
    }

    nodoHeap<T>* topDato()
    {
        return this->vecNodoHeap[0];
    }

    bool esVacia()
    {
        return this->tope == 0;
    }

    int largo()
    {
        return this->tope;
    }
};
