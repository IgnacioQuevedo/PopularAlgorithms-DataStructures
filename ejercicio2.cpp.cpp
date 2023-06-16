#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadAvl.cpp"
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

    int cantPalabras = 0;
    cin >> cantPalabras;
    int b=0;
    Avl<string> *miArbol = new Avl<string>(cantPalabras);
    
    string palabra = "";
    for (int i = 0; i < cantPalabras; i++)
    {
        palabra = "";
        cin >> palabra;
        miArbol->insertar(palabra);
    }
    miArbol->inOrder();

    return 0;
}