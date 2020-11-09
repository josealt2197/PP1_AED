/*Algoritmos y Estructuras de Datos - Grupo 1
	Tarea 5 - Algoritmos de Busqueda y Ordenamiento
	Estudiantes: Jose Altamirano Salazar - 2020426159
	             Josué Brenes Alfaro - 2020054427
*/

#include<stdio.h> 
#include <stdlib.h>
#include <time.h> 

#define CANTIDAD 10

typedef struct Lista Lista;
typedef struct Nodo Nodo;

typedef struct ListaD ListaD;
typedef struct NodoD NodoD;

struct NodoD{
	int dato;
	NodoD *siguiente;
	NodoD *anterior; 
};

struct ListaD{
	NodoD *inicio;
	NodoD *final;
};

struct Nodo{
	int dato;
	Nodo *siguiente;
};

struct Lista{
	int tamano;
	Nodo *inicio;
};

Lista *listaSimple(void){
	Lista *L;
	L = (Lista *) malloc(sizeof(Lista));
	L->inicio = NULL;
	L->tamano=0;
	return L;
}

ListaD *listaDoble(void){
	ListaD *L;
	L = (ListaD *) malloc(sizeof(ListaD));
	L->inicio = NULL;
	L->final = NULL;
	return L;
}

NodoD* crearNodoDoble(int dato){
	NodoD *nuevo;
	nuevo = (NodoD *) malloc(sizeof(NodoD));
	nuevo->anterior = NULL;
	nuevo->siguiente = NULL;
	nuevo->dato = dato;	
	
	return nuevo;
}

void insertarDato(Lista *L, int dato){
	Nodo *n, *aux;
	L->tamano=L->tamano+1;
	
	if(L->inicio == NULL) 
	{
		//Inserta el primer nodo de la lista
		L->inicio = (Nodo *) malloc(sizeof(Nodo));
		L->inicio->dato = dato;
		L->inicio->siguiente = NULL;
		
		return;
	}
	n = L->inicio;
	while(n!= NULL)
	{
		aux = n;
		n = n->siguiente;		
	}
	//Inserta al final de la lista
	aux->siguiente = (Nodo *) malloc(sizeof(Nodo));
	aux->siguiente->siguiente = NULL;
	aux->siguiente->dato = dato;

}

void insertarDato_NodoD(ListaD *L, int dato){
	if(L->inicio == NULL) //Valida si la lista est? vac?a
	{
		//Inserta al inicio de la lista
		L->inicio = crearNodoDoble(dato);
		L->final = L->inicio;
		return;
	}
	
	//Inserta el dato al final de la lista, no necesita un ciclo porque tiene el puntero final
	L->final->siguiente = crearNodoDoble(dato);
	L->final->siguiente->anterior = L->final;
	L->final = L->final->siguiente;
}

void mostrarLista(const Lista *L){
	Nodo *i;
	printf("-->La lista es: ");
	for(i = L->inicio; i!= NULL; i = i->siguiente)
		printf("[%d]->", i->dato);
	printf("|\n");
}

int obtenerTamano(const Lista *L){
	return L->tamano;
}

void liberarLista(Lista *L){
	Nodo *n, *aux;
	if(L->inicio == NULL) //La lista está vacía
		return;
	if(L->inicio->siguiente == NULL)
		return;		
	n = L->inicio;
	
	while(n != NULL)//El n se va desplazado por la lista y el aux va a ir liberando los espacios
	{
		aux = n;
		n = n->siguiente;
		free(aux);
	}
	
}

void liberarListaDoble(ListaD *L){
	NodoD *n, *aux;
	if(L->inicio == NULL)
		return;
	if(L->inicio->siguiente == NULL)
		return;		
	n = L->inicio;
	
	while(n != NULL)
	{
		aux = n;
		n = n->siguiente;
		free(aux);
	}
	
} 

//Buscar un dato dentro de la lista generada con el algoritmo de busqueda lineal
int findLinealSearch(Lista *L, int dato){
	
	Nodo *nAux = L->inicio;
	int posicion = 0;
	
	while(nAux != NULL)//Se recorre la lista del primer al ultimo valor
	{
		if(nAux->dato == dato)//Si el dato de nodo al que apunta nAux coincide con el recibido
			return posicion+1; //se retorna la posición del nodo nAux en la lista
		nAux = nAux->siguiente;	
		posicion = posicion + 1;	
	}
	return -1;//Si no se halla el valor, se retorna -1
	
}

//Buscar un dato dentro de la lista generada con el algoritmo de busqueda binaria
int findBinarySearch(Lista *L, int dato, int inicio, int fin){  
    int centro, valorCentral, posicion=0;
    Nodo *nAux = L->inicio;

	if(L->inicio->dato == dato){
		return 1;
	}
    
    if(fin >= inicio){ 
	    
        centro = (inicio + fin)/2;
        
		while(posicion!=centro)
		{
			valorCentral = nAux->dato; 
			nAux = nAux->siguiente;	
			posicion = posicion + 1;	
		}
				  
        if(valorCentral == dato)  
        {  
            return centro;  
        }  
        else if(valorCentral < dato)   
        {  
            return findBinarySearch(L, dato, centro+1, fin);  
        }  
        else   
        {  
            return findBinarySearch(L, dato, inicio, centro-1);  
        }  
      
    }  
    return -1;   
} 

//Obtener el valor mayor de la lista
int obtenerValorMayor(Lista *L){
	Nodo *i;
	int mayorNumero = -1;
	for(i = L->inicio; i!= NULL; i = i->siguiente){
		if(i->dato > mayorNumero) 
      		mayorNumero = i->dato ;
	}
	
	return mayorNumero;	
}

// Ordena una lista mediante el algoritmo de Radix Sort
void radixSort(Lista *L){

	int i,  posicion=0, valor=0;
	Nodo *j, *k;
	NodoD *nd, *ndAux;
	
	Lista *semiOrdenados;
	semiOrdenados = listaSimple();
	
	for (i = 0; i< CANTIDAD; i++)  
    { 
	 	insertarDato(semiOrdenados, 0);
    }
    
	ListaD *aux;
	aux = listaDoble();

    for(j = L->inicio; j!= NULL; j = j->siguiente){
		insertarDato_NodoD(aux, j->dato);
	}

	int digitoSignificativo = 1;
	int mayorNumero = obtenerValorMayor(L);
	
//	// Bucle hasta llegar al dígito significativo más grande
	while (mayorNumero / digitoSignificativo > 0){
		
		ListaD *bucket;
		bucket = listaDoble();

		for (i = 0; i< 11; i++)  
	    { 
		 	insertarDato_NodoD(bucket, 0);
	    }     
	    
		// Cuenta el número de "claves" o dígitos que entrarán en cada depósito (bucket).
		
		for(ndAux = aux->inicio; ndAux!= NULL; ndAux = ndAux->siguiente){
			posicion=0;
			nd = bucket->inicio;
			while(nd!=NULL){
				if(posicion==(((ndAux->dato / digitoSignificativo) % 10)+1)){
					nd->dato=nd->dato+1;
				}
				posicion++;
				nd = nd->siguiente;
			}
		}
		

		/**
		* Agregue el recuento de los depósitos anteriores, 
		* Adquiere los índices después del final de cada ubicación de depósito en el arreglo 
		* Funciona de manera similar al algoritmo de clasificación de recuento
		**/
		for(nd = bucket->inicio->siguiente; nd!= NULL; nd = nd->siguiente){
			nd->dato = nd->dato + nd->anterior->dato;
		}

		for(ndAux = aux->final; ndAux!= NULL; ndAux = ndAux->anterior){
			
			posicion=0;
			nd = bucket->inicio;
			while(nd!=NULL){
				if(posicion==((ndAux->dato / digitoSignificativo) % 10)){
					valor=(nd->dato)-1;
					nd->dato=(nd->dato)-1;
					break;
				}
				posicion++;
				nd = nd->siguiente;
			}
			
			posicion=0;
			k = semiOrdenados->inicio;
			while(k!=NULL){
				if(posicion==valor){
					k->dato=ndAux->dato;
					break;
				}
				posicion++;
				k = k->siguiente;
			}

		}
		
		k=semiOrdenados->inicio;
		for(ndAux= aux->inicio; ndAux!= NULL; ndAux = ndAux->siguiente){
			ndAux->dato = k->dato;	
			k = k->siguiente;
		}
		
		//liberarListaDoble(bucket);
		
		// Move to next significant digit
		digitoSignificativo *= 10;
				
	}
	
	k=L->inicio;
	for(ndAux= aux->inicio; ndAux!= NULL; ndAux = ndAux->siguiente){
		ndAux->dato = k->dato;	
		k = k->siguiente;
	}
	
	liberarLista(semiOrdenados);
}

//Generar un numero aleatorio
int numeroAleatorio(){
    int numero;

    numero = (rand() % (100 - 1 + 1)) + 1; 

    return numero;
}

//Invocar a las funciones creadas
void main ()  
{  
	Lista *L;
	int resultado, aleatorio, i;
	
	L = listaSimple();
	
	srand(time(0)); 
	for (i = 0; i< CANTIDAD; i++)  
    { 
	 	aleatorio=numeroAleatorio();
        insertarDato(L,aleatorio);
        
    } 
    
    mostrarLista(L);
	printf("\n");
	
	/*****************************************************************************************/

//	printf("\n****BUSQUEDA LINEAL****\n");	
//	printf("\n-->Valor a consultar: %d \n", aleatorio);
//			
//    resultado = findLinealSearch(L, aleatorio);
//	
//	if(resultado >= 0)
//		printf("\n-->El dato se encuentra en la posicion %d\n", resultado);	
//	else	
//		printf("\n-->El dato no esta en lista\n");
  
  	/*****************************************************************************************/
  	
  	radixSort(L);
  	
  	mostrarLista(L);

//	printf("\n****BUSQUEDA BINARIA****\n");
//	printf("\n-->Valor a consultar: %d \n", aleatorio);
//	resultado=obtenerTamano(L);
//
//    resultado = findBinarySearch(L, aleatorio, 0, resultado); 
//	
//	if(resultado >= 0)
//		printf("\n-->El dato se encuentra en la posicion %d\n", resultado);	
//	else	
//		printf("\n-->El dato no esta en lista\n");
			
	/*****************************************************************************************/
	
	liberarLista(L);
}

