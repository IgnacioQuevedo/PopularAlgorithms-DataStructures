#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadGrafoOT.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
   
    // // Para ingreso de datos
    // // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    // ifstream myFile("./in.txt");
    // cin.rdbuf(myFile.rdbuf());
    // // Para salida (BORRAR PARA ENTREGA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
    // ofstream myFile2("./out.txt");
    // cout.rdbuf(myFile2.rdbuf());

    int cantVertices,cantAristas;
    cin >> cantVertices >> cantAristas;
    
    Grafo* miGrafo = new Grafo(cantVertices);
    
    for (int i = 1; i <= cantVertices; i++)
    {
        miGrafo->agregarVertice(i);
    }

    int origen,conexion;

    for (int i = 0; i < cantAristas; i++)
    {   
        cin >> origen >> conexion;
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
   
    miGrafo->destruir();
    ret->destruirLista();
    iter = NULL;
    delete iter;
    delete miGrafo;
    delete ret;

    return 0;
}
