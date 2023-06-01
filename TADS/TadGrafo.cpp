#include <iostream>
#include <fstream>//borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#define INF 9999
using namespace std;
// grafo con lista de adyacencia y una cola prioridad ejercicio 4!!!!!!
//  GRAFO EN EJERCICIO 5 SE IMPLEMENTA CON ES UN GRAFO DISPEROS DEVILEMNET CONEXO Y DIRIGIDO TENER E EN CUNENTA QUE SOLUCION ECHA ES BASTANATE ADECUABLE ADECUAR REGLAS USAR COLA PRIORIDAD AHORA PARA PODER IR ELIGIENDIO Y QUE TENGNA UN ORDE DE VLOG DE V HAY QUE SABER RAPIDO EL NUMERITO QUE HAYQ UE IR SACANDO VAMOS A IR AGGREGANDO LOS ERTICES EN LA COLA PRIORIDAD POR ORDEN ASCENDENTE LA REGLA ES QUE CUMPLA CON LA COLA PRIORIDAD Y SER UN ORDEN TOPOPLIGICO Y QUE TENG ALA RELGA DE QUE SEA EN ESE ORDEN NUMERICO ENTONCES RENES 2 PRIORRIDAES QUE NO ES UNA ES UNA DOBLE LA PRIMERA ES EL GRADO OSE A QUE TAN ELJOS ESTA DE LO QUE VOS MPOSTRASTE QUE ES LA RAIZ Y EL SEGUNDODA DATO ES EL NUMEROQUE TIENE PORQUE EL NUMERO MAS CHIQUITO  LA MISMA COLA PRIORIDAD PERO TENER UN PUNTERO QUE TENGA EL NUMERITO DEL VECTORI Y EL GRADO PRIMERO COMPARAR EL GRADO SI VOS SACAS DE UN ELEMENTO DE GRADO 4 CUANDO ENCOLAS A LOS ADYACENTES LE PONEMOS GRADO 4+1 CRECE EN FUNCION  LOS ELEMENTOS
//  Creamos la clase Arista, que va a almacenar información sobre las aristas del grafo.
class Arista
{

public:
    int costo;
    int origen; 
    int destino;
    bool existe;

//listaAdy = unn vector que cada posicion del vector me representa unvertice, adentro dde cada posicion del vector tenemos una lista encadenada que esa lista cotiene punteros a aristas las cuales a su vez tiene origen  destino definido
    Arista(int costo, bool existe, origen, destino)
    {
        this->costo = costo;
        this->existe = existe;
    }

    Arista()
    {
        this->costo = 0;
        this->existe = false;
    }
};

// Creamos la clase Grafo, que va a representar un grafo genérico.
template <class T>
class Grafo
{

private:
    int cantVertices; // la cantidad de vértices que tiene el grafo
    int tope;         // la cantidad máxima de vértices que puede tener el grafo
    bool esDirigido;  // indica si el grafo es dirigido o no
    T **vertices;     // vector que adentro tiene punteros a datos tipo T ("Vertice")
    Lista listaAdy;   // matriz de adyacencia que indica las aristas que hay entre los vértices
    Lista<int> *huecos;

    int buscarVertice(T dato)
    {

        for (int i = 0; i < this->tope; i++)
        {
            if (this->vertices[i] == dato)
            {
                return i;
            }

            return -1;
        }
    }

    void agregarVertice(T dato)
    {
        // CONSIGO UN LUGAR LIBRE DE MI LISTA CON AQUELLOS LUGARES
        int libre = this->lugaresLibres->obtenerPpio();
        // BORRO EL LUGAR LIBRE DE MI LISTA
        this->lugaresLibres->borrrar(libre);
        // AÑADO AL VECTOR VERTICES EL NUEVO VERTICE("DATO")
        this->vertices[libre] = new T(dato);
        this->cantVertices++
    }

    void borrarVertice(T dato)
    {

        int pos = buscarPos(vertice); // LA POS RESPECTIVA DEL ELEMENTO EN EL VECTOR VERTICE
        delete this->vertices[pos];
        this->cantVertices--;
        this->lugaresLibres->agregarPpio(pos); // EL ELEMENTO QUE BORRE GENERA QUE QUEDE UNA NUEVA POS LIBRE
        // BORRO LAS ARISTAS RESPECTIVAS DEL VERTICE;
        if (this->esDirigido)
        {

            for (int k = 0; k < tope; k++)
            {
                // BORRO TODA ARISTA QUE TENGA ESE VERTICE, XQ ENTRE ELLAS SON MUY DISTINTAS!!!
                this->matAdy[pos][k]->existe = false; // BORRA EN FUNCION DE FILA
                this->matAdy[k][pos]->existe = false; // BORRA EN FUNCION DE LA COLUMNA
            }
        }
        else
        {
            // EN EL CASO QUE NO SEA DIRIGIDO (A,B)=(B,A) ENTONCES AÑADI EL ELEMENTO DOS VECES
            // LO BORRA UNA VEZ Y LISTO.
            for (int k = 0; k < tope; k++)
            {
                this->matAdy[pos][k]->existe = false;
            }
        }
    }

    // PRE: AMBOS NODOS SE ENCUENTRAN EN EL VECTOR VERTICE.
    agregarArista(T origen, T destino, int costo) // YA ME DAN LA DIRECCION DE LA ARISTA, AÑADO DE UNA ARISTA POR VEZ, ENTONCES LA DIRECCION NO IMPORTA
    {
        int posOrigen = this->buscarVertice(origen);
        int posDestino = this->buscarVertice(destino) this->matAdy[posOrigen][posDestino]->existe = true;
        this->matAdy[posOrigen][posDestino]->costo = costo;
    }

    borrarArista(T origen, T destino)
    {
        int posOrigen = this->buscarVertice(origen);
        int posDestino = this->buscarVertice(destino);
        -- > // VER TEMA HASH PARA EL OBLI

            this->matAdy[posOrigen][posDestino]->costo = false;
        this->matAdy[posOrigen][posDestino]->costo = 0;
    }

    int posNoVisDeMenorCosto(int *dist, bool *vis)
    {
        int sigVertice = -1;
        int min = INF;

        for (int i = 0; i < this->tope; i++)
        {
            if (!vis[i] && dist[i] < min)
            {                   // SI EL VERTICE AUN NO SE HA PASADO POR ALTO, ENTONCES PREGUNTO SI SU DISTANCIA ES MENOR AL MINIMO
                sigVertice = i; // ME GUARDO LA POS DEL VERTICE MAS CHICO
                min = dist[i];  // ME GUARDO LA DISTANCIA PARA LLEGAR A EL
            }
        }
        return sigVertice;
    }

    // devolvemos una lista
    Lista dijkstra(int origen) // ORDEN V cuadrado

    {
        int posOrigen = this->buscarVertice(origen); // ENCUENTRO LA POS DEL VERTICE

        bool *vis = new bool[this->tope]; // SI ESTAN VISITADOS
        int *dist = new int[this->tope];  // EL COSTO TOTAL PARA LLEGAR A ESE VERTICE
        int *ant = new int[this->tope];   // EL GRAFO ANTERIOR AL ACTUAL.

        dist[origen] = 0; // YO YA SE QUE EN EL VERTICE ORIGEN ES EN EL CUAL VOY A ARRANCAR ENTONCES NO HAY DISTANCIA

        for (int i = 0; i < this->to; i++) // INICIALIZO LOS VECTORES
        {
            vis[i] = false;
            dist[i] = INF;
            ant[i] = -1
        }

        for (int i = 0; i < this->tope; i++) // VOY A EVALUAR PARA CADA VERTICE DEL GRAFO
        {
            int proximoVertice = posNoVisDeMenorCosto(dist, vis); // CONSIGO EL SIGUIENTE VERTICE A ESTUDIAR

            if (proximoVertice == -1)
            { // SI NO HAY PROXIMO VERTICE MAS CHICO TERMINO
                return;
            }

            for (int j = 0; j < this->tope; j++) // ENCONTRAR TODA ARISTA CON ESE VERTICE
            {
                if (!vis[j] && this->matAdy[proximoVertice][j]->existe) // SI ESE VERTICE AUN NO FUE VISITADO Y TIENE ARISTAS
                {

                    int nuevaDistancia = dist[proximoVertice] + this->matAdy[proximoVertice][j]->costo; // ME GUARDO EL COSTO AL SIGUIENTE VERTICE PERTENECIENTE A LA ARISTA
                    if (nuevaDistancia < dist[j])                                                       // SI LA DISTANCIA NUEVA ES MENOR QUE LA VIEJA, ENCONTRE UN CAMINO MAS CORTO
                    {
                        // lo añado al heap

                        // el primero lo mostramos sin meterlo al heap cout inicio
                        // añado al heap el vertice con prioridad minheap
                        // cuando me paro en un nuevo nodo ya desencolé la cabeza y la devolvi
                        //  y tengo que marcarlo como visitaddo al primero que saco
                        dist[j] = nuevaDistancia;
                        ant[j] = proximoVertice;
                    }
                    else
                    {
                        // BORRAR SIN COUT
                    }
                }
            }
            vis[proximoVertice] = true; // UNA VEZ QUE EVALUÉ TODA ARISTA PARA ESE VERTICE, LO PONGO EN TRUE
        }
    }
};