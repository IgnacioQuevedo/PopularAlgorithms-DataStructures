#include <iostream>
using namespace std;

template <typename K, typename V>
class nodoHash
{
public:
    K clave;
    V dato;

    nodoHash(K clave1, V dato1)
    {
        clave = clave1;
        dato = dato1;
    }
};

template <typename K, typename V>
class HashCerrado
{
private:
    nodoHash<K, V> **Tablahash;
    int cantElementos;
    int largoEsperado;
    int (*funcionHash)(K);

    bool esPrimo(int largoEsperado)
    {
        if (largoEsperado <= 1)
        {
            return false;
        }
        else
        {
            for (int i = 2; i <= largoEsperado / 2; i++)
            {
                if (largoEsperado % i == 0)
                { // SI ESTO OCURRE ENTONCES EL NUM ES PAR
                    return false;
                }
            }
            return true; // SI OCURRE ENTONCES ES IMPAR
        }
    }

    int sigPrimo(int largoEsperado)
    {
        while (!esPrimo(++largoEsperado))
            ; // SI DA FALSE AUMENTA UNO, ENTONCES GENERA QUE SEA IMPAR
        return largoEsperado;
    }

    int potenciaElevada(int elevado, int base)
    {
        if (elevado == 0)
        {
            return 1;
        }
        return base * potenciaElevada(--elevado, base);
    }

    bool libre(int pos)
    {
        if (this->Tablahash[pos] == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int cuadratica(int posOcupada)
    {
        // el largo primo asegura que la cuadratica siempre encuentre una nueva pos
        int i = 1;

        while (!libre(posOcupada))
        {
            posOcupada = (posOcupada + potenciaElevada(2, i)); // NUEVA POSICION A ESTUDIAR
            i++;
        }

        return posOcupada;
    }

public:
    HashCerrado(int largoEsperado1, int (*funcionHash)(K))
    {
        this->largoEsperado = sigPrimo(largoEsperado1);
        this->Tablahash = new nodoHash<K, V> *[largoEsperado];
        this->cantElementos = 0;
        for (int i = 0; i < largoEsperado; i++)
        {
            Tablahash[i] = NULL;
        }
        this->funcionHash = funcionHash; //el ptr al inicio está en null(es necesario definir esta linea)
    }

    void agregarElemento(K clave, V dato)
    {

        int pos = this->funcionHash(clave) % this->largoEsperado;
        if (libre(pos))
        {
            nodoHash<K, V> *elementoNuevo = new nodoHash<K, V>(clave, dato);
            this->Tablahash[pos] = elementoNuevo;
            this->cantElementos++;
        }

        else
        {
            int posLibre = cuadratica(pos);
            nodoHash<K, V> *elementoNuevo = new nodoHash<K, V>(clave, dato);
            this->Tablahash[posLibre] = elementoNuevo;
            this->cantElementos++;
        }
    }

    void destruir()
    {

        for (int i = 0; i < this->largoEsperado; i++)
        {
            delete this->Tablahash[i];
            this->cantElementos--;
        }

        delete[] this->Tablahash; // UNA VEZ VACIA BORRO LA TABLA HASH
    }

    // Métodos para buscar y eliminar elementos del hash
};

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
    char *nombre = "ABC";
    int clave = 0;
    int promedio = 70; // calcularlo
    int largo = 10;
    HashCerrado<char*, int> *nuevo = new HashCerrado<char*, int>(largo, funcionHash);
    nuevo->agregarElemento(nombre, promedio);

    return 0;
}
