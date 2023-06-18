#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadLista.cpp"
using namespace std;

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

coordenadas* ubicarBedelia(char** mapa, int filas, int columnas){
    coordenadas* retorno = new coordenadas(0,0);
    for(int i = 0; i < filas; i++){
        for(int j = 0; j<columnas; j++){
            if(matriz[i][j] == 'B'){
                retorno->x = i;
                retorno->y = j;
                return retorno
            }
        }
    }
}

int darValor(char elemento){
    if(elemento == 'C' || elemento == 'B'){
        return 1;
    }
    else if(elemento == 'P'){
        return 0;
    }
}

void cMasCorto(char** mapa, int filas, int columnas, coordenadas* cordActual, coordenadas* destino, int costoCaminoMaximo, bool**& vis, int& costoCaminoActual, int& costoCaminoMasOptimo, coordenadas* posBedelia){
    //Definimos un caso base (llegar al destino) igual que en arboles
    if(cordActual->x == destino->x && cordActual->y == destino->y){
        costoCaminoMaximo = costoCaminoMaximo - (mapa[cordActual->x][cordActual->y]);
        if(costoCaminoMaximo >= 0 && costoCaminoActual < costoCaminoMasOptimo  && vis[posBedelia->x][posBedelia->y] == true){
            //Si entro acá significa que encontré una mejor solución que la anterior

        }
    }
}


Lista<coordenadas*>* caminoMasCorto(char** mapa, int filas, int columnas, coordenadas* origen, coordenadas* destino, int caminoMaximo, coordenadas* posBedelia){
    bool** vis = new bool*[filas];

    for(int i = 0; i<filas; i++){
        vis[i] = new bool[columnas];
        for(int j =0; j < columnas; j++){
            vis[i][j] = false;
        }
    }

    Lista<coordenadas*>* caminoActual = new Lista<coordenadas>();
    Lista<coordenadas*>* caminoMasOptimo = NULL;

    cMasCorto(mapa, filas, columnas, origen, destino, caminoMaximo, vis, caminoActual, caminoMasOptimo);

    return caminoMasOptimo;

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

    char** mapa = new char*[filas];

    for(int i = 0; i<filas; i++){

        mapa[i] = new char[columnas];

        for(int j = 0; j < columnas; j++){
            cin >> mapa[i][j];
        }
    }

    int cantPedidos, xOrigen, yOrigen, xDestino, yDestino, caminoMaximo;

    coordenadas* posBedelia = ubicarBedelia(mapa, filas, columnas); 

    cin >> cantPedidos;

    for(int i = 0; i<cantPedidos; i++){
        cin >> xOrigen >> yOrigen >> xDestino >> yDestino;
        coordenadas* origen = new coordenadas(xOrigen, yOrigen);
        coordenadas* destino = new coordenadas(xDestino, yDestino);
        caminoMaximo = filas*columnas;
        int caminoMasOptimo = caminoMasCorto(mapa, filas, columnas, origen, destino, caminoMaximo, posBedelia);
        cout << caminoMasOptimo;
    }

    return 0;
}
