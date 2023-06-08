#include <iostream>
#include <fstream> //borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#include "TadLista.cpp"
#include "TadHeap.cpp"
#define INF 9999
using namespace std;
// grafo con lista de adyacencia y una cola prioridad ejercicio 4!!!!!!
//  GRAFO EN EJERCICIO 5 SE IMPLEMENTA CON ES UN GRAFO DISPEROS DEVILEMNET CONEXO Y DIRIGIDO TENER E EN CUNENTA QUE SOLUCION ECHA ES BASTANATE ADECUABLE ADECUAR REGLAS USAR COLA PRIORIDAD AHORA PARA PODER IR ELIGIENDIO Y QUE TENGNA UN ORDEn DE VLOG DE V HAY QUE SABER RAPIDO EL NUMERITO QUE HAY QUE IR SACANDO VAMOS A IR AGREGANDO LOS vERTICES EN LA COLA PRIORIDAD POR ORDEN ASCENDENTE LA REGLA ES QUE CUMPLA CON LA COLA PRIORIDAD Y SER UN ORDEN TOPOLoGICO Y QUE TENGA LA RELGA DE QUE SEA EN ESE ORDEN NUMERICO ENTONCES tENES 2 PRIORRIDAES QUE NO ES UNA ES UNA DOBLE LA PRIMERA ES EL GRADO OSE A QUE TAN ELJOS ESTA DE LO QUE VOS MPOSTRASTE QUE ES LA RAIZ Y EL SEGUNDODA DATO ES EL NUMEROQUE TIENE PORQUE EL NUMERO MAS CHIQUITO  LA MISMA COLA PRIORIDAD PERO TENER UN PUNTERO QUE TENGA EL NUMERITO DEL VECTORI Y EL GRADO PRIMERO COMPARAR EL GRADO SI VOS SACAS DE UN ELEMENTO DE GRADO 4 CUANDO ENCOLAS A LOS ADYACENTES LE PONEMOS GRADO 4+1 CRECE EN FUNCION  LOS ELEMENTOS
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
    bool existe;
    bool dirigido;

    Arista(T conexion, int costo, bool dirigido, bool existe)
    {
        this->conexion = conexion;
        this->costo = costo;
        this->dirigido = dirigido;
        this->existe = existe;
    }

    Arista(T conexion) // MEPA QUE AL PEDO
    {
        this->conexion = conexion;
        this->costo = 0;
        this->dirigido = false;
        this->existe = false;
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
    void agregarArista(T origen, T conexion, int costo, int dirigido, int existe)
    {
        int posOrigen = this->buscarPos(origen); // Consigo la pos en la listaAdy
        Arista<T> *aristaSentido1 = new Arista<T>(conexion, costo, dirigido, existe);

        if (dirigido)
        {
            this->listaAdy[posOrigen]->insertarPpio(aristaSentido1);
        }
        else
        {
            Arista<T> *aristaSentido2 = new Arista<T>(origen, costo, dirigido, existe);
            this->listaAdy[posOrigen]->insertarPpio(aristaSentido1); // Inserte la original
            int posConexion = this->buscarPos(conexion);
            this->listaAdy[posConexion]->insertarPpio(aristaSentido2);
        }
    }

    void borrarVertice(T dato)
    {
        int posBorrar = this->buscarPos(dato);
        int i = 0;
        IteradorLista<Arista<T> *> *iter = NULL;
        for (i = 0; i < this->cantVertices; i++)
        {
            iter = this->listaAdy[i]->obtenerIterador();
            while (iter->hayElemento())
            {
                borrarArista(dato, iter->obtenerElemento()->conexion);
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
        bool sdaVuelta = false;
        borrarAristaAux(origen, destino, sdaVuelta);
    }
    void borrarAristaAux(T origen, T destino, bool sdaVuelta)
    {
        int posOrigen = this->buscarPos(origen);
        // if(posOrigen == -1){
        //     return; //Significa que estas probando con un borrado
        // }
        if (posOrigen != -1) //Porque como recorro todo, entonces voy a recorrer tambien la posible pos ya borrada. Incluso los vertices borrados.
        {
            IteradorLista<Arista<T> *> *iter = this->listaAdy[posOrigen]->obtenerIterador(); // iter es un puntero a la lista que apunta a la primera arista

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
    nodoDobleDato<T> *Dijkstra(T origen, T destino)
    {
        int *dist = new int[this->tope];
        bool *vis = new bool[this->tope];
        int *ant = new int[this->tope]; // realmente es necesario?

        bool esMinHeap = true;
        Heap<T> *miHeap = new Heap<T>(this->tope, esMinHeap); // El heap es el encargado de darle el siguiente vertice a estudiar. Suplanta la idea de PosNoVisMenorCosto.
        T *vector = new T[this->cantVertices];
        int totalCostosDeAristas = 0;
        nodoDobleDato<T> *retorno = new nodoDobleDato<T>(vector, totalCostosDeAristas);

        int posOrigen = 0;
        for (int i = 0; i < this->tope; i++)
        {
            dist[i] = INF;
            vis[i] = false;
            ant[i] = -1;
            retorno->vector[i] = -1;
        }

        posOrigen = this->buscarPos(origen);
        dist[posOrigen] = 0;
        int nuevaDist = 0;

        miHeap->encolar(nuevaDist, origen);
        IteradorLista<Arista<T> *> *iter = this->listaAdy[posOrigen]->obtenerIterador();

        for (int i = 0; i < this->cantVertices - 1; i++)
        {
            posOrigen = buscarPos(miHeap->topDato()); // Consigo la pos del primer elemento. (Por eso es importante el encolar de arriba). //camejin: faltaban ()
            Arista<T> *aristaActual = NULL;           // Será cada arista recorrida por el iter.
            iter = this->listaAdy[posOrigen]->obtenerIterador();

            miHeap->desencolar(); // Una vez conseguido el elemento siguiente a estudiar, lo desencolo.

            while (iter->hayElemento())
            {
                aristaActual = iter->obtenerElemento(); // Consigo una de las arista del vertice particular.
                nuevaDist = dist[posOrigen] + aristaActual->costo;
                if (!vis[this->buscarPos(aristaActual->conexion)] && aristaActual->existe && nuevaDist < dist[this->buscarPos(aristaActual->conexion)]) // Si el vertice "destino" (conexion) aún no fue visitado, si la arista existe ("True") y si la distancia a ese vertice "destino" es mas chica que la anterior. Ahi si me meto.
                {
                    miHeap->encolar(nuevaDist, aristaActual->conexion);
                    dist[this->buscarPos(aristaActual->conexion)] = nuevaDist;
                    ant[this->buscarPos(aristaActual->conexion)] = posOrigen;
                }
                iter->avanzar();
            }
            vis[posOrigen] = true; // Una vez estudiadas todas las aristas, el vertice actual ya figura como visitado.
        }

        // AFUERA DE TODO FOR, ESTA PARTE DE ABAJO GENERA TODA LA DEVOLUCION

        int i = 0;
        int posAnt = this->buscarPos(destino); // Es la posAnt del vertice anterior al de destino.

        while (ant[posAnt] != -1)
        { // cuando sea -1 significa que sos el primero

            retorno->vector[i] = *this->vertices[posAnt]; // Esto quedaria asi [Destino, AntDestino, AntAntDestino,....,Origen] // camejin: faltaba asterisco
            posAnt = ant[posAnt];                         // Actualizo la posAnt a la anterior de la misma.
            i++;                                          // Incremento para moverme a la siguiente posicion del vector a devolver.
        }
        retorno->vector[i] = origen;
        retorno->totalCostosDeAristas = dist[this->buscarPos(destino)];

        return retorno;
    }
};

// int main(int argc, char const *argv[])
// {
//     Grafo<int> *miGrafo = new Grafo<int>(5);
//     miGrafo->agregarVertice(1);
//     miGrafo->agregarVertice(2);
//     miGrafo->agregarVertice(3);
//     miGrafo->agregarVertice(4);
//     miGrafo->agregarArista(1, 2, 10, 1, 1);
//     miGrafo->agregarArista(1, 3, 7, 1, 1);
//     miGrafo->agregarArista(2, 4, 9, 1, 1);
//     miGrafo->agregarArista(3, 4, 1, 1, 1);
//     //miGrafo->agregarArista(3, 3, 22, 1, 1);
//     //miGrafo->agregarArista(1, 5, 10, 1, 1);
//     //miGrafo->borrarArista(3, 3);
//     //miGrafo->borrarVertice(2);
//     //miGrafo->agregarVertice(3500);
//     //miGrafo->borrarVertice(3);
//     //miGrafo->borrarVertice(4);
//     miGrafo->Dijkstra(1, 4);
// };