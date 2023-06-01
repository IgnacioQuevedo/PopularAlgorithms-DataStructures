#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class nodoHeap
{

    // LO QUE VA A TENER MI NODO HEAP
public:
    float prioridad;
    T dato;

    // LLAMO AL CONSTRUCTOR

    nodoHeap(float prioridad, T dato)
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

        if (pos == 0 || (this->vecNodoHeap[pos]->prioridad) <= (this->vecNodoHeap[(pos - 1) / 2]->prioridad))
        {           // Si el hijo es mas grande esta Ok.
            return; // SI SON IGUALES GONCHI, EL PADRE QUEDA DONDE ESTÁ -->fijate ACA, EL PADRE E HIJO TIENEN LA MISMA PRIO, EL PADRE QUEDO EN EL MISMO LUGAR
        }
        else // Sino hago Swap
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

    int max(int posIzq, int posDer)
    {
        if (this->vecNodoHeap[posIzq]->prioridad >= this->vecNodoHeap[posDer]->prioridad)
        {
            return posIzq;
        }
        else
        {
            return posDer;
        }
    }

    void hundir(int pos)
    {
        // POS ES EL PADRE
        //  TENES PADRE, TENES UN HIJO IZQ, O TENES IZQ Y DER.
        //  YA LLEGASTE AL ULTIMO HIJO, ENTONCES CORTAS

        if (this->tope == pos)
        { // SI LLEGASTE AL FINAL
            return;
        }
        else
        {
            // HAY DOS CASOS
            // CASO EN QUE TU HIJO DER ES NULO
            // CASO EN QUE TENES HIJO DER E HIJO IZQ

            // CASO BORDE QUE ESTES EN EL ARBOL DONDE LA DER ES NULA

            if (this->tope == pos * 2 + 2)
            { // SI TU TOPE ES TU HIJO DER SIGNIFICA QUE TU ULTIMO HIJO ES EL IZQ, ENTONCES NO TENES DERECHO. (YA QUE TOPE SIEMPRE APUNTA A LA POS SIGUIENTE DE TU ULTIMO NODO)

                if (this->vecNodoHeap[pos]->prioridad < this->vecNodoHeap[pos * 2 + 1]->prioridad) // EN CASO QUE MI PADRE ES MAS GRANDE QUE MI UNICO HIJO (IZQ)
                {
                    // SWAP
                    nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[pos]->prioridad, this->vecNodoHeap[pos]->dato);
                    delete this->vecNodoHeap[pos];
                    this->vecNodoHeap[pos] = this->vecNodoHeap[2 * pos + 1];
                    this->vecNodoHeap[2 * pos + 1] = aux;
                    aux = NULL;
                    delete aux;
                }
                else
                {
                    return; // ES PORQUE MI PADRE ES MAS GRANDE QUE MI ULTIMO ELEMENTO, ENTONCES NADA MAS QUE HACER
                }
            }
            else
            { // ES PORQUE TIENE HIJO DER Y IZQ -> ME FIJO CUAL ES MAS CHICO PARA EL SWAP
                if (2 * pos + 1 >= this->tope && 2 * pos + 2 >= this->tope)
                {
                    return;
                }
                int posHijoGrande = this->max(2 * pos + 1, 2 * pos + 2); // Me guardo la pos del de prio mas grande

                if (this->vecNodoHeap[pos]->prioridad < this->vecNodoHeap[posHijoGrande]->prioridad)
                {

                    nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[pos]->prioridad, this->vecNodoHeap[pos]->dato);
                    delete this->vecNodoHeap[pos];
                    this->vecNodoHeap[pos] = this->vecNodoHeap[posHijoGrande];
                    this->vecNodoHeap[posHijoGrande] = aux;
                    aux = NULL;
                    delete aux;
                    hundir(posHijoGrande); // LLAMAS A LA RECURSION
                }
                else
                {
                    return;
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

    void encolar(float prioridad, T dato)
    {
        if (this->tope <= this->maxElem)
        {
            this->vecNodoHeap[tope] = new nodoHeap<T>(prioridad, dato); // TOPE = LA POS siguiente al ultimo eleme
            flotar(this->tope);
            this->tope = tope + 1; // El tope aumenta porque añadi un elemento
        }
    }

    void desencolar()
    {
        if (tope == 0)
        {
            return;
        }
        nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[tope - 1]->prioridad, this->vecNodoHeap[tope - 1]->dato);
        delete this->vecNodoHeap[0];
        this->vecNodoHeap[0] = aux;
        delete this->vecNodoHeap[tope - 1];
        this->vecNodoHeap[tope - 1] = NULL;
        this->tope--;
        hundir(0);
    }

    void destruir()
    {

        for (int i = 0; i < this->tope; i++)
        {
            delete this->vecNodoHeap[i];
        }

        delete[] this->vecNodoHeap;
    }

    float maximaPrioridad()
    {
        return (this->vecNodoHeap[0])->prioridad;
    }

    T datoMayPrio()
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

    string dato1primero(T dato1, T dato2)
    {
        for (int i = 0; i < this->tope; i++)
        {
            if (this->vecNodoHeap[i]->dato == dato1)
            {
                return "es BFS";
            }
            if (this->vecNodoHeap[i]->dato == dato2)
            {
                return "es 93ENC";
            }
        }
        return "no hay ninguno";
    }
};

// int main(int argc, char const *argv[])
// {
//     Heap<char> *miHeap = new Heap<char>(5);
//     miHeap->encolar(6,'G');
//     miHeap->encolar(0,'O');
//     miHeap->encolar(1,'I');
//     miHeap->encolar(5,'S');
//     miHeap->encolar(9,'P');
//     miHeap->desencolar();
//     return 0;
// }
