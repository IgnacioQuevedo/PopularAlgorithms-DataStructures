template <class T>
class nodoHeap
{

    // LO QUE VA A TENER MI NODO HEAP
public:
    int prioridad;
    T dato;

    // LLAMO AL CONSTRUCTOR

    nodoHeap(int prioridad, T dato)
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

        if (pos == 0 || this->vecNodoHeap[pos] > this->vecNodoHeap[(pos - 1) / 2])
        { // Si el hijo es mas grande esta Ok.
            return;
        }
        else // Sino hago Swap
        {                                                              
            int aux = this->vecNodoHeap[(pos - 1) / 2];                // Me guardo el padre
            this->vecNodoHeap[(pos - 1) / 2] = this->vecNodoHeap[pos]; // el padre es el nuevo hijo
            this->vecNodoHeap[pos] = aux;                              // el hijo pasa a ser el padre
            flotar((pos - 1) / 2);                                     // Repito con el nuevo padre.
        }
    }

    int min(int posIzq, int posDer)
    {
        if (this->vecNodoHeap[posIzq]->prioridad < this->vecNodoHeap[posDer]->prioridad)
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
        // TENES PADRE, TENES UN HIJO IZQ, O TENES IZQ Y DER.
        // YA LLEGASTE AL ULTIMO HIJO, ENTONCES CORTAS

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

            if (this->tope == pos * 2 + 1)
            { // SI TU TOPE ES TU HIJO IZQ SIGNIFICA QUE TU ULTIMO HIJO ES EL IZQ, ENTONCES NO TENES DERECHO

                if (this->vecNodoHeap[pos]->prioridad > this->vecNodoHeap[pos * 2 + 1]->prioridad) // EN CASO QUE MI PADRE ES MAS GRANDE QUE MI UNICO HIJO (IZQ)
                {
                    // SWAP
                    int aux = this->vecNodoHeap[pos];
                    this->vecNodoHeap[pos] = this->vecNodoHeap[2 * pos + 1];
                    this->vecNodoHeap[2 * pos + 1] = aux;
                }
                else
                {
                    return; // ES PORQUE MI PADRE ES MAS CHICO QUE MI ULTIMO ELEMENTO, ENTONCES NADA MAS QUE HACER
                }
            }
            else
            { // ES PORQUE TIENE HIJO DER Y IZQ -> ME FIJO CUAL ES MAS CHICO PARA EL SWAP

                int posHijoChico = this->min(2 * pos + 1, 2 * pos + 2); // Me guardo la pos del de prio mas chico
                if (this->vecNodoHeap[pos]->prioridad > this->vecNodoHeap[posHijoChico]->prioridad)
                {

                    nodoHeap aux = new nodoHeap<T>(); // checkear si anda
                    aux = this->vecNodoHeap[pos];
                    this->vecNodoHeap[pos] = this->vecNodoHeap[posHijoChico];
                    this->vecNodoHeap[posHijoChico] = aux;
                    delete aux;
                    hundir(posHijoChico); //LLAMAS A LA RECURSION 
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
        this->vecNodoHeap = new vecNodoHeap<T>[maxElem];
    }

    void encolar(int prioridad, T dato)
    {
        if (this->tope <= this->maxElem)
        {
            this->vecNodoHeap[tope] = new nodoHeap<T>(prioridad, dato); // Te tenes que preguntar, donde añado, y eso es en tope, q seria la pos siguiente al ultimo eleme
            flotar(this->tope);
            this->tope = tope + 1; // El tope aumenta porque añadi un elemento
        }
    }

    void desencolar()
    {
        if(tope == 0){
            return;
        }

        delete this->vecNodoHeap[0];
        this->vecNodoHeap[0] = this->vecNodoHeap[tope]; //NO SERIA TOPE-1?? VER CON GONCHI
        delete this->vecNodoHeap[tope];
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

    T minimo()
    {
        return (this->heap[0])->dato;
    }

    bool esVacia()
    {
        return this->tope == 0:
    }

    int largo()
    {
        return this->tope;
    }
};