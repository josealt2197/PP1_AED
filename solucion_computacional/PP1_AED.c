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
FILE* ArchCalificaciones;
FILE* ArchOficinas;

typedef struct Requerimiento Requerimiento;
typedef struct MiembroEquipo MiembroEquipo;
typedef struct Asignacion Asignacion;
typedef struct Incidentes Incidentes;
typedef struct Calificacion Calificacion;
typedef struct Oficina Oficina;

typedef struct ColaMiembros ColaMiembros;
typedef struct ListaRequerimientos ListaRequerimientos;
typedef struct ListaAsignaciones ListaAsignaciones;
typedef struct ColaIncidentes ColaIncidentes;
typedef struct ListaCalificaciones ListaCalificaciones;
typedef struct ListaOficinas ListaOficinas;

//Procedimientos para Menus de Opciones
void MenuPrincipal();
void GestionEquipo();
void GestionAsignacion();
void GestionRequerimiento();
void GestionIncidentes();
void AnalisisDeDatos();

//Procedimientos para Miembros de Equipo
void registrarMiembro();
void guardarMiembro(MiembroEquipo *miembro);
int cargarMiembros(struct ColaMiembros *C);
void consultarMiembroEquipo();
void liberarColaMiembros(ColaMiembros *C);
int validarNivelMiembro(const char identificador []);

//Procedimientos para Requerimientos
void registrarRequerimiento();
void guardarRequerimiento(Requerimiento *requerimiento);
int cargarRequerimientos(struct ListaRequerimientos *L);
void consultarRequerimiento();
int validarIDRequerimiento(const char identificador []);
void liberarListaRequerimientos(ListaRequerimientos *L);
void modificarRequerimiento();
void actualizarRequerimientos(struct ListaRequerimientos *L);
void registrarCalificaciones();
void guardarCalificacion(Calificacion *calificacion);
void actualizarCalificacion(struct ListaCalificaciones *L);
int cargarOficinas(struct ListaOficinas *L);
void consultarOficinas();

//Procedimientos para Asignaciones
void registrarAsignacion();
void guardarAsignacion(Asignacion *asignacion);
int cargarAsignaciones(struct ListaAsignaciones *L);
void consultarAsignaciones();
void liberarListaAsignaciones(ListaAsignaciones *L);
void cancelarAsignacion();

//Procedimientos para Incidentes
void registrarIncidentes();
void guardarIncidentes(Incidentes *incidente);
int cargarIncidentes(struct ColaIncidentes *C);
void consultarIncidentes(int tipoConsulta);
void liberarColaIncidentes(ColaIncidentes *C);

//Procedimientos de Apoyo
int numeroAleatorio();
void obtenerFechaActual(char *hoy);

void analisisDeDatos(int tipoAnalisis);



struct Requerimiento{
    char identificador[50];
    char tipo[20];
    char descripcion[100];
    char riesgo[60];
    char dependencia[100];
    char recursos[55];
    char estado [15];
    char esfuerzo[5];
    char oficina [15];
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
	char codigoAsignacion[15];
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
    char codigoIncidente[15];
	char codigoRequerimiento[15];
    char codigoAsignacion[15];
    char descripcionIncidente[100];
    char fecha[20];
    Incidentes *anterior;
    Incidentes *siguiente;
};

struct Calificacion{
    char codigoRequerimiento[15];
    char codigoAsignacion[15];
    char miembro[30];
    char calificacion[10];
    Calificacion *anterior;
    Calificacion *siguiente;
};

struct Oficina{
    char codigo[50];
    char dias[30];
    char horaApertura[15];
    char horaCierre[15];
    Oficina *anterior;
    Oficina *siguiente;
};

struct ListaCalificaciones {
	Calificacion *inicio;
	Calificacion *final;
};

struct ColaMiembros {
	MiembroEquipo *inicio;
	MiembroEquipo *final;
};

struct ListaRequerimientos{
	Requerimiento *inicio;
	Requerimiento *final;
};

struct ColaIncidentes{
	Incidentes *inicio;
	Incidentes *final;
};

struct ListaAsignaciones{
	Asignacion *inicio;
	Asignacion *final;
};

struct ListaOficinas{
	Oficina *inicio;
	Oficina *final;
};


typedef struct ListaTopAsignaciones ListaTopAsignaciones;
typedef struct NodoTopAsignacion NodoTopAsignacion;

struct NodoTopAsignacion{
	char identificador[15];
	int cantidad;
	NodoTopAsignacion *siguiente;
};

struct ListaTopAsignaciones{
	NodoTopAsignacion *inicio;
	NodoTopAsignacion *final;
};

typedef struct ListaTopHorarios ListaTopHorarios;
typedef struct NodoTopHorario NodoTopHorario;

struct NodoTopHorario{
	char identificador[15];
	int cantidad;
	NodoTopHorario *siguiente;
};

struct ListaTopHorarios{
	NodoTopHorario *inicio;
	NodoTopHorario *final;
};

typedef struct ListaTopMiembros ListaTopMiembros;
typedef struct NodoTopMiembro NodoTopMiembro;

struct NodoTopMiembro{
	char identificador[15];
	int cantidad;
	NodoTopMiembro *siguiente;
};

struct ListaTopMiembros{
	NodoTopMiembro *inicio;
	NodoTopMiembro *final;
};

typedef struct ListaTopEsfuerzo ListaTopEsfuerzo;
typedef struct NodoTopEsfuerzo NodoTopEsfuerzo;

struct NodoTopEsfuerzo{
	char identificador[15];
	int cantidad;
	NodoTopEsfuerzo *siguiente;
};

struct ListaTopEsfuerzo{
	NodoTopEsfuerzo *inicio;
	NodoTopEsfuerzo *final;
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
				case '3': registrarCalificaciones();
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
				case '3': cancelarAsignacion();
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
				case '2': consultarIncidentes(1);
					break;
				case '3': consultarIncidentes(2);
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
				case '1': analisisDeDatos(1);
					break;
				case '2': analisisDeDatos(2);
					break;
				case '3': analisisDeDatos(3);
					break;
				case '4': analisisDeDatos(4);
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
	
	char dia[3], mes[3], anho[5];
	sprintf(dia, "%d", tm.tm_mday);
	sprintf(mes, "%d", (tm.tm_mon + 1));
	sprintf(anho, "%d", (tm.tm_year + 1900));
	
	strcat(hoy, dia);  
	strcat(hoy, "/");
	strcat(hoy, mes); 
	strcat(hoy, "/");
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
	Entradas: Una cadena de caracteres.
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
	Entradas: Una cadena de caracteres con formato de fecha (dd/MM/AAAA) y tres punteros a variables de tipo entero.
	Salidas: Asigna al valor de los punteros los segmentos de cada extracto de la fecha.
	Restricciones: Ninguna.
*/
void separarValores(char fecha[], int *d, int *m, int *a){
	int cont=0;
	char delim[] = "/";

	char *ptr = strtok(fecha, delim);
	*d = atoi(ptr);
	
	while (ptr != NULL)
	{
		ptr = strtok(NULL, delim);
		
		if(cont==0){
			*m = atoi(ptr);
		}else if(cont==1){
			*a = atoi(ptr);
		}
		
		cont++;
	}
}

/*
	Entradas: Dos cadena de caracteres con formato de fecha (dd/MM/AAAA)
	Salidas: 1 si la primera fecha es menor que la segunda y 2 si la segunda fecha es menor que la primera.
	Restricciones: Ninguna.
*/
int compararFechas(char fecha1[], char fecha2[]){
	int d1, m1, a1, d2, m2, a2;
		
	//Obtener valores fecha 1
	separarValores(fecha1, &d1, &m1, &a1);
	//Obtener valores fecha 2
	separarValores(fecha2, &d2, &m2, &a2);
		
	if (a1 < a2) 
        return 1; 
    if (a1 == a2 && m1 < m2) 
        return 1; 
    if (a1 == a2 && m1 == m2 && d1 < d2){
    	return 1;
	}else{
		return 2;	
	}
}

/*
    Entradas: Una puntero a una cadena de caacteres.
    Salidas: La cadena de caracteres recibida, con el valor de la hora actual.
    Restricciones: Ninguna.
*/
void obtenerHoraActual(char *horaActual, char *minutoActual){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char hora[4];
    char minuto[4];
    sprintf(hora, "%d", tm.tm_hour);
    sprintf(minuto, "%d", tm.tm_min);

    strcpy(horaActual, hora);
    strcpy(minutoActual, minuto);
}

/*
    Entradas: .
    Salidas: .
    Restricciones: Ninguna.
*/
void separarHoras(char hora[], int *h, int *min ){
    int cont=0;
    char delim[] = ":";

    char *ptr = strtok(hora, delim);

    *h = atoi(ptr);

    ptr = strtok(NULL, delim);
    *min = atoi(ptr);

}

/*
    Entradas: .
    Salidas: .
    Restricciones: Ninguna.
*/
int compararHoras(char hora1[], char hora2[]){

    int h=0;
    int min=0;
    int horaActual=0;
    int minutoActual=0;
    char x[4],y[4], aux[10];
    strcpy(aux,hora1);
    separarHoras( aux , &h, &min );

    obtenerHoraActual( x, y);

    horaActual = atoi(x);
    minutoActual = atoi(y);

    if(horaActual==h){
        return -1;
    }
    if(horaActual > h){
        return -1;
    }
    if(horaActual < h){
        if ((h-horaActual)>1){
            return 1;
        }
        else{

            if((minutoActual<=min)){
                return 1;
            }else{
                return -1;
            }
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
	Entradas: Una puntero a una lista del tipo ColaMiembros de Miembros de equipo.
	Salidas: Una lista  enlazada con los diferentes objetos de la estructura Miembro de Equipo(nombre, 
			cedula, correo, telefono, nivel de acceso).
	Restricciones: Ninguna.
*/
int cargarMiembros(struct ColaMiembros *C){
	
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
			
			if(C->inicio == NULL) 
			{
				//Inserta al inicio de la lista
				C->inicio = (struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));
				strcpy(C->inicio->cedula , aux->cedula);
				strcpy(C->inicio->nombre_completo , aux->nombre_completo); 
				strcpy(C->inicio->correo , aux->correo ); 
				strcpy(C->inicio->nivel_acceso , aux->nivel_acceso); 
				strcpy(C->inicio->telefono , aux->telefono); 
				C->inicio->siguiente = NULL; 
				C->inicio->anterior = NULL; 
				C->final = C->inicio;
	
			}else{	
				//Inserta al final de la lista	
				C->final->siguiente = (struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));
				strcpy(C->final->siguiente->cedula , aux->cedula);
				strcpy(C->final->siguiente->nombre_completo , aux->nombre_completo); 
				strcpy(C->final->siguiente->correo , aux->correo ); 
				strcpy(C->final->siguiente->nivel_acceso , aux->nivel_acceso); 
				strcpy(C->final->siguiente->telefono , aux->telefono); 
				C->final->siguiente->siguiente = NULL; 
				C->final->siguiente->anterior = C->final; 
				C->final = C->final->siguiente;
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

    struct ColaMiembros *C;
    struct MiembroEquipo *i;

    struct ListaAsignaciones *LAsig;
    struct Asignacion *iAsig;

    struct ListaRequerimientos *LReque;
    struct Requerimiento *iReque;
    
    struct ColaIncidentes *CIncidente;
    struct Incidentes *iIncidente;

    int val=3, val2=3, val3=3, res=0, resRequerimiento=0, resAsignacion=0,resIncidente=0;
    char id[12];

    system( "CLS" );
    printf("\n\n+-------------------------------+\n");
    printf("      Gestor de Requerimientos       \n");
    printf("+-------------------------------+\n");
    printf( "  Consultar Miembro de Equipo\n" );
    printf("+-------------------------------+\n");

    printf("\n Ingrese la cedula: (Ejm.208140809) \n ");
    gets(id);

    C = (struct ColaMiembros *) malloc(sizeof(struct ColaMiembros));
    C->inicio = NULL;
    C->final = NULL;

    LAsig = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
    LAsig->inicio = NULL;
    LAsig->final = NULL;

    LReque = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
    LReque->inicio = NULL;
    LReque->final = NULL;
    
    CIncidente = (struct ColaIncidentes *) malloc(sizeof(struct ColaIncidentes));
    CIncidente->inicio = NULL;
    CIncidente->final = NULL;

    resAsignacion=cargarAsignaciones(LAsig);

    resRequerimiento = cargarRequerimientos(LReque);
    
    resIncidente = cargarIncidentes(CIncidente);

    res=cargarMiembros(C);
    
		if(res==1){

	        i = C->inicio;
	        while( i->siguiente!= NULL){
	            val=strcmp(id,i->cedula);
	            if(val==0){
	                printf("\n+-------------------------------------+");
	                printf("\nCedula: %s \n", i->cedula);
	                printf("Nombre: %s \n", i->nombre_completo);
	                printf("Correo Electronico: %s \n", i->correo);
	                printf("Nivel de Acceso: %s \n", i->nivel_acceso);
	                printf("Numero Telefonico: %s \n", i->telefono);
	                printf("+-------------------------------------+\n");
	                printf( "      Requerimientos Asignados   \n" );
	                printf("+-------------------------------------+\n");
					if(resRequerimiento=1)
                	{

                    iAsig = LAsig->inicio;
                    while( iAsig->siguiente!= NULL){
                        if(compararCadenas(iAsig->miembros, i->cedula)==1){
                            val2=0;
                            printf("\n~~~~Datos de la Asignacion~~~~\n");
                            printf("Asignacion Numero: %s \n", iAsig->identificador);
                            printf("Descripcion: %s \n", iAsig->descripcion);
                            printf("Priodidad: %s \n", iAsig->prioridad ); 
                            printf("Estado: %s \n", iAsig->estado);
                            printf("+-------------------------------------+\n");
                            
                            iReque = LReque->inicio;
                            while(iReque->siguiente!= NULL){
                                if (compararCadenas(iAsig->identificador , iReque->identificador)==1){
                                	val3=0;
                                    printf("\n    ~~~~Datos del Requerimiento~~~~\n");
                                    printf("    Identificador: %s \n", iReque->identificador);
                                    printf("    Descripcion: %s \n", iReque->descripcion);
                                    printf("    Estado: %s \n", iReque->estado);
                                    printf("    +-------------------------------------+\n");
									
									iIncidente = CIncidente->inicio;
                                    while(iIncidente->siguiente!= NULL){
	                                    if (compararCadenas(iIncidente->codigoRequerimiento , iReque->identificador)==1){
	                                    	
	                                        printf("\n        ~~~~Datos de Incidentes~~~~\n");
	                                        printf("        Descripcion del incidente: %s \n", iIncidente->descripcionIncidente); 
	                                        printf("        Fecha de Incidente: %s \n", iIncidente->fecha);
	                                        printf("        +-------------------------------------+\n");
	
	                                    }
                                    	iIncidente = iIncidente->siguiente;
                                    }
								
								}
                                iReque = iReque->siguiente;
                            }
                            if(val3!=0){
                                printf( "\nNo hay incidentes registrados");
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
    liberarColaMiembros(C);
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

    struct ColaMiembros *C;
    struct MiembroEquipo *i;
    char id [50], res=0;
    int similitud=0;

    C = (struct ColaMiembros *) malloc(sizeof(struct ColaMiembros));
    C->inicio = NULL;
    C->final = NULL;

    res=cargarMiembros(C);

    if(res==1)
    {
         i = C->inicio;
        while( i->siguiente!= NULL){
            strcpy(id, i->cedula);
			similitud = compararCadenas(id, identificador);
            if(similitud==1){
            	liberarColaMiembros(C);
                return 1;
            }
            i = i->siguiente;
        }
    }

	liberarColaMiembros(C);
    return 0;
}

/*
    Entradas: 
    Salidas: 
    Restricciones:
*/
int validarNivelMiembro(const char identificador []){

    struct ColaMiembros *C;
    struct MiembroEquipo *i;
    char id [50], res=0;
    int similitud=0;

    C = (struct ColaMiembros *) malloc(sizeof(struct ColaMiembros));
    C->inicio = NULL;
    C->final = NULL;

    res=cargarMiembros(C);

    if(res==1)
    {
         i = C->inicio;
        while( i->siguiente!= NULL){
            strcpy(id, i->cedula);
			similitud = compararCadenas(id, identificador);
            if(similitud==1){   
				if(atoi(i->nivel_acceso)<=3){   		       	
	            	return -1;
	            }   	
            	return 1;
            }
            i = i->siguiente;
        }
    }
	liberarColaMiembros(C);
}

/*
    Entradas: 
    Salidas: 
    Restricciones: 
*/
int validarIncidentes(const char identificador[]){

   	struct ColaIncidentes *C;
	struct Incidentes *i;
	int val=3, res=0, similitud=0, contIncidentes=0;
	char id [50];

	C = (struct ColaIncidentes *) malloc(sizeof(struct ColaIncidentes));
	C->inicio = NULL;
	C->final = NULL;

	res=cargarIncidentes(C);
	
	if(res==1)
	{
		i = C->inicio;
		while( i->siguiente!= NULL){
			strcpy(id, i->codigoRequerimiento);		
			similitud = compararCadenas(id, identificador);
            if(similitud==1){   
				contIncidentes++;
            }
			i = i->siguiente;
		}
		
		if(contIncidentes>=3){   		       	
        	return -1;
        }   	
    	return 1;
				
	}else{
		return 1;
	}	
	liberarColaIncidentes(C);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

/*
    Entradas: 
    Salidas: 
    Restricciones: 
*/
int validarAsignaciones(const char identificador[]){

   	struct ListaAsignaciones *L;
	struct Asignacion *i;
	int val=3, res=0, similitud=0, contAsignaciones=0;
	char id [50];

	L = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
	L->inicio = NULL;
	L->final = NULL;

	res=cargarAsignaciones(L);
	
	if(res==1)
	{
		i = L->inicio;
		while( i->siguiente!= NULL){
			strcpy(id, i->identificador);		
			similitud = compararCadenas(id, identificador);
            if(similitud==1){   
				contAsignaciones++;
            }
			i = i->siguiente;
		}
		
		if(contAsignaciones>=3){   		       	
        	return -1;
        }   	
    	return 1;
				
	}else{
		return 1;
	}	
	liberarListaAsignaciones(L);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

/*
	Entradas: Una puntero a una lista del tipo ListaOficinas de Oficinas.
	Salidas: Una lista enlazada con los diferentes objetos de la estructura Asignacion (codgo, dias, horaApertura, horaCierre). 
	Restricciones: Ninguna.
*/
int cargarOficinas(struct ListaOficinas *L){
	
	struct Oficina *oficina, *aux;

	aux =(struct Oficina *) malloc (sizeof(struct Oficina));

	ArchOficinas = fopen("Archivos\\Oficinas.txt","r");

	if(ArchOficinas==NULL){
		return 0;	
	}else{

		while(!feof(ArchOficinas)){
			fgets(aux->codigo, 50, ArchOficinas); 
			quitaFinLinea(aux->codigo);
			fgets(aux->dias, 30, ArchOficinas);
			quitaFinLinea(aux->dias);
			fgets(aux->horaApertura, 15, ArchOficinas); 
			quitaFinLinea(aux->horaApertura);
			fgets(aux->horaCierre, 15, ArchOficinas);
			quitaFinLinea(aux->horaCierre);	
			
			if(L->inicio == NULL) 
			{
				//Inserta al inicio de la lista
				L->inicio =(struct Oficina *) malloc (sizeof(struct Oficina));
				strcpy(L->inicio->codigo , aux->codigo);
				strcpy(L->inicio->dias , aux->dias); 
				strcpy(L->inicio->horaApertura , aux->horaApertura ); 
				strcpy(L->inicio->horaCierre , aux->horaCierre); 
				L->inicio->siguiente = NULL; 
				L->inicio->anterior = NULL; 
				L->final = L->inicio;
	
			}else{	
				//Inserta al final de la lista	
				L->final->siguiente =(struct Oficina *) malloc (sizeof(struct Oficina));
				strcpy(L->final->siguiente->codigo , aux->codigo);
				strcpy(L->final->siguiente->dias , aux->dias); 
				strcpy(L->final->siguiente->horaApertura , aux->horaApertura ); 
				strcpy(L->final->siguiente->horaCierre , aux->horaCierre); 
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
void consultarOficinas(){

	struct ListaOficinas *L;
	struct Oficina *i;
	int res=0;
	
	printf("\n+-------------------------------------------------------------------+\n");
	printf( "                         Oficinas y Horarios" );
	printf("\n+-------------------------------------------------------------------+\n");
	
	L = (struct ListaOficinas *) malloc(sizeof(struct ListaOficinas));
	L->inicio = NULL;
	L->final = NULL;
	
	res=cargarOficinas(L);

	if(res=1)
	{
        i = L->inicio;
        int cont=1;
        	printf(" Codigo        Dias de Trabajo       Hora-Apertura   Hora-Cierre\n" ); 
        while(i->siguiente!=NULL){
            printf("\n %s          %s                %s         %s\n" , i->codigo, i->dias, i->horaApertura, i->horaCierre );
            i = i->siguiente;

        }
        printf("\n+-------------------------------------------------------------------+\n");		
		
	}else{
		printf( "\n***No se han encontrado Oficinas registradas***");
	}
	
	//liberarListaAsignaciones(L);
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
		printf("\n Ingrese el identificador: (Ejm. RQ-001) \n");
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
	printf("\n Ingrese la dependencia: (Ejm. RQ-001) \n");
	gets(requerimiento->dependencia);
	printf("\n Ingrese los recursos:\n");
	gets(requerimiento->recursos);
	strcpy(requerimiento->estado, "Por hacer");
	printf("\n Ingrese el esfuerzo: ( 1...10 ) \n");
	gets(requerimiento->esfuerzo);
	consultarOficinas();
	printf("\n Ingrese el codigo de la oficina para la seleccion del horario: \n");
	gets(requerimiento->oficina);
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
		fprintf(ArchRequerimiento,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", requerimiento->identificador, requerimiento->tipo, requerimiento->descripcion,
	requerimiento->riesgo, requerimiento->dependencia, requerimiento->recursos, requerimiento->estado,  requerimiento->esfuerzo, requerimiento->oficina);
	}
	fclose(ArchRequerimiento);
	printf("\n ==>Informacion guardada<==.\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 

}

/*
	Entradas: Una puntero a una lista del tipo ListaRequerimientos de Requerimientos.
	Salidas: Una lista   enlazada con los diferentes objetos de la estructura Requerimiento(identificador, tipo, 
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
			fgets(aux->tipo, 20, ArchRequerimiento); 
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
			fgets(aux->oficina, 15, ArchRequerimiento);
			quitaFinLinea(aux->oficina); 
			
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
				strcpy(L->inicio->oficina , aux->oficina);
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
				strcpy(L->final->siguiente->oficina , aux->oficina);
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
    
    struct ListaOficinas *LOf;
    struct Oficina *iOf;
    
    int val=3, res=0, res2=0;
    char id[10];

    system( "CLS" );
    printf("\n\n+-------------------------------+\n");
    printf("      Gestor de Requerimientos       \n");
    printf("+-------------------------------+\n");
    printf( "  Consultar un Requerimiento\n" );
    printf("+-------------------------------+\n");

    printf("\n Ingrese el identificador: (Ejm. RQ-000) \n ");
    gets(id);

    L = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
    L->inicio = NULL;
    L->final = NULL;
    
    LOf = (struct ListaOficinas *) malloc(sizeof(struct ListaOficinas));
    LOf->inicio = NULL;
    LOf->final = NULL;

    res = cargarRequerimientos(L);  
    res2 = cargarOficinas(LOf);

    if(res==1)
    {
        i = L->inicio;
        while( i->siguiente!= NULL){
            val=strcmp(id,i->identificador);
            if(val==0){
            	printf("\n+-------------------------------+");
                printf("\nIdentificador: %s \n", i->identificador);
                printf(" Tipo: %s \n", i->tipo);
                printf(" Descripcion: %s \n", i->descripcion);
                printf(" Riesgo: %s \n", i->riesgo);
                printf(" Dependencia: %s \n", i->dependencia);
                printf(" Recursos: %s \n", i->recursos);
                printf(" Estado: %s \n", i->estado);
                printf(" Esfuerzo: %s \n", i->esfuerzo);
                printf(" Oficina: %s \n", i->oficina);
                
                iOf = LOf->inicio;
                while(iOf->siguiente!= NULL){
                    if (compararCadenas(iOf->codigo , i->oficina)==1){
                    	
                        printf(" Horarios de Operacion\n");
                        printf("  - Dias de trabajo: %s \n", iOf->dias); 
                        printf("  - Hora de Apertura: %s \n", iOf->horaApertura);
                        printf("  - Hora de Cierre: %s \n", iOf->horaCierre);

                    }
                	iOf = iOf->siguiente;
                }
                
                printf("+-------------------------------+\n");

            }
            i = i->siguiente;
        }

        if(val == 1){
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
	struct Requerimiento *i;
	char id[10], respuesta[2], tipo[20], recursos[55], estado [15];
	int val=3, res=0, resp;
	
	printf("\n Ingrese el identificador: (Ejm. RQ-000) \n ");
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
                printf("Oficina: %s \n", i->oficina);
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
					strcpy(i->estado, estado);
						
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
	Entradas: Una puntero a una lista del tipo ListaRequerimientos de Requerimientos.
	Salidas: Se sobreescribe el archivo que almacena la lista de requerimietnos con los valores modificados.
	Restricciones: No tiene restricciones.
*/
void actualizarRequerimientos(struct ListaRequerimientos *L){
	
	struct Requerimiento *i;
	
	 if (remove("Archivos\\Requerimientos.txt") != 0)
	 	return;
	 	
	ArchRequerimiento=fopen("Archivos\\Requerimientos.txt","a+");
	if(ArchRequerimiento==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		
		i = L->inicio;
        while( i->siguiente!= NULL){
			fprintf(ArchRequerimiento,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", i->identificador, i->tipo, i->descripcion,
					i->riesgo, i->dependencia, i->recursos, i->estado,  i->esfuerzo, i->oficina);
            i = i->siguiente;
        }
		
	}
	fclose(ArchRequerimiento);
	printf("\n ==>Informacion guardada<==.\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 

}

/*
	Entradas: Dos cadenas de caracteres con los valores de dos horas con el formato hh:mm
	Salidas: 1 indica que la hora del del requerimiento es mayor que la de la asigancion
			 2 indica que la hora del del requerimiento es menor que la de la asigancion
			 0 indica que ambas horas son iguales
	Restricciones: No tiene restricciones.
*/
int validarHoras(char horaRQ[], char horaAS[]){
    
    int hRQ, mRQ, hAS, mAS;
		
	//Obtener valores hora 1
	separarHoras(horaRQ, &hRQ, &mRQ);
	//Obtener valores hora 2
	separarHoras(horaAS, &hAS, &mAS);

    if(hRQ==hAS){
        if(mRQ==mAS){
        	return 0;
		}else if (mRQ>mAS){
            return 1;
        }else{
			return 2;
        }
    }
    
    if(hRQ > hAS){
        return 1;
    }else{
		return 2;
    }

}

/*
	Entradas: Un objeto de tipo estado de la estructura Requerimiento.
	Salidas: Llama a la función guardarRequerimiento para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void modificarEstadoRQ(struct ListaRequerimientos *L, const char identificador[]){
	struct Requerimiento *i;
	char id[15];
	int val;

    i = L->inicio;
    while( i->siguiente!= NULL){
        if(strcmp(i->identificador, identificador)==0){
			strcpy(i->estado, "Activo");		
		}
        i = i->siguiente;
    }

	actualizarRequerimientos(L);
	liberarListaRequerimientos(L);	
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
	int prioridad=0, val0=0, val1=0, val2=0, val3=0, res=0, res2=0;
	
	asignacion=(struct Asignacion *) malloc (sizeof(struct Asignacion));
	
	char fecha [50];
	char hRQ_Inicio[10], hRQ_Fin[10], hAS_Inicio[10], hAS_Fin[10];
	
	struct ListaRequerimientos *LRQ;
    struct Requerimiento *iRQ;
    
    struct ListaOficinas *LOf;
    struct Oficina *iOf;
	
	LRQ = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
    LRQ->inicio = NULL;
    LRQ->final = NULL;
    
    LOf = (struct ListaOficinas *) malloc(sizeof(struct ListaOficinas));
    LOf->inicio = NULL;
    LOf->final = NULL;
	
	printf("\n Ingrese el Codigo de la Asignacion: (Ejm. AS-001) \n");
	gets(asignacion->codigoAsignacion);
	
	obtenerFechaActual(fecha);
	strcpy(asignacion->fechaSolicitud, fecha);
	
	printf("\n Ingrese las Cedula del Miembro: (Ejm. 105450656) \n");
	gets(asignacion->miembros);
	
	val0=validarCedula(asignacion->miembros);
	if(val0!=1){//Validar el miembro se encuentra registrado.
		printf("\n***No es posible completar la asignacion, la cedula ingresada\n   no corresponde a ningun miembro registrado***");
		printf("\n\nPresione una tecla para regresar..." ); 
		getchar();
		return;
	}
	
	val1=validarNivelMiembro(asignacion->miembros);
	if(val1==-1){//Validar el nivel de acceso para el miembro consultado.
		printf("\n***No es posible completar la asignacion, el nivel de acceso\n   del miembro consultado debe ser mayor a 3***");
		printf("\n\nPresione una tecla para regresar..." ); 
		getchar();
		return;
	}
	
	printf("\n Ingrese la Hora de Inicio: (Ejm. 07:25) \n");
	gets(asignacion->horaInicio);
	printf("\n Ingrese el Hora de Fin: (Ejm. 14:25) \n");
	gets(asignacion->horaFin);
	
	printf("\n Ingrese el ID del Requerimiento: \n");
	//Mostrar Requerimientos
	res = cargarRequerimientos(LRQ);
	res2 = cargarOficinas(LOf);

	iRQ = LRQ->inicio;
	printf("\n                     ***Lista de Requerimientos Compatibles***\n");
	printf("+-----------------------------------------------------------------------------------+\n");
	printf("\n   ID        Oficina      Hora-Apertura   Hora-Cierre  Dias de Trabajo   Descripcion\n" ); 
    while(iRQ->siguiente!= NULL){         
    	iOf = LOf->inicio;
        while(iOf->siguiente!= NULL){
            if (compararCadenas(iOf->codigo , iRQ->oficina)==1){
            	strcpy(hRQ_Inicio, iOf->horaApertura);
    			strcpy(hRQ_Fin, iOf->horaCierre);
    			strcpy(hAS_Inicio, asignacion->horaInicio);
    			strcpy(hAS_Fin, asignacion->horaFin);
            	if((validarHoras(hRQ_Inicio, hAS_Inicio)==2 || validarHoras(hRQ_Inicio, hAS_Inicio)==0) && (validarHoras(hRQ_Fin, hAS_Fin)==1 || validarHoras(hRQ_Fin, hAS_Fin)==0)){
            		printf("\n   %s      %s           %s        %s         %s       %s\n" , iRQ->identificador, iOf->codigo, iOf->horaApertura, iOf->horaCierre, iOf->dias, iRQ->descripcion);
            		
            	}
            }
        	iOf = iOf->siguiente;
        }
    	iRQ = iRQ->siguiente;
    }
    printf("\n+-----------------------------------------------------------------------------------+\n");           
	gets(asignacion->identificador);
	
	val2=validarIncidentes(asignacion->identificador);
	if(val2==-1){ //Validar el numero de Incidentes para el requerimiento seleccionado.
		printf("\n***No es posible completar la asignacion, el requerimiento\n   seleccionado posee 3 o mas incidentes***");
		printf("\n\nPresione una tecla para regresar..." ); 
		getchar();	
		return;
	}
	
	val3=validarAsignaciones(asignacion->identificador);
	if(val3==-1){ //Validar el numero de Asignaciones para el requerimiento seleccionado.
		printf("\n***No es posible completar la asignacion, el numero de\n   participantes es mayor a 3***");
		printf("\n\nPresione una tecla para regresar..." ); 
		getchar();	
		return;
	}
	
	printf("\n Ingrese el Recurso (Opcional): \n");
	gets(asignacion->recurso);
	
	printf("\n Ingrese la Descripcion: \n");
	gets(asignacion->descripcion);
		
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
	printf("%s \n", asignacion->identificador);
	modificarEstadoRQ(LRQ, asignacion->identificador);

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
		fprintf(ArchAsignaciones,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", asignacion->codigoAsignacion, asignacion->fechaSolicitud, asignacion->horaInicio, asignacion->horaFin, asignacion->recurso, asignacion->identificador, 
																asignacion->descripcion,  asignacion->miembros, asignacion->prioridad, asignacion->estado);
					
	}
	fclose(ArchAsignaciones);

}

/*
	Entradas: Una puntero a una lista del tipo ListaAsiganciones de Asignaciones.
	Salidas: Una lista enlazada con los diferentes objetos de la estructura Asignacion (fechaSolicitud, horaInicio, 
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
			fgets(aux->codigoAsignacion, 15, ArchAsignaciones); 
			quitaFinLinea(aux->codigoAsignacion);
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
			fgets(aux->miembros, 15, ArchAsignaciones);
			quitaFinLinea(aux->miembros);
			fgets(aux->prioridad, 15, ArchAsignaciones);
			quitaFinLinea(aux->prioridad);
			fgets(aux->estado, 15, ArchAsignaciones);
			quitaFinLinea(aux->estado);
			
			if(L->inicio == NULL) 
			{
				//Inserta al inicio de la lista
				L->inicio =(struct Asignacion *) malloc (sizeof(struct Asignacion));
				strcpy(L->inicio->codigoAsignacion , aux->codigoAsignacion);
				strcpy(L->inicio->fechaSolicitud , aux->fechaSolicitud);
				strcpy(L->inicio->horaInicio , aux->horaInicio ); 
				strcpy(L->inicio->horaFin , aux->horaFin); 
				strcpy(L->inicio->recurso , aux->recurso); 
				strcpy(L->inicio->identificador , aux->identificador); 
				strcpy(L->inicio->descripcion , aux->descripcion);
				strcpy(L->inicio->miembros , aux->miembros); 
				strcpy(L->inicio->prioridad , aux->prioridad ); 
				strcpy(L->inicio->estado , aux->estado); 
				L->inicio->siguiente = NULL; 
				L->inicio->anterior = NULL; 
				L->final = L->inicio;
	
			}else{	
				//Inserta al final de la lista	
				L->final->siguiente =(struct Asignacion *) malloc (sizeof(struct Asignacion));
				strcpy(L->final->siguiente->codigoAsignacion , aux->codigoAsignacion);
				strcpy(L->final->siguiente->fechaSolicitud , aux->fechaSolicitud);
				strcpy(L->final->siguiente->horaInicio , aux->horaInicio ); 
				strcpy(L->final->siguiente->horaFin , aux->horaFin); 
				strcpy(L->final->siguiente->identificador , aux->identificador); 
				strcpy(L->final->siguiente->descripcion , aux->descripcion);
				strcpy(L->final->siguiente->recurso , aux->recurso);
				strcpy(L->final->siguiente->miembros , aux->miembros); 
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
	Entradas: Una puntero a una lista del tipo ListaAsiganciones de Asignaciones.
	Salidas: Una lista enlazada con los diferentes objetos de la estructura Asignacion, ordenadas por fecha de solicitud. 
	Restricciones: Ninguna.
*/
void ordenarAsignaciones(struct ListaAsignaciones *L){
	
	struct Asignacion *i, *j, *temp;
	char fecha1[15], fecha2[15];	
	int res=0;

	temp=(struct Asignacion *) malloc (sizeof(struct Asignacion));
	
	i = L->inicio;
	while( i->siguiente!= NULL){
		
		j = i->siguiente;
		while( j->siguiente!= NULL){
			strcpy(fecha1, i->fechaSolicitud);
			strcpy(fecha2, j->fechaSolicitud);
				
			res = compararFechas(fecha1, fecha2);

			if(res==1){
				
				//Guardar los valores del nodo i
				strcpy(temp->codigoAsignacion,i->codigoAsignacion);
				strcpy(temp->fechaSolicitud,i->fechaSolicitud);
				strcpy(temp->horaInicio, i->horaInicio);
				strcpy(temp->horaFin, i->horaFin);
				strcpy(temp->recurso, i->recurso);
				strcpy(temp->identificador, i->identificador);
				strcpy(temp->descripcion, i->descripcion);
				strcpy(temp->miembros, i->miembros);
				strcpy(temp->prioridad, i->prioridad);
				strcpy(temp->estado, i->estado);
				
				//Asignar los valores del nodo j al nodo i
				strcpy(i->codigoAsignacion, j->codigoAsignacion);				
				strcpy(i->fechaSolicitud, j->fechaSolicitud);
				strcpy(i->horaInicio, j->horaInicio);
				strcpy(i->horaFin, j->horaFin);
				strcpy(i->recurso, j->recurso);
				strcpy(i->identificador, j->identificador);
				strcpy(i->descripcion, j->descripcion);
				strcpy(i->miembros, j->miembros);
				strcpy(i->prioridad, j->prioridad);
				strcpy(i->estado, j->estado);
				
				//Asignar los valores guardados del nodo i al nodo j
				strcpy(j->codigoAsignacion, temp->codigoAsignacion);
				strcpy(j->fechaSolicitud, temp->fechaSolicitud);
				strcpy(j->horaInicio, temp->horaInicio);
				strcpy(j->horaFin, temp->horaFin);
				strcpy(j->recurso, temp->recurso);
				strcpy(j->identificador, temp->identificador);
				strcpy(j->descripcion, temp->descripcion);
				strcpy(j->miembros, temp->miembros);
				strcpy(j->prioridad, temp->prioridad);
				strcpy(j->estado, temp->estado);
				
			}
			
			j = j->siguiente;
		}
		i = i->siguiente;
	}
	
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
		ordenarAsignaciones(L);	
		printf("\n+-------------------------------+\n");
		i = L->inicio;
		while( i->siguiente!= NULL){
			val=strcmp(id,i->miembros);
			if(val==0){
				printf("ID de la Asignacion: %s \n", i->codigoAsignacion);
				printf("Fecha de Solicitud: %s \n", i->fechaSolicitud);
				printf("Hora de Inicio: %s \n", i->horaInicio ); 
				printf("Hora de Fin: %s \n", i->horaFin); 
				printf("Identificador: %s \n", i->identificador); 
				printf("Recurso: %s \n", i->recurso); 
				printf("Descripcion: %s \n", i->descripcion);
				printf("Miembros: %s \n", i->miembros); 
				printf("Priodidad: %s \n", i->prioridad ); 
				printf("Estado: %s \n", i->estado); 
				printf("+-------------------------------+\n");
			
			}
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
    Entradas:  
    Salidas: 
    Restricciones: 
*/
int validarAsignacion(struct ListaAsignaciones *L, char idAsignacion[], char idRQ[], char idMiembro[]){
	struct  Asignacion *i;

    i = L->inicio;
    while( i->siguiente!= NULL){
        if(strcmp(i->codigoAsignacion, idAsignacion)==0){
        	strcpy(idRQ,i->identificador);
        	strcpy(idMiembro,i->miembros);
			return 1;		
		}
        i = i->siguiente;
    }
	
	return 0;
}

/*
    Entradas:  
    Salidas: 
    Restricciones: 
*/
void modificarCalificacion(struct ListaCalificaciones *L,  char idAsignacion[]){
	struct Calificacion *i;
	int calificacionInt;
	char calificacionChar [20];

    i = L->inicio;
    while( i->siguiente!= NULL){
        if(strcmp(idAsignacion, i->codigoAsignacion)==0){
			calificacionInt = atoi(i->calificacion);
			calificacionInt = calificacionInt - 1;
			sprintf(calificacionChar, "%d", calificacionInt);
			strcpy(i->calificacion, calificacionChar);	
			printf("%s", i->calificacion);	
		}
        i = i->siguiente;
    }
	
	actualizarCalificacion(L);
}


/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
void actualizarCalificacion(struct ListaCalificaciones *L){
	
	struct Calificacion *i;
	
	 if (remove("Archivos\\Calificaciones.txt") != 0)
	 	return;
	 	
	ArchRequerimiento=fopen("Archivos\\Calificaciones.txt","a+");
	if(ArchRequerimiento==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		
		i = L->inicio;
        while( i->siguiente!= NULL){
			fprintf(ArchCalificaciones,"%s\n%s\n%s\n%s\n", i->codigoAsignacion, i->codigoRequerimiento, i->miembro,  i->calificacion);
            i = i->siguiente;
        }
		
	}
	fclose(ArchRequerimiento);

}

/*
    Entradas: Un ID determinado en la tabla que se presenta de Asiganciones. 
    Salidas: Se cambia el estado de la asignacion escogida por el ID a Cancelada . 
    Restricciones: No valida.
*/
void cancelarAsignacion(){
    struct ListaAsignaciones *L;
    struct ListaCalificaciones *LC;
    struct Asignacion *i;
    int val=3, res=0, res2=0;
    char idAsignacion[50], seleccion[10];

    system( "CLS" );
    printf("\n\n+-------------------------------------+\n");
    printf("      Gestor de Requerimientos       \n");
    printf("+-------------------------------------+\n");
    printf( "         Cancelar Asignacion        \n" );
    printf("+-------------------------------------+\n");

    L = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
    L->inicio = NULL;
    L->final = NULL;
    
	res=cargarAsignaciones(L);
    
    if(res=1)
    {
        printf("\n\n+-----------------------Lista de Asignaciones-----------------------+\n");
        printf("\n+-------------------------------------------------------------------+\n");
        i = L->inicio;
        int cont=1;
        printf(" ID          Miembro             RQ         Estado    Hora inicio\n" ); 
        while(i->siguiente!=NULL){
            if (compararCadenas( i->estado , "Cancelada")!=1){
                printf("\n %s        %s        %s        %s        %s\n" , i->codigoAsignacion, i->miembros , i->identificador, i->estado, i->horaInicio );
                cont++;
            }
            i = i->siguiente;

        }
        printf("\n+-------------------------------------------------------------------+\n");

    }else{
        printf( "\nNo se han registrado Asignaciones");
    }
	int eliminar=0;
    printf("Ingrese el numero del ID de la asignacion que desea cancelar: ");
    gets(seleccion);
    
    i = L->inicio;
    while(i->siguiente!=NULL){
        if (strcmp( i->codigoAsignacion , seleccion)==0){
            if(compararHoras( i->horaInicio,  i->horaFin)==1){
                strcpy(i->estado,"Cancelada");
                break;
            }else{
                printf("\n+----------------------------------------------------------------------------------+\n");
                printf("  La asignacion no puede cancelarse si se tiene menos de una para su hora de inicio");
                printf("\n+----------------------------------------------------------------------------------+\n"); 

                printf("\nPresione una tecla para regresar..." ); 
                getchar();
                return;
            }
            break;
        }
        i = i->siguiente;
     }
           
	if (remove("Archivos\\Asignaciones.txt") == 0){

        ArchAsignaciones=fopen("Archivos\\Asignaciones.txt","a+");
        if(ArchAsignaciones==NULL){
            printf("\n Error al intentar usar el archivo.\n");
        }else{

            i=L->inicio;
            while(i->siguiente!=NULL){
                fprintf(ArchAsignaciones,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", i->codigoAsignacion, i->fechaSolicitud, i->horaInicio, i->horaFin, i->recurso, i->identificador, 
                                                                        			 i->descripcion,  i->miembros, i->prioridad, i->estado);
                i=i->siguiente;
            }
        }
        fclose(ArchAsignaciones);
        printf("\n\n ==>Informacion guardada<==\n");

    }else{
       printf("Problema al borrar el archivo de Asignaciones");
    }
    
    //Actualizar la calificaion del miembro, según la asignacion cancelada
	LC = (struct ListaCalificaciones *) malloc(sizeof(struct ListaCalificaciones));
    LC->inicio = NULL;
    LC->final = NULL;
    
    
	res2=cargarCalificaciones(LC);
	modificarCalificacion(LC, seleccion);
	
	
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
	
	printf("\n Ingrese el Codigo del Incidente: (Ejm. IN001) \n");
	gets(incidente->codigoIncidente);	
	printf("\n Ingrese el Codigo del Requerimiento: (Ejm. RQ-000) \n");
	gets(incidente->codigoRequerimiento);
	printf("\n Ingrese el Codigo de Asignacion: (Ejm. 1, 2, 3, 4....) \n");
	gets(incidente->codigoAsignacion);
	printf("\n Ingrese la Descripcion de Incidente: \n");
	printf(" (Ejm. Requerimiento no terminado, con errores, o incompleto)\n");
	gets(incidente->descripcionIncidente);
	printf("\n Ingrese la Fecha del Incidente: (Ejm. 10/3/2020) \n");
	gets(incidente->fecha);
	printf("\n");
	incidente->siguiente=NULL;

	guardarIncidentes(incidente);
	printf("\n\nPresione una tecla para regresar..." ); 
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
		fprintf(ArchIncidentes,"%s\n%s\n%s\n%s\n%s\n", incidente->codigoIncidente, incidente->codigoRequerimiento, incidente->codigoAsignacion, 
														incidente->descripcionIncidente, incidente->fecha);
	}
	fclose(ArchIncidentes);
	printf("\n\n ==>Informacion guardada<==.\n");

}

/*
	Entradas: Una puntero a una lista del tipo ListaIncidentes de Incidentes.
	Salidas: Una lista   enlazada con los diferentes objetos de la estructura Incidente (codigoRequerimiento, codigoAsignacion, 
			descripcionIncidente, fecha). 
	Restricciones: Ninguna.
*/
int cargarIncidentes(struct ColaIncidentes *C){
	
	struct Incidentes *aux;

	aux = (struct Incidentes *) malloc (sizeof(struct Incidentes));

	ArchIncidentes = fopen("Archivos\\Incidentes.txt","r");

	if(ArchIncidentes==NULL){
		return 0;	
	}else{
	
		while(!feof(ArchIncidentes)){
			fgets(aux->codigoIncidente, 15, ArchIncidentes);
			quitaFinLinea(aux->codigoIncidente);
			fgets(aux->codigoRequerimiento, 15, ArchIncidentes); 
			quitaFinLinea(aux->codigoRequerimiento);
			fgets(aux->codigoAsignacion, 15, ArchIncidentes); 
			quitaFinLinea(aux->codigoAsignacion);
			fgets(aux->descripcionIncidente, 100, ArchIncidentes);
			quitaFinLinea(aux->descripcionIncidente);	
			fgets(aux->fecha, 20, ArchIncidentes);
			quitaFinLinea(aux->fecha);		
						
			if(C->inicio == NULL){
				//Inserta al inicio de la lista
				C->inicio = (struct Incidentes *) malloc (sizeof(struct Incidentes));
				strcpy(C->inicio->codigoIncidente , aux->codigoIncidente);
				strcpy(C->inicio->codigoRequerimiento , aux->codigoRequerimiento);
				strcpy(C->inicio->codigoAsignacion , aux->codigoAsignacion ); 
				strcpy(C->inicio->descripcionIncidente , aux->descripcionIncidente); 
				strcpy(C->inicio->fecha , aux->fecha); 
				C->inicio->siguiente = NULL; 
				C->inicio->anterior = NULL; 
				C->final = C->inicio;
	
			}else{
				//Inserta al final de la lista	
				C->final->siguiente =(struct Incidentes *) malloc (sizeof(struct Incidentes));
				strcpy(C->final->siguiente->codigoIncidente , aux->codigoIncidente);
				strcpy(C->final->siguiente->codigoRequerimiento , aux->codigoRequerimiento);
				strcpy(C->final->siguiente->codigoAsignacion , aux->codigoAsignacion ); 
				strcpy(C->final->siguiente->descripcionIncidente , aux->descripcionIncidente); 
				strcpy(C->final->siguiente->fecha , aux->fecha); 
				C->final->siguiente->siguiente = NULL; 
				C->final->siguiente->anterior = C->final; 
				C->final = C->final->siguiente;
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
void consultarIncidentes(int tipoConsulta){

	struct ColaIncidentes *C;
	struct Incidentes *i;
	
	struct ListaAsignaciones *LAs;
	struct Asignacion *iAs;
	
	int val=3, res=0, res2=0;
	char fechaInicio[15], fechaFin[15], fechaIncidente[15], idRQ[15], idIN[15];
	
	system( "CLS" );
	printf("\n\n+-------------------------------------+\n");
	printf("      Gestor de Requerimientos         \n");
	printf("+-------------------------------------+\n");
	
	C = (struct ColaIncidentes *) malloc(sizeof(struct ColaIncidentes));
	C->inicio = NULL;
	C->final = NULL;

	res=cargarIncidentes(C);
	
	if(res==1)
	{
	
		switch(tipoConsulta){
			case 1:
				printf( "Consultar Incidentes (Rango de Fechas) \n");
				printf("+-------------------------------------+\n");
				printf("\n Ingrese la Fecha de Inicio: (Ejm. 01/01/2020) \n ");
				gets(fechaInicio);
			 	printf("\n Ingrese la Fecha de Fin: (Ejm. 01/01/2020) \n ");
				gets(fechaFin);
				
				i = C->inicio;
				printf("\n+--------------------------------------------------------+\n");
				printf(" ID Incidente    ID Requerimiento   Fecha de Incidente\n" ); 
				while( i->siguiente!= NULL){
					strcpy(fechaIncidente, i->fecha);
					
					if(compararFechas(fechaInicio, fechaIncidente)==1 && compararFechas(fechaFin, fechaIncidente)==2){
						printf("\n %s              %s                  %s\n",i->codigoIncidente, i->codigoRequerimiento, i->fecha);					
					}
					i = i->siguiente;
				}
				
			
				break;
			case 2: 
				printf( "     Consultar Incidentes (Por RQ) \n");
				printf("+-------------------------------------+\n");
				printf("\n Ingrese el ID del requerimiento: (Ejm. RQ-001) \n ");
				gets(idRQ);
				
				i = C->inicio;
				printf("\n+--------------------------------------------------------+\n");
				printf(" ID Incidente    ID Requerimiento   Fecha de Incidente\n" ); 
				while( i->siguiente!= NULL){
					if(strcmp(idRQ, i->codigoRequerimiento)==0){
						printf("\n %s         %s           %s\n", i->codigoIncidente, i->codigoRequerimiento, i->fecha);				
					}
					i = i->siguiente;
				}
				break;	
		}
	printf("\n+--------------------------------------------------------+\n");

	printf("\n Ingrese el ID del Incidente para ver el detalle: (Ejm. IN-001) \n ");
	gets(idIN);
	
	LAs = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
	LAs->inicio = NULL;
	LAs->final = NULL;

	res2=cargarAsignaciones(LAs);
	
	i = C->inicio;
	while( i->siguiente!= NULL){
		if(strcmp(idIN, i->codigoIncidente)==0){
			
			iAs = LAs->inicio;
			while( iAs->siguiente!= NULL){
				if(strcmp(i->codigoAsignacion,iAs->codigoAsignacion)){
					printf("\n+- - - - - - - - - - - - - - - - - - - - - - - - - - - - +");
					printf("\n              Detalle del Incidente\n");
					printf("+- - - - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
					printf(" ID Incidente    ID Requerimiento   Fecha de Incidente" ); 
					printf("\n %s              %s                  %s\n",i->codigoIncidente, i->codigoRequerimiento, i->fecha);
					printf("+- - - - - - - - - - - - - - - - - - - - - - - - - - - - +");	
					printf("\n Ansignacion->         %s   \n", i->codigoAsignacion);
					printf("\n Miembro asignado->    %s   \n", iAs->miembros);
					printf("\n Descripcion->         %s   \n", i->descripcionIncidente);
					printf("+- - - - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
					break;
				}
				iAs = iAs->siguiente;
			}
		}
		i = i->siguiente;
	}
	
						
	}else{
		printf( "\n***No se han registrado Incidentes***");
	}	
	liberarColaIncidentes(C);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

/*
	Entradas: Los diferentes objetos de la estructura Calificación(codigoRequerimiento, codigoAsignacion, calificacion). 
	Salidas: LLama a la función guardarCalificacion para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void registrarCalificaciones(){
	system( "CLS" );
	printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------+\n");
	printf( "   Calificar un requerimiento\n" );
	printf("+-------------------------------+\n");	
	
	struct Calificacion *calificacion, *i;
	char idRQ [15], miembro[15];
	int res=0, res2=0, actualizar=0;

	calificacion = (struct Calificacion *) malloc (sizeof(struct Calificacion));
	
	struct ListaAsignaciones *L;
	L = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
	L->inicio = NULL;
	L->final = NULL;

	res=cargarAsignaciones(L);
	
	struct ListaCalificaciones *LC;
	LC = (struct ListaCalificaciones *) malloc(sizeof(struct ListaCalificaciones));
    LC->inicio = NULL;
    LC->final = NULL;
        
	res2=cargarCalificaciones(LC);
	
	if(calificacion == NULL){
		printf("Espacio insuficiente para almacenar los datos.\n");	
	}
	
	if(res == 0){
		printf("No ha resgistrado ninguna asignación\n");
		getchar();	
		return;	
	}
		
	do{
        printf("\n Ingrese el Codigo de Asignacion: (Ejm. AS-001) \n");
		gets(calificacion->codigoAsignacion);

        if(validarAsignacion(L, calificacion->codigoAsignacion, idRQ, miembro)==1){
            strcpy(calificacion->codigoRequerimiento, idRQ);
            strcpy(calificacion->miembro, miembro);
            break;
        }else{
            printf("\n **El ID no corresponde con ninguna Asignacion registrada**\n ");
        }
    }while(1);
	
	
	printf("\n Ingrese la Calificacion de Requerimiento (1-100): \n");
	gets(calificacion->calificacion);
	printf("\n");
	calificacion->siguiente=NULL;
	calificacion->anterior=NULL;
	
    i = LC->inicio;
    while( i->siguiente!= NULL){
        if(strcmp(calificacion->codigoAsignacion, i->codigoAsignacion)==0){
			strcpy(i->codigoAsignacion, calificacion->codigoAsignacion);
			strcpy(i->codigoRequerimiento, calificacion->codigoRequerimiento);
            strcpy(i->miembro,calificacion->miembro);
            strcpy(i->calificacion,calificacion->calificacion);
            actualizar=1;
            break;
		}
        i = i->siguiente;
    }
	
	if(actualizar=1){
		actualizarCalificacion(LC);
	}else{
		guardarCalificacion(calificacion);
	}
		
	printf("\n\nPresione una tecla para regresar..." ); 
    getchar();	
}

/*
	Entradas: Una estructura Calificacion. 
	Salidas: Guardar los datos de la estructura en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void guardarCalificacion(Calificacion *calificacion){
	

	ArchCalificaciones=fopen("Archivos\\Calificaciones.txt","a+");
	if(ArchCalificaciones==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		fprintf(ArchCalificaciones,"%s\n%s\n%s\n%s\n", calificacion->codigoAsignacion, calificacion->codigoRequerimiento, calificacion->miembro,  calificacion->calificacion);
	}
	fclose(ArchCalificaciones);
	printf("\n ==>Informacion guardada<==.\n");
	
}

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
int cargarCalificaciones(struct ListaCalificaciones *L){
	
	struct Calificacion *aux;

	aux = (struct Calificacion *) malloc (sizeof(struct Calificacion));

	ArchCalificaciones = fopen("Archivos\\Calificaciones.txt","r");

	if(ArchCalificaciones==NULL){
		return 0;	
	}else{
	
		while(!feof(ArchCalificaciones)){
			fgets(aux->codigoAsignacion, 15, ArchCalificaciones);
			quitaFinLinea(aux->codigoAsignacion);
			fgets(aux->codigoRequerimiento, 15, ArchCalificaciones); 
			quitaFinLinea(aux->codigoRequerimiento);
			fgets(aux->miembro, 50, ArchCalificaciones); 
			quitaFinLinea(aux->miembro);
			fgets(aux->calificacion, 50, ArchCalificaciones);
			quitaFinLinea(aux->calificacion);		
						
			if(L->inicio == NULL){
				//Inserta al inicio de la lista
				L->inicio = (struct Calificacion *) malloc (sizeof(struct Calificacion));
				strcpy(L->inicio->codigoAsignacion , aux->codigoAsignacion);
				strcpy(L->inicio->codigoRequerimiento , aux->codigoRequerimiento);
				strcpy(L->inicio->miembro , aux->miembro ); 
				strcpy(L->inicio->calificacion , aux->calificacion); 
				L->inicio->siguiente = NULL; 
				L->inicio->anterior = NULL; 
				L->final = L->inicio;
	
			}else{
				//Inserta al final de la lista	
				L->final->siguiente =(struct Calificacion *) malloc (sizeof(struct Calificacion));
				strcpy(L->final->siguiente->codigoAsignacion , aux->codigoAsignacion);
				strcpy(L->final->siguiente->codigoRequerimiento , aux->codigoRequerimiento);
				strcpy(L->final->siguiente->miembro , aux->miembro ); 
				strcpy(L->final->siguiente->calificacion , aux->calificacion); 
				L->final->siguiente->siguiente = NULL; 
				L->final->siguiente->anterior = L->final; 
				L->final = L->final->siguiente;
			}		
		}
		fclose(ArchCalificaciones);		
	}	
	return 1;
}

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
NodoTopAsignacion* crearNodoAsignacion(char identificador[], int cantidad){
	NodoTopAsignacion *nuevo;
	nuevo = (NodoTopAsignacion *) malloc(sizeof(NodoTopAsignacion));
	nuevo->siguiente = NULL;
	strcpy(nuevo->identificador, identificador);
	nuevo->cantidad = cantidad;	
	
	return nuevo;
}

/*
	Entradas: 
	Salidas: 
	Restricciones: Ninguna.
*/
void ordenarTopAsignaciones(struct ListaTopAsignaciones *LT){

	struct NodoTopAsignacion *i, *j, *temp;

	temp=(struct NodoTopAsignacion *) malloc (sizeof(struct NodoTopAsignacion));
	
	i = LT->inicio;
	while( i->siguiente!= NULL){
		
		j = i->siguiente;
		while( j!= NULL){

			if(i->cantidad < j->cantidad){
				
				//Guardar los valores del nodo i
				temp->cantidad = i->cantidad;
				strcpy(temp->identificador,i->identificador);
				
				//Asignar los valores del nodo j al nodo i
				i->cantidad = j->cantidad;			
				strcpy(i->identificador, j->identificador);
				
				//Asignar los valores guardados del nodo i al nodo j
				j->cantidad = temp->cantidad;
				strcpy(j->identificador, temp->identificador);
				
			}			
			j = j->siguiente;
		}
		i = i->siguiente;
	}
	
} 

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
void consultarTopAsignaciones(){
	struct ListaAsignaciones *L;
	struct Asignacion *i, *j;
	struct ListaTopAsignaciones *LT;
	struct NodoTopAsignacion *nA;
	int  res=0, contAsignaciones=0, contado=0;
	char id[12];
	
	L = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
	L->inicio = NULL;
	L->final = NULL;
	
	LT = (struct ListaTopAsignaciones *) malloc(sizeof(struct ListaTopAsignaciones));
	LT->inicio = NULL;
	LT->final = NULL;

	res=cargarAsignaciones(L);

	if(res=1)
	{
		i = L->inicio;
		while( i->siguiente!= NULL){
			
			j = L->inicio;
			contAsignaciones=0;

			while( j->siguiente!= NULL){
					if(strcmp(i->identificador,j->identificador)==0){
						contAsignaciones++;	
					}
				j = j->siguiente;
			}
			
			//Agregar los datos a la listas del top de asignaciones
			for(nA = LT->inicio; nA!= NULL; nA = nA->siguiente){
				if(strcmp(i->identificador,nA->identificador)==0){
					contado=1;
					break;
				}
			}

			if(contado==0){
				if(LT->inicio == NULL) 
				{
					//Inserta al inicio de la cola
					LT->inicio = crearNodoAsignacion(i->identificador, contAsignaciones);
					LT->final = LT->inicio;
				}else{
					LT->final->siguiente = crearNodoAsignacion(i->identificador, contAsignaciones);
					LT->final = LT->final->siguiente;
				}	
				
			}
			contado=0;	
			
			i = i->siguiente;
		}
		
	}else{
		printf( "\n***No se han registrado Asignaciones***");
	}
	
	ordenarTopAsignaciones(LT);
	
	int top=0;
	nA = LT->inicio;
	printf("\n Identificador    Cantidad de Asignaciones \n");
	while(nA!= NULL && top!=5){
		printf("\n   %s                     %d", nA->identificador, nA->cantidad); 
		nA = nA->siguiente;
		top++;
	}
	
	//Liberar la cola
	liberarListaAsignaciones(L);

	fflush(stdin);
}

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
NodoTopHorario* crearNodoHorario(char identificador[], int cantidad){
	NodoTopHorario *nuevo;
	nuevo = (NodoTopHorario *) malloc(sizeof(NodoTopHorario));
	nuevo->siguiente = NULL;
	strcpy(nuevo->identificador, identificador);
	nuevo->cantidad = cantidad;	
	
	return nuevo;
}

/*
	Entradas: 
	Salidas: 
	Restricciones: Ninguna.
*/
void ordenarTopHorarios(struct ListaTopHorarios *LT){

	struct NodoTopHorario *i, *j, *temp;

	temp=(struct NodoTopHorario *) malloc (sizeof(struct NodoTopHorario));
	
	i = LT->inicio;
	while( i->siguiente!= NULL){
		
		j = i->siguiente;
		while( j!= NULL){

			if(i->cantidad < j->cantidad){
				
				//Guardar los valores del nodo i
				temp->cantidad = i->cantidad;
				strcpy(temp->identificador,i->identificador);
				
				//Asignar los valores del nodo j al nodo i
				i->cantidad = j->cantidad;			
				strcpy(i->identificador, j->identificador);
				
				//Asignar los valores guardados del nodo i al nodo j
				j->cantidad = temp->cantidad;
				strcpy(j->identificador, temp->identificador);
				
			}			
			j = j->siguiente;
		}
		i = i->siguiente;
	}
	
} 

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
void consultarTopHorarios(){
	struct ListaRequerimientos *L;
	struct Requerimiento *i, *j;
	
	struct ListaTopHorarios *LT;
	struct NodoTopHorario *nA;
	
	struct ListaOficinas *LOf;
    struct Oficina *iOf;
    
	int  res=0, res2=0, contOficina=0, contado=0;
	char id[12];
	
	L = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
	L->inicio = NULL;
	L->final = NULL;
	
	LT = (struct ListaTopHorarios *) malloc(sizeof(struct ListaTopHorarios));
	LT->inicio = NULL;
	LT->final = NULL;
	
	LOf = (struct ListaOficinas *) malloc(sizeof(struct ListaOficinas));
    LOf->inicio = NULL;
    LOf->final = NULL;

	res=cargarRequerimientos(L);

	if(res=1)
	{
		i = L->inicio;
		while( i->siguiente!= NULL){
			
			j = L->inicio;
			contOficina=0;

			while( j->siguiente!= NULL){
					if(strcmp(i->oficina,j->oficina)==0){
						contOficina++;	
					}
				j = j->siguiente;
			}
			
			//Agregar los datos a la listas del top de asignaciones
			for(nA = LT->inicio; nA!= NULL; nA = nA->siguiente){
				if(strcmp(i->oficina,nA->identificador)==0){
					contado=1;
					break;
				}
			}

			if(contado==0){
				if(LT->inicio == NULL) 
				{
					//Inserta al inicio de la cola
					LT->inicio = crearNodoHorario(i->oficina, contOficina);
					LT->final = LT->inicio;
				}else{
					LT->final->siguiente = crearNodoHorario(i->oficina, contOficina);
					LT->final = LT->final->siguiente;
				}	
				
			}
			contado=0;	
			
			i = i->siguiente;
		}
		
	}else{
		printf( "\n***No se han registrado Asignaciones***");
	}
	
	ordenarTopHorarios(LT);
	
	res2 = cargarOficinas(LOf);
			
	int top=0;
	nA = LT->inicio;
	printf("\n Oficina   Cantidad de Requerimientos \n");
	while(nA!= NULL && top!=5){
		printf("\n   %s                     %d\n", nA->identificador, nA->cantidad); 
		
		iOf = LOf->inicio;
        while(iOf->siguiente!= NULL){
            if (strcmp(iOf->codigo , nA->identificador)==1){
            	
                printf("\n   Horario de Operacion\n");
                printf("       - Dias de trabajo: %s \n", iOf->dias); 
                printf("       - Hora de Apertura: %s \n", iOf->horaApertura);
                printf("       - Hora de Cierre: %s \n", iOf->horaCierre);
				break;
            }
        	iOf = iOf->siguiente;
        }
        
        printf("+-------------------------------+\n");
				
		nA = nA->siguiente;
		top++;
	}
	
	//Liberar la cola
	liberarListaRequerimientos(L);

	fflush(stdin);
}

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
NodoTopMiembro* crearNodoMiembro(char identificador[], int cantidad){
	NodoTopMiembro *nuevo;
	nuevo = (NodoTopMiembro *) malloc(sizeof(NodoTopMiembro));
	nuevo->siguiente = NULL;
	strcpy(nuevo->identificador, identificador);
	nuevo->cantidad = cantidad;	
	
	return nuevo;
}

/*
	Entradas: 
	Salidas: 
	Restricciones: Ninguna.
*/
void ordenarTopMiembros(struct ListaTopMiembros *LT){

	struct NodoTopMiembro *i, *j, *temp;

	temp=(struct NodoTopMiembro *) malloc (sizeof(struct NodoTopMiembro));
	
	i = LT->inicio;
	while( i->siguiente!= NULL){
		
		j = i->siguiente;
		while( j!= NULL){

			if(i->cantidad < j->cantidad){
				
				//Guardar los valores del nodo i
				temp->cantidad = i->cantidad;
				strcpy(temp->identificador,i->identificador);
				
				//Asignar los valores del nodo j al nodo i
				i->cantidad = j->cantidad;			
				strcpy(i->identificador, j->identificador);
				
				//Asignar los valores guardados del nodo i al nodo j
				j->cantidad = temp->cantidad;
				strcpy(j->identificador, temp->identificador);
				
			}			
			j = j->siguiente;
		}
		i = i->siguiente;
	}
	
} 

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
void consultarTopMiembros(){
	struct ListaAsignaciones *L;
	struct Asignacion *i, *j;
	struct ListaTopMiembros *LT;
	struct NodoTopMiembro *nA;
	int  res=0, contMiembros=0, contado=0;
	char id[12];
	
	L = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
	L->inicio = NULL;
	L->final = NULL;
	
	LT = (struct ListaTopMiembros *) malloc(sizeof(struct ListaTopMiembros));
	LT->inicio = NULL;
	LT->final = NULL;

	res=cargarAsignaciones(L);

	if(res=1)
	{
		i = L->inicio;
		while( i->siguiente!= NULL){
			
			j = L->inicio;
			contMiembros=0;

			while( j->siguiente!= NULL){
					if(strcmp(i->miembros,j->miembros)==0){
						contMiembros++;	
					}
				j = j->siguiente;
			}
			
			//Agregar los datos a la listas del top de asignaciones
			for(nA = LT->inicio; nA!= NULL; nA = nA->siguiente){
				if(strcmp(i->miembros,nA->identificador)==0){
					contado=1;
					break;
				}
			}

			if(contado==0){
				if(LT->inicio == NULL) 
				{
					//Inserta al inicio de la cola
					LT->inicio = crearNodoMiembro(i->miembros, contMiembros);
					LT->final = LT->inicio;
				}else{
					LT->final->siguiente = crearNodoMiembro(i->miembros, contMiembros);
					LT->final = LT->final->siguiente;
				}	
				
			}
			contado=0;	
			
			i = i->siguiente;
		}
		
	}else{
		printf( "\n***No se han registrado Asignaciones***");
	}
	
	ordenarTopMiembros(LT);
	
	int top=0;
	nA = LT->inicio;
	printf("\n Cedula del Miembro    Cantidad de Asignaciones \n");
	while(nA!= NULL && top!=5){
		printf("\n   %s                     %d", nA->identificador, nA->cantidad); 
		nA = nA->siguiente;
		top++;
	}
	
	//Liberar la cola
	liberarListaAsignaciones(L);

	fflush(stdin);
}

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
NodoTopEsfuerzo* crearNodoEsfuerzo(char identificador[], int cantidad){
	NodoTopEsfuerzo *nuevo;
	nuevo = (NodoTopEsfuerzo *) malloc(sizeof(NodoTopEsfuerzo));
	nuevo->siguiente = NULL;
	strcpy(nuevo->identificador, identificador);
	nuevo->cantidad = cantidad;	
	
	return nuevo;
}

/*
	Entradas: 
	Salidas: 
	Restricciones: Ninguna.
*/
void ordenarTopEsfuerzo(struct ListaTopEsfuerzo *LT){

	struct NodoTopEsfuerzo *i, *j, *temp;

	temp=(struct NodoTopEsfuerzo *) malloc (sizeof(struct NodoTopEsfuerzo));
	
	i = LT->inicio;
	while( i->siguiente!= NULL){
		
		j = i->siguiente;
		while( j!= NULL){

			if(i->cantidad < j->cantidad){
				
				//Guardar los valores del nodo i
				temp->cantidad = i->cantidad;
				strcpy(temp->identificador,i->identificador);
				
				//Asignar los valores del nodo j al nodo i
				i->cantidad = j->cantidad;			
				strcpy(i->identificador, j->identificador);
				
				//Asignar los valores guardados del nodo i al nodo j
				j->cantidad = temp->cantidad;
				strcpy(j->identificador, temp->identificador);
				
			}			
			j = j->siguiente;
		}
		i = i->siguiente;
	}
	
} 

/*
	Entradas: 
	Salidas: 
	Restricciones: 
*/
void consultarTopEsfuerzo(){
	struct ListaRequerimientos *L;
	struct Requerimiento *i, *j;
	
	struct ListaTopEsfuerzo *LT;
	struct NodoTopEsfuerzo *nA;
	
	int  res=0, esfuerzo=0, contOficina=0, contado=0;
	char id[12];
	
	L = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
	L->inicio = NULL;
	L->final = NULL;
	
	LT = (struct ListaTopEsfuerzo *) malloc(sizeof(struct ListaTopEsfuerzo));
	LT->inicio = NULL;
	LT->final = NULL;

	res=cargarRequerimientos(L);

	if(res=1)
	{
		i = L->inicio;
		while( i->siguiente!= NULL){
					
			esfuerzo = atoi(i->esfuerzo);
			
			//Agregar los datos a la listas del top de asignaciones
			for(nA = LT->inicio; nA!= NULL; nA = nA->siguiente){
				if(strcmp(i->identificador,nA->identificador)==0){
					contado=1;
					break;
				}
			}

			if(contado==0){
				if(LT->inicio == NULL) 
				{
					//Inserta al inicio de la cola
					LT->inicio = crearNodoEsfuerzo(i->identificador, esfuerzo);
					LT->final = LT->inicio;
				}else{
					LT->final->siguiente = crearNodoEsfuerzo(i->identificador, esfuerzo);
					LT->final = LT->final->siguiente;
				}	
				
			}
			contado=0;	
			
			i = i->siguiente;
		}
		
	}else{
		printf( "\n***No se han registrado Asignaciones***");
	}
	
	ordenarTopEsfuerzo(LT);
	
	int top=0;
	nA = LT->inicio;
	printf("\n Identificador       Esfuerzo \n");
	while(nA!= NULL && top!=5){
		printf("\n   %s                %d\n", nA->identificador, nA->cantidad); 
				
		nA = nA->siguiente;
		top++;
	}
	
	//Liberar la cola
	liberarListaRequerimientos(L);

	fflush(stdin);
}

/*
	Entradas: Un dato que indique la cédula del Miembro del Equipo por consultar las Asignaciones
	Salidas: Los datos relacionado a las Asignaciones del Miembro consultado en caso de que existan, de lo contrario un mensaje indicando 
			que no se han encontrado.
	Restricciones: Ninguna
*/
void analisisDeDatos(int tipoAnalisis){

	system( "CLS" );
	printf("\n\n+--------------------------------------+\n");
	printf("        Gestor de Requerimientos       \n");
	printf("+--------------------------------------+\n");
	printf( "	     Analisis de Datos\n" );
	printf("+--------------------------------------+\n");
	
	switch(tipoAnalisis){
			case 1:
				printf( "Requerimientos con mas Asignaciones \n");
				printf("+--------------------------------------+\n");				
			
				consultarTopAsignaciones();
				
				break;
			case 2:
				printf(      "Horarios mas Utilizados \n");
				printf("+--------------------------------------+\n");				
			
				consultarTopHorarios();
				
				break;
			case 3:
				printf( "Miembros de Equipo con mas Asignaciones \n");
				printf("+--------------------------------------+\n");				
			
				consultarTopMiembros();
				
				break;
			case 4:
				printf( "  Requerimientos con mayor esfuerzo \n");
				printf("+-------------------------------------+\n");				
			
				consultarTopEsfuerzo();
				
				break;
		}
	
	 
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

/*
	Entradas: Un puntero a una lista de nodos de tipo struct Miembros de Equipo.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual señala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarColaMiembros(ColaMiembros *C){
	struct MiembroEquipo *n, *aux;
	if(C->inicio == NULL)
		return;
	if(C->inicio->siguiente == NULL)
		return;		
	n = C->inicio;
	
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
void liberarColaIncidentes(ColaIncidentes *C){
		
	struct Incidentes *n, *aux;
	if(C->inicio == NULL)
		return;
	if(C->inicio->siguiente == NULL)
		return;		
	n = C->inicio;
	
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
