#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadLista.cpp"
using namespace std;

class elemento
{
public:
    int tamanio;
    int lineas;
    int puntaje;

    elemento(int tamanio, int lineas, int puntaje)
    {
        this->tamanio = tamanio;
        this->lineas = lineas;
        this->puntaje = puntaje;
    }
};

void ejersDP(elemento **elementos, int maxTamanio, int maxLineas, int cantElem)
{

    int ***matDP = new int **[cantElem]; // Aca cree el vector

    // Creamos la matriz tridimensional
    for (int i = 0; i < cantElem; i++)
    {
        matDP[i] = new int *[maxTamanio + 1]; // Hasta aca, tengo la matriz creada
        for (int j = 0; j < maxTamanio; j++)
        {
            matDP[i][j] = new int[maxLineas + 1]; // Aca creamos la "profundidad" -> "una fila que va hacia adentro"
        }
    }

    for (int j = 1; j <= maxTamanio; j++)
    {
        for (int z = 0; z < maxLineas; z++) // Recorro la profundidad
        {
            if (elementos[0]->tamanio < j && elementos[0]->lineas < z) // Entonces puedo añadir ese elemento
            {
                matDP[0][j][z] = elementos[0]->puntaje;
            }
            else
            {
                matDP[0][j][z] = 0; // Significa que no puede entrar ese valor porque o falla en lineas o falla en tamaño
            }
        }
    }

    // Ahora recorro los lugares restantes.

    for (int i = 0; i < cantElem; i++)
    {
        for (int j = 0; j < maxTamanio; j++)
        {
            for (int z = 0; z < maxLineas; z++)
            {

                if (j < elementos[i]->tamanio || z < elementos[i]->lineas)
                {
                    matDP[i][j][z] = matDP[i - 1][j][z]; // Copio al de arriba
                }
                else
                {
                    max(matDP[i-1][j][z],matDP[i][j-elementos[i]->tamanio][z-elementos[i]->lineas]); //Me quedo con el mejor de los dos
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{

    int cantArchivos, maxTamaño, maxLineas;
    cin >> cantArchivos;
    cin >> maxTamaño;
    cin >> maxLineas;

    return 0;
}
