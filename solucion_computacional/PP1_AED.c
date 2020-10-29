/*Algoritmos y Estructuras de Datos - Grupo 1
	Proyecto Programado 1 
	Estudiantes: Jose Altamirano Salazar - 2020426159
	             Josu� Brenes Alfaro - 2020054427
*/
  
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

FILE* ArchRequerimiento;
FILE* ArchMiembros;
FILE* ArchAsignaciones;
FILE* ArchIncidente;

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

//Procedimientos para Requerimientos
void registrarRequerimiento();
void guardarRequerimiento(Requerimiento *requerimiento);
void cargarRequerimientos(struct ListaRequerimientos *L);
void consultarRequerimiento();

//Procedimientos para Asignaciones
void registrarAsignacion();
void guardarAsignacion(Asignacion *asignacion);

//Procedimientos para Incidentes
void registrarIncidentes();
void guardarIncidentes(Incidentes *incidente);

struct Requerimiento{
    char identificador[50];
    char tipo[12];
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
    Asignacion *siguiente;
};

struct Incidentes{
    char codigoRequerimiento[15];
    char codigoAsignacion[15];
    char descripcionIncidente[100];
    char fecha[20];
    Incidentes *siguiente;
};

struct ListaMiembros {
	MiembroEquipo *inicio;
};

struct ListaRequerimientos{
	Requerimiento *inicio;
	Requerimiento *final;
};

struct ListaIncidentes{
	Incidentes *inicio;
};

struct ListaAsignaciones{
	Asignacion *inicio;
};


void Temporal(){
	getchar();
}

/*
	Entradas: Un n�mero (tipo char) en un rango de 0 a 6 para escoger una de las opciones disponibles en el men�. 
	Salidas: Llamada a las demas funciones de men�s.
	Restricciones: Solo se deben ingresar n�meros en un rango de 0 a 6.
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
	Entradas: Un n�mero (tipo char) en un rango de 0 a 2 para escoger una de las opciones disponibles en el men�. 
	Salidas: en caso de que el n�mero ingresado sea 0 se devuelve al men� principal, si el n�mero es 1 se a llama la funcion registrarMiembro(), 
	         Si el n�mero ingresado es 2 se llama a la funci�n ** .
	Restricciones: Solo se deben ingresar n�meros en un rango de 0 a 2.
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
				case '2': Temporal();
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
	Entradas: Un n�mero (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el men�. 
	Salidas: en caso de que el n�mero ingresado sea 0 se devuelve al men� principal, si el n�mero es 1 se a llama la funcion registrarRequerimiento(), 
	         Si el n�mero ingresado es 2 se llama a la funci�n **, Si el n�mero ingresado es 3 se llama a la funci�n **,
	         Si el n�mero ingresado es 4 se llama a la funci�n ***.
	Restricciones: Solo se deben ingresar n�meros en un rango de 0 a 4.
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
				case '2': Temporal();
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
	Entradas: Un n�mero (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el men�. 
	Salidas: en caso de que el n�mero ingresado sea 0 se devuelve al men� principal, si el n�mero es 1 se a llama la funcion registrarAsignacion(), 
	         Si el n�mero ingresado es 2 se llama a la funci�n **, Si el n�mero ingresado es 3 se llama a la funci�n **,
	         Si el n�mero ingresado es 4 se llama a la funci�n ***.
	Restricciones: Solo se deben ingresar n�meros en un rango de 0 a 4.
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
		printf("\n 1. Crear una nueva asignaci�n.");
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
	Entradas: Un n�mero (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el men�. 
	Salidas: en caso de que el n�mero ingresado sea 0 se devuelve al men� principal, si el n�mero es 1 se a llama la funcion registrarIncidentes(), 
	         Si el n�mero ingresado es 2 se llama a la funci�n **
	Restricciones: Solo se deben ingresar n�meros en un rango de 0 a 4.
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
				case '2': Temporal();
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
	Entradas:
	Salidas:
	Restricciones:
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
		printf("\n 1. Mostrar requerimientos con m�s asignaciones.");
		printf("\n 2. Mostrar horarios m�s utilizados.");
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
	Entradas:
	Salidas:
	Restricciones:
*/
void registrarMiembro(){
	system( "CLS" );
    printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos          \n");
	printf("+-------------------------------+\n");
	printf( "  Registrar Miembro de Equipo\n" );
	printf("+-------------------------------+\n");	

	struct MiembroEquipo *miembro;

	miembro=(struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));

	printf("\n Ingrese la Cedula: ");
	gets(miembro->cedula);
	printf("\n Ingrese el Nombre Completo: ");
	gets(miembro->nombre_completo);
	printf("\n Ingrese el Correo Electronico: ");
	gets(miembro->correo);
	printf("\n Ingrese el Nivel de Acceso: ");
	gets(miembro->nivel_acceso);
	printf("\n Ingrese un Numero Telefonico: ");
	gets(miembro->telefono);

	guardarMiembro(miembro);
	free(miembro);
	getchar();	
}

/*
	Entradas:
	Salidas:
	Restricciones:
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
	Entradas: Los diferentes objetos de la estructura Requerimiento(identificador, tipo, descripcion, riesgo, 
	           dependencia, recursos, esfuerzo). 
	Salidas: LLama a la funci�n guardarRequerimiento para guardar los datos antes registrados en un archivo .txt. 
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

	printf("\n Ingrese el identificador: ");
	gets(requerimiento->identificador);
	printf("\n Ingrese el tipo: ");
	gets(requerimiento->tipo);
	printf("\n Ingrese la descripcion: ");
	gets(requerimiento->descripcion);
	printf("\n Ingrese el riesgo: ");
	gets(requerimiento->riesgo);
	printf("\n Ingrese la dependencia: ");
	gets(requerimiento->dependencia);
	printf("\n Ingrese los recursos: ");
	gets(requerimiento->recursos);
	//printf("\n Ingrese el estado: \n");
	//gets(requerimiento->estado);
	strcpy(requerimiento->estado, "Por hacer");
	printf("\n Ingrese el esfuerzo: ");
	gets(requerimiento->esfuerzo);
	printf("\n");
	requerimiento->siguiente=NULL;

	guardarRequerimiento(requerimiento);
	free(requerimiento);
	getchar();	
}

/*
	Entradas: Una estructura Requerimiento. 
	Salidas: Guardar los datos de la estructura requerimiento en un archivo .txt. 
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

void quitaFinLinea(char linea[]){
	int i;
	for(i=0; linea[i]!='\0'; i++){
		if(linea[i] == '\n'){
			linea[i]='\0';
			break;
		}
	}
}

void cargarRequerimientos(struct ListaRequerimientos *L){

	struct Requerimiento *requerimiento, *aux;
		
	aux = (struct Requerimiento *) malloc(sizeof(struct Requerimiento));

	ArchRequerimiento = fopen("Archivos\\Requerimientos.txt","r");

	if(ArchRequerimiento==NULL){
		printf("\n Error al intentar abrir el archivo.\n");	
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
		
		
	}	
	fclose(ArchRequerimiento);
}

void consultarRequerimiento(){

	struct ListaRequerimientos *L;
	struct Requerimiento *i;
	int val=3;
	char id[10];
	
	system( "CLS" );
	printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------+\n");
	printf( "  Agregar nuevo requerimiento\n" );
	printf("+-------------------------------+\n");
	
	printf("\n Ingrese el identificador: ");
	gets(id);

	L = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
	L->inicio = NULL;
	L->final = NULL;

	cargarRequerimientos(L);

	if(L->inicio == NULL)
	{
		printf("La lista esta vacia...\n");		
	}
	else
	{
		printf("+-------------------------------+");
		i = L->inicio;
		while( i->siguiente!= NULL){
			val=strcmp(id,i->identificador);
			if(val==0){
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
		if(val==1){
			printf( "\n***Articulo no encontrado***");
		}		
	}	

	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}


/*
	Entradas:
	Salidas:
	Restricciones:
*/
void registrarAsignacion(){
	system( "CLS" );
    printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------+\n");
	printf( "  Crear una nueva asignaci�n\n" );
	printf("+-------------------------------+\n");	

	struct Asignacion *asignacion;
	
//	char prioridad [3][10] = {"ALTA", "MEDIA", "BAJA"};
//	int aleatorio = (rand() % (2 � 0 + 1));
	
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	
	asignacion=(struct Asignacion *) malloc (sizeof(struct Asignacion));

	strcpy(asignacion->descripcion, asctime(tm));
	printf("\n Ingrese la Hora de Inicio: ");
	gets(asignacion->horaInicio);
	printf("\n Ingrese el Hora de Fin: ");
	gets(asignacion->horaFin);
	printf("\n Ingrese el Recurso (Opcional): ");
	gets(asignacion->recurso);
	printf("\n Ingrese el ID del Requerimiento: ");
	//Mostrar Requerimientos
	gets(asignacion->identificador);
	printf("\n Ingrese la Descripcion: ");
	gets(asignacion->descripcion);
	printf("\n Ingrese las Cedulas de los Miembros: ");
	//Mostrar Miembros
	gets(asignacion->miembros);
	//strcpy(asignacion->prioridad, prioridad[prioridad]);
	strcpy(asignacion->prioridad, "ALTA");
	strcpy(asignacion->estado, "En proceso");
	//Actualizar el Estado del Requerimiento
	
	guardarAsignacion(asignacion);
	free(asignacion);
	getchar();	
}

/*
	Entradas:
	Salidas:
	Restricciones:
*/
void guardarAsignacion(Asignacion *asignacion){
	
	ArchAsignaciones=fopen("Archivos\\Asignaciones.txt","a+");
	if(ArchAsignaciones==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		fprintf(ArchAsignaciones,"%s %s %s %s %s %s %s %s %s\n", asignacion->fechaSolicitud, asignacion->horaInicio, asignacion->horaFin, asignacion->recurso, asignacion->identificador, 
																asignacion->descripcion, asignacion->miembros, asignacion->prioridad, asignacion->estado);
	}
	fclose(ArchAsignaciones);
	printf("\n\n ==>Informacion guardada<==\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 
}

/*
	Entradas:
	Salidas:
	Restricciones:
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
		
	printf("\n Ingrese el codigo del Requerimiento: ");
	gets(incidente->codigoRequerimiento);
	printf("\n Ingrese el codigo de Asignacion: ");
	gets(incidente->codigoAsignacion);
	printf("\n Ingrese la descripcion de Incidente: ");
	gets(incidente->descripcionIncidente);
	printf("\n Ingrese la fecha: ");
	gets(incidente->fecha);
	printf("\n");
	incidente->siguiente=NULL;

	guardarIncidentes(incidente);
	getchar();	
}

/*
	Entradas:
	Salidas:
	Restricciones:
*/
void guardarIncidentes(Incidentes *incidente){
	

	ArchIncidente=fopen("Archivos\\Incidentes.txt","a+");
	if(ArchIncidente==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		fprintf(ArchIncidente,"%s %s %s %s \n", incidente->codigoRequerimiento, incidente->codigoAsignacion, incidente->descripcionIncidente,
						incidente->fecha);
	}
	fclose(ArchIncidente);
	printf("\n\n ==>Informacion guardada<==.\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 

}

/*
	Entradas:
	Salidas:
	Restricciones:
*/
int main(){   
    MenuPrincipal();    
	return 0; 
}
