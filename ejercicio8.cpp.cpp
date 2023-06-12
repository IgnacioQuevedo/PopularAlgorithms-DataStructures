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

    int cantVuelos = 0;
    cin >> cantVuelos;

    Heap<int> *heapVuelos = new Heap<int>(cantVuelos,true);
    int llegada = 0;
    int salida = 0;
    int idVuelo = 1;
    // Generamos el Heap Con los vuelos ordenados
    for (int i = 0; i < cantVuelos; i++)
    {
        cin >> llegada;
        cin >> salida;
        heapVuelos->encolar(llegada, salida); // Heap ordenado por llegada.
    }

    Heap<int> *heapPlataformas = new Heap<int>(cantVuelos,true);
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
            heapPlataformas->encolar(heapVuelos->topDato(),idVuelo);
        }
        heapVuelos->desencolar();
        idVuelo++; //No sirve de nada, solo lo tengo para que se vea mas lindo
    }
    cout << heapPlataformas->largo();
    return 0;
}

// IMPORTANCIA ORDENADO, Y USAR DOS HEAPS, HEAP 1->ORDENAMIENTO, PRECISA LLEGADA Y SALIDA
// Heap2 --> CANTIDAD DE RESEVAS, ATT: PLATAFORMAS, SU PRIO ES SALIDA, HEAP 2, SOLO PRECISA SALIDA


//Tenemos dos Heaps, El primer Heap, se encarga de ordenar los vuelos por orden de llegada,
//El segundo Heap se encarga de la cantidad de plataformas, (att: las reservas).
//Si el siguiente vuelo tiene un horario de llegada mayor al tiempo de la primera liberacion de plataforma, significa que esa plataforma ya queda libre,Por lo tanto la borramos, y encolamos el nuevo avion en esa plataforma.
//Si esto no ocurre, hay que añadir otra plataforma nueva.
//Las plataformas se basan en un sistema de reservas, logicamente si vos llegas en un horario donde la primera reserva ya finalizo, no precisas otra plataforma, utilizas la misma.
//Por ende borramos esa plataforma e insertamos la nueva reserva (que seria la tuya). Como borro y añado, no se aumentan la cantidad de plataformas, sino que realiza una especie de "sustitucion"
//Y si vos llegas en un horario donde la reserva aun no finalizo, precisas otra plataforma.
//Gracias a que esta ordenado,puedo borrar la primer reserva con total seguridad, ya que no habra vuelos con horarios intercalados. Si el vuelo A llega a las 13, el vuelo B llega si o si dsp.
//Por lo tanto, sabemos que la reserva que ya finalizo, realmente finalizo para todo vuelo existente.
//El problema si no estuviese ordenado, es que quiza le decimos al Vuelo A, si, usame desde 13 a 17, ya que la anterior reserva lo usa desde las 10 hasta las 12.
//El problema viene ahora, si no estuviese ordenado podria llegar una reserva la cual es desde las 15 a 16, y como el anterior no lo utiliza, se reservaria, fallando con el primer caso.
//Si no fuese ordenado, fallaria, ya que el codigo se basa en que la primer reserva es la primera en terminar, por lo tanto, una vez que se termina, borramos todo contacto con ella.
//Si me pasas un horario donde este mismo interceptase con alguna vieja reserva ya borrada, fallaria todo, ya que se podrian interceptar.
//La gracia es que cada vuelo, al estar ordenado se que el siguiente pasara despues, entonces no tendré este problema.


