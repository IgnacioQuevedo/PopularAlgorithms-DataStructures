#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadHeap.cpp"
using namespace std;

int encontrarElem(int *numeros, int medio,int medioAnterior, int largo)
{
    //Derecha ---> "Ir hacia adelante"
    //Izquierda --> "Ir hacia atras"

    int posMedio = medio - 1; // Porque medio es el lugar siguiente a la real posicion, ya que el array arranca en 0
    int nuevoMedio = 0;
    int aux =0;

    if ((posMedio % 2) == 0)
    {

        //Si vos sos par, entonces hay una cantidad impar de personitas atras tuyas.

        if (numeros[posMedio] != numeros[posMedio - 1] && numeros[posMedio] != numeros[posMedio + 1])
        {
            //Si vos sos distinto a tu anterior y distinto a tu siguiente, entonces el error sos vos
            return numeros[posMedio];
        }

        if (numeros[posMedio] == numeros[posMedio - 1])
        {
            //Atras tuyo hay una cantidad impar de personas.
            //Si vos sos igual que tu anterior, significa que dejaste una cantidad par de parejitas atras tuyo. Entonces vos sabes que
            //El error esta a la derecha
            medioAnterior = medio;
            nuevoMedio = medio + (largo - medio)/2;
            return encontrarElem(numeros, nuevoMedio,medio, largo);
        }
        else
        {
            //Si vos sos distinto que tu anterior, significa que hay una cantidad impar de personitas solas, 
            //entonces sabes que tenes que ir por izquierda.
            
            nuevoMedio = medioAnterior + (medio - medioAnterior)/2;
            largo = medio;
            return encontrarElem(numeros, nuevoMedio,medioAnterior,largo);
        }
    }
    // Si es impar
    else
    {
        //Si sos impar, significa que atras tuyo hay una cantidad par de personitas.

        if (numeros[posMedio] != numeros[posMedio - 1] && numeros[posMedio] != numeros[posMedio + 1] )
        {
            //Si vos sos distinto a tu anterior y distinto a tu siguiente, entonces el error sos vos
            return numeros[posMedio];
        }

        if (numeros[posMedio] == numeros[posMedio - 1])
        {
            //Si vos sos igual a tu anterior significa que algun anterior no tiene a su parejita correcta. Ya que sin contarte a vos, atras tuyo hay una cantidad par de personitas.
            //Si vos te robas a una de ellas, implica que alguna personita quede sola, ya que dejas una cantidad impar de personitas libres.
            //Entonces el error esta a la izquierda

            nuevoMedio = medioAnterior + (medio - medioAnterior)/2;
            largo = medio;
            return encontrarElem(numeros,nuevoMedio,medioAnterior, largo);
            
        }
        else
        {
            //Si vos sos distinto a tu anterior, significa que la cantidad par de personitas estan todas bien juntas.
            //Entonces el error esta a tu derecha
            medioAnterior = medio;
            nuevoMedio = medio + (largo - medio)/2;
            return encontrarElem(numeros, nuevoMedio,medio, largo);
        }
    }
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

    int largo = 0;
    int elemento = 0;
    cin >> largo;
    int *numeros = new int[largo];

    numeros[0] = -1; //Obviamos el primer lugar, por ende lo definimos en algo que sabemos que nunca puede ser.
    for (int i = 1; i <= largo; i++)
    {
        cin >> elemento;
        numeros[i] = elemento;
    }
    
    int medio = (largo / 2);                      // El -1 para que el valor del medio sea igual a la pos del array
    cout << encontrarElem(numeros, medio,0, largo); // largo porque es la primera llamada.
    //delete[] numeros; BOUZA
}