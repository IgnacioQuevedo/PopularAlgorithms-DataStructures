#include <iostream>
#include <fstream> //borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#include "TadLista.cpp"
#include "TadHeap.cpp"
#define INF 9999
using namespace std;
// grafo con lista de adyacencia y una cola prioridad ejercicio 4!!!!!!
//  Creamos la clase Arista, que va a almacenar información sobre las aristas del grafo.

class nodoDobleDato
{

public:
    Lista<int>* listaElem;
    int totalCostosDeAristas;

    nodoDobleDato(Lista<int> *listaElem, int totalCostosDeAristas)
    {
        this->listaElem = listaElem;
        this->totalCostosDeAristas = totalCostosDeAristas;
    }
};

class Arista
{
public:
    int costo;
    int conexion;
    bool existe;
    bool dirigido;

    Arista(int conexion, int costo, bool dirigido, bool existe)
    {
        this->conexion = conexion;
        this->costo = costo;
        this->dirigido = dirigido;
        this->existe = existe;
    }

    Arista(int conexion) // MEPA QUE AL PEDO
    {
        this->conexion = conexion;
        this->costo = 0;
        this->dirigido = false;
        this->existe = false;
    }
};

class Grafo
{

private:
    int cantVertices;
    int cantAristas;
    int tope;
    bool* vis;                      // la cantidad máxima de vértices que puede tener el grafo
    int *vertices;                  // vector que adentro tiene punteros a datos tipo int ("Vertice")
    Lista<int> *lugaresLibres;     // vector con posiciones libres.
    Lista<Arista*> **listaAdy; // Un array en el que cada posicion del array me representa un vertice, adentro de cada posicion del array tenemos un puntero a una lista encadenada que esa lista contiene punteros a aristas las cuales a su vez tiene origen  destino definido

public:
    Grafo(int tope)
    {
        this->tope = tope;
        this->vis = new bool[this->tope];
        this->vertices = new int[tope];
        this->lugaresLibres = new Lista<int>(); // Creamos una lista que guarde los lugares libres
        this->listaAdy = new Lista<Arista*> *[tope];
        this->cantVertices = 0;
        this->cantAristas = 0;

        for (int i = 0; i < tope; i++)
        {
            vertices[i] = 0;
            this->listaAdy[i] = new Lista<Arista*>(); // Seteo a null
            this->lugaresLibres->insertarFin(i);
            this->vis[i] = false;
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
    void agregarArista(int origen, int conexion, int costo, int dirigido, int existe)
    {
        int posOrigen = origen -1; //PORQUE ESTA TRASLADADO UN LUGAR ATRAS EN EL ARRAY DE VERTICES
        Arista *aristaSentido1 = new Arista(conexion, costo, dirigido, existe);

        if (dirigido)
        {
            this->listaAdy[posOrigen]->insertarPpio(aristaSentido1);
            this->cantAristas++;
        }
        else
        {
            Arista *aristaSentido2 = new Arista(origen, costo, dirigido, existe);
            this->listaAdy[posOrigen]->insertarPpio(aristaSentido1); // Inserte la original
            int posConexion = conexion -1;
            this->listaAdy[posConexion]->insertarPpio(aristaSentido2);
            this->cantAristas = this->cantAristas + 2; // porque agregamos 2 aristas ya que es no dirigido
        }
        

    }

    void borrarVertice(int dato)
    {
        int posBorrar = dato-1;
        this->vis[posBorrar] = true;
        this->vertices[posBorrar] = 0;
        this->cantVertices--;
        this->lugaresLibres->insertarPpio(posBorrar);
    }

    void borrarArista(int origen, int destino)
    {
        bool sdaVuelta = false;
        borrarAristaAux(origen, destino, sdaVuelta);
    }
    void borrarAristaAux(int origen, int destino, bool sdaVuelta)
    {
        int posOrigen = origen-1;
 
        if (posOrigen != -1) // Porque como recorro todo, entonces voy a recorrer tambien la posible pos ya borrada. Incluso los vertices borrados.
        {
            IteradorLista<Arista*> *iter = this->listaAdy[posOrigen]->obtenerIterador(); // iter es un puntero a la lista que apunta a la primera arista

            while (iter->hayElemento() && (iter->obtenerElemento())->conexion != destino)
            {
                iter->avanzar();
            }

            if (iter->hayElemento()) // Si no entra, es porque no fue creada esa arista.
            {
                // Si entras, significa que encontraste la arista.
                if (!iter->obtenerElemento()->existe)
                {
                    return;
                }

                iter->obtenerElemento()->existe = false;
                this->cantAristas--;
            }

            if (sdaVuelta)
            {
                return;
            }

            sdaVuelta = true;
            borrarAristaAux(destino, origen, sdaVuelta);
            iter = NULL;
            delete iter;
        }
    }

    nodoDobleDato *Dijkstra(int origen, int destino)
    {
        int *dist = new int[this->tope];
        int *ant = new int[this->tope];

        bool esMinHeap = true;
        Heap<int> *miHeap = new Heap<int>(this->cantAristas, esMinHeap); // El heap es el encargado de darle el siguiente vertice a estudiar. Suplanta la idea de PosNoVisMenorCosto.
        Lista<int>* listaElem = new Lista<int>();
        int totalCostosDeAristas = 0;
        nodoDobleDato *retorno = new nodoDobleDato(listaElem, totalCostosDeAristas);

        int posOrigen = 0;
        for (int i = 0; i < this->tope; i++)
        {
            dist[i] = INF;
            ant[i] = -1;
        }

        posOrigen = origen-1;
        dist[posOrigen] = 0;
        int nuevaDist = 0;

        miHeap->encolar(nuevaDist, origen);
        IteradorLista<Arista *> *iter = this->listaAdy[posOrigen]->obtenerIterador();

        while(!miHeap->esVacia()){
            
            int dato = miHeap->topDato();
            posOrigen = miHeap->topDato() -1; // Consigo la pos del primer elemento. (Por eso es importante el encolar de arriba).
            Arista *aristaActual = NULL;           // Será cada arista recorrida por el iter.
            iter = this->listaAdy[posOrigen]->obtenerIterador();
            miHeap->desencolar(); // Una vez conseguido el elemento siguiente a estudiar, lo desencolo.
    
            while (iter->hayElemento())
            {
                //guardar buscar pos en una variable 
                aristaActual = iter->obtenerElemento(); // Consigo una de las arista del vertice particular.
                nuevaDist = dist[posOrigen] + aristaActual->costo;   
                int posBuscada = (aristaActual->conexion) -1;
                if (!(this->vis[posBuscada]) && aristaActual->existe && nuevaDist < dist[posBuscada]) // Si el vertice "destino" (conexion) aún no fue visitado, si la arista existe ("True") y si la distancia a ese vertice "destino" es mas chica que la anterior. Ahi si me meto.
                {
                    miHeap->encolar(nuevaDist, aristaActual->conexion);
                    dist[posBuscada] = nuevaDist;
                    ant[posBuscada] = posOrigen;
                }
                iter->avanzar();
            }
            this->vis[posOrigen] = true; // Una vez estudiadas todas las aristas, el vertice actual ya figura como visitado.
        
        }
        // AFUERA DEL WHILE,ESTA PARTE DE ABAJO GENERA TODA LA DEVOLUCION
        //--------------------------------------------------------------------

        int posAnt = destino -1; // Es la posAnt del vertice anterior al de destino.
        while (ant[posAnt] != -1)
        { // cuando el anterior a esa posicion sea -1 significa: --> o que sos el primero o no existe el camino

            retorno->listaElem->insertarPpio(this->vertices[posAnt]); //Insertamos al ppio, asi queda en orden, EL vector ant, contiene la pos del vertice anterior al parado
            posAnt = ant[posAnt];                         // Actualizo la posAnt a la anterior de la misma.
        }

        if(this->vertices[posAnt] != origen){ //Si la posAnt no es el origen, significa que el while salió antes lo que significa que no se encontró un valor anterior para ese valor por ende -> NO EXISTE CAMINO
            return NULL;      
        }
        // Si es el origen, entonce se encontró el camino total, por lo tanto 10/10
        retorno->listaElem->insertarPpio(origen);
        retorno->totalCostosDeAristas = dist[destino-1];

        return retorno;
    }
};

//IMPLE
// SINO HACERLO EXCLUSIVO
