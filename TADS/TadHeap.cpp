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
    bool esMinHeap;

    void flotarMax(int pos)
    {

        if (pos == 0 || (this->vecNodoHeap[pos]->prioridad) <= (this->vecNodoHeap[(pos - 1) / 2]->prioridad))
        { // Si el hijo es mas chico esta Ok.
            return;
        }
        else // Sino hago Swap
        {
            nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[(pos - 1) / 2]->prioridad, this->vecNodoHeap[(pos - 1) / 2]->dato); // Me guardo el padre
            delete this->vecNodoHeap[(pos - 1) / 2];
            this->vecNodoHeap[(pos - 1) / 2] = this->vecNodoHeap[pos]; // el padre es el nuevo hijo
            this->vecNodoHeap[pos] = aux;                              // el hijo pasa a ser el padre
            aux = NULL;
            delete aux;
            flotarMax((pos - 1) / 2); // Repito con el nuevo padre.
        }
    }

    void flotarMin(int pos)
    {

        if (pos == 0 || (this->vecNodoHeap[pos]->prioridad) >= (this->vecNodoHeap[(pos - 1) / 2]->prioridad))
        { // Si el hijo es mas grande esta Ok.
            return;
        }
        else // Sino hago Swap
        {
            nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[(pos - 1) / 2]->prioridad, this->vecNodoHeap[(pos - 1) / 2]->dato); // Me guardo el padre
            delete this->vecNodoHeap[(pos - 1) / 2];
            this->vecNodoHeap[(pos - 1) / 2] = this->vecNodoHeap[pos]; // el padre es el nuevo hijo
            this->vecNodoHeap[pos] = aux;                              // el hijo pasa a ser el padre
            aux = NULL;
            delete aux;
            flotarMin((pos - 1) / 2); // Repito con el nuevo padre.
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

    int min(int posIzq, int posDer)
    {
        if (this->vecNodoHeap[posIzq]->prioridad <= this->vecNodoHeap[posDer]->prioridad)
        {
            return posIzq;
        }
        else
        {
            return posDer;
        }
    }

    void hundirMax(int pos)
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
                    hundirMax(posHijoGrande); // LLAMAS A LA RECURSION
                }
                else
                {
                    return;
                }
            }
        }
    }

    void hundirMin(int pos)
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

                if (this->vecNodoHeap[pos]->prioridad > this->vecNodoHeap[pos * 2 + 1]->prioridad) // EN CASO QUE MI PADRE ES MAS GRANDE QUE MI UNICO HIJO (IZQ)
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
                int posHijoChico = this->min(2 * pos + 1, 2 * pos + 2); // Me guardo la pos del de prio mas grande

                if (this->vecNodoHeap[pos]->prioridad > this->vecNodoHeap[posHijoChico]->prioridad)
                {

                    nodoHeap<T> *aux = new nodoHeap<T>(this->vecNodoHeap[pos]->prioridad, this->vecNodoHeap[pos]->dato);
                    delete this->vecNodoHeap[pos];
                    this->vecNodoHeap[pos] = this->vecNodoHeap[posHijoChico];
                    this->vecNodoHeap[posHijoChico] = aux;
                    aux = NULL;
                    delete aux;
                    hundirMin(posHijoChico); // LLAMAS A LA RECURSION
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
    Heap(int maxElem, bool esMinHeap)
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

    void encolar(float prioridad, T dato)
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
            if(this->esMinHeap){
                hundirMin(0);
            }
            else{
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

    bool chequearHeap (){
        for(int i =0; i<this->tope; i++){
            float b = this->vecNodoHeap[i]->prioridad;
            if(b <= 0.1 && b != 0){
                return true;
            }
        }
        return false;
    }

};
