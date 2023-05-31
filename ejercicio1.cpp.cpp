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
    string nombre;

    //cout << "Ingrese cantidad Personas" << endl;
    cin >> cantPersonas;

    HashCerrado <string,int> *miHash = new HashCerrado <string,int> (cantPersonas, funcionHash);
    string *estudiantes = new string [cantPersonas];

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
        cout << estudiantes[i] << " " << miHash->elemento(estudiantes[i]) << endl;
 
    }
    return 0; 
}