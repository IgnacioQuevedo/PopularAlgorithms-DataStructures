#include <iostream>
#include <fstream> //borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#include "TadLista.cpp"
#define INF 9999
using namespace std;
// grafo con lista de adyacencia y una cola prioridad ejercicio 4!!!!!!
//  GRAFO EN EJERCICIO 5 SE IMPLEMENTA CON ES UN GRAFO DISPEROS DEVILEMNET CONEXO Y DIRIGIDO TENER E EN CUNENTA QUE SOLUCION ECHA ES BASTANATE ADECUABLE ADECUAR REGLAS USAR COLA PRIORIDAD AHORA PARA PODER IR ELIGIENDIO Y QUE TENGNA UN ORDE DE VLOG DE V HAY QUE SABER RAPIDO EL NUMERITO QUE HAYQ UE IR SACANDO VAMOS A IR AGGREGANDO LOS ERTICES EN LA COLA PRIORIDAD POR ORDEN ASCENDENTE LA REGLA ES QUE CUMPLA CON LA COLA PRIORIDAD Y SER UN ORDEN TOPOPLIGICO Y QUE TENG ALA RELGA DE QUE SEA EN ESE ORDEN NUMERICO ENTONCES RENES 2 PRIORRIDAES QUE NO ES UNA ES UNA DOBLE LA PRIMERA ES EL GRADO OSE A QUE TAN ELJOS ESTA DE LO QUE VOS MPOSTRASTE QUE ES LA RAIZ Y EL SEGUNDODA DATO ES EL NUMEROQUE TIENE PORQUE EL NUMERO MAS CHIQUITO  LA MISMA COLA PRIORIDAD PERO TENER UN PUNTERO QUE TENGA EL NUMERITO DEL VECTORI Y EL GRADO PRIMERO COMPARAR EL GRADO SI VOS SACAS DE UN ELEMENTO DE GRADO 4 CUANDO ENCOLAS A LOS ADYACENTES LE PONEMOS GRADO 4+1 CRECE EN FUNCION  LOS ELEMENTOS
//  Creamos la clase Arista, que va a almacenar información sobre las aristas del grafo.

class Arista
{
public:
    int costo;
    // int origen;
    int conexion;
    // bool existe;
    bool dirigido;

    Arista(int conexion, int costo, bool dirigido)
    {
        this->conexion = conexion;
        this->costo = costo;
        this->dirigido = dirigido;
        // this->existe = existe;
        // this->origen = origen;
    }

    Arista()
    {
        this->costo = 0;
        // this->existe = false;
        // this->origen = -1;
        this->conexion = -1;
        this->dirigido = false;
    }
};

template <class T>
class Grafo
{

private:
    int cantVertices;
    int tope;                   // la cantidad máxima de vértices que puede tener el grafo
    T **vertices;               // vector que adentro tiene punteros a datos tipo T ("Vertice")
    Lista<int>* lugaresLibres;         // vector con posiciones libres.
    Lista<Arista *> **listaAdy; // Un array en el que cada posicion del array me representa un vertice, adentro de cada posicion del array tenemos un puntero a una lista encadenada que esa lista contiene punteros a aristas las cuales a su vez tiene origen  destino definido

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
        this->listaAdy = new Lista<Arista *> *[tope];
        this->cantVertices = 0;

        for (int i = 0; i < tope; i++)
        {
            vertices[i] = NULL; // Seteo a null, (Porque es un vector de vectores, sino apunta a basura.)
        }

        for (int i = 0; i < this->tope; i++)
        {
            this->listaAdy[i] = new Lista<Arista *>(); // Seteo a null
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
    agregarArista(T origen, T conexion, int costo, int dirigido)
    {
        int posOrigen = this->buscarPos(origen); // Consigo la pos en la listaAdy
        Arista *arista = new Arista(conexion, costo, dirigido);
        this->listaAdy[posOrigen]->insertarPpio(arista);
    }
};

int main(int argc, char const *argv[])
{
    Grafo<int> *miGrafo = new Grafo<int>(5);
    miGrafo->agregarVertice(1);
    miGrafo->agregarVertice(2);
    miGrafo->agregarVertice(3);
    miGrafo->agregarVertice(4);
    miGrafo->agregarArista(1, 2, 10, 1);
    miGrafo->agregarArista(1, 3, 7, 1);
    miGrafo->agregarArista(2, 4, 9, 1);
    miGrafo->agregarArista(3, 3, 22, 1);
}
