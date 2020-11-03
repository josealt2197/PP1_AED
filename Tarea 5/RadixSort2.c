#include <stdio.h>

void printArray(int * arreglo, int tamano){
  
  int i;
  printf("[ ");
  for (i = 0; i < tamano; i++)
    printf("%d ", arreglo[i]);
  printf("]\n");
}

int obtenerValorMayor(int * arreglo, int tamano){
  
  int i;
  int mayorNumero = -1;
  
  for(i = 0; i < tamano; i++){
    if(arreglo[i] > mayorNumero)
      mayorNumero = arreglo[i];
  }
  
  return mayorNumero;
}

// Radix Sort
void radixSort(int * arreglo, int tamano){
  
  printf("\n\nRadix Sort en la lista desordenada\n\n");

  // Se utiliza la base 10
  int i;
  int semiOrdenados[tamano];
  int digitoSignificativo = 1;
  int mayorNumero = obtenerValorMayor(arreglo, tamano);
  
  // Bucle hasta llegar al dígito significativo más grande
  while (mayorNumero / digitoSignificativo > 0){
    
    printf("\n\tOrdenando posicion del %d ", digitoSignificativo);
    printArray(arreglo, tamano);
    
    int bucket[10] = { 0 };
    
    // Cuenta el número de "claves" o dígitos que entrarán en cada depósito (bucket).
    for (i = 0; i < tamano; i++){
    	bucket[(arreglo[i] / digitoSignificativo) % 10]++;
    	printf("\n %d", ((arreglo[i] / digitoSignificativo) % 10));
	}

      
    /**
	 * Agregue el recuento de los depósitos anteriores, 
	 * Adquiere los índices después del final de cada ubicación de depósito en el arreglo 
	    * Funciona de manera similar al algoritmo de clasificación de recuento
     **/
    for (i = 1; i < 10; i++)
      bucket[i] += bucket[i - 1];
    
    // Usa el depósito para llenar el arreglo "semiOrdenados"
    for (i = tamano - 1; i >= 0; i--)
      semiOrdenados[--bucket[(arreglo[i] / digitoSignificativo) % 10]] = arreglo[i]; 
    
    for (i = 0; i < tamano; i++)
      arreglo[i] = semiOrdenados[i];
    
    // Move to next significant digit
    digitoSignificativo *= 10;
    
    printf("\t\tBucket: ");
    printArray(bucket, 10);
  }
}

int main(){
  
  printf("\n\nEjemplo de Radix Sort en C\n");
  printf("----------------------------------\n");
  
  int tamano = 12;
  int lista[] = {10, 2, 303, 4021, 293, 1, 0, 429, 480, 92, 2999, 14};
  
  printf("\nLista Desordenada: ");
  printArray(&lista[0], tamano);
  
  radixSort(&lista[0], tamano);
  
  printf("\nLista Ordenada:");
  printArray(&lista[0], tamano);
  printf("\n");
  
  return 0;
}
