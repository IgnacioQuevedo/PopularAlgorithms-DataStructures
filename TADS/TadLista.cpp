#include <iostream>
using namespace std;


template <class T>

class NodoLista{


    //MI STRUCT (LO QUE VA A TENER MI NODOLISTA)
    private:
    NodoLista* sig;

    public:
    T dato;

    //TENGO QUE DARLE VIDA A LA LISTA (CONSTRUCTOR)

    NodoLista(T dato1){

        this->dato = dato1;
        this->sig = NULL;

    }

    agregarElem(T dato){

        if(NodoLista == NULL){

            NodoLista elem = new NodoLista(dato);
        }
        else{

            agregarElem(this->sig,dato);

        }
    }
};


































int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
