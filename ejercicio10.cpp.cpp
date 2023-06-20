#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadLista.cpp"
using namespace std;

int vX[4]{-1, 0, 1, 0}; // Movimientos de x y de y en conjunto forman movs hacia der izq arriba y abajo
int vY[4]{0, 1, 0, -1};

class coordenadas
{

public:
    int x;
    int y;

    coordenadas(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

coordenadas *ubicarBedelia(char **mapa, int filas, int columnas)
{
    coordenadas *retorno = new coordenadas(0, 0);
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (mapa[i][j] == 'B')
            {
                retorno->x = i;
                retorno->y = j;
                return retorno;
            }
        }
    }
}

int darValor(char elemento)
{
    if (elemento == 'C' || elemento == 'B')
    {
        return 1;
    }
    else if (elemento == 'P')
    {
        return 0;
    }
}

bool esAceptable(char **&mapa, coordenadas *cordActual, bool **&vis, int filas, int columnas)
{
    return cordActual->x >= 0 && cordActual->y >= 0 && cordActual->x < filas && cordActual->y < columnas && !vis[cordActual->x][cordActual->y];
}

void cMasCorto(char **&mapa, const int &filas, const int &columnas, coordenadas *cordActual, coordenadas *&destino, bool **&vis, Lista<coordenadas *> *&caminoActual, Lista<coordenadas *> *&caminoOptimo, coordenadas *&posBedelia)
{
    // Definimos un caso base (llegar al destino) igual que en arboles
    if (cordActual->x == destino->x && cordActual->y == destino->y)
    {
        if ((!caminoOptimo || caminoActual->cantidadElementos() < caminoOptimo->cantidadElementos()) && vis[posBedelia->x][posBedelia->y] == true)
        {
            // Si entro acá significa que encontré una mejor solución que la anterior
            if (caminoOptimo != NULL)
            {
                caminoOptimo->vaciar();
            }
            else
            {
                caminoOptimo = new Lista<coordenadas *>();
            }
            IteradorLista<coordenadas *> *iter = caminoActual->obtenerIterador();
            while (iter->hayElemento())
            {
                coordenadas *elemento = iter->obtenerElemento();
                caminoOptimo->insertarFin(new coordenadas(elemento->x, elemento->y));
                iter->avanzar();
            }
        }
    }
    else
    {
        if (esAceptable(mapa, cordActual, vis, filas, columnas))
        {
            vis[cordActual->x][cordActual->y] = true;
            //             int vX[4] {-1, 0, 1, 0};
            //             int vY[4] {0, 1, 0, -1};
            for (int d = 0; d < 4; d++)
            {
                coordenadas *cordNueva = new coordenadas(cordActual->x + vX[d], cordActual->y + vY[d]);
                caminoActual->insertarFin(cordNueva);
                cMasCorto(mapa, filas, columnas, cordNueva, destino, vis, caminoActual, caminoOptimo, posBedelia);
                caminoActual->borrarFinal(); // va borrando el final del camino por si la recursion encuentra mejor camino
                delete cordNueva;            // Para no dejar memoria colgada
            }
            vis[cordActual->x][cordActual->y] = false;
        }
    }
}

Lista<coordenadas *> *caminoMasCorto(char **mapa, int filas, int columnas, coordenadas *origen, coordenadas *destino, coordenadas *posBedelia)
{
    bool **vis = new bool *[filas];

    for (int i = 0; i < filas; i++)
    {
        vis[i] = new bool[columnas];
        for (int j = 0; j < columnas; j++)
        {
            if (mapa[i][j] != 'P')
            {
                vis[i][j] = false;
            }
            else
            {
                vis[i][j] = true;
            }
        }
    }

    Lista<coordenadas *> *caminoActual = new Lista<coordenadas *>();
    caminoActual->insertarPpio(new coordenadas(origen->x, origen->y));
    Lista<coordenadas *> *caminoOptimo = NULL;

    cMasCorto(mapa, filas, columnas, origen, destino, vis, caminoActual, caminoOptimo, posBedelia);

    return caminoOptimo;
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

    int filas, columnas;

    cin >> filas;
    cin >> columnas;

    char **mapa = new char *[filas];
    coordenadas *posBedelia = new coordenadas(0, 0);

    for (int i = 0; i < filas; i++)
    {

        mapa[i] = new char[columnas];

        for (int j = 0; j < columnas; j++)
        {
            // guardar bedelia aca
            cin >> mapa[i][j];
            if(mapa[i][j] == 'B'){
                posBedelia->x = i;
                posBedelia->y = j;
            }
        }
    }

    int cantPedidos, xOrigen, yOrigen, xDestino, yDestino;
    int sumaCamino = 0;

    cin >> cantPedidos;

    for (int i = 0; i < cantPedidos; i++)
    {
        cin >> yOrigen >> xOrigen;
        coordenadas *origen = new coordenadas(xOrigen - 1, yOrigen - 1);
        cin >> yDestino >> xDestino;
        coordenadas *destino = new coordenadas(xDestino - 1, yDestino - 1);

        Lista<coordenadas *> *caminoMasOptimo = caminoMasCorto(mapa, filas, columnas, origen, destino, posBedelia);
        if (caminoMasOptimo == NULL)
        {
            sumaCamino = 0;
        }
        else
        {
            sumaCamino = caminoMasOptimo->cantidadElementos();
        }
        cout << sumaCamino << endl;
    }

    return 0;
}
