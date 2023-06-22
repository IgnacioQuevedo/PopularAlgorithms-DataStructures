#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadHeap.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
     // Para ingreso de datos
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    // ifstream myFile("./in.txt");
    // cin.rdbuf(myFile.rdbuf());

    // // Para salida (BORRAR PARA ENTREGA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
    // ofstream myFile2("./out.txt");
    // cout.rdbuf(myFile2.rdbuf());

    int cantVuelos = 0;
    cin >> cantVuelos;
    Heap<int> *heapVuelos = new Heap<int>(cantVuelos, true);
    int llegada = 0;
    int salida = 0;
    int idVuelo = 1;
    //Generamos el Heap Con los vuelos ordenados
    for (int i = 0; i < cantVuelos; i++)
    {
        cin >> llegada;
        cin >> salida;
        heapVuelos->encolar(llegada, salida); // Heap ordenado por llegada
    }

    Heap<int> *heapPlataformas = new Heap<int>(cantVuelos, true);
    heapPlataformas->encolar(heapVuelos->topDato(), 1);
    heapVuelos->desencolar();
    int horarioLlegada = 0;

    while (!heapVuelos->esVacia())
    {
        horarioLlegada = heapVuelos->topPrio();
        // SI LA RESPUESTA ES NO ---> PRECISO OTRA PLATAFORMA
        // CUANDO YO LLEGO, EL YA SE FUE?
        // SI LA RESPUESTA ES SI -->  NO PASA NADA
        if (horarioLlegada < heapPlataformas->topPrio()) // Si yo llego antes de que el se vaya, entonces
        {
            heapPlataformas->encolar(heapVuelos->topDato(), idVuelo); // Aumento una plataforma
        }
        else
        {
            heapPlataformas->desencolar();
            heapPlataformas->encolar(heapVuelos->topDato(), idVuelo);
        }
        heapVuelos->desencolar();
        idVuelo++; // No sirve de nada, solo lo tengo para que se vea mas lindo
    }
    int largo = 0;
    largo = heapPlataformas->largo();
    cout << heapPlataformas->largo();

    //Liberacion de memoria
    heapPlataformas->destruir();
    heapVuelos->destruir();
    delete heapPlataformas;
    delete heapVuelos;
    return 0;
}
