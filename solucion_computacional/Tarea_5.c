/*Algoritmos y Estructuras de Datos - Grupo 1
	Tarea 5 - Algoritmos de Busqueda y Ordenamiento
	Estudiantes: Jose Altamirano Salazar - 2020426159
	             Josué Brenes Alfaro - 2020054427
*/

#include<stdio.h>  

void linearSearch()  
{  
    int a[10] = {10, 23, 40, 1, 2, 0, 14, 13, 50, 9};  
    int item, i,flag;  
    printf("\nEnter Item which is to be searched\n");  
    scanf("%d",&item);  
    for (i = 0; i< 10; i++)  
    {  
        if(a[i] == item)   
        {  
            flag = i+1;  
            break;  
        }   
        else   
        flag = 0;  
    }   
    if(flag != 0)  
    {  
        printf("\nItem found at location %d\n",flag);  
    }  
    else  
    {  
        printf("\nItem not found\n");   
    }  
}   

int binarySearch(int a[], int beg, int end, int item)  
{  
    int mid;  
    if(end >= beg)   
    {     
        mid = (beg + end)/2;  
        if(a[mid] == item)  
        {  
            return mid+1;  
        }  
        else if(a[mid] < item)   
        {  
            return binarySearch(a,mid+1,end,item);  
        }  
        else   
        {  
            return binarySearch(a,beg,mid-1,item);  
        }  
      
    }  
    return -1;   
}  

void main ()  
{  
    int arr[10] = {16, 19, 20, 23, 45, 56, 78, 90, 96, 100};  
    int item, location=-1;   
    printf("Enter the item which you want to search ");  
    scanf("%d",&item);  
    location = binarySearch(arr, 0, 9, item);  
    if(location != -1)   
    {  
        printf("Item found at location %d",location);  
    }  
    else  
    {  
        printf("Item not found");  
    }  
} 



