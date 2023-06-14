#include <iostream>
#include <fstream>
#include <string>
#include "./TADS/TadHeap.cpp"
using namespace std;


long long calcularCombinatoria(int n, int k){ //Formula de la combinatoria: 10c2 ---> (10!)/(2!*(10-2)) ---> (10x9x8x...x1)/(2x1)*(8)---> Se te cancelan 10x9/2*1 --> y esto es igual a (10/1)*(9/2)
                                              
    long long res = 1;
    for (int i = 0; i < k; i++)
    {
        res = res * (n-i); // Esto genera el numerador,la primera run va a quedar: 10
        res = res / (i+1); // esto va a generar el divisor, la primera run va a quedar 10/1
    }
   
    return res;
    //Al finalizar la run quedaria: (10*9)/(1*2) -->Esto equivale a lo representado bien arriba del todo.
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

    int paraKe = 0; 
    int cantCombinatorias = 0;
    
    cin >> paraKe;
    cin >> cantCombinatorias;

    //Esto genera nCk --> Combinaciones de n para k
    int n = 0; 
    int k = 0; 

    //Ejemplo: Le paso 10c2
    for (int i = 0; i < cantCombinatorias; i++)
    {
        cin >> n;
        cin >> k;
        cout << calcularCombinatoria(n,k) << endl;
    }









    return 0;
}
