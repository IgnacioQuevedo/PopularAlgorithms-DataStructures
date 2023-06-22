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
    int largo;
    unsigned long long (*funcionHash)(K);

    bool esPrimo(int largoDado)
    {
        if (largoDado <= 1)
        {
            return false;
        }
        else
        {
            for (int i = 2; i <= largoDado / 2; i++)
            {
                if (largoDado % i == 0)
                { // SI ESTO OCURRE ENTONCES EL NUM ES PAR
                    return false;
                }
            }
            return true; // SI OCURRE ENTONCES ES IMPAR
        }
    }

    int sigPrimo(int largoDado)
    {
        while (!esPrimo(++largoDado))
            ; // SI DA FALSE AUMENTA UNO, ENTONCES GENERA QUE SEA IMPAR
        return largoDado;
    }

    unsigned long long potenciaElevada(unsigned long long base, int elevado) //PORQUE LA USA LA CUADRATICA
    {
        if (elevado <= 0) 
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
        int i = 0;
        int posFinal = posOcupada;
        while (!libre(posFinal) && i != this->largo) //SI I ES DISTINTO AL LARGO, IMPLICA QUE TENGO MAS CUBETAS EN LA CUAL AVERIGUAR SI ESTA LIBRE.
        {

            posFinal = (posOcupada + potenciaElevada(i, 2)) % this->largo; // NUEVA POSICION A ESTUDIAR, I ELEVADO A LA 2
            i++;
        }
        return posFinal;
    }

public:
    HashCerrado(int largoDado, unsigned long long (*funcionHash)(K))
    {
        this->largo = 2* sigPrimo(largoDado);
        this->Tablahash = new nodoHash<K, V> *[largo];
        this->cantElementos = 0;
        for (int i = 0; i <largo; i++)
        {
            Tablahash[i] = NULL;
        }
        this->funcionHash = funcionHash; // el ptr al inicio está en null(es necesario definir esta linea)
    }

    void agregarElemento(K clave, V dato)
    {
        int pos = this->funcionHash(clave) % this->largo;
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
    V elemento(K estudiante)
    {
        int i = 0;
        bool encontre = false;
        int posOriginal = (this->funcionHash(estudiante)) % this->largo; // POS ORIGINAL
        unsigned long long posBuscada = 0; 
        posBuscada = posOriginal;  // Al ppio la pos original sera la buscada.En el caso que no sea, sera modificada mediante la cuadratica
        
        while (!encontre && i!= this->largo)
        {
            if (this->Tablahash[posBuscada] != NULL && this->funcionHash(this->Tablahash[posBuscada]->clave) == this->funcionHash(estudiante))
            {
                return Tablahash[posBuscada]->dato;
            }
            else
            {   
                posBuscada = (posOriginal + potenciaElevada(i, 2)) % this->largo; // ESTILO CUADRATICA, PERO NO REPITIENDO HASTA ENCONTRAR UNA VACIA
                i++;
            }
        }
    }

    void destruir()
    {
        for (int i = 0; i < this->largo; i++)
        {
            delete this->Tablahash[i];
            this->cantElementos--;
        }

        delete[] this->Tablahash; // UNA VEZ VACIA BORRO LA TABLA HASH
    }

    // Método eliminar elementos del hash
};
