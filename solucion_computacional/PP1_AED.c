/*Algoritmos y Estructuras de Datos - Grupo 1
	Proyecto Programado 1 
	Estudiantes: Jose Altamirano Salazar - 2020426159
	             Josué Brenes Alfaro - 2020054427
*/
  
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

FILE* ArchRequerimiento;
FILE* ArchMiembros;
FILE* ArchAsignaciones;
FILE* ArchIncidentes;

//Procedimientos para Menus de Opciones
void MenuPrincipal();
void GestionEquipo();
void GestionAsignacion();
void GestionRequerimiento();
void GestionIncidentes();
void AnalisisDeDatos();

typedef struct Requerimiento Requerimiento;
typedef struct MiembroEquipo MiembroEquipo;
typedef struct Asignacion Asignacion;
typedef struct Incidentes Incidentes;

typedef struct ListaMiembros ListaMiembros;
typedef struct ListaRequerimientos ListaRequerimientos;
typedef struct ListaAsignaciones ListaAsignaciones;
typedef struct ListaIncidentes ListaIncidentes;

//Procedimientos para Miembros de Equipo
void registrarMiembro();
void guardarMiembro(MiembroEquipo *miembro);
int cargarMiembros(struct ListaMiembros *L);
void consultarMiembroEquipo();
void liberarListaMiembros(ListaMiembros *L);

//Procedimientos para Requerimientos
void registrarRequerimiento();
void guardarRequerimiento(Requerimiento *requerimiento);
int cargarRequerimientos(struct ListaRequerimientos *L);
void consultarRequerimiento();
int validarIDRequerimiento(const char identificador []);
void liberarListaRequerimientos(ListaRequerimientos *L);
void modificarRequerimiento();
void actualizarRequerimientos(struct ListaRequerimientos *L);

//Procedimientos para Asignaciones
void registrarAsignacion();
void guardarAsignacion(Asignacion *asignacion);
int cargarAsignaciones(struct ListaAsignaciones *L);
void consultarAsignaciones();
void liberarListaAsignaciones(ListaAsignaciones *L);

//Procedimientos para Incidentes
void registrarIncidentes();
void guardarIncidentes(Incidentes *incidente);
int cargarIncidentes(struct ListaIncidentes *L);
void consultarIncidentes();
void liberarListaIncidentes(ListaIncidentes *L);

//Procedimientos de Apoyo
int numeroAleatorio();
void obtenerFechaActual(char *hoy);

struct Requerimiento{
    char identificador[50];
    char tipo[20];
    char descripcion[100];
    char riesgo[60];
    char dependencia[100];
    char recursos[55];
    char estado [15];
    char esfuerzo[5];
    Requerimiento *siguiente;
    Requerimiento *anterior;
};

struct MiembroEquipo{
    char nombre_completo[50];
    char cedula[12];
    char correo[50];
    char nivel_acceso[3];
    char telefono[15];
    MiembroEquipo *anterior;
    MiembroEquipo *siguiente;
};

struct Asignacion{
    char fechaSolicitud[50];
    char horaInicio[15];
    char horaFin[15];
    char recurso[50];
    char identificador[10];
    char descripcion[100];
    char miembros[15];
    char prioridad[15];
    char estado[15];
    Asignacion *anterior;
    Asignacion *siguiente;
};

struct Incidentes{
    char codigoRequerimiento[15];
    char codigoAsignacion[15];
    char descripcionIncidente[100];
    char fecha[20];
    Incidentes *anterior;
    Incidentes *siguiente;
};

struct ListaMiembros {
	MiembroEquipo *inicio;
	MiembroEquipo *final;
};

struct ListaRequerimientos{
	Requerimiento *inicio;
	Requerimiento *final;
};

struct ListaIncidentes{
	Incidentes *inicio;
	Incidentes *final;
};

struct ListaAsignaciones{
	Asignacion *inicio;
	Asignacion *final;
};


void Temporal(){
	getchar();
}

/*
	Entradas: Un número (tipo char) en un rango de 0 a 6 para escoger una de las opciones disponibles en el menú. 
	Salidas: Llamada a las demas funciones de menús.
	Restricciones: Solo se deben ingresar números en un rango de 0 a 6.
*/
void MenuPrincipal(){
	char opcion;
	
	do{
        system( "CLS" );
        fflush(stdin);
        printf("\n\n+-------------------------------+\n");
		printf("      Gestor de Requerimientos          \n");
		printf("+-------------------------------+\n");
		printf( "\t  Menu Principal\n" );
		printf("+-------------------------------+\n");
		printf( "\n 1 - Gestion de Miembros de Equipo" );
	    printf( "\n 2 - Gestion de Requerimientos" );
	    printf( "\n 3 - Gestion de Asignaciones" );
	    printf( "\n 4 - Gestion de Incidentes" );
		printf( "\n 5 - Analisis de Datos" );   
	    printf( "\n 6 - Salir" );
	    printf("\n");
	    printf("\n\n Elija una opcion : ");
        opcion = getchar();
        
        switch ( opcion ){
            case '1': GestionEquipo();
                break;
			case '2': GestionRequerimiento();
                break;
            case '3': GestionAsignacion();
                break;
			case '4': GestionIncidentes();
                break;
            case '5': AnalisisDeDatos();
				break;
			case '6': exit(1);
				break;
            default:
            	fflush(stdin);
				printf("**Opcion no valida. Intente de nuevo.**\n");
				getchar();
                break;
        }
    } while (opcion!='6');    
    fflush(stdin);
	getchar();	
}

/*
	Entradas: Un número (tipo char) en un rango de 0 a 2 para escoger una de las opciones disponibles en el menú. 
	Salidas: en caso de que el número ingresado sea 0 se devuelve al menú principal, si el número es 1 se a llama la funcion registrarMiembro(), 
	         Si el número ingresado es 2 se llama a la función ** .
	Restricciones: Solo se deben ingresar números en un rango de 0 a 2.
*/
void GestionEquipo(){
	char opcion, ch;	

	do{
		system( "CLS" );
		fflush(stdin);
		printf("\n\n+---------------------------------+\n");
		printf("      Gestor de Requerimientos          \n");
		printf("+---------------------------------+\n");
		printf( "   Gestion de Miembros de Equipo\n" );
		printf("+---------------------------------+\n");
		printf("\n 0. Volver al Menu Principal.");
		printf("\n 1. Registrar un Miembro de Equipo.");
		printf("\n 2. Consultar un Miembro de Equipo.");
		printf("\n");
		printf("\n\nElija una opcion : ");	
		opcion=getchar();
		
		while((ch = getchar()) != EOF && ch != '\n');
			switch(opcion){
				case '1':  registrarMiembro();
					break;
				case '2': consultarMiembroEquipo();
					break;
				case '0': MenuPrincipal();
					break;
				default:
					fflush(stdin);
					printf("**Opcion no valida. Intente de nuevo.**\n");
					getchar();
					break;	
		}	
	}while(opcion!=3);			
	fflush(stdin);
	getchar();
}

/*
	Entradas: Un número (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el menú. 
	Salidas: en caso de que el número ingresado sea 0 se devuelve al menú principal, si el número es 1 se a llama la funcion registrarRequerimiento(), 
	         Si el número ingresado es 2 se llama a la función **, Si el número ingresado es 3 se llama a la función **,
	         Si el número ingresado es 4 se llama a la función ***.
	Restricciones: Solo se deben ingresar números en un rango de 0 a 4.
*/
void GestionRequerimiento(){
	char opcion, ch;	

	do{
		system( "CLS" );
		fflush(stdin);
        printf("\n\n+-------------------------------+\n");
		printf("      Gestor de Requerimientos          \n");
		printf("+-------------------------------+\n");
		printf( "   Gestion de Requerimientos\n" );
		printf("+-------------------------------+\n");
		printf("\n 0. Volver al Menu Principal.");
		printf("\n 1. Agregar nuevo requerimiento.");
		printf("\n 2. Modificar un requerimiento.");
		printf("\n 3. Calificar un requerimiento.");
		printf("\n 4. Consultar un requerimiento.");
		printf("\n");
		printf("\n\nElija una opcion : ");	
		opcion=getchar();
		
		while((ch = getchar()) != EOF && ch != '\n');
			switch(opcion){
				case '1': registrarRequerimiento();
					break;
				case '2': modificarRequerimiento();
					break;
				case '3': Temporal();
					break;
				case '4': consultarRequerimiento();
					break;
				case '0': MenuPrincipal();
					break;
				default:
					fflush(stdin);
					printf("**Opcion no valida. Intente de nuevo.**\n");
					getchar();
					break;	
		}	
	}while(opcion!=3);			
	fflush(stdin);
	getchar();
}

/*
	Entradas: Un número (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el menú. 
	Salidas: en caso de que el número ingresado sea 0 se devuelve al menú principal, si el número es 1 se a llama la funcion registrarAsignacion(), 
	         Si el número ingresado es 2 se llama a la función **, Si el número ingresado es 3 se llama a la función **,
	         Si el número ingresado es 4 se llama a la función ***.
	Restricciones: Solo se deben ingresar números en un rango de 0 a 4.
*/
void GestionAsignacion(){
	char opcion, ch;	

	do{
		system( "CLS" );
		fflush(stdin);
        printf("\n\n+-------------------------------+\n");
		printf("      Gestor de Requerimientos          \n");
		printf("+-------------------------------+\n");
		printf( "     Gestion de Asignaciones\n" );
		printf("+-------------------------------+\n");
		printf("\n 0. Volver al Menu Principal.");
		printf("\n 1. Crear una nueva asignacion.");
		printf("\n 2. Consultar asignaciones de un miembro.");
		printf("\n 3. Cancelar una asignacion.");
		printf("\n 4. Atender una asignacion.");
		printf("\n");
		printf("\n\nElija una opcion : ");	
		opcion=getchar();
		
		while((ch = getchar()) != EOF && ch != '\n');
			switch(opcion){
				case '1':  registrarAsignacion();
					break;
				case '2': consultarAsignaciones();
					break;
				case '3': Temporal();
					break;
				case '4': Temporal();
					break;
				case '0': MenuPrincipal();
					break;
				default:
					fflush(stdin);
					printf("**Opcion no valida. Intente de nuevo.**\n");
					getchar();
					break;	
		}	
	}while(opcion!=3);			
	fflush(stdin);
	getchar();
}

/*
	Entradas: Un número (tipo char) en un rango de 0 a 2 para escoger una de las opciones disponibles en el menú. 
	Salidas: en caso de que el número ingresado sea 0 se devuelve al menú principal, si el número es 1 se a llama la funcion registrarIncidentes(), 
	         Si el número ingresado es 2 se llama a la función **, Si el número ingresado es 3 se llama a la función **
	Restricciones: Solo se deben ingresar números en un rango de 0 a 2.
*/
void GestionIncidentes(){
	char opcion, ch;	

	do{
		system( "CLS" );
		fflush(stdin);
        printf("\n\n+-------------------------------+\n");
		printf("      Gestor de Requerimientos          \n");
		printf("+-------------------------------+\n");
		printf( "      Gestion de Incidentes\n" );
		printf("+-------------------------------+\n");
		printf("\n 0. Volver al Menu Principal.");
		printf("\n 1. Registrar un incidente.");
		printf("\n 2. Consultar por rango de fechas.");
		printf("\n 3. Consultar por codigo de requerimiento.");
		printf("\n");
		printf("\n\nElija una opcion : ");	
		opcion=getchar();
		
		while((ch = getchar()) != EOF && ch != '\n');
			switch(opcion){
				case '1': registrarIncidentes();
					break;
				case '2': consultarIncidentes();
					break;
				case '3': consultarIncidentes();
					break;
				case '0': MenuPrincipal();
					break;
				default:
					fflush(stdin);
					printf("**Opcion no valida. Intente de nuevo.**\n");
					getchar();
					break;	
		}	
	}while(opcion!=3);			
	fflush(stdin);
	getchar();
}

/*
	Entradas: Un número (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el menú. 
	Salidas: en caso de que el número ingresado sea 0 se devuelve al menú principal, si el número es 1 se a llama la funcion registrarIncidentes(), 
	         Si el número ingresado es 2 se llama a la función **, Si el número ingresado es 3 se llama a la función **,
	         Si el número ingresado es 4 se llama a la función ***.
	Restricciones: Solo se deben ingresar números en un rango de 0 a 4.
*/
void AnalisisDeDatos(){
	char opcion, ch;	

	do{
		system( "CLS" );
		fflush(stdin);
        printf("\n\n+-------------------------------+\n");
		printf("      Gestor de Requerimientos          \n");
		printf("+-------------------------------+\n");
		printf( "\t  Analisis de Datos\n" );
		printf("+-------------------------------+\n");
		printf("\n 0. Volver al Menu Principal.");
		printf("\n 1. Mostrar requerimientos con más asignaciones.");
		printf("\n 2. Mostrar horarios más utilizados.");
		printf("\n 3. Mostrar personas que son mas asignadas.");
		printf("\n 4. Mostrar requerimientos con mayor esfuerzo.");
		printf("\n");
		printf("\n\nElija una opcion : ");	
		opcion=getchar();
		
		while((ch = getchar()) != EOF && ch != '\n');
			switch(opcion){
				case '1': Temporal();
					break;
				case '2': Temporal();
					break;
				case '3': Temporal();
					break;
				case '4': Temporal();
					break;
				case '0': MenuPrincipal();
					break;
				default:
					fflush(stdin);
					printf("**Opcion no valida. Intente de nuevo.**\n");
					getchar();
					break;	
		}	
	}while(opcion!=3);			
	fflush(stdin);
	getchar();
}

/*
	Entradas: Una puntero a una cadena de caacteres.
	Salidas: La cadena de caracteres recibida, con el valor de la fecha actual, siguiendo el formato dd/MM/AAAA.
	Restricciones: Ninguna.
*/
void obtenerFechaActual(char *hoy){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	char dia[3], mes[3], anho[3];
	sprintf(dia, "%d", tm.tm_mday);
	sprintf(mes, "%d", (tm.tm_mon + 1));
	sprintf(anho, "%d", (tm.tm_year + 1900));
	
	strcat(hoy, dia);  
	strcat(hoy, "-");
	strcat(hoy, mes); 
	strcat(hoy, "-");
	strcat(hoy, anho);
 	
}

/*
	Entradas: Ninguna.
	Salidas: Un valor entero leatorio entre 1 y 3.
	Restricciones: Ninguna.
*/
int numeroAleatorio(){
    int numero;

    srand(time(NULL));
    do{
        numero =10+rand () %(13+1-10);
    }while(numero-10==0);
    return numero-10;
}

/*
	Entradas: Dos cadenas de caracteres.
	Salidas: Un valor de 1 si ambas cadenas son iguales y cero si son diferentes.
	Restricciones: Ninguna.
*/
int compararCadenas(const char cadena1[], const char cadena2[] ){
    int j=0, similitud=0;


    while(1){

        if(cadena1[j] == '\0' || cadena2[j]== '\0')
            break;
        if(cadena1[j] != cadena2[j]){
            similitud=0;
            break;
        }else{
            similitud=1;
        }

        j++;
        }
    if(similitud==1){
        return 1;
    }
    return 0;
}

/*
	Entradas: Una cadena de caacteres.
	Salidas: La cadena de caracteres recibida, sustituyendo el valor de los campos con un salto de linea (\n) por un caracter nulo.
	Restricciones: El parametro debe corresponder con el tipo cadena de caracteres.
*/
void quitaFinLinea(char linea[]){
	int i;
	for(i=0; linea[i]!='\0'; i++){
		if(linea[i] == '\n'){
			linea[i]='\0';
			break;
		}
	}
}

/*
	Entradas: Los diferentes objetos de la estructura Miembro de Equipo(nombre, cedula, correo, telefono, nivel  
	          de acceso). 
	Salidas: LLama a la función guardarMiembro para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void registrarMiembro(){
    char validacion[15];
    system( "CLS" );
    printf("\n\n+-------------------------------+\n");
    printf("      Gestor de Requerimientos          \n");
    printf("+-------------------------------+\n");
    printf( "  Registrar Miembro de Equipo\n" );
    printf("+-------------------------------+\n");

    struct MiembroEquipo *miembro;

    miembro=(struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));

    do{
        printf("\n Ingrese la Cedula: (Ejm.105450656) \n");
        gets(miembro->cedula);

        if(validarCedula(miembro->cedula)==1){
            printf("\n Esta cedula ya ha sido registrada\n ");
        }else{
            break;
        }
    }while(1);
    
    printf("\n Ingrese el Nombre Completo: (Ejm.Juan Perez) \n");
    gets(miembro->nombre_completo);
    printf("\n Ingrese el Correo Electronico: (ejemplousuario@correo.com) \n");
    gets(miembro->correo);
    printf("\n Ingrese el Nivel de Acceso (1-10) : \n");
    gets(miembro->nivel_acceso);
    printf("\n Ingrese un Numero Telefonico: (Ejm. 83728492) \n");
    gets(miembro->telefono);

    guardarMiembro(miembro);
    free(miembro);
    getchar();
}

/*
	Entradas: Una estructura de Miembro de Equipo. 
	Salidas: Guardar los datos de la estructura en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void guardarMiembro(MiembroEquipo *miembro){
	
	ArchMiembros=fopen("Archivos\\MiembroEquipo.txt","a+");
	if(ArchMiembros==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		fprintf(ArchMiembros,"%s\n%s\n%s\n%s\n%s\n", miembro->cedula, miembro->nombre_completo, miembro->correo, miembro->nivel_acceso, miembro->telefono);
	}
	fclose(ArchMiembros);
	printf("\n\n ==>Informacion guardada<==\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 
}

/*
	Entradas: Una puntero a una lista del tipo ListaMiembros de Miembros de equipo.
	Salidas: Una lista doblemente enlazada con los diferentes objetos de la estructura Miembro de Equipo(nombre, 
			cedula, correo, telefono, nivel de acceso).
	Restricciones: Ninguna.
*/
int cargarMiembros(struct ListaMiembros *L){
	
	struct MiembroEquipo *aux;

	aux =(struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));

	ArchMiembros = fopen("Archivos\\MiembroEquipo.txt","r");

	if(ArchMiembros==NULL){
		return 0;
	}else{
		while(!feof(ArchMiembros)){
			fgets(aux->cedula, 12, ArchMiembros); 
			quitaFinLinea(aux->cedula);
			fgets(aux->nombre_completo, 50, ArchMiembros); 
			quitaFinLinea(aux->nombre_completo);
			fgets(aux->correo, 50, ArchMiembros);
			quitaFinLinea(aux->correo);			
			fgets(aux->nivel_acceso, 4, ArchMiembros);
			quitaFinLinea(aux->nivel_acceso);
			fgets(aux->telefono, 15, ArchMiembros);
			quitaFinLinea(aux->telefono);
			
			if(L->inicio == NULL) 
			{
				//Inserta al inicio de la lista
				L->inicio = (struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));
				strcpy(L->inicio->cedula , aux->cedula);
				strcpy(L->inicio->nombre_completo , aux->nombre_completo); 
				strcpy(L->inicio->correo , aux->correo ); 
				strcpy(L->inicio->nivel_acceso , aux->nivel_acceso); 
				strcpy(L->inicio->telefono , aux->telefono); 
				L->inicio->siguiente = NULL; 
				L->inicio->anterior = NULL; 
				L->final = L->inicio;
	
			}else{	
				//Inserta al final de la lista	
				L->final->siguiente = (struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));
				strcpy(L->final->siguiente->cedula , aux->cedula);
				strcpy(L->final->siguiente->nombre_completo , aux->nombre_completo); 
				strcpy(L->final->siguiente->correo , aux->correo ); 
				strcpy(L->final->siguiente->nivel_acceso , aux->nivel_acceso); 
				strcpy(L->final->siguiente->telefono , aux->telefono); 
				L->final->siguiente->siguiente = NULL; 
				L->final->siguiente->anterior = L->final; 
				L->final = L->final->siguiente;
			}		
		}
		fclose(ArchMiembros);
	}	
	return 1;
		
}

/*
	Entradas: Un dato que indique la cédula del Miembro del Equipo por consultar
	Salidas: Los datos relacionado al Miembro consultado en caso de que existan, de lo contrario un mensaje indicando 
			que no se ha encontrado.
	Restricciones: Ninguna
*/
void consultarMiembroEquipo(){

    struct ListaMiembros *L;
    struct MiembroEquipo *i;

    struct ListaAsignaciones *LAsig;
    struct Asignacion *iAsig;

    struct ListaRequerimientos *LReque;
    struct Requerimiento *iReque;

    int val=3, val2=3, res=0, resRequerimiento=0, resAsignacion=0;
    char id[12];

    system( "CLS" );
    printf("\n\n+-------------------------------+\n");
    printf("      Gestor de Requerimientos       \n");
    printf("+-------------------------------+\n");
    printf( "  Consultar Miembro de Equipo\n" );
    printf("+-------------------------------+\n");

    printf("\n Ingrese la cedula: (Ejm.208140809) \n ");
    gets(id);

    L = (struct ListaMiembros *) malloc(sizeof(struct ListaMiembros));
    L->inicio = NULL;
    L->final = NULL;

    LAsig = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
    LAsig->inicio = NULL;
    LAsig->final = NULL;

    LReque = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
    LReque->inicio = NULL;
    LReque->final = NULL;

    resAsignacion=cargarAsignaciones(LAsig);

    resRequerimiento = cargarRequerimientos(LReque);

    res=cargarMiembros(L);
		if(res==1){

	        i = L->inicio;
	        while( i->siguiente!= NULL){
	            val=strcmp(id,i->cedula);
	            if(val==0){
	                printf("\n+-------------------------------+");
	                printf("\nCedula: %s \n", i->cedula);
	                printf("Nombre: %s \n", i->nombre_completo);
	                printf("Correo Electronico: %s \n", i->correo);
	                printf("Nivel de Acceso: %s \n", i->nivel_acceso);
	                printf("Numero Telefonico: %s \n", i->telefono);
	                printf("+------------------------------------+\n");
	                printf( "      Requerimientops asignados   \n" );
	                printf("+-------------------------------------+\n");
					if(resRequerimiento=1)
                	{

                    iAsig = LAsig->inicio;
                    while( iAsig->siguiente!= NULL){
                        if(compararCadenas(iAsig->miembros, i->cedula)==1){
                            val2=0;
                            printf("Asignacion Numero: %s \n", iAsig->identificador);
                            printf("Descripcion: %s \n", iAsig->descripcion);
                            printf("Priodidad: %s \n", iAsig->prioridad ); 
                            printf("Estado: %s \n", iAsig->estado);
                            iReque = LReque->inicio;
                            while(iReque->siguiente!= NULL){
                                if (compararCadenas(iAsig->identificador , iReque->identificador)==1){
                                    printf("\n Datos del Requerimiento \n");
                                    printf("\nIdentificador: %s \n", iReque->identificador);
                                    printf("Descripcion: %s \n", iReque->descripcion);
                                    printf("Estado: %s \n", iReque->estado);
                                    printf("+-------------------------------------+\n");
								}
                                iReque = iReque->siguiente;
                            }

                        }

                        iAsig = iAsig->siguiente;
                    }
                    if(val2!=0){
                        printf( "\nNo tiene requerimentos asignados");
                    }
                }else{
                    printf( "\nNo se han registrado Requerimientos");
                }

                break;
            }
            i = i->siguiente;
        }
        if(val!=0){
            printf( "\nMiembro no encontrado");
        }

    }else{
        printf( "\nNo se ha registrado ningún Miembro*");
    }
    liberarListaMiembros(L);
    printf("\n\nPresione una tecla para regresar..." ); 
    getchar();
    fflush(stdin);
}

/*
    Entradas: Un dato que indique la cedula del Miembro de Equipo
    Salidas: Retorna 1 en caso de que el valor recibido coindicida con una cedula ya registrado, caso contrario retorna un 0.
    Restricciones: Ninguna
*/
int validarCedula(const char identificador []){

    struct ListaMiembros *L;
    struct MiembroEquipo *i;
    char id [50], res=0;
    int similitud=0;

    L = (struct ListaMiembros *) malloc(sizeof(struct ListaMiembros));
    L->inicio = NULL;
    L->final = NULL;

    res=cargarMiembros(L);

    if(res==1)
    {
         i = L->inicio;
        while( i->siguiente!= NULL){
            strcpy(id, i->cedula);
			similitud = compararCadenas(id, identificador);
            if(similitud==1){
            	liberarListaMiembros(L);
                return 1;
            }
            i = i->siguiente;
        }
    }

	liberarListaMiembros(L);
    return 0;
}

/*
	Entradas: Los diferentes objetos de la estructura Requerimiento(identificador, tipo, descripcion, riesgo, 
	           dependencia, recursos, esfuerzo). 
	Salidas: LLama a la función guardarRequerimiento para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void registrarRequerimiento(){
	system( "CLS" );
	printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------+\n");
	printf( "  Agregar nuevo requerimiento\n" );
	printf("+-------------------------------+\n");
	
	struct Requerimiento *requerimiento;

	requerimiento= (struct Requerimiento *) malloc (sizeof(struct Requerimiento));
	
	if(requerimiento == NULL){
		printf("Espacio insuficiente para almacenar los datos.\n");	
	}

	do{
		printf("\n Ingrese el identificador: (Ejm. RQ001) \n");
		gets(requerimiento->identificador);
		
		if(validarIDRequerimiento(requerimiento->identificador)==1){
			printf("\n ***Este identificador ya ha sido registrado***\n");
		}else{
			break;
		}		
		
	}while(1);
	
	printf("\n Ingrese el Tipo: (Ejm. Funcional) \n");
	gets(requerimiento->tipo);
	printf("\n Ingrese la Descripcion: (Ejm. El sistema debe....) \n");
	gets(requerimiento->descripcion);
	printf("\n Ingrese el riesgo: (Ejm. ....) \n");
	gets(requerimiento->riesgo);
	printf("\n Ingrese la dependencia: (Ejm. RQ001) \n ");
	gets(requerimiento->dependencia);
	printf("\n Ingrese los recursos:\n");
	gets(requerimiento->recursos);
	strcpy(requerimiento->estado, "Por hacer");
	printf("\n Ingrese el esfuerzo: ( 1...10 ) \n");
	gets(requerimiento->esfuerzo);
	requerimiento->siguiente=NULL;

	guardarRequerimiento(requerimiento);
	free(requerimiento);
	getchar();	
}

/*
	Entradas: Una estructura Requerimiento. 
	Salidas: Guardar los datos de la estructura en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void guardarRequerimiento(Requerimiento *requerimiento){
	
	ArchRequerimiento=fopen("Archivos\\Requerimientos.txt","a+");
	if(ArchRequerimiento==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		fprintf(ArchRequerimiento,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", requerimiento->identificador, requerimiento->tipo, requerimiento->descripcion,
						requerimiento->riesgo, requerimiento->dependencia, requerimiento->recursos, requerimiento->estado,  requerimiento->esfuerzo);
	}
	fclose(ArchRequerimiento);
	printf("\n ==>Informacion guardada<==.\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 

}

/*
	Entradas: Una puntero a una lista del tipo ListaRequerimientos de Requerimientos.
	Salidas: Una lista doblemente enlazada con los diferentes objetos de la estructura Requerimiento(identificador, tipo, 
			descripcion, riesgo, dependencia, recursos, esfuerzo).
	Restricciones: Ninguna.
*/
int cargarRequerimientos(struct ListaRequerimientos *L){

	struct Requerimiento *requerimiento, *aux;
		
	aux = (struct Requerimiento *) malloc(sizeof(struct Requerimiento));

	ArchRequerimiento = fopen("Archivos\\Requerimientos.txt","r");

	if(ArchRequerimiento==NULL){
		return 0;	
	}else{

		while(!feof(ArchRequerimiento)){
			fgets(aux->identificador, 50, ArchRequerimiento); 
			quitaFinLinea(aux->identificador);
			fgets(aux->tipo, 12, ArchRequerimiento); 
			quitaFinLinea(aux->tipo);
			fgets(aux->descripcion, 100, ArchRequerimiento);
			quitaFinLinea(aux->descripcion);			
			fgets(aux->riesgo, 60, ArchRequerimiento);
			quitaFinLinea(aux->riesgo);
			fgets(aux->dependencia, 100, ArchRequerimiento);
			quitaFinLinea(aux->dependencia);
			fgets(aux->recursos, 55, ArchRequerimiento);
			quitaFinLinea(aux->recursos);
			fgets(aux->estado, 15, ArchRequerimiento);
			quitaFinLinea(aux->estado);
			fgets(aux->esfuerzo, 5, ArchRequerimiento);
			quitaFinLinea(aux->esfuerzo); 
			
			if(L->inicio == NULL) 
			{
				//Inserta al inicio de la lista
				L->inicio = (struct Requerimiento *) malloc (sizeof(struct Requerimiento));
				strcpy(L->inicio->identificador , aux->identificador);
				strcpy(L->inicio->tipo , aux->tipo); 
				strcpy(L->inicio->descripcion , aux->descripcion ); 
				strcpy(L->inicio->riesgo , aux->riesgo); 
				strcpy(L->inicio->dependencia , aux->dependencia); 
				strcpy(L->inicio->recursos , aux->recursos); 
				strcpy(L->inicio->estado , aux->estado); 
				strcpy(L->inicio->esfuerzo , aux->esfuerzo);
				L->inicio->siguiente = NULL; 
				L->inicio->anterior = NULL; 
				L->final = L->inicio;
	
			}else{	
				//Inserta al final de la lista	
				L->final->siguiente = (struct Requerimiento *) malloc (sizeof(struct Requerimiento));
				strcpy(L->final->siguiente->identificador , aux->identificador);
				strcpy(L->final->siguiente->tipo , aux->tipo); 
				strcpy(L->final->siguiente->descripcion , aux->descripcion ); 
				strcpy(L->final->siguiente->riesgo , aux->riesgo); 
				strcpy(L->final->siguiente->dependencia , aux->dependencia); 
				strcpy(L->final->siguiente->recursos , aux->recursos); 
				strcpy(L->final->siguiente->estado , aux->estado); 
				strcpy(L->final->siguiente->esfuerzo , aux->esfuerzo);
				L->final->siguiente->siguiente = NULL; 
				L->final->siguiente->anterior = L->final; 
				L->final = L->final->siguiente;
			}		
		}
		
		fclose(ArchRequerimiento);	
	}	
	
	return 1;
}

/*
	Entradas: Un dato que indique el identificador del Requerimiento por consultar
	Salidas: Los datos relacionado al Requerimiento consultado en caso de que existan, de lo contrario un mensaje indicando 
			que no se ha encontrado.
	Restricciones: Ninguna
*/
void consultarRequerimiento(){

    struct ListaRequerimientos *L;
    struct Requerimiento *i;
    int val=3, res=0;
    char id[10];

    system( "CLS" );
    printf("\n\n+-------------------------------+\n");
    printf("      Gestor de Requerimientos       \n");
    printf("+-------------------------------+\n");
    printf( "  Consultar un Requerimiento\n" );
    printf("+-------------------------------+\n");

    printf("\n Ingrese el identificador: (Ejm. RQ000) \n ");
    gets(id);

    L = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
    L->inicio = NULL;
    L->final = NULL;

    res = cargarRequerimientos(L);

    if(res==1)
    {
        i = L->inicio;
        while( i->siguiente!= NULL){
            val=strcmp(id,i->identificador);
            if(val==0){
            	printf("\n+-------------------------------+");
                printf("\nIdentificador: %s \n", i->identificador);
                printf("Tipo: %s \n", i->tipo);
                printf("Descripcion: %s \n", i->descripcion);
                printf("Riesgo: %s \n", i->riesgo);
                printf("Dependencia: %s \n", i->dependencia);
                printf("Recursos: %s \n", i->recursos);
                printf("Estado: %s \n", i->estado);
                printf("Esfuerzo: %s \n", i->esfuerzo);
                printf("+-------------------------------+\n");

            }
            i = i->siguiente;
        }
        if(val!=0){
            printf( "\n**Requerimiento no encontrado***");
        }
    }else{		
		printf("\n**No se ha registrado ningún requerimiento***");
	}
	
	liberarListaRequerimientos(L);
    printf("\n\nPresione una tecla para regresar..." ); 
    getchar();
    fflush(stdin);
}

/*
	Entradas: Un dato que indique el identificador del Requerimiento
	Salidas: Retorna 1 en caso de que el valor recibido coindicida con un Requerimiento ya registrado, caso contrario retorna un 0.
	Restricciones: Ninguna
*/
int validarIDRequerimiento(const char identificador []){

	struct ListaRequerimientos *L;
	struct Requerimiento *i;
	char id [50], res=0;
	int similitud=0;

	L = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
	L->inicio = NULL;
	L->final = NULL;

	res=cargarRequerimientos(L);

	if(res==1)
	{
		i = L->inicio;
		while( i->siguiente!= NULL){
			strcpy(id, i->identificador);
			similitud = compararCadenas(id, identificador);
			if(similitud==1){
				liberarListaRequerimientos(L);
				return 1;
			}
			i = i->siguiente;			
		}		
	}
	liberarListaRequerimientos(L);
	return 0;		
}

/*
	Entradas: Los objetos de tipo, recursos o estado de la estructura Requerimiento.
	Salidas: Llama a la función guardarRequerimiento para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void modificarRequerimiento(){
	system( "CLS" );
	printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------+\n");
	printf( "  Modificar un Requerimiento\n" );
	printf("+-------------------------------+\n");
	
	struct ListaRequerimientos *L;
	char id[10], respuesta[2], tipo[20], recursos[55], estado [15];
	int val=3, res=0, resp;
	
	printf("\n Ingrese el identificador: (Ejm. RQ000) \n ");
    gets(id);

    L = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
    L->inicio = NULL;
    L->final = NULL;

    res = cargarRequerimientos(L);

    if(res==1)
    {
 
        i = L->inicio;
        while( i->siguiente!= NULL){
            val=strcmp(id,i->identificador);
            if(val==0){
            	printf("\n+------------------------------------+");
				printf("\n      Datos del  Requerimiento " );
            	printf("\n+------------------------------------+");
                printf("\nIdentificador: %s \n", i->identificador);
                printf("Tipo: %s \n", i->tipo);
                printf("Descripcion: %s \n", i->descripcion);
                printf("Riesgo: %s \n", i->riesgo);
                printf("Dependencia: %s \n", i->dependencia);
                printf("Recursos: %s \n", i->recursos);
                printf("Estado: %s \n", i->estado);
                printf("Esfuerzo: %s \n", i->esfuerzo);
                printf("+-------------------------------------+\n");
                
                //Modificar el Tipo de Requerimiento
                do{
			        printf("\nDesea modificar el tipo? (1-Si 2-No)\n" );
                	gets(respuesta);
					resp=atoi(respuesta);
                
			        if(resp==1 || resp==2){
			            break;
			        }
			    }while(1);
                
                if(resp==1){
                	printf("\n Ingrese el Tipo: (Ejm. Funcional) \n");
                	gets(tipo);	
					strcpy(i->tipo,tipo);
				}
				
				//Modificar los Recursos
				do{
			        printf("\nDesea modificar los Recursos? (1-Si 2-No)\n" );
                	gets(respuesta);
					resp=atoi(respuesta);
                
			        if(resp==1 || resp==2){
			            break;
			        }
			    }while(1);
                
                if(resp==1){
                	printf("\n Ingrese los Recursos: \n");
					gets(recursos);	
					strcpy(i->recursos, recursos);
						
				}
				
				//Modificar el Estado del Requerimiento
				do{
			        printf("\nDesea modificar el Estado? (1-Si 2-No)\n" );
                	gets(respuesta);
					resp=atoi(respuesta);
                
			        if(resp==1 || resp==2){
			            break;
			        }
			    }while(1);
                
                if(resp==1){
                	printf("\n Ingrese el Estado del Requerimiento \n");
					gets(estado);	
					strcpy(i->recursos, estado);
						
				}
				
				break;
            }
            i = i->siguiente;
        }
        if(val!=0){
            printf( "\n**Requerimiento no encontrado***");
        }
    }else{		
		printf("\n**No se ha registrado ningún requerimiento***");
	}
	
	actualizarRequerimientos(L);
	liberarListaRequerimientos(L);
		
	//guardarRequerimiento(requerimiento);
	getchar();	
}

/*
	Entradas: Los objetos de tipo, recursos o estado de la estructura Requerimiento.
	Salidas: Llama a la función guardarRequerimiento para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void actualizarRequerimientos(struct ListaRequerimientos *L){
	
	struct Requerimiento *i;
	
	 if (remove("Archivos\\Requerimientos.txt") == 0){
	 	printf("Archivo Borrado"); 
	 }else{
	 	printf("Archivo NO Borrado"); 
	 }

	ArchRequerimiento=fopen("Archivos\\Requerimientos.txt","a+");
	if(ArchRequerimiento==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		
		i = L->inicio;
        while( i->siguiente!= NULL){
			fprintf(ArchRequerimiento,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", i->identificador, i->tipo, i->descripcion,
					i->riesgo, i->dependencia, i->recursos, i->estado,  i->esfuerzo);
            i = i->siguiente;
        }
		
	}
	fclose(ArchRequerimiento);
	printf("\n ==>Informacion guardada<==.\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 

}


/*
	Entradas: Los diferentes objetos de la estructura Asignacion(fechaSolicitud, horaInicio, horaFin, recurso, identificador 
			descripcion, miembros, prioridad y estado). 
	Salidas: Llama a la función guardarAsignacion para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void registrarAsignacion(){
	system( "CLS" );
    printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------+\n");
	printf( "  Crear una nueva asignacion\n" );
	printf("+-------------------------------+\n");	

	struct Asignacion *asignacion;
	int prioridad=0;
	
	asignacion=(struct Asignacion *) malloc (sizeof(struct Asignacion));
	
	char fecha [50];
	obtenerFechaActual(fecha);
	strcpy(asignacion->fechaSolicitud, fecha);
	printf("\n Ingrese la Hora de Inicio: (Ejm. 07:25) \n");
	gets(asignacion->horaInicio);
	printf("\n Ingrese el Hora de Fin: (Ejm. 14:25) \n");
	gets(asignacion->horaFin);
	printf("\n Ingrese el Recurso (Opcional): \n");
	gets(asignacion->recurso);
	printf("\n Ingrese el ID del Requerimiento: (Ejm. RQ001) \n");
	//Mostrar Requerimientos
	gets(asignacion->identificador);
	printf("\n Ingrese la Descripcion: \n");
	gets(asignacion->descripcion);
	printf("\n Ingrese las Cedulas de los Miembros: (Ejm. 105450656) \n ");
	//Mostrar Miembros
	gets(asignacion->miembros);

	prioridad = numeroAleatorio();

	switch(prioridad){
		case 1:  strcpy(asignacion->prioridad, "ALTA");
			break;
		case 2: strcpy(asignacion->prioridad, "MEDIA");
			break;
		case 3: strcpy(asignacion->prioridad, "BAJA");
			break;	
	}	

	strcpy(asignacion->estado, "En proceso");
	//Actualizar el Estado del Requerimiento
	
	guardarAsignacion(asignacion);
	free(asignacion);
	getchar();	
}

/*
	Entradas: Una estructura Asignación. 
	Salidas: Guardar los datos de la estructura en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void guardarAsignacion(Asignacion *asignacion){
	
	ArchAsignaciones=fopen("Archivos\\Asignaciones.txt","a+");
	if(ArchAsignaciones==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		fprintf(ArchAsignaciones,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", asignacion->fechaSolicitud, asignacion->horaInicio, asignacion->horaFin, asignacion->recurso, asignacion->identificador, 
																asignacion->descripcion,  asignacion->prioridad, asignacion->estado);
//																asignacion->miembros,
	}
	fclose(ArchAsignaciones);
	printf("\n\n ==>Informacion guardada<==\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 
}

/*
	Entradas: Una puntero a una lista del tipo ListaAsiganciones de Asignaciones.
	Salidas: Una lista doblemente enlazada con los diferentes objetos de la estructura Asignacion (fechaSolicitud, horaInicio, 
			horaFin, recurso, identificador, descripcion, miembros, prioridad y estado). 
	Restricciones: Ninguna.
*/
int cargarAsignaciones(struct ListaAsignaciones *L){
	
	struct Asignacion *asignacion, *aux;

	aux =(struct Asignacion *) malloc (sizeof(struct Asignacion));

	ArchAsignaciones = fopen("Archivos\\Asignaciones.txt","r");

	if(ArchAsignaciones==NULL){
		return 0;	
	}else{

		while(!feof(ArchAsignaciones)){
			fgets(aux->fechaSolicitud, 50, ArchAsignaciones); 
			quitaFinLinea(aux->fechaSolicitud);
			fgets(aux->horaInicio, 15, ArchAsignaciones); 
			quitaFinLinea(aux->horaInicio);
			fgets(aux->horaFin, 15, ArchAsignaciones);
			quitaFinLinea(aux->horaFin);	
			fgets(aux->recurso, 50, ArchAsignaciones);
			quitaFinLinea(aux->recurso);		
			fgets(aux->identificador, 10, ArchAsignaciones);
			quitaFinLinea(aux->identificador);
			fgets(aux->descripcion, 100, ArchAsignaciones);
			quitaFinLinea(aux->descripcion);
//			fgets(aux->miembros, 15, ArchAsignaciones);
//			quitaFinLinea(aux->miembros);
			fgets(aux->prioridad, 15, ArchAsignaciones);
			quitaFinLinea(aux->prioridad);
			fgets(aux->estado, 15, ArchAsignaciones);
			quitaFinLinea(aux->estado);
			
			if(L->inicio == NULL) 
			{
				//Inserta al inicio de la lista
				L->inicio =(struct Asignacion *) malloc (sizeof(struct Asignacion));
				strcpy(L->inicio->fechaSolicitud , aux->fechaSolicitud);
				strcpy(L->inicio->horaInicio , aux->horaInicio ); 
				strcpy(L->inicio->horaFin , aux->horaFin); 
				strcpy(L->inicio->recurso , aux->recurso); 
				strcpy(L->inicio->identificador , aux->identificador); 
				strcpy(L->inicio->descripcion , aux->descripcion);
//				strcpy(L->inicio->miembros , aux->miembros); 
				strcpy(L->inicio->prioridad , aux->prioridad ); 
				strcpy(L->inicio->estado , aux->estado); 
				L->inicio->siguiente = NULL; 
				L->inicio->anterior = NULL; 
				L->final = L->inicio;
	
			}else{	
				//Inserta al final de la lista	
				L->final->siguiente =(struct Asignacion *) malloc (sizeof(struct Asignacion));
				strcpy(L->final->siguiente->fechaSolicitud , aux->fechaSolicitud);
				strcpy(L->final->siguiente->horaInicio , aux->horaInicio ); 
				strcpy(L->final->siguiente->horaFin , aux->horaFin); 
				strcpy(L->final->siguiente->identificador , aux->identificador); 
				strcpy(L->final->siguiente->descripcion , aux->descripcion);
				strcpy(L->final->siguiente->recurso , aux->recurso);
//				strcpy(L->final->siguiente->miembros , aux->miembros); 
				strcpy(L->final->siguiente->prioridad , aux->prioridad ); 
				strcpy(L->final->siguiente->estado , aux->estado); 
				L->final->siguiente->siguiente = NULL; 
				L->final->siguiente->anterior = L->final; 
				L->final = L->final->siguiente;
			}		
		}
		fclose(ArchAsignaciones);
	}	
	return 1;
}

/*
	Entradas: Un dato que indique la cédula del Miembro del Equipo por consultar las Asignaciones
	Salidas: Los datos relacionado a las Asignaciones del Miembro consultado en caso de que existan, de lo contrario un mensaje indicando 
			que no se han encontrado.
	Restricciones: Ninguna
*/
void consultarAsignaciones(){

	struct ListaAsignaciones *L;
	struct Asignacion *i;
	int val=3, res=0;
	char id[12];
	
	system( "CLS" );
	printf("\n\n+-------------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------------+\n");
	printf( "Consultar Asignaciones de un Miembro\n" );
	printf("+-------------------------------------+\n");
	
	printf("\n Ingrese la la cedula del miembro: (Ejm.208140809) \n ");
	gets(id);

	L = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
	L->inicio = NULL;
	L->final = NULL;

	res=cargarAsignaciones(L);

	if(res=1)
	{
	
		printf("\n+-------------------------------+\n");
		i = L->inicio;
		while( i->siguiente!= NULL){
//			val=strcmp(id,i->miembros);
//			if(val==0){
				printf("Fecha de Solicitud: %s \n", i->fechaSolicitud);
				printf("Hora de Inicio: %s \n", i->horaInicio ); 
				printf("Hora de Fin: %s \n", i->horaFin); 
				printf("Identificador: %s \n", i->identificador); 
				printf("Recurso: %s \n", i->recurso); 
				printf("Descripcion: %s \n", i->descripcion);
//				printf("Miembros: %s \n", i->miembros); 
				printf("Priodidad: %s \n", i->prioridad ); 
				printf("Estado: %s \n", i->estado); 
				printf("+-------------------------------+\n");
			
//			}
			i = i->siguiente;
		}
		if(val!=0){
			printf( "\n***No se han encontrado Asignaciones***");
		}		
	}else{
		printf( "\n***No se han registrado Asignaciones***");
	}	
	
	liberarListaAsignaciones(L);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

/*
	Entradas: Los diferentes objetos de la estructura Incidente(codigoRequerimiento, codigoAsignacion, descripcionIncidente, fecha). 
	Salidas: LLama a la función guardarIncidente para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void registrarIncidentes(){
	system( "CLS" );
	printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------+\n");
	printf( "  Crear un nuevo incidente\n" );
	printf("+-------------------------------+\n");	
	
	struct Incidentes *incidente;

	incidente= (struct Incidentes *) malloc (sizeof(struct Incidentes));
	
	if(incidente == NULL){
		printf("Espacio insuficiente para almacenar los datos.\n");	
	}
		
	printf("\n Ingrese el Codigo del Requerimiento: (Ejm. RQ000) \n  ");
	gets(incidente->codigoRequerimiento);
	printf("\n Ingrese el Codigo de Asignacion: (Ejm. 1, 2, 3, 4....) \n ");
	gets(incidente->codigoAsignacion);
	printf("\n Ingrese la Descripcion de Incidente: \n");
	gets(incidente->descripcionIncidente);
	printf("\n Ingrese la Fecha del Incidente: (Ejm. 10/3/2020) \n ");
	gets(incidente->fecha);
	printf("\n");
	incidente->siguiente=NULL;

	guardarIncidentes(incidente);
	getchar();	
}

/*
	Entradas: Una estructura Incidente. 
	Salidas: Guardar los datos de la estructura en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void guardarIncidentes(Incidentes *incidente){
	

	ArchIncidentes=fopen("Archivos\\Incidentes.txt","a+");
	if(ArchIncidentes==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		fprintf(ArchIncidentes,"%s\n%s\n%s\n%s\n", incidente->codigoRequerimiento, incidente->codigoAsignacion, incidente->descripcionIncidente,
						incidente->fecha);
	}
	fclose(ArchIncidentes);
	printf("\n\n ==>Informacion guardada<==.\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 

}

/*
	Entradas: Una puntero a una lista del tipo ListaIncidentes de Incidentes.
	Salidas: Una lista doblemente enlazada con los diferentes objetos de la estructura Incidente (codigoRequerimiento, codigoAsignacion, 
			descripcionIncidente, fecha). 
	Restricciones: Ninguna.
*/
int cargarIncidentes(struct ListaIncidentes *L){
	
	struct Incidentes *aux;

	aux = (struct Incidentes *) malloc (sizeof(struct Incidentes));

	ArchIncidentes = fopen("Archivos\\Incidentes.txt","r");

	if(ArchIncidentes==NULL){
		return 0;	
	}else{
	
		while(!feof(ArchIncidentes)){
			fgets(aux->codigoRequerimiento, 15, ArchIncidentes); 
			quitaFinLinea(aux->codigoRequerimiento);
			fgets(aux->codigoAsignacion, 15, ArchIncidentes); 
			quitaFinLinea(aux->codigoAsignacion);
			fgets(aux->descripcionIncidente, 100, ArchIncidentes);
			quitaFinLinea(aux->descripcionIncidente);	
			fgets(aux->fecha, 20, ArchIncidentes);
			quitaFinLinea(aux->fecha);		
						
			if(L->inicio == NULL){
				//Inserta al inicio de la lista
				L->inicio = (struct Incidentes *) malloc (sizeof(struct Incidentes));
				strcpy(L->inicio->codigoRequerimiento , aux->codigoRequerimiento);
				strcpy(L->inicio->codigoAsignacion , aux->codigoAsignacion ); 
				strcpy(L->inicio->descripcionIncidente , aux->descripcionIncidente); 
				strcpy(L->inicio->fecha , aux->fecha); 
				L->inicio->siguiente = NULL; 
				L->inicio->anterior = NULL; 
				L->final = L->inicio;
	
			}else{
				//Inserta al final de la lista	
				L->final->siguiente =(struct Incidentes *) malloc (sizeof(struct Incidentes));
				strcpy(L->final->siguiente->codigoRequerimiento , aux->codigoRequerimiento);
				strcpy(L->final->siguiente->codigoAsignacion , aux->codigoAsignacion ); 
				strcpy(L->final->siguiente->descripcionIncidente , aux->descripcionIncidente); 
				strcpy(L->final->siguiente->fecha , aux->fecha); 
				L->final->siguiente->siguiente = NULL; 
				L->final->siguiente->anterior = L->final; 
				L->final = L->final->siguiente;
			}		
		}
		fclose(ArchIncidentes);		
	}	
	return 1;
}

/*
	Entradas: Un dato que indique la cédula del Miembro del Equipo por consultar los Incidentes
	Salidas: Los datos relacionado a los Incidentes en caso de que existan, de lo contrario un mensaje indicando 
			que no se han encontrado.
	Restricciones: Ninguna
*/
void consultarIncidentes(){

	struct ListaIncidentes *L;
	struct Incidentes *i;
	int val=3, res=0;
	
	system( "CLS" );
	printf("\n\n+-------------------------------------+\n");
	printf("      Gestor de Requerimientos         \n");
	printf("+-------------------------------------+\n");
	printf( "       Consultar Incidentes           \n");
	printf("+-------------------------------------+\n");

	L = (struct ListaIncidentes *) malloc(sizeof(struct ListaIncidentes));
	L->inicio = NULL;
	L->final = NULL;

	res=cargarIncidentes(L);

	if(res==1)
	{	
		i = L->inicio;
		while( i->siguiente!= NULL){
			printf("\n+-------------------------------+\n");
			printf("Requerimiento: %s \n", i->codigoRequerimiento);
			printf("Asignacion: %s \n", i->codigoAsignacion ); 
			printf("Descripcion: %s \n", i->descripcionIncidente); 
			printf("Fecha de Incidente: %s \n", i->fecha); 
			printf("+-------------------------------+\n");
	
			i = i->siguiente;
		}				
	}else{
		printf( "\n***No se han registrado Incidentes***");
	}	
	liberarListaIncidentes(L);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

/*
	Entradas: Un puntero a una lista de nodos de tipo struct Miembros de Equipo.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual señala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarListaMiembros(ListaMiembros *L){
	struct MiembroEquipo *n, *aux;
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

/*
	Entradas: Un puntero a una lista de nodos de tipo struct Asignacion.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual señala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarListaAsignaciones(ListaAsignaciones *L){
	struct Asignacion *n, *aux;
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

/*
	Entradas: Un puntero a una lista de nodos de tipo struct Requerimiento.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual señala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarListaRequerimientos(ListaRequerimientos *L){
	struct Requerimiento *n, *aux;
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

/*
	Entradas: Un puntero a una lista de nodos de tipo struct Incidentes.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual señala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarListaIncidentes(ListaIncidentes *L){
		
	struct Incidentes *n, *aux;
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

int main(){ 
	MenuPrincipal();    
	return 0; 
}
