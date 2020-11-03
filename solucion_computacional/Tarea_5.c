/*Algoritmos y Estructuras de Datos - Grupo 1
	Tarea 5 - Algoritmos de Busqueda y Ordenamiento
	Estudiantes: Jose Altamirano Salazar - 2020426159
	             Josué Brenes Alfaro - 2020054427
*/

#include<stdio.h> 
#include <stdlib.h>

#define CANTIDAD 500

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
	printf("-->La lista es: ");
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
int findBinarySearch(Lista *L, int dato, int inicio, int fin)  
{  
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

//Generar un numero aleatorio
int numeroAleatorio(){
    int numero;

    numero = (rand() % (CANTIDAD - 1 + 1)) + 1; 

    return numero;
}


//Invocar a las funciones creadas
void main ()  
{  
	Lista *L, *L2;
	int resultado, aleatorio, i;
	
	L = listaNueva();
	L2 = listaNueva();
	
	srand(time(0)); 
	for (i = 0; i< CANTIDAD; i++)  
    { 
	 	aleatorio=numeroAleatorio();
        insertarDato(L,aleatorio);
    } 

	printf("\n****Lista generada****\n");
	mostrarLista(L);
	
	printf("\n****Prueba Busqueda Lineal****\n");	
	aleatorio=numeroAleatorio();
	printf("\n-->Valor a consultar: %d \n", aleatorio);
	resultado = findLinealSearch(L, aleatorio);
	
	if(resultado >= 0)
		printf("\n-->El dato se encuentra en la posicion %d\n", resultado);	
	else	
		printf("\n-->El dato no esta en lista\n");
	
	int consulta;
	printf("\n-->Consultar otro valor \n", aleatorio);
	printf("\n<--Digite el valor para consultar: ");
	scanf("%d", &consulta);
	resultado = findLinealSearch(L, consulta);
	
	if(resultado >= 0)
		printf("\n-->El dato se encuentra en la posicion %d\n", resultado);	
	else	
		printf("\n-->El dato no esta en lista\n");
	
	printf("\n****Prueba Busqueda Binaria****\n");
	
	resultado=obtenerTamano(L);
	printf("\n-->Tamano de la lista: %d\n", resultado);
	
	int par=2;
	for (i = 0; i< CANTIDAD; i++)  
    { 
        insertarDato(L2,par);
        par=par+2;
    } 
    
    printf("\n****Lista generada****\n");
	mostrarLista(L2);
    
    printf("\n<--Digite el valor para consultar: ");
	scanf("%d", &consulta);
	resultado = findBinarySearch(L2, consulta, 0, resultado);
	
	if(resultado >= 0)
		printf("\n-->El dato se encuentra en la posicion %d\n", resultado);	
	else	
		printf("\n-->El dato no esta en lista\n");
			
	liberarLista(L);
	liberarLista(L2);
}

