
#include<stdio.h> 
#include <stdlib.h>

#define CANTIDAD 50

typedef struct Lista Lista;
typedef struct Nodo Nodo;

struct Nodo
{
	int dato;
	Nodo *siguiente;
};

struct Lista
{
	int tamano;
	Nodo *inicio;
};

Lista *listaNueva(void)
{
	Lista *L;
	L = (Lista *) malloc(sizeof(Lista));
	L->inicio = NULL;
	L->tamano=0;
	return L;
}

//Insertar el primer dato o un dato al final de la lista creada
void insertarDato(Lista *L, int dato)
{
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

//Mostrar los valores contenids en los nodos de la lista
void mostrarLista(const Lista *L)
{
	Nodo *i;
	for(i = L->inicio; i!= NULL; i = i->siguiente)
		printf("[%d]->", i->dato);
	printf("|\n");
}

//Retorna el tamano de la lista
int obtenerTamano(const Lista *L)
{
	return L->tamano;
}

//Liberar el espacio en memoria ocupado por los nodos de la lista creada
void liberarLista(Lista *L)
{
	Nodo *n, *aux;
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

int obtenerValorMayor(Lista *L)
{
	Nodo *i;
	int mayorNumero = -1;
	for(i = L->inicio; i!= NULL; i = i->siguiente){
		if(i->dato > mayorNumero) 
      		mayorNumero = i->dato ;
	}
	
	return mayorNumero;	
}

// Radix Sort
void radixSort(Lista *L){
	
	// Se utiliza la base 10
	int i;
	Nodo *j;

	int semiOrdenados[CANTIDAD];
	int arreglo[CANTIDAD];
	int digitoSignificativo = 1;
	int mayorNumero = obtenerValorMayor(L);
	
	// Bucle hasta llegar al dígito significativo más grande
	while (mayorNumero / digitoSignificativo > 0){
	
		printf("\n\tOrdenando posicion del %d \n", digitoSignificativo);
		//printArray(arreglo, tamano);
		
		i=0;
		for(j = L->inicio; j!= NULL; j = j->siguiente){
			arreglo[i] = j->dato;
			i++;	
		}
		
		int bucket[CANTIDAD] = { 0 };	
		
		// Cuenta el número de "claves" o dígitos que entrarán en cada depósito (bucket).
		for (i = 0; i < CANTIDAD; i++)
			bucket[(arreglo[i] / digitoSignificativo) % 10]++;
		
		/**
		* Agregue el recuento de los depósitos anteriores, 
		* Adquiere los índices después del final de cada ubicación de depósito en el arreglo 
		* Funciona de manera similar al algoritmo de clasificación de recuento
		**/
		for (i = 1; i < CANTIDAD; i++)
			bucket[i] += bucket[i - 1];
		
		// Usa el depósito para llenar el arreglo "semiOrdenados"
		for (i = CANTIDAD - 1; i >= 0; i--)
			semiOrdenados[--bucket[(arreglo[i] / digitoSignificativo) % 10]] = arreglo[i]; 
		
		i=0;
		for(j= L->inicio; j!= NULL; j = j->siguiente){
			j->dato = semiOrdenados[i];	
			i++;
		}
		
//		for (i = 0; i < tamano; i++)
//			arreglo[i] = semiOrdenados[i];
//		
		// Move to next significant digit
		digitoSignificativo *= 10;
				
	}
}

//Generar un numero aleatorio
int numeroAleatorio(){
    int numero;

    numero = (rand() % (CANTIDAD - 1 + 1)) + 1; 

    return numero;
}

int main(){

	Lista *L;
	int resultado, aleatorio, i;
	
	L = listaNueva();
	
	srand(time(0)); 
	for (i = 0; i< CANTIDAD; i++)  
    { 
	 	aleatorio=numeroAleatorio();
        insertarDato(L,aleatorio);
    } 

	printf("-->La lista desordenada es: ");
	mostrarLista(L);
	
	resultado=obtenerTamano(L);
	printf("\n-->Tamano de la lista: %d \n", resultado);
	
	printf("-->Mayor numero en la lista: %d \n", obtenerValorMayor(L));
	
	radixSort(L);
	
	printf("-->La lista ordenada es: ");
	mostrarLista(L);
	
	liberarLista(L);
	
	return 0;
}
