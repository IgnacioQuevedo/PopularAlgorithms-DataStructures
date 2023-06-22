#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadHeap.cpp"
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

    int cantReservas = 0;
    float personasXGrupo = 0;
    string viajeros;
    string pasaporte;
    int cantvuelos = 0;
    float promedioGrupo = 0;
    int cantVuelosGrupo = 0;

    cin >> cantReservas;
    bool esMinHeap = false;
    Heap<string> *miHeap = new Heap<string>(cantReservas, esMinHeap);

    for (int i = 0; i < cantReservas; i++)
    {
        cin >> personasXGrupo;
        for (int j = 0; j < personasXGrupo; j++)
        {
            cin >> pasaporte;
            pasaporte = pasaporte + " ";
            cin >> cantvuelos;
            viajeros = viajeros + pasaporte;
            cantVuelosGrupo = cantVuelosGrupo + cantvuelos;
        }
        promedioGrupo = cantVuelosGrupo / personasXGrupo;
        miHeap->encolar(promedioGrupo, viajeros);
        cantVuelosGrupo = 0;
        viajeros.erase(); // VACIA LA VARIABLE STRING.
    }

    while (!miHeap->esVacia())
    {
        promedioGrupo = miHeap->prioridadTope();
        viajeros = miHeap->topDato();
        miHeap->desencolar();
        cout.precision(2);
        if (promedioGrupo == static_cast<int>(promedioGrupo))
        {
            cout << static_cast<int>(promedioGrupo) << " " << viajeros << endl;
        }
        else
        {
            cout << fixed << promedioGrupo << " " << viajeros << endl;
        }
    }
    //BOUZA: BORRO ACA?
    miHeap->destruir();
    delete miHeap;
    return 0;
}