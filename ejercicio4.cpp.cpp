#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadGrafo.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
    // Para ingreso de datos
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("./in.txt");
    cin.rdbuf(myFile.rdbuf());

    // Para salida (BORRAR PARA ENTREGA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
    ofstream myFile2("./out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int cantVertices = 0;
    cin >> cantVertices;
    Grafo<int> *miGrafo = new Grafo<int>(cantVertices);

    for (int i = 1; i <= cantVertices; i++)
    {
        miGrafo->agregarVertice(i);
    }

    int cantAristas = 0;
    cin >> cantAristas;

    int origen = 0;
    int destino = 0;
    int costo = 0;
    int dirigido = 0;
    int existe = 0;
    for (int i = 0; i < cantAristas; i++)
    {
        cin >> origen;
        cin >> destino;
        cin >> costo;
        cin >> dirigido;
        dirigido = abs(dirigido - 2); // Si es 0 es NO DIRIGIDO, y si es 1 es DIRIGIDO
        cin >> existe;

        miGrafo->agregarArista(origen, destino, costo, dirigido, existe);
    }

    int cantCiudadNoHabi = 0;
    int ciudadABorrar = 0;
    cin >> cantCiudadNoHabi;
    for (int i = 0; i < cantCiudadNoHabi; i++)
    {
        cin >> ciudadABorrar;
        miGrafo->borrarVertice(ciudadABorrar);
    }

    int cantCarreterasNohabi = 0;
    cin >> cantCarreterasNohabi;
    for (int i = 0; i < cantCarreterasNohabi; i++)
    {
        cin >> origen;
        cin >> destino;
        miGrafo->borrarArista(origen, destino);
    }

    cin >> origen;
    cin >> destino;
    nodoDobleDato<int> *retorno = miGrafo->Dijkstra(origen, destino);

    if (retorno == NULL) // Significa que NO hay realmente un camino de inicio a fin
    {
        cout << -1 << endl;
        cout << "[]";
    }

    else
    {
        IteradorLista<int> *iter = (retorno->listaElem)->obtenerIterador(); // Conseguimos un iter para recorrer la lista, sin romper valores.
        cout << retorno->totalCostosDeAristas << endl;
        cout << "[";
        cout << iter->obtenerElemento(); // Añadimos el primero;
        iter->avanzar();
        while (iter->hayElemento())
        {
            cout << ", ";
            cout << iter->obtenerElemento();
            iter->avanzar();
        }
        cout << "]";
    }
    return 0;
}