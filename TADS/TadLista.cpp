#include <iostream>
using namespace std;

class nodoLista
{
public:
    char* dato;
    nodoLista *sig;

    nodoLista(char* dato)
    {
        this->dato = dato;
        this->sig = NULL;
    }
};

class Lista
{

private:
    nodoLista* ppio;
    nodoLista* fin;
    int cantElem;

public:
    Lista()
    {
        this->ppio = NULL;
        this->fin = NULL;
        this->cantElem = 0;
    }

    void agregarElem(char* dato)
    {

        if (this->ppio == NULL)
        {
            nodoLista* elem = new nodoLista(dato);
            this->ppio = elem;
            this->fin = elem;
            this->cantElem++;
        }
        else
        {
            nodoLista* elem = new nodoLista(dato);
            this->fin->sig = elem;
            this->fin = elem;
            this->cantElem++;
        }
    }
};

int main(int argc, char const *argv[])
{

    HashCerrado* nuevo = new HashCerrado(3);
    nuevo->agregarElemento("hola",60);

return 0;
}
