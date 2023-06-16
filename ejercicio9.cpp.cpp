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

    int filasPascal = 0;
    int cantCombinaciones = 0;

    cin >> filasPascal;       // N
    cin >> cantCombinaciones; // P

    int *pascal = new int[filasPascal + 1]; // Porque arranca en nivel 0

    int exponenteCombinatoria = 0; // N de la combinatoria
    int baseCombinatoria = 0;      // Base de la combinatoria
    pascal[0] = 1;
    int filaActual = 0;
    cin >> exponenteCombinatoria; // Te da hasta la fila del triangulo que vas a estudiar
    cin >> baseCombinatoria;

    while(cantCombinaciones != 0){
        if (filaActual == exponenteCombinatoria)
        { // Significa que estas parado en la fila pedida y ahora podes devolver el valor.
            cout << pascal[baseCombinatoria] << endl;
            cin >> exponenteCombinatoria; // Te da hasta la fila del triangulo que vas a estudiar
            cin >> baseCombinatoria;
            cantCombinaciones--;
        }

        if (exponenteCombinatoria != filaActual)
        {
            pascal[exponenteCombinatoria] = 1; // Ya dejas pronta la siguiente linea a actualizar
            filaActual++;                      // Significa que te moviste una fila para adelante pero aun no llegaste a la fila pedida
            for (int j = filaActual; j >= 0; j--) // Te crea el array de la fila HASTA donde estas parado.
            {
                if (j - 1 > 0)
                { // significa que NO estas en el origen
                    pascal[j - 1] = pascal[j - 1] + pascal[j-2];
                }
            }
        }
        // FILA ANTERIOR MIRALO COMO UN i --> El i ESLA FILA DONDE TOY PARADO

        // PARA LA ACTUALIZACION DEL ARRAY

        // Una vez salido del for, actualizaste el array a la fila actual.
    }
    return 0;
}
