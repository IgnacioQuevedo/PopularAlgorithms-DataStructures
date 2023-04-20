// HASH CERRADO, ORDENAMIENTO MEDIANTE FUNCION CUADRATICA
#include <iostream>
#include <fstream>
#include <./TADS/TadHashCerrado.cpp>
using namespace std;

int main(int argc, char const *argv[])
{
    ofstream myFile2("./out.txt");
    cout.rdbuf(myFile2.rdbuf());
    int cantPersonas, promedio = 0;
    int cantNotas, notaActual = 0;
    char* nombre;

    cout << "Ingrese cantidad Personas";
    cin >> cantPersonas;
    HashCerrado<char*, int> *miHash = new HashCerrado<char*, int>(cantPersonas, funcionHash);

    for(int i=0; i<cantPersonas;i++){

        cout<< "Nombre del Estudiante";
        cin >> nombre;
        cout<< "Cant notas";
        cin >> cantNotas;
    
        for(int i = 0; i< cantNotas; i++){

            cout << ("Ingrese Nota" +i+1);
            cin  >> notaActual;
            promedio = promedio + notaActual;    
        }
        promedio = promedio / cantNotas;
        miHash->agregarElemento(nombre, promedio);
    return 0;
}

