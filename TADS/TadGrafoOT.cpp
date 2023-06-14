#include <iostream>
#include <fstream> //borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#include "TadLista.cpp"
#include "TadHeapOT.cpp"
using namespace std;

class Arista
{
public:
    int conexion;
    Arista(int conexion)
    {
        this->conexion = conexion;
    }
};

class Grafo
{

private:
    int cantVertices;
    int* grados;
    int tope;                      // la cantidad máxima de vértices que puede tener el grafo
    int *vertices;                  // vector que adentro tiene punteros a datos 
    Lista<int> *lugaresLibres;     // vector con posiciones libres.
    Lista<Arista*> **listaAdy; // Un array en el que cada posicion del array me representa un vertice, adentro de cada posicion del array tenemos un puntero a una lista encadenada que esa lista contiene punteros a aristas las cuales a su vez tiene origen  destino definido

public:
    Grafo(int tope)
    {
        this->tope = tope;
        this->grados = new int[this->tope];
        this->vertices = new int[this->tope];
        this->lugaresLibres = new Lista<int>(); // Creamos una lista que guarde los lugares libres
        this->listaAdy = new Lista<Arista*> *[tope];
        this->cantVertices = 0;

        for (int i = 0; i < this->tope; i++)
        {
            vertices[i] = 0; 
            this->listaAdy[i] = new Lista<Arista*>(); // Seteo a null
            this->lugaresLibres->insertarFin(i);
        }

    }

    void agregarVertice(int dato)
    {
        int posLibre = this->lugaresLibres->obtenerPpio();
        this->lugaresLibres->borrar(posLibre);
        this->vertices[posLibre] = dato;
        this->cantVertices++;
    }

    // Pre: Ambos nodos se encuentran en el vector vertices.
    void agregarArista(int origen, int conexion)
    {
        int posOrigen = origen-1; // Consigo la pos en la listaAdy
        Arista *arista = new Arista(conexion);
        this->listaAdy[posOrigen]->insertarPpio(arista);
        this->grados[conexion-1]++;
    }

    void borrarVertice(int dato)
    {
        int posBorrar = dato-1;
        this->vertices[posBorrar] = 0;
        this->cantVertices--;
        this->lugaresLibres->insertarPpio(posBorrar);
    }

    void borrarArista(int origen, int destino)
    {
        int posOrigen = origen-1;

        IteradorLista<Arista*> *iter = this->listaAdy[posOrigen]->obtenerIterador(); // iter es un puntero a la lista que apunta a la primera arista

        while (iter->hayElemento() && (iter->obtenerElemento())->conexion != destino)
        {
            iter->avanzar();
        }
        // Una vez salimos del while, estamos parados en la arista pedida, o esa arista nunca fue creada.

        if (iter->hayElemento()) // Si no entra, es porque no fue creada esa arista.
        {

            this->listaAdy[posOrigen]->borrar(iter->obtenerElemento());
        }
        iter = NULL;
        delete iter;
    }

    Lista<int> *ordenTopologico()
    {
        for (int i = 0; i < this->cantVertices; i++)
        {
            this->grados[i] = 0;
        }
        IteradorLista<Arista*> *iter = NULL;
        for (int i = 0; i < this->cantVertices; i++)
        {
            iter = this->listaAdy[i]->obtenerIterador();
            while (iter->hayElemento())
            {
                this->grados[(iter->obtenerElemento()->conexion)-1]++;
                iter->avanzar();
            }
        }
        // Hasta aca setteamos el vector "grados"
        Lista<int> *retorno = new Lista<int>();
        Heap<int>* miHeap = new Heap<int>(this->cantVertices);
        for (int i = 0; i < this->cantVertices; i++)
        {
            
            if (grados[i] == 0)
            {
                int vertice = this->vertices[i];
                miHeap->encolar(0, vertice); // nivel cero porque son los origenes (sin incidencias)
            }
        }

        while (!miHeap->esVacia())
        {
            nodoHeap<int>* cabezal = miHeap->topDato();
            
            int nivelConexion = cabezal->prioridad + 1;
            int vertice = cabezal->dato;
            
            int posOrigen = vertice -1; // posOrigen es el padre
            retorno->insertarFin(vertice);
            miHeap->desencolar();
            iter = this->listaAdy[posOrigen]->obtenerIterador();

            //Recorremos la lista de adyacencia y disminuimos uno a las aristas
            //Si el grado una vez borrado es 0 añadimos la conexion
            while (iter->hayElemento())
            {
                this->grados[(iter->obtenerElemento()->conexion)-1]--;
                if(this->grados[iter->obtenerElemento()->conexion -1] == 0){
                    
                    int vertice = iter->obtenerElemento()->conexion;
                    miHeap->encolar(nivelConexion, vertice);
                }
                iter->avanzar();
            }
        }


        return retorno;
    }
};

//eliminar factores repetidos de busacar pos
//sino dejar de hacerlo generico y hacerlo para int exclusivo y hacer coincidir la pos con el vertice restando uno o agregando un elemento al array de vertices 
//CUADNO AGREGAMOS ARISTA ADMINISTRAMOS EL GRADO DESDE ALLI ESO MEJORA