// HASH CERRADO, ORDENAMIENTO MEDIANTE FUNCION CUADRATICA
#include <iostream>
#include <fstream>
#include "./TADS/TadHashCerrado.cpp"
using namespace std;
// Todo esto formara parte del ejercicio (POR AHORA VA ACA PARA PRUEBAS)

int potenciaElevada(int elevado, int base)
{
    if (elevado == 0)
    {
        return 1;
    }
    return base * potenciaElevada(--elevado, base);
}

int horner(char *clave) // funcion solo para strings (en int no hacer nada)
{
    unsigned long long claveConvertida = 0;
    int largoPalabra = 0;

    while (clave[largoPalabra] != '\0')
    {
        claveConvertida = claveConvertida + potenciaElevada(largoPalabra, 37) * clave[largoPalabra];
        largoPalabra++;
    }
    return claveConvertida;
}

int funcionHash(char *clave) // RETORNA POS VALIDA DENTRO DEL HASH
{
    return horner(clave);
}

int main(int argc, char const *argv[])
{
    ofstream myFile2("./out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int cantPersonas, promedio = 0;
    int cantNotas, notaActual = 0;
    char *nombre;

    cout << "Ingrese cantidad Personas";
    cin >> cantPersonas;

    HashCerrado<char *, int> *miHash = new HashCerrado<char *, int>(cantPersonas, funcionHash);
    char **estudiantes = new char *[cantPersonas];

    for (int i = 0; i < cantPersonas; i++)
    {

        cout << "Nombre del Estudiante";
        cin >> nombre;
        cout << "Cant notas";
        cin >> cantNotas;

        for (int i = 0; i < cantNotas; i++)
        {
            cout << ("Ingrese Nota" + i + 1);
            cin >> notaActual;
            promedio = promedio + notaActual;
        }

        promedio = promedio / cantNotas;
        miHash->agregarElemento(nombre, promedio);
        estudiantes[i] = nombre;
    }

    for (int i = 0; i < cantPersonas; i++)
    {
        cout << miHash->buscar(estudiantes[i]);
    }

    return 0;
}