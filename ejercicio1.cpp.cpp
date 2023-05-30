// HASH CERRADO, ORDENAMIENTO MEDIANTE FUNCION CUADRATICA
#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadHashCerrado.cpp"
using namespace std;

int potenciaElevada(int base, int elevado) //PORQUE LA USA EL HORNER
{
    if (elevado == 0)
    {
        return 1;
    }
    return base * potenciaElevada(base, --elevado);
}


//TIENE QUE IR ACA, PORQUE SINO EL TAD HASH NO ES GENERICO, DEPENDIENDO DE LO QUE QUIERA GUARDAR EL USUARIO,
//LA FUNCION HASH VA A UTILIZAR HORNER O NO. 
//ENTONCES SI GUARDO PALABRAS PRECISO DE UN HORNER PARA TRANSFORMAR LA PALABRA A INT, Y RECIEN AHI PODER CONSEGUIR LA CUBETA
//PERO SI SON INTS **HORNER NO SE PRECISA** ENTONCES SI PONGO LA FUNCION HASH EN EL HASH PROPIO
//CRASHEA DADO QUE VA A LLAMAR A UN HORNER Y ES INTS Y ROMPE
//ENTONCES HORNER Y FHASH TIENEN QUE IR EN LA IMPLE DEL USUARIO. YA QUE LA FHASH SE COMPORTA DISTINTO
//DEPENDIENDO DEL TIPO DE DATO QUE GUARDE.

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

// char *copia(const char *nombre)
// {
//     int i = 0;
//     while (nombre[i] != '\0')
//     {
//         i++;
//     }
//     int largo = i + 1;
//     char *copia = new char[largo + 1];

//     int n = 0;
//     while (nombre[n] != '\0')
//     {
//         copia[n] = nombre[n];
//         n++;
//         copia[n + 1] = '\0';
//     }
//     if (nombre[0] == '\0')
//     {
//         copia[0] = '\0';
//     }
//     return copia;
// }

int main(int argc, char const *argv[])
{
    // Para ingreso de datos
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("./in.txt");
    cin.rdbuf(myFile.rdbuf());

    // Para salida (BORRAR PARA ENTREGA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
    ofstream myFile2("./out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int cantPersonas, promedio = 0;
    int cantNotas, notaActual = 0;
    char *nombre;

    //cout << "Ingrese cantidad Personas" << endl;
    cin >> cantPersonas;

    HashCerrado <string,int> *miHash = new HashCerrado <string,int> (cantPersonas, funcionHash);
    char **estudiantes = new char *[cantPersonas];

    for (int i = 0; i < cantPersonas; i++)
    {

        //cout << "Nombre del Estudiante" << endl;
        cin >> nombre;
        //cout << "Cant notas" << endl;
        cin >> cantNotas;

        for (int i = 0; i < cantNotas; i++)
        {
          //  cout << ("Ingrese Nota ") << i << endl;
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
        if (miHash->buscar(estudiantes[i]) == -1)
        {
            cout << "La persona no esta registrada" << endl;
        }
        else
        {
            cout << estudiantes[i] << " " << miHash->buscar(estudiantes[i]) << endl;
        }
    }

    return 0;
}