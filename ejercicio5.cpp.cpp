#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadGrafoOT.cpp"
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
    int cantAristas = 0;
    cin >> cantVertices;
    cin >> cantAristas;


    Grafo<int>* miGrafo = new Grafo<int>(cantVertices);
    
    for (int i = 1; i <= cantVertices; i++)
    {
        miGrafo->agregarVertice(i);
    }

    int origen = 0;
    int conexion = 0;

    for (int i = 0; i < cantAristas; i++)
    {   
        cin >> origen;
        cin >> conexion;
        
        miGrafo->agregarArista(origen,conexion);
    }
    
    Lista<int>* ret = new Lista<int>();
    ret = miGrafo->ordenTopologico();
    
    IteradorLista<int>* iter = ret->obtenerIterador();

   while (iter->hayElemento())
   {
    cout << iter->obtenerElemento() <<endl;
    iter->avanzar();
   }
   
    return 0;
    
}
