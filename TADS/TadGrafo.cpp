#include <iostream>
#include <fstream> //borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#include "TadLista.cpp"
#include "TadHeap.cpp"
#define INF 9999
using namespace std;
// grafo con lista de adyacencia y una cola prioridad ejercicio 4!!!!!!
//  GRAFO EN EJERCICIO 5 SE IMPLEMENTA CON ES UN GRAFO DISPEROS DEVILEMNET CONEXO Y DIRIGIDO TENER E EN CUNENTA QUE SOLUCION ECHA ES BASTANATE ADECUABLE ADECUAR REGLAS USAR COLA PRIORIDAD AHORA PARA PODER IR ELIGIENDIO Y QUE TENGNA UN ORDE DE VLOG DE V HAY QUE SABER RAPIDO EL NUMERITO QUE HAYQ UE IR SACANDO VAMOS A IR AGGREGANDO LOS ERTICES EN LA COLA PRIORIDAD POR ORDEN ASCENDENTE LA REGLA ES QUE CUMPLA CON LA COLA PRIORIDAD Y SER UN ORDEN TOPOPLIGICO Y QUE TENG ALA RELGA DE QUE SEA EN ESE ORDEN NUMERICO ENTONCES RENES 2 PRIORRIDAES QUE NO ES UNA ES UNA DOBLE LA PRIMERA ES EL GRADO OSE A QUE TAN ELJOS ESTA DE LO QUE VOS MPOSTRASTE QUE ES LA RAIZ Y EL SEGUNDODA DATO ES EL NUMEROQUE TIENE PORQUE EL NUMERO MAS CHIQUITO  LA MISMA COLA PRIORIDAD PERO TENER UN PUNTERO QUE TENGA EL NUMERITO DEL VECTORI Y EL GRADO PRIMERO COMPARAR EL GRADO SI VOS SACAS DE UN ELEMENTO DE GRADO 4 CUANDO ENCOLAS A LOS ADYACENTES LE PONEMOS GRADO 4+1 CRECE EN FUNCION  LOS ELEMENTOS
//  Creamos la clase Arista, que va a almacenar información sobre las aristas del grafo.

template <class T>
class nodoDobleDato
{

public:
    T *vector;
    int totalCostosDeAristas;

    nodoDobleDato(T *vector, int totalCostosDeAristas)
    {
        this->vector = vector; // THIS->PRIORIDAD ("LA PRIO DEL HEAP SERÁ LA QUE ME PASEN POR PARAMETRO")
        this->totalCostosDeAristas = totalCostosDeAristas;
    }
};

template <class T>
class Arista
{
public:
    int costo;
    T conexion;
    bool dirigido;
    bool existe;

    Arista(T conexion, int costo, bool dirigido, bool existe)
    {
        this->conexion = conexion;
        this->costo = costo;
        this->dirigido = dirigido;
        this->existe = existe;
    }

    Arista(T conexion)
    {
        this->costo = 0;
        this->existe = false;
        this->conexion = conexion;
        this->dirigido = false;
    }
};

template <class T>
class Grafo
{

private:
    int cantVertices;
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
    void agregarArista(T origen, T conexion, int costo, int dirigido, bool existe)
    {
        int posOrigen = this->buscarPos(origen); // Consigo la pos en la listaAdy
        Arista<T> *arista = new Arista<T>(conexion, costo, dirigido, existe);
        this->listaAdy[posOrigen]->insertarPpio(arista);
    }

    void borrarVertice(T dato)
    {
        int posBorrar = this->buscarPos(dato);
        delete this->vertices[posBorrar];
        this->vertices[posBorrar] = NULL;
        this->cantVertices--;
        this->lugaresLibres->insertarPpio(posBorrar);
        this->listaAdy[posBorrar]->destruirLista(); // Te devuelve un puntero a la lista, y a esa lista llamas al destruir
    }

    void borrarArista(T origen, T destino)
    {
        int posOrigen = this->buscarPos(origen);
        IteradorLista<Arista<T> *> *iter = this->listaAdy[posOrigen]->obtenerIterador(); // iter es un puntero a la lista que apunta a la primera arista
        bool borrado = false;
        Arista<T> *aBorrar = NULL;
        while (!borrado && iter->hayElemento())
        {
            aBorrar = iter->obtenerElemento(); // aBorrar es la arista obtenida
            if (aBorrar->conexion == destino)
            {
                aBorrar->existe = false;
                borrado = true;
            }
        }
        aBorrar = NULL;
        delete aBorrar;
        iter = NULL;
        delete iter;
    }

    nodoDobleDato<T> *DijkstraNacho(T origen, T destino)
    {
        int *dist = new int[this->tope];
        bool *vis = new bool[this->tope];
        int *ant = new int[this->tope];

        Heap<T> *miHeap = new Heap<T>(this->tope); //El heap es el encargado de darle el siguiente vertice a estudiar. Suplanta la idea de PosNoVisMenorCosto.
        nodoDobleDato<T> *retorno = NULL; // Lo defino, pero aun sin nada
        IteradorLista<Arista *> *iter = NULL;
        int posOrigen = 0;
        for (int i = 0; i < this->tope; i++)
        {
            dist[i] = INF;
            vis[i] = false;
            ant[i] = -1;
        }

        posOrigen = this->buscarPos(origen);
        dist[posOrigen] = 0;
        int nuevaDist = 0;
        //vector[0] = origen; No va (Creo yo) Porque lo hago al final final del todo, en el while.
        miHeap->encolar(origen);

        for (int i = 0; i < this->tope; i++)
        {
            posOrigen = this->buscarPos(miHeap->datoMinPrio()); // Consigo la pos del primer elemento. (Por eso es importante el encolar de arriba).
            iter = this->listaAdy[posOrigen];                   // Situo el iter en la lista de aristas del vertice especifico(posOrigen).
            Arista<T> *aristaActual = NULL;                     // Será cada arista recorrida por el iter.

            miHeap->desencolar(); //Una vez conseguido el elemento siguiente a estudiar, lo desencolo.

            while (iter->hayElemento())
            {
                aristaActual = iter->obtenerElemento(); // Consigo una de las arista del vertice particular.
                nuevaDist = dist[posOrigen] + aristaActual->costo;
                if (!vis[aristaActual->conexion] && aristaActual->existe && nuevaDist < dist[this->buscarPos(aristaActual->conexion)]) //Si el vertice "destino" (conexion) aún no fue visitado, si la arista existe ("True") y si la distancia a ese vertice "destino" es mas chica que la anterior. Ahi si me meto.
                {
                    miHeap->encolar(aristaActual->conexion);
                    dist[this->buscarPos(aristaActual->conexion)] = nuevaDist;
                    ant[aristaActual] = posOrigen;
                }
            }
            vis[posOrigen] = true; // Una vez estudiadas todas las aristas, el vertice actual ya figura como visitado.
        }

        //AFUERA DE TODO FOR, ESTA PARTE DE ABAJO GENERA TODA LA DEVOLUCION

        int i=0; 
        T *vector = new T[this->cantVertices];             
        vector[0] = destino;   
        int posAnt = this->buscarPos(destino); //Es la posAnt del vertice anterior al de destino.

        while(ant[posAnt] != -1){ //cuando sea -1 significa que sos el primero

            vector[i] = this->vertices[posAnt]; // Esto quedaria asi [Destino, AntDestino, AntAntDestino,....,Origen]
            posAnt = ant[posAnt]; //Actualizo la posAnt a la anterior de la misma.
            i++; //Incremento para moverme a la siguiente posicion del vector a devolver.
        }
        retorno->vector = vector;
        retorno->totalCostosDeAristas = dist[this->buscarPos(destino)];

        return retorno;
    }

    nodoDobleDato<T> *DijkstraCamejin(T origen, T destino)
    {
        int posOrigen = this->buscarPos(origen);

        int *dist = new int[this->tope];
        bool *vis = new bool[this->tope];
        Heap<T> *miHeap = new Heap<T>(this->tope);

        T *vector = new T[this->cantVertices];                               // Vector con los vertices recorridos.
        int sumaTotal = 0;                                                   // distancia total del recorrido de esos vertices.
        nodoDobleDato<T> *retorno = new nodoDobleDato<T>(vector, sumaTotal); // Lo de arriba va al constructor del nodoDobleDato

        IteradorLista<Arista *> *iter = NULL;
        for (int i = 0; i < this->tope; i++)
        {
            dist[i] = INF;
            vis[i] = false;
        }

        dist[posOrigen] = 0;

        while (!miHeap->esVacia)
        {
            // sumaTotal = sumaTotal + miNodoHeap->darPrioridad;
            // vector[algo] = valor en pos;
            miHeap->desencolar();

            while (iter->hayElemento())
            {
                int posProxVertice = buscarPos(iter->obtenerElemento->destino);
                int nuevaDistancia = dist[posProxVertice] + iter->obtenerElemento->costo;

                if (nuevaDistancia < dist[i])
                {
                    dist[proxVertice] = nuevaDistancia;
                    miHeap->encolar((iter->obtenerElemento())->conexion);
                }
            }
        }

        return retorno;
    }
};

int main(int argc, char const *argv[])
{
    Grafo<int> *miGrafo = new Grafo<int>(5);
    miGrafo->agregarVertice(1);
    miGrafo->agregarVertice(2);
    miGrafo->agregarVertice(3);
    miGrafo->agregarVertice(4);
    miGrafo->agregarArista(1, 2, 10, 1, 1);
    miGrafo->agregarArista(1, 3, 7, 1, 1);
    miGrafo->agregarArista(2, 4, 9, 1, 1);
    miGrafo->agregarArista(3, 3, 22, 1, 1);
    miGrafo->agregarArista(1, 5, 10, 1, 1);
    miGrafo->borrarArista(3, 3);
    miGrafo->borrarVertice(2);
    miGrafo->agregarVertice(3500);
    miGrafo->borrarVertice(3);
    miGrafo->borrarVertice(4);
    miGrafo->Dijkstra(3, 2);
};