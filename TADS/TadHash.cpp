#include <iostream>
using namespace std;
//unsigned long long acumulado -->tipo para la clave.9
// EL ORDEN IMPORTA SI VOS NO CONOCES EL LARGO TOTAL QUE REALIZARA ESA FUNCION, EJEMPLO VOS NO SABES CUANTAS VECES VAS A AGREGAR POR ENDE TE IMPORTA EL ORDEN, PERO EL ORDEN DE CALCULAR CLAVE
// NO TE INTERESA DADO QUE YA CONOCES EL LARGO TOTAL QUE VAS A CALCULAR, POR ENDE COMO YA LO CONOCES NO TE IMPORTA. --> CONSTANTE

//LA GRACIA DE USAR UNA CLASE, ES QUE NO SE NECESITA LLAMAR POR PARAMETRO SIEMPRE AL HASH, DADO QUE AL
//SER UNA CLASE, LA PUEDO LLAMAR EN TODO EL ARCHIVO SIN NECESIDAD DE IR PASANDOME EL HASH COMO PARAMETRO.
//CON UTILIZAR THIS->LoQueMeInteresa YA QUEDA.

class nodoHash{ //CLASE DE LOS ELEMENTOS QUE VAN EN LA TABLAHASH, AL DEFINIRL LA LISTA SE CREA EL NODOHASH.
    public: //STRUCT (ME DEFINE LA ESTRUCTURA DE MI NODOHASH)
    char* clave; //LA POS EXACTA CALCULADA EN LA CUADRATICA
    int dato;   // DATO ES EL PROMEDIO

     nodoHash(char* clave1, int dato1){
        this->clave = clave1; //EN UN FUTURO SERA EL NOMBRE DE USUARIO CALCULADO POR LA CUADRATICA
        this->dato = dato1; // EN UN FUTURO SERA EL PROMEDIO
    }
    //LE DA FORMA A MI nodoHash
    
};

class HashCerrado{ //LA BOLSA

    private: //STRUCT (ME DEFINE LA ESTRUCTURA DE MI HASH)

        nodoHash **Tablahash; //vector que contiene al hash compuesto de cubos de tipo nodoHash
        int cantElementos; //cantElementos Actual.
        int largoEsperado; //Largo esperado del hash

        bool esPrimo(int largoEsperado){
            if(largoEsperado <=1){
                return false;
            }
            else{           
                for(int i=2; i<= largoEsperado/2;i++){
                    if(largoEsperado % i == 0){ //SI ESTO OCURRE ENTONCES EL NUM ES PAR
                        return false;
                    }
                }
                return true; // SI OCURRE ENTONCES ES IMPAR
            }
        }
        int sigPrimo(int largoEsperado){
            while(!esPrimo(++largoEsperado)); // SI DA FALSE AUMENTA UNO, ENTONCES GENERA QUE SEA IMPAR
            return largoEsperado;
        }

        int potenciaElevada(int elevado,int base){

            if(elevado == 0)
            {
                return 1;
            }
            return base * potenciaElevada(--elevado,base);
        }

    
        int horner(char* clave){ //ME TRANSFORMA LA CLAVE A UN INT DONDE CON ESE INT CONSEGUIRÉ LA POSICION (HORNER).
            
            unsigned long long claveConvertida = 0;
            int largoPalabra = 0;

            while (clave[largoPalabra] != '\0')

            {
                claveConvertida = claveConvertida + potenciaElevada(largoPalabra,37) * clave[largoPalabra];
                largoPalabra++;
            }
            return claveConvertida;
        }
        
        bool libre(int pos){
            if(this->Tablahash[pos]==NULL){
                return true;
            }
            else{
                return false;
            }
        }
        
        int funcionHash(int clave) //ME UNA POS VALIDA DENTRO DEL HASH
         {

            int resto = clave % this->largoEsperado;
            if (resto < 0) {
                resto = resto*(-1);
            }
	        return resto;
        }

        int cuadratica(int posOcupada) //SI OCURRE COLISION TE DA LA SIGUIENTE POSICION VACIA.
        { 
            //el largo primo me asegura que la cuadratica siempre encuentre una nueva posicion

            int posLibre = 0;
            int i = 1;

            while(!libre(posOcupada))
            {
                posOcupada = funcionHash(posOcupada + potenciaElevada(2,i)); //NUEVA POSICION A ESTUDIAR
                i++;
            }
        }


    public:
        //LE DA VIDA A MI HASH, "LO CREA"
        HashCerrado(int largoEsperado1){
            this->largoEsperado = sigPrimo(largoEsperado1); //DEFINO EL LARGO DE LA TABLAHASH
            this->Tablahash = new nodoHash*[largoEsperado1]; //CREO LA TABLAHASH (VECTOR DE TIPO T) CON ESE LARGO (VECTOR)
            //"CREO UN VECTOR DE LARGO X QUE TE GUARDE EN CADA POS UN PUNTERO DE TIPO NODOHASH, ESE PUNTERO APUNTA A CUALQUIER LADO, INTENTA LEERLO COMO NODOHASH NO FUNCIONA, DA BASURA. "
            this->cantElementos = 0; //SETTEO LA CANT ELEMENTOS

            for(int i=0;i<this->largoEsperado;i++){
                 // REDIRIGIS LOS PUNTEROS A NULL YA QUE APUNTAN BASURA
                this->Tablahash[i] = NULL;
            }
        }

        //datoClave, ES LA KEY A CALCULAR PARA LA FHASH
        void agregarElemento(char* clave, int dato){

            int pos = funcionHash(horner(clave));

            if(libre(pos)){ // SI NO ESTA OCUPADO, AGREGA
            nodoHash* elementoNuevo = new nodoHash(clave,dato);
            this->Tablahash[pos] = elementoNuevo;  
            this->cantElementos++;
            }

            else{
                int posLibre = cuadratica(pos); //A IMPLEMENTAR, ACTUALIZO EL POS CON UNO NUEVO
                nodoHash* elementoNuevo = new nodoHash(clave,dato);
                this->Tablahash[pos] = elementoNuevo;  
                this->cantElementos++;
            }
        }

        //MOSTRAR DATO
        int mostrarPromedio(char* nombre)
        {
            int promedioADar = funcionHash(horner(nombre)); //ME CONSIGUE EL PROMEDIO DEL NOMBRE ESPECIFICO
            return(promedioADar);
        }


        void destruir(){

           for (int i = 0; i < this->largoEsperado; i++)
           {
            delete this->Tablahash[i]; //VA SIN CORCHETES PORQUE ESTOY BORRANDO PUNTEROS
            this->cantElementos--; // CADA VEZ QUE BORRO BAJO UNO LA CANT ELEMENTOS
           }

            delete[] this->Tablahash; //UNA VEZ VACIA BORRO LA TABLA HASH ENTERA 
        }

};

















































int main(int argc, char const *argv[])
{
    int a =0;
    HashCerrado* miHash= new HashCerrado(7);  //SI NO TENES EL PUNTERO NO HAY FORMA DE LLEGAR A LA "BOLSA" QUE SERÍA MI HASH
    miHash->agregarElemento("hola",2);
    //int a = sistema.sigPrimo(5);
    return a;
}

 // //POS: ME DEVUELVE EL PROMEDIO DEL NOMBRE
        // T elemento(HashCerrado hash,T datoClave){
        //     return hash[funcionHash(datoClave, hash->largoEsperado)];
        // }
