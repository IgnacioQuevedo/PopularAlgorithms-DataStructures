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
        for (int j = 0; j <= maxTamanio; j++)
        {
            matDP[i][j] = new int[maxLineas + 1]; // Aca creamos la "profundidad" -> "una fila que va hacia adentro"
        }
    }
    // Inicializacion de la matriz tridimensional
    for (int i = 0; i < cantElem; i++)
    {
        for (int j = 0; j <= maxTamanio; j++)
        {
            for (int z = 0; z <= maxLineas; z++)
            {
                matDP[i][j][z] = -1;
            }
        }
    }

    //Caso borde cuando el tamaño sea 0
    for (int i = 0; i < cantElem; i++)
    {
        for (int z = 0; z <= maxLineas; z++)
        {
            matDP[i][0][z] = 0;
        }
    }

    //Caso borde cuando la profundidad es 0
    for (int i = 0; i < cantElem; i++)
    {
        for (int j = 0; j <= maxTamanio; j++)
        {
            matDP[i][j][0] = 0;
        }
    }

    // CASO BORDE PRIMERA FILA
    for (int j = 1; j <= maxTamanio; j++)
    {
        for (int z = 0; z <= maxLineas; z++) // Recorro la profundidad
        {
            if (elementos[0]->tamanio <= j && elementos[0]->lineas <= z) // Entonces puedo añadir ese elemento
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
    for (int i = 1; i < cantElem; i++)
    {
        for (int j = 1; j <= maxTamanio; j++)
        {
            for (int z = 0; z <= maxLineas; z++)
            {

                if (j < elementos[i]->tamanio || z < elementos[i]->lineas)
                {
                    matDP[i][j][z] = matDP[i-1][j][z]; // Copio al de arriba
                }
                else
                {
                    matDP[i][j][z] = max(matDP[i-1][j][z], elementos[i]->puntaje + matDP[i][j-elementos[i]->tamanio][z-elementos[i]->lineas]); // Me quedo con el mejor de los dos
                }
            }
        }
    }
    cout << matDP[cantElem -1][maxTamanio][maxLineas];
}

int main(int argc, char const *argv[])
{

    // Para ingreso de datos
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("./in.txt");
    cin.rdbuf(myFile.rdbuf());

    // Para salida (BORRAR PARA ENTREGA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
    ofstream myFile2("./out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int cantArchivos, maxTamanio, maxLineas;
    cin >> cantArchivos >> maxTamanio >> maxLineas;

    elemento **vectorElementos = new elemento *[cantArchivos];
    int tamanioArchivo, lineasArchivo, puntajeArchivo;

    for (int i = 0; i < cantArchivos; i++)
    {
        cin >> tamanioArchivo >> lineasArchivo >> puntajeArchivo;

        vectorElementos[i] = new elemento(tamanioArchivo, lineasArchivo, puntajeArchivo);
    }

    ejersDP(vectorElementos, maxTamanio, maxLineas, cantArchivos);

    return 0;
}
