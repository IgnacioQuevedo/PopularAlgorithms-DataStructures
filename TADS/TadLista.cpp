#include <iostream>
using namespace std;


template <class T>

class nodoLista{
    public:
    T dato;
    nodoLista* sig;
    
    crearNodoLista(T dato){
        this->dato = dato;
        this->sig = NULL;
    }
};

template <class T>
class Lista{

    private:
    nodoLista<T>*ppio;
    nodoLista<T>*fin;
    int cantElem;

    public:

    crearLista(){
        this->ppio = NULL;
        this->fin = NULL;
        this->cantElem = 0;
    }

    public:

      
     agregarElem(T dato){
        if(this->ppio == NULL){

            nodoLista<T>* elem = new nodoLista(dato);
            elem->sig = NULL;
            this->ppio = elem;
            this->fin = elem;
            this->cantElem++;
        }
        else{
            nodoLista<T>* elem = new NodoLista(dato);
            elem->sig = NULL;
            this->fin->sig = elem;
            this->fin = elem;
            this->cantElem++;
        }
    }
};


































int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
