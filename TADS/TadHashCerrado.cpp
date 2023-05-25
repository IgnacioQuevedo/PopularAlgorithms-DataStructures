#include <iostream>
#include <fstream>
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
    unsigned long long (*funcionHash)(K);

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

    int potenciaElevada(int base, int elevado)
    {
        if (elevado == 0)
        {
            return 1;
        }
        return base * potenciaElevada(base, --elevado);
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
        int posFinal = posOcupada;
        while (!libre(posFinal) && posFinal <= this->largoEsperado)
        {

            posFinal = (posOcupada + potenciaElevada(i, 2)) % this->largoEsperado; // NUEVA POSICION A ESTUDIAR, I ELEVADO A LA 2
            i++;
        }
        return posFinal;
    }

public:
    HashCerrado(int largoEsperado1, unsigned long long (*funcionHash)(K))
    {
        this->largoEsperado = sigPrimo(largoEsperado1);
        this->Tablahash = new nodoHash<K, V> *[largoEsperado];
        this->cantElementos = 0;
        for (int i = 0; i <largoEsperado; i++)
        {
            Tablahash[i] = NULL;
        }
        this->funcionHash = funcionHash; // el ptr al inicio está en null(es necesario definir esta linea)
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

    // CAMBIAR ESTUDIANTE, POR DATO Y PROMEDIO POR DATO2
    V buscar(K estudiante)
    {
        int i = 1;
        bool encontre = false;
        int posOriginal = (this->funcionHash(estudiante)) % this->largoEsperado; // POS ORIGINAL
        int posBuscada = posOriginal;                                            // Al ppio la pos original sera la buscada.En el caso que no sea, sera modificada mediante la cuadratica
        while (!encontre && posBuscada <= this->largoEsperado)
        {
            if (this->Tablahash[posBuscada] != NULL && this->funcionHash(this->Tablahash[posBuscada]->clave) == this->funcionHash(estudiante))
            {
                encontre = true;
            }
            else
            {
                posBuscada = (posOriginal + potenciaElevada(2, i)) % this->largoEsperado; // ESTILO CUADRATICA, PERO NO REPITIENDO HASTA ENCONTRAR UNA VACIA
                i++;
            }

            if (posBuscada > this->largoEsperado)
            { 
                return -1;
            }
        }

        return Tablahash[posBuscada]->dato;
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

    // Método eliminar elementos del hash
};
