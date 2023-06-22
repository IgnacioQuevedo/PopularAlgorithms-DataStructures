// HASH CERRADO, ORDENAMIENTO MEDIANTE FUNCION CUADRATICA
#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadHashCerrado.cpp"
using namespace std;

unsigned long long potenciaElevada(int base, int elevado) //PORQUE LA USA EL HORNER
{
    if (elevado == 0)
    {
        return 1;
    }
    return base * potenciaElevada(base, --elevado);
}

unsigned long long horner(string clave) // funcion solo para strings (en int no hacer nada)
{
    unsigned long long claveConvertida = 0;
    int posCaracter = 0;

    while (clave[posCaracter] != '\0')
    {
        claveConvertida = claveConvertida + potenciaElevada(37, posCaracter) * clave[posCaracter];
        posCaracter++;
    }
    return claveConvertida;
}

unsigned long long funcionHash(string clave) // RETORNA POS VALIDA DENTRO DEL HASH
{
    unsigned long long pos = 0;
    pos = horner(clave);
    return pos;
}


int main(int argc, char const *argv[])
{
    // Para ingreso de datos
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    // ifstream myFile("./in.txt");
    // cin.rdbuf(myFile.rdbuf());
    // // Para salida (BORRAR PARA ENTREGA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
    // ofstream myFile2("./out.txt");
    // cout.rdbuf(myFile2.rdbuf());

    int cantPersonas, promedio = 0;
    int cantNotas, notaActual = 0;
    string nombre;

    cin >> cantPersonas;

    HashCerrado <string,int> *miHash = new HashCerrado <string,int> (cantPersonas, funcionHash);
    string *estudiantes = new string [cantPersonas];

    for (int i = 0; i < cantPersonas; i++)
    {
        cin >> nombre;
        cin >> cantNotas;

        for (int i = 0; i < cantNotas; i++)
        {
            cin >> notaActual;
            promedio = promedio + notaActual;
        }

        promedio = promedio / cantNotas;
        miHash->agregarElemento(nombre, promedio);
        promedio = 0;
        estudiantes[i] = nombre;
    }

    for (int i = 0; i < cantPersonas; i++)
    {
        cout << estudiantes[i] << " " << miHash->elemento(estudiantes[i]) << endl;
 
    }
    miHash->destruir();
    delete[] estudiantes;
    return 0; 
}