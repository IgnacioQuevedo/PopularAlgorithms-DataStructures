#include <iostream>
#include <fstream> //borrarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!
#include "TadLista.cpp"
#define INF 9999
using namespace std;
// grafo con lista de adyacencia y una cola prioridad ejercicio 4!!!!!!
//  GRAFO EN EJERCICIO 5 SE IMPLEMENTA CON ES UN GRAFO DISPEROS DEVILEMNET CONEXO Y DIRIGIDO TENER E EN CUNENTA QUE SOLUCION ECHA ES BASTANATE ADECUABLE ADECUAR REGLAS USAR COLA PRIORIDAD AHORA PARA PODER IR ELIGIENDIO Y QUE TENGNA UN ORDE DE VLOG DE V HAY QUE SABER RAPIDO EL NUMERITO QUE HAYQ UE IR SACANDO VAMOS A IR AGGREGANDO LOS ERTICES EN LA COLA PRIORIDAD POR ORDEN ASCENDENTE LA REGLA ES QUE CUMPLA CON LA COLA PRIORIDAD Y SER UN ORDEN TOPOPLIGICO Y QUE TENG ALA RELGA DE QUE SEA EN ESE ORDEN NUMERICO ENTONCES RENES 2 PRIORRIDAES QUE NO ES UNA ES UNA DOBLE LA PRIMERA ES EL GRADO OSE A QUE TAN ELJOS ESTA DE LO QUE VOS MPOSTRASTE QUE ES LA RAIZ Y EL SEGUNDODA DATO ES EL NUMEROQUE TIENE PORQUE EL NUMERO MAS CHIQUITO  LA MISMA COLA PRIORIDAD PERO TENER UN PUNTERO QUE TENGA EL NUMERITO DEL VECTORI Y EL GRADO PRIMERO COMPARAR EL GRADO SI VOS SACAS DE UN ELEMENTO DE GRADO 4 CUANDO ENCOLAS A LOS ADYACENTES LE PONEMOS GRADO 4+1 CRECE EN FUNCION  LOS ELEMENTOS
//  Creamos la clase Arista, que va a almacenar información sobre las aristas del grafo.

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
        this->vertices[posBorrar] = NULL;
        this->lugaresLibres->insertarPpio(posBorrar);
        IteradorLista<Arista<T> *> *iter = this->listaAdy[posBorrar]->obtenerIterador(); // Me creo un iterador para recorrer la lista ("Las aristas")
        Arista<T> *aBorrar = NULL;
        // Para el borrado de las aristas                                                     // Representara la arista a borrar ("logicamente")
        while (iter->hayElemento())
        {
            aBorrar = iter->obtenerElemento();
            aBorrar->existe = false;
            iter->avanzar();
        }
        aBorrar = NULL;
        delete aBorrar;
        delete iter;
    }

    void borrarArista(T origen, T destino)
    {
        int posOrigen = this->buscarPos(origen);
        IteradorLista<Arista<T> *> *iter = this->listaAdy[posOrigen]->obtenerIterador(); // iter es un puntero a la primera arista
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
        delete iter;
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
    miGrafo->borrarVertice(3);
    miGrafo->borrarVertice(4);
}
