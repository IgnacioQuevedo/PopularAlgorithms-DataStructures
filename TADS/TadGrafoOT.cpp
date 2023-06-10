#include <iostream>
#include <fstream> //borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#include "TadLista.cpp"
#include "TadHeap.cpp"
#define INF 9999
using namespace std;
// grafo con lista de adyacencia y una cola prioridad ejercicio 4!!!!!!
//  GRAFO EN EJERCICIO 5 SE IMPLEMENTA CON ES UN GRAFO DISPEROS DEVILEMNET CONEXO Y DIRIGIDO TENER 
USAR COLA PRIORIDAD PARA PODER IR ELIGIENDO Y QUE TENGA UN ORDEN V LOG, HAY QUE SABER RAPIDO EL 
NUMERP QUE HAY QUE IR SACANDO, ENTONCES VAMOS A IR AGREGANDO LOS VERTICES EN LA COLA PRIORIDAD POR ORDEN ASCENDENTE.
LA REGLA ES QUE CUMPLA CON LA COLA PRIORIDAD Y SER UN ORDEN TOPOLoGICO.
REGLA DE QUE SEA EN ESE ORDEN NUMERICO ENTONCES TENES 2 PRIORIDADES QUE NO ES UNA ES UNA DOBLE LA PRIMERA ES EL GRADO O SEA QUE TAN ELJOS ESTA DE LO QUE VOS MPOSTRASTE QUE ES LA RAIZ Y 
EL SEGUNDODA DATO ES EL NUMERO //DE ARISTAS QUE TIENE??
QUE TIENE PORQUE EL NUMERO MAS CHIQUITO  LA MISMA COLA PRIORIDAD -----PERO TENER UN PUNTERO QUE TENGA EL NUMERITO DEL VECTORI-- 
Y EL GRADO PRIMERO COMPARAR EL GRADO SI VOS SACAS DE UN ELEMENTO DE GRADO 4 CUANDO ENCOLAS A LOS ADYACENTES LE PONEMOS GRADO 4+1 CRECE EN FUNCION  LOS ELEMENTOS

//  Creamos la clase Arista, que va a almacenar información sobre las aristas del grafo.

template <class T>
class nodoTripleDato
{

public:
    nodoTripleDato(T vertice,int nivel,int cantAristas)
    {
        this->vertice = vertice;
        this->nivel = nivel;
        this->cantAristas = cantAristas;
    }
};

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

    void ordenTopologico()
    {
        int *grados = new int[this->cantVertices];
        bool esMin = true;
        HeapOT<nodoTripleDato> *miHeap = new HeapOT(this->cantAristas, esMin);

        for (int i = 0; i < this->tope; i++)
        {
            cantIncidencias[i] = 0;
        }
        
        //CALCULO DE GRADOS
        IteradorLista<T> *iter = NULL;
        for (int i = 0; i < this->cantVertices; i++) // No seria tope?
        {
            iter = this->listaAdy[i]->obtenerIterador();
            while (iter->hayElemento())
            {
                T verticeReceptor = (iter->obtenerElemento())->conexion; // Vertice al que le incide una arista
                grados[this->buscarPos(verticeReceptor)]++;
                iter->avanzar();
            }
        }

        //Recorro el vector grados
        
        for (int i = 0; i < this->cantVertices; i++)
        {
            
            if(grados[i] == 0){







            }







        }
        
        











    }
};
