#include <iostream>
#include <fstream> //borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#include "TadLista.cpp"
#include "TadHeapOT.cpp"
using namespace std;
// grafo con lista de adyacencia y una cola prioridad ejercicio 4!!!!!!
//  GRAFO EN EJERCICIO 5 SE IMPLEMENTA CON ES UN GRAFO DISPEROS DEVILEMNET CONEXO Y DIRIGIDO TENER
// USAR COLA PRIORIDAD PARA PODER IR ELIGIENDO Y QUE TENGA UN ORDEN V LOG, HAY QUE SABER RAPIDO EL NUMERP QUE HAY QUE IR SACANDO, ENTONCES VAMOS A IR AGREGANDO LOS VERTICES EN LA COLA PRIORIDAD POR ORDEN ASCENDENTE.LA REGLA ES QUE CUMPLA CON LA COLA PRIORIDAD Y SER UN ORDEN TOPOLoGICO.REGLA DE QUE SEA EN ESE ORDEN NUMERICO ENTONCES TENES 2 PRIORIDADES QUE NO ES UNA ES UNA DOBLE LA PRIMERA ES EL GRADO O SEA QUE TAN ELJOS ESTA DE LO QUE VOS MPOSTRASTE QUE ES LA RAIZ Y EL SEGUNDODA DATO ES EL NUMERO // DE ARISTAS QUE TIENE??

template <class T>
class Arista
{
public:
    T conexion;
    Arista(T conexion)
    {
        this->conexion = conexion;
    }
};

template <class T>
class Grafo
{

private:
    int cantVertices;
    int cantAristas;
    int tope;                      // la cantidad máxima de vértices que puede tener el grafo
    T **vertices;                  // vector que adentro tiene punteros a datos tipo T ("Vertice")
    Lista<int> *lugaresLibres;     // vector con posiciones libres.
    Lista<Arista<T> *> **listaAdy; // Un array en el que cada posicion del array me representa un vertice, adentro de cada posicion del array tenemos un puntero a una lista encadenada que esa lista contiene punteros a aristas las cuales a su vez tiene origen  destino definido

    int buscarPos(T vertice)
    {
        for (int i = 0; i < this->tope; i++)
        {
            if (this->vertices[i] && *this->vertices[i] == vertice)
            {
                return i;
            }
        }
        return -1;
    }

public:
    Grafo(int tope)
    {
        this->tope = tope;
        this->vertices = new T *[tope];
        this->lugaresLibres = new Lista<int>(); // Creamos una lista que guarde los lugares libres
        this->listaAdy = new Lista<Arista<T> *> *[tope];
        this->cantVertices = 0;
        this->cantAristas = 0;

        for (int i = 0; i < tope; i++)
        {
            vertices[i] = NULL; // Seteo a null, (Porque es un vector de vectores, sino apunta a basura.)
        }

        for (int i = 0; i < this->tope; i++)
        {
            this->listaAdy[i] = new Lista<Arista<T> *>(); // Seteo a null
        }

        for (int i = 0; i < tope; i++)
        {
            this->lugaresLibres->insertarFin(i);
        }
    }

    void agregarVertice(T dato)
    {
        int posLibre = this->lugaresLibres->obtenerPpio();
        this->lugaresLibres->borrar(posLibre);
        this->vertices[posLibre] = new T(dato);
        this->cantVertices++;
    }

    // Pre: Ambos nodos se encuentran en el vector vertices.
    void agregarArista(T origen, T conexion)
    {
        int posOrigen = this->buscarPos(origen); // Consigo la pos en la listaAdy
        Arista<T> *arista = new Arista<T>(conexion);

        this->listaAdy[posOrigen]->insertarPpio(arista);
        this->cantAristas++;
    }
    void borrarVertice(T dato)
    {
        int posBorrar = this->buscarPos(dato);
        IteradorLista<Arista<T> *> *iter = NULL;
        for (int i = 0; i < this->cantVertices; i++)
        {
            iter = this->listaAdy[i]->obtenerIterador();
            while (iter->hayElemento())
            {
                borrarArista(dato, (iter->obtenerElemento())->conexion);
                iter->avanzar();
            }
        }
        // bouza : tema ordenes
        iter = NULL;
        delete iter;
        delete this->vertices[posBorrar];
        this->vertices[posBorrar] = NULL;
        this->cantVertices--;
        this->lugaresLibres->insertarPpio(posBorrar);
    }

    void borrarArista(T origen, T destino)
    {
        int posOrigen = this->buscarPos(origen);

        IteradorLista<Arista<T> *> *iter = this->listaAdy[posOrigen]->obtenerIterador(); // iter es un puntero a la lista que apunta a la primera arista

        while (iter->hayElemento() && (iter->obtenerElemento())->conexion != destino)
        {
            iter->avanzar();
        }
        // Una vez salimos del while, estamos parados en la arista pedida, o esa arista nunca fue creada.

        if (iter->hayElemento()) // Si no entra, es porque no fue creada esa arista.
        {

            this->listaAdy[posOrigen]->borrar(iter->obtenerElemento());
            this->cantAristas--;
        }
        iter = NULL;
        delete iter;
    }

    Lista<T> *ordenTopologico()
    {
        int *grados = new int[this->cantVertices];
        int *cantAristasVertice = new int[this->cantVertices];
        int aux = 0;
        for (int i = 0; i < this->cantVertices; i++)
        {
            grados[i] = 0;
        }
        IteradorLista<Arista<T> *> *iter = NULL;
        for (int i = 0; i < this->cantVertices; i++)
        {
            iter = this->listaAdy[i]->obtenerIterador();
            aux = 0;
            while (iter->hayElemento())
            {
                grados[this->buscarPos(iter->obtenerElemento()->conexion)]++;
                aux++;
                iter->avanzar();
            }
            cantAristasVertice[i] = aux;
        }
        // Hasta aca setteamos el vector "grados"
        Lista<T> *retorno = new Lista<T>();
        Heap<T>* miHeap = new Heap<T>(this->cantVertices);
        for (int i = 0; i < this->cantVertices; i++)
        {
            
            if (grados[i] == 0)
            {
                int cantAristas = cantAristasVertice[i];
                T vertice = *this->vertices[i];
                nodoDobleDato<T> *elemento = new nodoDobleDato<T>(cantAristas,vertice);
                miHeap->encolar(0, elemento); // nivel cero porque son los origenes (sin incidencias)
            }
        }

        while (!miHeap->esVacia())
        {
            nodoHeap<T>* cabezal = miHeap->topDato();
            
            int nivelConexion = cabezal->prioridad + 1;
            nodoDobleDato<T>* elementoOrigen = cabezal->dato;
            
            int posOrigen = buscarPos(elementoOrigen->vertice); // posOrigen es el padre
            retorno->insertarFin(elementoOrigen->vertice);
            miHeap->desencolar();
            iter = this->listaAdy[posOrigen]->obtenerIterador();

            //Recorremos la lista de adyacencia y disminuimos uno a las aristas
            //Si el grado una vez borrado es 0 añadimos la conexion
            while (iter->hayElemento())
            {
                grados[this->buscarPos(iter->obtenerElemento()->conexion)]--;
                cantAristasVertice[posOrigen]--;
                if(grados[this->buscarPos(iter->obtenerElemento()->conexion)] == 0){
                    
                    int cantAristas = cantAristasVertice[buscarPos(iter->obtenerElemento()->conexion)];
                    T vertice = iter->obtenerElemento()->conexion;
                    nodoDobleDato<T>* elementoOrigen = new nodoDobleDato<T>(cantAristas,vertice);
                    miHeap->encolar(nivelConexion, elementoOrigen);
                }
                iter->avanzar();
            }
        }

        return retorno;
    }
};

