/*Algoritmos y Estructuras de Datos - Grupo 1
	Proyecto Programado 1 
	Estudiantes: Jose Altamirano Salazar - 2020426159
	             Josu� Brenes Alfaro - 2020054427
*/
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE* ArchRequerimiento;
FILE* ArchMiembros;
FILE* ArchAsignaciones;
FILE* ArchIncidentes;
FILE* ArchCalificaciones;
FILE* ArchOficinas;

//Tipos para la gestion de los datos de cada elemento
typedef struct Requerimiento Requerimiento;
typedef struct MiembroEquipo MiembroEquipo;
typedef struct Asignacion Asignacion;
typedef struct Incidentes Incidentes;
typedef struct Calificacion Calificacion;
typedef struct Oficina Oficina;
typedef struct NodoTopAsignacion NodoTopAsignacion;
typedef struct NodoTopHorario NodoTopHorario;
typedef struct NodoTopMiembro NodoTopMiembro;
typedef struct NodoTopEsfuerzo NodoTopEsfuerzo;
typedef struct NodoPrioridad NodoPrioridad;

//Tipos para la construccion de las estructuras de datos
typedef struct ColaMiembros ColaMiembros;
typedef struct ColaIncidentes ColaIncidentes;
typedef struct ListaRequerimientos ListaRequerimientos;
typedef struct ListaAsignaciones ListaAsignaciones;
typedef struct ListaCalificaciones ListaCalificaciones;
typedef struct ListaOficinas ListaOficinas;
typedef struct ListaTopAsignaciones ListaTopAsignaciones;
typedef struct ListaTopHorarios ListaTopHorarios;
typedef struct ListaTopEsfuerzo ListaTopEsfuerzo;
typedef struct ListaTopMiembros ListaTopMiembros;
typedef struct PilaAsignaciones PilaAsignaciones;
typedef struct ColaPrioridad ColaPrioridad;

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
int validarNivelMiembro(const char identificador []);
int validarCedula(const char identificador []);
int validarNivelMiembro(const char identificador []);

//Procedimientos para Requerimientos
void registrarRequerimiento();
void guardarRequerimiento(Requerimiento *requerimiento);
int cargarRequerimientos(struct ListaRequerimientos *L);
void consultarRequerimiento();
int validarIDRequerimiento(const char identificador []);
void modificarRequerimiento();
void actualizarRequerimientos(struct ListaRequerimientos *L);
void modificarEstadoRQ(struct ListaRequerimientos *L, const char identificador[], int condicion);
int cargarOficinas(struct ListaOficinas *L);
void consultarOficinas();

//Procedimientos para Asignaciones
void registrarAsignacion();
void guardarAsignacion(Asignacion *asignacion);
int cargarAsignaciones(struct ListaAsignaciones *L);
void consultarAsignaciones();
void cancelarAsignacion();
void atencionAsignaciones();
int validarAsignaciones(const char identificador[]);
void ordenarAsignaciones(struct ListaAsignaciones *L);
int validarAsignacion(struct ListaAsignaciones *L, char idAsignacion[], char idRQ[], char idMiembro[]);
int validarHorario(ListaAsignaciones *L,  NodoPrioridad *np);
void actualizarAsignaciones(struct ListaAsignaciones *L );

//Procedimientos para Incidentes
void registrarIncidentes();
void guardarIncidentes(Incidentes *incidente);
int cargarIncidentes(struct ColaIncidentes *C);
void consultarIncidentes(int tipoConsulta);
int contarIncidentes (const char identificador[]);
int validarIncidentes(ColaIncidentes *C, const char identificador[]);

//Procedimientos para Calificaciones
void registrarCalificaciones();
void guardarCalificacion(Calificacion *calificacion);
void actualizarCalificacion(struct ListaCalificaciones *L);
void modificarCalificacion(struct ListaCalificaciones *L,  char idAsignacion[]);
void actualizarCalificacion(struct ListaCalificaciones *L);
double promedioCalificaciones(const char idRequerimiento[]);

//Procedimientos para An�lisis de Datos
void analisisDeDatos(int tipoAnalisis);
NodoTopAsignacion* crearNodoAsignacion(char identificador[], int cantidad);
void ordenarTopAsignaciones(struct ListaTopAsignaciones *LT);
void consultarTopAsignaciones();
NodoTopHorario* crearNodoHorario(char identificador[], int cantidad);
void ordenarTopHorarios(struct ListaTopHorarios *LT);
void consultarTopHorarios();
NodoTopMiembro* crearNodoMiembro(char identificador[], int cantidad);
void ordenarTopMiembros(struct ListaTopMiembros *LT);
void consultarTopMiembros();
NodoTopEsfuerzo* crearNodoEsfuerzo(char identificador[], int cantidad);
void ordenarTopEsfuerzo(struct ListaTopEsfuerzo *LT);
void consultarTopEsfuerzo();

//Procedimientos de Apoyo
int numeroAleatorio();
void obtenerFechaActual(char *hoy);
int compararCadenas(const char cadena1[], const char cadena2[]);
void quitaFinLinea(char linea[]);
void separarValoresFecha(char fecha[], int *d, int *m, int *a);
int compararFechas(char fecha1[], char fecha2[]);
void obtenerHoraActual(char *horaActual, char *minutoActual);
void separarHoras(char hora[], int *h, int *min );
int compararHoras(char hora[]);
int validarHoras(char horaRQ[], char horaAS[]);

//Procedimientos para liberar estructuras de datos
void liberarColaMiembros(ColaMiembros *C);
void liberarColaIncidentes(ColaIncidentes *C);
void liberarListaRequerimientos(ListaRequerimientos *L);
void liberarListaAsignaciones(ListaAsignaciones *L);
void liberarTopMiembros(ListaTopMiembros *L);
void liberarTopEsfuerzo(ListaTopEsfuerzo *L);
void liberarTopHorarios(ListaTopHorarios *L);
void liberarTopAsignaciones(ListaTopAsignaciones *L);
void liberarListaOficinas(ListaOficinas *L);
void liberarListaCalificaciones(ListaCalificaciones *L);
void liberarPilaAsignaciones(PilaAsignaciones *P);


struct Requerimiento{
    char identificador[50];
    char tipo[20];
    char descripcion[200];
    char riesgo[60];
    char dependencia[10];
    char recursos[55];
    char estado [15];
    char esfuerzo[5];
    char oficina [15];
    Requerimiento *siguiente;

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
    Asignacion *siguiente;
    
};

struct Incidentes{
    char codigoIncidente[15];
	char codigoRequerimiento[15];
    char codigoAsignacion[15];
    char descripcionIncidente[100];
    char fecha[20];
    Incidentes *siguiente;
};

struct Calificacion{
    char codigoRequerimiento[15];
    char codigoAsignacion[15];
    char miembro[30];
    char calificacion[10];
    Calificacion *siguiente;
};

struct Oficina{
    char codigo[50];
    char dias[30];
    char horaApertura[15];
    char horaCierre[15];
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

struct NodoTopAsignacion{
	char identificador[15];
	int cantidad;
	NodoTopAsignacion *siguiente;
};

struct ListaTopAsignaciones{
	NodoTopAsignacion *inicio;
	NodoTopAsignacion *final;
};

struct NodoTopHorario{
	char identificador[15];
	int cantidad;
	NodoTopHorario *siguiente;
};

struct ListaTopHorarios{
	NodoTopHorario *inicio;
	NodoTopHorario *final;
};

struct NodoTopMiembro{
	char identificador[15];
	int cantidad;
	NodoTopMiembro *siguiente;
};

struct ListaTopMiembros{
	NodoTopMiembro *inicio;
	NodoTopMiembro *final;
};

struct NodoTopEsfuerzo{
	char identificador[15];
	int cantidad;
	NodoTopEsfuerzo *siguiente;
};

struct ListaTopEsfuerzo{
	NodoTopEsfuerzo *inicio;
	NodoTopEsfuerzo *final;
};

struct PilaAsignaciones{
	Asignacion *tope;
};

struct NodoPrioridad{
	char prioridad[10];
	Asignacion *asignacion;
	NodoPrioridad *siguiente;
	
};

struct ColaPrioridad{
	NodoPrioridad *frente;
	NodoPrioridad *final;

};

/****************************************************************Men�s de Opciones***********************************************************************************************/

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
		printf( "\n 5 - Reportes de la Aplicacion" );   
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
	         Si el n�mero ingresado es 2 se llama a la funci�n consultarMiembroEquipo().
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
	Entradas: Un n�mero (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el men�. 
	Salidas: en caso de que el n�mero ingresado sea 0 se devuelve al men� principal, si el n�mero es 1 se a llama la funcion registrarRequerimiento(), 
	         Si el n�mero ingresado es 2 se llama a la funci�n modificarRequerimiento(), Si el n�mero ingresado es 3 se llama a la funci�n registrarCalificaciones(),
	         Si el n�mero ingresado es 4 se llama a la funci�n consultarRequerimiento().
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
	Entradas: Un n�mero (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el men�. 
	Salidas: en caso de que el n�mero ingresado sea 0 se devuelve al men� principal, si el n�mero es 1 se a llama la funcion registrarAsignacion(), 
	         Si el n�mero ingresado es 2 se llama a la funci�n consultarAsignaciones(), Si el n�mero ingresado es 3 se llama a la funci�n cancelarAsignacion(),
	         Si el n�mero ingresado es 4 se llama a la funci�n atencionAsignaciones().
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
				case '4': atencionAsignaciones();
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
	Entradas: Un n�mero (tipo char) en un rango de 0 a 2 para escoger una de las opciones disponibles en el men�. 
	Salidas: en caso de que el n�mero ingresado sea 0 se devuelve al men� principal, si el n�mero es 1 se a llama la funcion registrarIncidentes(), 
	         Si el n�mero ingresado es 2  o 3 se llama a la funci�n consultarIncidentes, con los par�metros respectivos.
	Restricciones: Solo se deben ingresar n�meros en un rango de 0 a 2.
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
	Entradas: Un n�mero (tipo char) en un rango de 0 a 4 para escoger una de las opciones disponibles en el men�. 
	Salidas: en caso de que el n�mero ingresado sea 0 se devuelve al men� principal, si el n�mero es un valor entre 1 y 4 se llama a la funci�n analisisDeDatos()
			con el par�metro que indique la opcion seleccionada.
	Restricciones: Solo se deben ingresar n�meros en un rango de 0 a 4.
*/
void AnalisisDeDatos(){
	char opcion, ch;	

	do{
		system( "CLS" );
		fflush(stdin);
        printf("\n\n+-------------------------------+\n");
		printf("      Gestor de Requerimientos          \n");
		printf("+-------------------------------+\n");
		printf( "    Reportes de la Aplicacion\n" );
		printf("+-------------------------------+\n");
		printf("\n 0. Volver al Menu Principal.");
		printf("\n 1. Mostrar requerimientos con mas asignaciones.");
		printf("\n 2. Mostrar horarios mas utilizados.");
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

/****************************************************************Procedimientos de Apoyo***********************************************************************************************/

/*
	Entradas: Ninguna.
	Salidas: Un valor entero aleatorio entre 1 y 3.
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
	Entradas: Un puntero a una cadena de caracteres.
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
void separarValoresFecha(char fecha[], int *d, int *m, int *a){
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
	separarValoresFecha(fecha1, &d1, &m1, &a1);
	//Obtener valores fecha 2
	separarValoresFecha(fecha2, &d2, &m2, &a2);
		
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
    Entradas: Un puntero a una cadena de caracteres.
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
    Entradas: Un puntero a una cadena de caracteres y dos punteros a enteros.
    Salidas: los valores de horaas y minutos extraidos de la cadena recibida, se asignan a los dos punteros recidos por par�metro.
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
    Entradas: Dos cadenas de caracteres con formato de hora (hh:mm).
    Salidas: 1 si la hora actual es almenos una hora menor que la hora recibida y -1 si la hora actual es mayor.
    Restricciones: Ninguna.
*/
int compararHoras(char hora[]){

    int h=0;
    int min=0;
    int horaActual=0;
    int minutoActual=0;
    char x[4], y[4], aux[10];
    strcpy(aux,hora);
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
        else
		{
            if((minutoActual<=min)){
                return 1;
            }else{
                return -1;
            }
        }
    }

}

/*
	Entradas: Dos cadenas de caracteres con los valores de dos horas con el formato hh:mm
	Salidas: 1 indica que la hora del del requerimiento es mayor que la de la asignacion
			 2 indica que la hora del del requerimiento es menor que la de la asignacion
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

/****************************************************************Procedimientos para Miembros de Equipo*********************************************************************************/

/*
	Entradas: Los diferentes objetos de la estructura Miembro de Equipo(nombre, cedula, correo, telefono, nivel  
	          de acceso). 
	Salidas: Llama a la funci�n guardarMiembro para guardar los datos al registrarlos en un archivo .txt. 
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
    int acceso=0;

    miembro=(struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));

    do{
        printf("\n Ingrese la Cedula: (Ejm.105450656) \n");
        gets(miembro->cedula);

        if(validarCedula(miembro->cedula)==1){
            printf("\n**Esta cedula ya ha sido registrada**\n ");
        }else{
            break;
        }
    }while(1);
    
    printf("\n Ingrese el Nombre Completo: (Ejm.Juan Perez) \n");
    gets(miembro->nombre_completo);
    printf("\n Ingrese el Correo Electronico: (ejemplousuario@correo.com) \n");
    gets(miembro->correo);
    
    do{
        printf("\n Ingrese el Nivel de Acceso (1-10) : \n");
        gets(miembro->nivel_acceso);
        acceso=atoi(miembro->nivel_acceso);
        if( acceso>=1 && acceso<=10 ){
            break;
        }
        printf("\n**El numero que ingrese debe estar en el rango de 1 a 16**\n");
    }while(1);
    
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
	Entradas: Un puntero a una lista del tipo ColaMiembros de Miembros de equipo.
	Salidas: Una lista  enlazada con los diferentes objetos de la estructura Miembro de Equipo(nombre, 
			cedula, correo, telefono, nivel de acceso).
	Restricciones: Ninguna.
*/
int cargarMiembros(struct ColaMiembros *C){
	
	struct MiembroEquipo *aux;

	

	ArchMiembros = fopen("Archivos\\MiembroEquipo.txt","r");

	if(ArchMiembros==NULL){
		return 0;
	}else{
		while(!feof(ArchMiembros)){
			aux =(struct MiembroEquipo *) malloc (sizeof(struct MiembroEquipo));
			
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
				C->inicio = aux;
				C->inicio->siguiente = NULL; 
				C->final = C->inicio;
	
			}else{	
				//Inserta al final de la lista	
				C->final->siguiente = aux; 
				C->final->siguiente->siguiente = NULL; 
				C->final = C->final->siguiente;
			}		
		}
		fclose(ArchMiembros);
	}	
	return 1;
		
}

/*
	Entradas: Ninguna.
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
					
					if(resAsignacion==1)
                	{
	
                    iAsig = LAsig->inicio;
                    while( iAsig->siguiente!= NULL){
                        if(compararCadenas(iAsig->miembros, i->cedula)==1){
                            val2=0;
                            printf("\n~~~~Datos de la Asignacion~~~~\n");
                            printf("Asignacion Numero: %s \n", iAsig->codigoAsignacion);
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
									
									if(resIncidente==1)
                					{
									
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
                    printf( "\nNo tiene requerimentos asignados");
                }

                break;
            }
            i = i->siguiente;
        }
        if(val!=0){
            printf( "\n**Miembro no encontrado**");
        }

    }else{
        printf( "\n**No se ha registrado ningun Miembro*");
    }
    liberarColaMiembros(C);
    liberarColaIncidentes(CIncidente);
    liberarListaAsignaciones(LAsig);
    liberarListaRequerimientos(LReque);
    
    printf("\n\nPresione una tecla para regresar..." ); 
    getchar();
    fflush(stdin);
}

/*
    Entradas: Una cadena de caracteres que indique la cedula del Miembro de Equipo
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
    Entradas: Una cadena de caracteres que indique la cedula del Miembro de Equipo
    Salidas: -1 si el nivel del miembro es menor o igual que 3, 1 si es mayor que 3.
    Restricciones: Ninguna.
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

/****************************************************************Procedimientos para Requerimientos***********************************************************************************************/

/*
	Entradas: Los diferentes objetos de la estructura Requerimiento(identificador, tipo, descripcion, riesgo, 
	           dependencia, recursos, esfuerzo). 
	Salidas: Llama a la funci�n guardarRequerimiento para guardar los datos al registrarlos en un archivo .txt. 
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
	
	 int esfuerzo=0;

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
	printf("\n Ingrese el riesgo: \n");
	gets(requerimiento->riesgo);
	printf("\n Ingrese la dependencia: (Ejm. RQ-001) \n");
	gets(requerimiento->dependencia);
	printf("\n Ingrese los recursos:\n");
	gets(requerimiento->recursos);
	strcpy(requerimiento->estado, "Por hacer");
	
	do{
        printf("\n Ingrese el esfuerzo: ( 1...16 ) \n");
        gets(requerimiento->esfuerzo);
        esfuerzo=atoi(requerimiento->esfuerzo);
        if( esfuerzo>=1 && esfuerzo<=16 ){
            break;
        }
        printf("\n**El numero que ingrese debe estar en un rango de 1 a 16**\n");
    }while(1);
	
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
	Entradas: Un puntero a una lista del tipo ListaRequerimientos de Requerimientos.
	Salidas: Una lista   enlazada con los diferentes objetos de la estructura Requerimiento(identificador, tipo, 
			descripcion, riesgo, dependencia, recursos, esfuerzo).
	Restricciones: Ninguna.
*/
int cargarRequerimientos(struct ListaRequerimientos *L){

	struct Requerimiento *requerimiento, *aux;
		
	

	ArchRequerimiento = fopen("Archivos\\Requerimientos.txt","r");

	if(ArchRequerimiento==NULL){
		return 0;	
	}else{

		while(!feof(ArchRequerimiento)){
			aux = (struct Requerimiento *) malloc(sizeof(struct Requerimiento));
			
			fgets(aux->identificador, 50, ArchRequerimiento); 
			quitaFinLinea(aux->identificador);
			fgets(aux->tipo, 20, ArchRequerimiento); 
			quitaFinLinea(aux->tipo);
			fgets(aux->descripcion, 200, ArchRequerimiento);
			quitaFinLinea(aux->descripcion);			
			fgets(aux->riesgo, 60, ArchRequerimiento);
			quitaFinLinea(aux->riesgo);
			fgets(aux->dependencia, 10, ArchRequerimiento);
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
				L->inicio = aux;
				L->inicio->siguiente = NULL; 
				L->final = L->inicio;
	
			}else{	
				//Inserta al final de la lista	
				L->final->siguiente = aux;
				L->final->siguiente->siguiente = NULL; 
				L->final = L->final->siguiente;
			}		
		}
		
		fclose(ArchRequerimiento);	
	}	
	
	return 1;
}

/*
	Entradas: Una cadena de caracteres que indique el identificador del Requerimiento por consultar
	Salidas: Los datos relacionado al Requerimiento consultado en caso de que existan, de lo contrario un mensaje indicando 
			que no se ha encontrado.
	Restricciones: Ninguna
*/
void consultarRequerimiento(){

    struct ListaRequerimientos *L;
    struct Requerimiento *i;
    
    struct ListaOficinas *LOf;
    struct Oficina *iOf;
    
    struct ListaAsignaciones *LAsig;
    struct Asignacion *iAsig;

    int val=3, val2=3, res=0, res2=0, resAsignacion=0;;
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
    
    LAsig = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
    LAsig->inicio = NULL;
    LAsig->final = NULL;

    res = cargarRequerimientos(L);  
    res2 = cargarOficinas(LOf);
    resAsignacion=cargarAsignaciones(LAsig);

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
                printf(" Calificacion Promedio: %.2f \n", promedioCalificaciones(i->identificador));
                
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
                
                printf("\n     ~~Asignacion para el requerimiento~~~\n");
            	if(resAsignacion==1)
			    {
			
			        iAsig = LAsig->inicio;
			        while( iAsig->siguiente!= NULL){
			            if(compararCadenas(iAsig->identificador, i->identificador)==1){
			                val2=0;
			                
			                printf("        Asignacion Numero: %s \n", iAsig->codigoAsignacion);
			                printf("        Descripcion: %s \n", iAsig->descripcion);
			                printf("        Priodidad: %s \n", iAsig->prioridad ); 
			                printf("        Estado: %s \n", iAsig->estado);
			                printf("     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
			                   
			            }
			            iAsig = iAsig->siguiente;
			            
			        }
			    }else{
			        printf( "\n**No se tienen asignaciones registradas**");
			    }
                if(val2==3){
			        printf( "\n**El requerimiento no tiene asignaciones registradas**");               
	            }
                
                printf("\n+-------------------------------+\n");

            }
            i = i->siguiente;
        }

        if(val == 1){
            printf( "\n**Requerimiento no encontrado***");
        }
    }else{		
		printf("\n**No se ha registrado ningun requerimiento***");
	}
	
	liberarListaRequerimientos(L);
	liberarListaOficinas(LOf);	
    printf("\n\nPresione una tecla para regresar..." ); 
    getchar();
    fflush(stdin);
}

/*
	Entradas: Una cadena de caracteres que indique el identificador del Requerimiento
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
	Salidas: Llama a la funci�n actualizarRequerimiento para guardar los datos al registrarlos en un archivo .txt. 
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
		printf("\n**No se ha registrado ningun requerimiento***");
	}
	
	actualizarRequerimientos(L);
	liberarListaRequerimientos(L);
		
	//guardarRequerimiento(requerimiento);
	getchar();	
}

/*
	Entradas: Un puntero a una lista del tipo ListaRequerimientos de Requerimientos.
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
}

/*
	Entradas: Un objeto de tipo estado de la estructura Requerimiento y una cadena de caracteres que indique el identificador del Requerimiento.
	Salidas: Se actualiza el estado del requerimiento y se llama a la funci�n actualizaRequerimiento para guardar los datos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void modificarEstadoRQ(struct ListaRequerimientos *L, const char identificador[], int condicion){
	struct Requerimiento *i;
	char id[15];
	int val;
	
    i = L->inicio;
    while( i->siguiente!= NULL){
        if(strcmp(i->identificador, identificador)==0){
			if(condicion == 1){
				strcpy(i->estado, "Activo");
			}else{
				strcpy(i->estado, "Asignado");
			}					
		}
        i = i->siguiente;
    }

	actualizarRequerimientos(L);	
}

/*
	Entradas: Un puntero a una lista del tipo ListaOficinas de Oficinas.
	Salidas: Una lista enlazada con los diferentes objetos de la estructura Asignacion (codgo, dias, horaApertura, horaCierre). 
	Restricciones: Ninguna.
*/
int cargarOficinas(struct ListaOficinas *L){
	
	struct Oficina *oficina, *aux;

	ArchOficinas = fopen("Archivos\\Oficinas.txt","r");

	if(ArchOficinas==NULL){
		return 0;	
	}else{

		while(!feof(ArchOficinas)){
			
			aux =(struct Oficina *) malloc (sizeof(struct Oficina));
			
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
				L->inicio = aux;
				L->inicio->siguiente = NULL; 
				L->final = L->inicio;
	
			}else{	
				//Inserta al final de la lista	
				L->final->siguiente = aux;
				L->final->siguiente->siguiente = NULL;
				L->final = L->final->siguiente;
			}		
		}
		fclose(ArchAsignaciones);
	}	
	return 1;
}

/*
	Entradas: Ninguna
			que no se han encontrado.
	Salidas: Los datos relacionado a las Oficinas registradas, sus dias laborales y horas de apertur y cierre.
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
	
	liberarListaOficinas(L);
}

/****************************************************************Procedimientos para Asignaciones***********************************************************************************************/

/*
	Entradas: Los diferentes objetos de la estructura Asignacion(fechaSolicitud, horaInicio, horaFin, recurso, identificador 
			descripcion, miembros, prioridad y estado). 
	Salidas: Llama a la funci�n guardarAsignacion para guardar los datos al registrarlos en un archivo .txt. 
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
	int prioridad=0, val0=0, val1=0, val2=0, val3=0, res=0, res2=0, res3=0, contRQ=0;
	
	asignacion=(struct Asignacion *) malloc (sizeof(struct Asignacion));
	
	char fecha [50];
	char hRQ_Inicio[10], hRQ_Fin[10], hAS_Inicio[10], hAS_Fin[10];
	char idRQ [15], miembro[15];
	
	struct ListaRequerimientos *LRQ;
    struct Requerimiento *iRQ;
    
    struct ListaOficinas *LOf;
    struct Oficina *iOf;
    
    struct ListaAsignaciones *LA;
	
	LRQ = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
    LRQ->inicio = NULL;
    LRQ->final = NULL;
    
    res = cargarRequerimientos(LRQ);
    
    if(res==1){
    	LOf = (struct ListaOficinas *) malloc(sizeof(struct ListaOficinas));
	    LOf->inicio = NULL;
	    LOf->final = NULL;
		
		
		LA = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
		LA->inicio = NULL;
		LA->final = NULL;
	
		res3=cargarAsignaciones(LA);
			
		do{
	        printf("\n Ingrese el Codigo de la Asignacion: (Ejm. AS-001) \n");
			gets(asignacion->codigoAsignacion);
			
			if(res3==1){
				if(validarAsignacion(LA, asignacion->codigoAsignacion, idRQ, miembro)==1){
					printf("\n **El codigo ingresado corresponde una Asignacion registrada**\n ");        
		        }else{
		        	break;  
		        }
			}else{
				break;
			}
		        
	    }while(1);
		
		obtenerFechaActual(fecha);
		strcpy(asignacion->fechaSolicitud, fecha);
		
		printf("\n Ingrese la Cedula del Miembro: (Ejm. 105450656) \n");
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
		printf("\n Ingrese el Recurso (Opcional): \n");
		gets(asignacion->recurso);
		
			
		res3 = cargarOficinas(LOf);
	
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
	            		contRQ++;
	            	}
	            }
	        	iOf = iOf->siguiente;
	        }
	    	iRQ = iRQ->siguiente;
	    }
	    
	    if(contRQ==0){
	    	printf("\n***No fue posible encontrar un requerimiento que cumpla con las condicion de busqueda***");
			printf("\n\nPresione una tecla para regresar..." ); 
			getchar();
			return;
		}
	    
	    printf("\n+-----------------------------------------------------------------------------------+\n");           
		printf("\n Ingrese el ID del Requerimiento: \n");
		gets(asignacion->identificador);
		
		val2=contarIncidentes(asignacion->identificador);
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
		modificarEstadoRQ(LRQ, asignacion->identificador, 1);
	
		guardarAsignacion(asignacion);
		
		printf("\n ==>Informacion guardada<==.\n");
		
		liberarListaAsignaciones(LA);
		liberarListaOficinas(LOf);
		
	
	}else{
		printf("\n***No es posible completar la asignacion, no se ha resgistrado\n   ningun requerimiento***");
		printf("\n\nPresione una tecla para regresar..." ); 
	}
	
	
    liberarListaRequerimientos(LRQ);
    free(asignacion);
    
    	
	
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();	
}

/*
	Entradas: Una estructura Asignaci�n. 
	Salidas: Guardar los datos de la estructura en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void actualizarAsignaciones(struct ListaAsignaciones *L ){
	
	struct Asignacion *asignacion;
	
	 if (remove("Archivos\\Asignaciones.txt") != 0)
	 	return;
	
	ArchAsignaciones=fopen("Archivos\\Asignaciones.txt","a+");
	if(ArchAsignaciones==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		asignacion = L->inicio;
        while( asignacion->siguiente!= NULL){
			fprintf(ArchAsignaciones,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", asignacion->codigoAsignacion, asignacion->fechaSolicitud, asignacion->horaInicio, asignacion->horaFin, asignacion->recurso, asignacion->identificador, 
																				 asignacion->descripcion,  asignacion->miembros, asignacion->prioridad, asignacion->estado);
            asignacion = asignacion->siguiente;
        }
		
	}
	
	fclose(ArchAsignaciones);

}

/*
	Entradas: Una estructura Asignaci�n. 
	Salidas: Guardar los datos de la estructura en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void guardarAsignacion (Asignacion *asignacion){
	
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
	Entradas: Un puntero a una lista del tipo ListaAsignaciones de Asignaciones.
	Salidas: Una lista enlazada con los diferentes objetos de la estructura Asignacion (fechaSolicitud, horaInicio, 
			horaFin, recurso, identificador, descripcion, miembros, prioridad y estado). 
	Restricciones: Ninguna.
*/
int cargarAsignaciones(struct ListaAsignaciones *L){
	
	struct Asignacion *asignacion, *aux;

	ArchAsignaciones = fopen("Archivos\\Asignaciones.txt","r");

	if(ArchAsignaciones==NULL){
		return 0;	
	}else{

		while(!feof(ArchAsignaciones)){
			aux =(struct Asignacion *) malloc (sizeof(struct Asignacion));
			
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
				L->inicio = aux;
				L->inicio->siguiente = NULL; 
				L->final = L->inicio;
	
			}else{	
				//Inserta al final de la lista	
				L->final->siguiente = aux; 
				L->final->siguiente->siguiente = NULL; 
				L->final = L->final->siguiente;
			}		
		}
		fclose(ArchAsignaciones);
	}	
	return 1;
}

/*
	Entradas: Un puntero a una pila del tipo PilaAsignaciones de Asignaciones.
	Salidas: Una pila con los diferentes objetos de la estructura Asignacion (fechaSolicitud, horaInicio, 
			horaFin, recurso, identificador, descripcion, miembros, prioridad y estado). 
	Restricciones: Ninguna.
*/
int cargarPilaAsignaciones(struct PilaAsignaciones *P){
	
	struct Asignacion *nuevo, *i;

	ArchAsignaciones = fopen("Archivos\\Asignaciones.txt","r");

	if(ArchAsignaciones==NULL){
		return 0;	
	}else{

		while(!feof(ArchAsignaciones)){
			
			nuevo =(struct Asignacion *) malloc (sizeof(struct Asignacion));
			
			fgets(nuevo->codigoAsignacion, 15, ArchAsignaciones); 
			quitaFinLinea(nuevo->codigoAsignacion);
			fgets(nuevo->fechaSolicitud, 50, ArchAsignaciones); 
			quitaFinLinea(nuevo->fechaSolicitud);
			fgets(nuevo->horaInicio, 15, ArchAsignaciones); 
			quitaFinLinea(nuevo->horaInicio);
			fgets(nuevo->horaFin, 15, ArchAsignaciones);
			quitaFinLinea(nuevo->horaFin);	
			fgets(nuevo->recurso, 50, ArchAsignaciones);
			quitaFinLinea(nuevo->recurso);		
			fgets(nuevo->identificador, 10, ArchAsignaciones);
			quitaFinLinea(nuevo->identificador);
			fgets(nuevo->descripcion, 100, ArchAsignaciones);
			quitaFinLinea(nuevo->descripcion);
			fgets(nuevo->miembros, 15, ArchAsignaciones);
			quitaFinLinea(nuevo->miembros);
			fgets(nuevo->prioridad, 15, ArchAsignaciones);
			quitaFinLinea(nuevo->prioridad);
			fgets(nuevo->estado, 15, ArchAsignaciones);
			quitaFinLinea(nuevo->estado);
			
			nuevo->siguiente = P->tope;
			P->tope = nuevo;
				
		}
		fclose(ArchAsignaciones);
		
	}	
	return 1;
}

/*
	Entradas: Un puntero a una pila del tipo PilaAsignaciones de Asignaciones.
	Salidas: Una pila con los diferentes objetos de la estructura Asignacion (fechaSolicitud, horaInicio, 
			horaFin, recurso, identificador, descripcion, miembros, prioridad y estado). 
	Restricciones: Ninguna.
*/
void cargarColaPrioridad(struct ColaPrioridad *CP, struct ListaAsignaciones *L){
	
	struct Asignacion *i;
	struct NodoPrioridad *nodoPrioridad;

	for(i = L->inicio; i!= NULL; i = i->siguiente){
		if(strcmp(i->prioridad, "ALTA")==0){
			nodoPrioridad = (struct NodoPrioridad *) malloc (sizeof(struct NodoPrioridad));
			nodoPrioridad->asignacion = i;
			strcpy(nodoPrioridad->prioridad, "ALTA");
			nodoPrioridad->siguiente=NULL;
			
			if(CP->frente == NULL){
				//Inserta el primer nodo
				CP->frente = nodoPrioridad;
				CP->frente->siguiente = NULL; 
				CP->final = CP->frente;
	
			}else{				
				//Inserta al final de la cola	
				CP->final->siguiente = nodoPrioridad; 
				CP->final->siguiente->siguiente = NULL; 
				CP->final = CP->final->siguiente;
			}			
		}
	}
	
	for(i = L->inicio; i!= NULL; i = i->siguiente){
		if(strcmp(i->prioridad, "MEDIA")==0){
			nodoPrioridad = (struct NodoPrioridad *) malloc (sizeof(struct NodoPrioridad));
			nodoPrioridad->asignacion = i;
			strcpy(nodoPrioridad->prioridad, "MEDIA");
			nodoPrioridad->siguiente=NULL;
			
			if(CP->frente == NULL){
				//Inserta el primer nodo
				CP->frente = nodoPrioridad;
				CP->frente->siguiente = NULL; 
				CP->final = CP->frente;
	
			}else{				
				//Inserta al final de la cola	
				CP->final->siguiente = nodoPrioridad; 
				CP->final->siguiente->siguiente = NULL; 
				CP->final = CP->final->siguiente;
			}			
		}
	}
	
	for(i = L->inicio; i!= NULL; i = i->siguiente){
		if(strcmp(i->prioridad, "BAJA")==0){
			nodoPrioridad = (struct NodoPrioridad *) malloc (sizeof(struct NodoPrioridad));
			nodoPrioridad->asignacion = i;
			strcpy(nodoPrioridad->prioridad, "BAJA");
			nodoPrioridad->siguiente=NULL;
			
			if(CP->frente == NULL){
				//Inserta el primer nodo
				CP->frente = nodoPrioridad;
				CP->frente->siguiente = NULL; 
				CP->final = CP->frente;
	
			}else{				
				//Inserta al final de la cola	
				CP->final->siguiente = nodoPrioridad; 
				CP->final->siguiente->siguiente = NULL; 
				CP->final = CP->final->siguiente;
			}			
		}
	}
	
}

/*
	Entradas: Un dato que indique la c�dula del Miembro del Equipo por consultar las Asignaciones
	Salidas: Los datos relacionado a las Asignaciones del Miembro consultado en caso de que existan, de lo contrario un mensaje indicando 
			que no se han encontrado.
	Restricciones: Ninguna
*/
void consultarAsignaciones(){

	struct PilaAsignaciones *P;
	struct Asignacion *i;
	int val=0, val2=0, res=0, res2=0;
	char id[12];
	
	struct ListaCalificaciones *LC;
	LC = (struct ListaCalificaciones *) malloc(sizeof(struct ListaCalificaciones));
    LC->inicio = NULL;
    LC->final = NULL;
    
    struct Calificacion *aux;
	
	system( "CLS" );
	printf("\n\n+-------------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------------+\n");
	printf( "Consultar Asignaciones de un Miembro\n" );
	printf("+-------------------------------------+\n");
	
	printf("\n Ingrese la cedula del miembro: (Ejm.304560789) \n ");
	gets(id);

	P = (struct PilaAsignaciones *) malloc(sizeof(struct PilaAsignaciones));
	P->tope = NULL;

	res=cargarPilaAsignaciones(P);

	if(res==1)
	{
		printf("\n+-------------------------------+\n");
		for(i = P->tope; i!= NULL; i = i->siguiente){
			if(strcmp(id,i->miembros)==0){
				printf("       Asignacion: %s \n", i->codigoAsignacion);
				printf("  Fecha de Solicitud: %s \n", i->fechaSolicitud);
				printf("  Hora de Inicio: %s \n", i->horaInicio ); 
				printf("  Hora de Fin: %s \n", i->horaFin); 
				printf("  Requerimiento: %s \n", i->identificador); 
				printf("  Recurso: %s \n", i->recurso); 
				printf("  Descripcion: %s \n", i->descripcion);
				printf("  Miembros: %s \n", i->miembros); 
				printf("  Priodidad: %s \n", i->prioridad ); 
				printf("  Estado: %s \n", i->estado); 
				
				res2=cargarCalificaciones(LC);
	
				if(res2 == 0){	
					printf("  Calificacion: sin registrar \n");	
				}else{		
					aux = LC->inicio;
					while( aux->siguiente!= NULL){	
				        if(strcmp(aux->codigoAsignacion, i->codigoAsignacion)==0){   
							printf("  Calificacion: %s \n", aux->calificacion); 
							val2=1;
							break;
				        }
						aux = aux->siguiente;
					}
					
					if(val2==0){
						printf("  Calificacion: sin registrar \n");				
					}
					
				}
				
				printf("+-------------------------------+\n");
				val=1;
			}
		}
		
		if(val==0){
			printf( "\n***No se han registrado Asignaciones para este miembro***");
		}
		
	}else{
		printf( "\n***No se han registrado Asignaciones***");
	}
	
	liberarListaCalificaciones(LC);
	liberarPilaAsignaciones(P);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

/*
    Entradas: Un ID determinado en la tabla que se presenta de Asiganciones. 
    Salidas: Se cambia el estado de la asignacion escogida por el ID a Cancelada . 
    Restricciones: No valida.
*/
void cancelarAsignacion(){
	
    struct ListaAsignaciones *L;
    struct ListaCalificaciones *LC;
    struct Asignacion *i, *j;
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
    
    if(res==1)
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
        printf("\nNo se han registrado Asignaciones");
        
        printf("\nPresione una tecla para regresar..." ); 
        getchar();
        return;
        
    }
	int eliminar=0;
    printf("Ingrese el numero del ID de la asignacion que desea cancelar: ");
    gets(seleccion);
    
    j = L->inicio;
    while(j->siguiente!=NULL){
        if (strcmp( j->codigoAsignacion , seleccion)==0){
            if(compararHoras(j->horaInicio)==-1){
                printf("\n+----------------------------------------------------------------------------------+\n");
                printf("  La asignacion no puede cancelarse si se tiene menos de una para su hora de inicio\n  o si esta ya ha iniciado.");
                printf("\n+----------------------------------------------------------------------------------+\n"); 

                printf("\nPresione una tecla para regresar..." ); 
                getchar();
                return;
            }else{
            	strcpy(j->estado,"Cancelada");
                break;
               
            }
            //break;
        }
        j = j->siguiente;
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
    
    //Actualizar la calificaion del miembro, seg�n la asignacion cancelada
	LC = (struct ListaCalificaciones *) malloc(sizeof(struct ListaCalificaciones));
    LC->inicio = NULL;
    LC->final = NULL;
    
    
	res2=cargarCalificaciones(LC);
	if(res2==1){
		modificarCalificacion(LC, seleccion);
	}
	
    printf("\n\nPresione una tecla para regresar..." ); 
    getchar();
    fflush(stdin);
}

/*
    Entradas: Un puntero a una lista de asignaciones y un puntero a un NodoPrioridad.
    Salidas: 1 si la asignacion consultada cumpe con las condiciones para ser aprobada o -1 si no cumple alguna de als condiciones.
    Restricciones: No valida.
*/
int validarHorario(ListaAsignaciones *L,  NodoPrioridad *np){

    struct Asignacion *i;

    i = L->inicio;
    while( i->siguiente!= NULL){
    	
    	if (strcmp( i->identificador , np->asignacion->identificador )==0 && strcmp( i->estado, "Aprobada" )==0){
			if ((validarHoras(i->horaInicio, np->asignacion->horaInicio)==1) ){
    			if(validarHoras(i->horaInicio, np->asignacion->horaFin )==1 || validarHoras(i->horaInicio, np->asignacion->horaFin )==0){
	    			return 1;
				}			
			}
			
			if (validarHoras(i->horaFin, np->asignacion->horaInicio )==2 || validarHoras(i->horaFin, np->asignacion->horaInicio )==0){
				if(validarHoras(i->horaFin, np->asignacion->horaFin )==2){
    				return 1;
				}		
			}

    		return -1;		
    	}

        i = i->siguiente;     
    }
    
    return 1;
    
}

/*
    Entradas: Un puntero a una lista de asignaciones, el una cedena de caracteres con el identificador de una asignacion, y un entero indicado 1 si se se debe aprobar o -1 si se debe rechazar  
    Salidas: Se modifica el estado de la asignacion que corresponda con el identificadro de la recibido a Aprobada o Rechazada seg�n lo indique el entero condicion.
    Restricciones: No valida.
*/
void actualizarEstadoAsignacion(ListaAsignaciones *L,  char identificador[], int condicion){

    struct Asignacion *i;
    int res=0;
    
    struct ListaRequerimientos *LRQ;
    LRQ = (struct ListaRequerimientos *) malloc(sizeof(struct ListaRequerimientos));
    LRQ->inicio = NULL;
    LRQ->final = NULL;
    
    res = cargarRequerimientos(LRQ);

    i = L->inicio;
    while( i->siguiente!= NULL){
    	if (strcmp( i->codigoAsignacion , identificador )==0 ){				
			if(condicion==1){
				strcpy(i->estado, "Aprobada");
				modificarEstadoRQ(LRQ, i->identificador, 2);
				break;
			}else{
				strcpy(i->estado, "Rechazada");
				break;
			}		
    	}

        i = i->siguiente;     
    }
    
    liberarListaRequerimientos(LRQ);  
}

/*
	Entradas: Ninguna.
	Salidas: Se actualiza el estado de algunas de las asignaciones registradas a Aprobada.
	Restricciones: Ninguna.
*/
void atencionAsignaciones(){

	struct ListaAsignaciones *L;
	struct NodoPrioridad *i;
	int val=3, res=0, res2=0;
	char opcion[3];
	
	system( "CLS" );
	printf("\n\n+-------------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------------+\n");
	printf( "         Atencion Asignaciones\n" );
	printf("+-------------------------------------+\n");

	L = (struct ListaAsignaciones *) malloc(sizeof(struct ListaAsignaciones));
	L->inicio = NULL;
	L->final = NULL;
	
	struct ColaPrioridad *CP;
	CP = (struct ColaPrioridad *) malloc(sizeof(struct ColaPrioridad));
    CP->frente = NULL;
    CP->final = NULL;

	res=cargarAsignaciones(L);
	
	if(res==1){	
	
		cargarColaPrioridad(CP, L);	
		
		for(i = CP->frente; i!= NULL; i = i->siguiente){
		
			if (strcmp( i->asignacion->estado , "Aprobada" )==1){		
				printf("\n+-------------------------------+\n");
				printf("      Asignacion: %s \n", i->asignacion->codigoAsignacion);
				printf("  Fecha de Solicitud: %s \n", i->asignacion->fechaSolicitud);
				printf("  Hora de Inicio: %s \n", i->asignacion->horaInicio ); 
				printf("  Hora de Fin: %s \n", i->asignacion->horaFin); 
				printf("  Requerimiento: %s \n", i->asignacion->identificador); 
				printf("  Recurso: %s \n", i->asignacion->recurso); 
				printf("  Descripcion: %s \n", i->asignacion->descripcion);
				printf("  Miembros: %s \n", i->asignacion->miembros); 
				printf("  Priodidad: %s \n", i->asignacion->prioridad ); 
				printf("  Estado: %s \n", i->asignacion->estado); 
				printf("+-------------------------------+\n");
				printf("-->Desea atender esta asignacion? \n");
				printf("<--Digite 1 para SI, 2 para NO, o 3 para finalizar:");
	
				gets(opcion);
				
				if (strcmp(opcion ,"3")==0){
					break;			
				}
	
				if (strcmp(opcion ,"1")==0){
					res2=validarHorario(L, i);
					
					actualizarEstadoAsignacion(L,  i->asignacion->codigoAsignacion, res2);
					
					if(res2==1){
						printf("\n-->La asignacion %s ha sido Aprobada\n", i->asignacion->codigoAsignacion);	
					}else{
						printf("\n-->La asignacion %s ha sido Rechazada\n", i->asignacion->codigoAsignacion);
					}
					
										
				}												
			}
		}
				
		actualizarAsignaciones(L);

	}else{
		printf( "\n***No se han registrado Asignaciones***");
	}
		
	liberarListaAsignaciones(L);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);	
}

/*
    Entradas: Una cadena de caracteres que indica el c�digo de requerimiento consultado
    Salidas: -1 en caso de que se tengan 3 o m�s asignaciones relacionadas al requerimiento recibido, 1 si fueran menos de 3.
    Restricciones: Ninguna.
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
    Entradas: Un puntero a una lista del tipo ListaAsiganciones, tres cadenas de caracteres para la consulta y almacenamiento del c�digo de la asignacion, de requerimiento y del miembro  
    Salidas: 1 en caso de que alguna asignaci�n registrada coincida con el c�digo recibido por par�metro, y la asignacion de los valores del c�digo de de requerimiento y del miembro que
    		correspondan a la asignacion encontrada, caso contrario retorna -1
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


/****************************************************************Procedimientos para Incidentes***********************************************************************************************/

/*
	Entradas: Los diferentes objetos de la estructura Incidente(codigoRequerimiento, codigoAsignacion, descripcionIncidente, fecha). 
	Salidas: LLama a la funci�n guardarIncidente para guardar los datos al registrarlos en un archivo .txt. 
	Restricciones: No tiene restricciones.
*/
void registrarIncidentes(){
	system( "CLS" );
	printf("\n\n+-------------------------------+\n");
	printf("      Gestor de Requerimientos       \n");
	printf("+-------------------------------+\n");
	printf( "  Crear un nuevo incidente\n" );
	printf("+-------------------------------+\n");	
	
	struct ColaIncidentes *C;
	struct Incidentes *i, *incidente;
	int res;
	
	C = (struct ColaIncidentes *) malloc(sizeof(struct ColaIncidentes));
	C->inicio = NULL;
	C->final = NULL;

	res=cargarIncidentes(C);

	incidente= (struct Incidentes *) malloc (sizeof(struct Incidentes));
	
	if(incidente == NULL){
		printf("Espacio insuficiente para almacenar los datos.\n");	
	}
	
	do{
        printf("\n Ingrese el Codigo del Incidente: (Ejm. IN-001) \n");
		gets(incidente->codigoIncidente);
	
        
		if(res==1){
			if(validarIncidentes(C, incidente->codigoIncidente)==1){
				printf("\n **El codigo ingresado corresponde con un Incidente registrado**\n ");        
	        }else{
	        	break;  
	        }
		}else{
			break;	
		}
		
    }while(1);
		
	printf("\n Ingrese el Codigo del Requerimiento: (Ejm. RQ-000) \n");
	gets(incidente->codigoRequerimiento);
	printf("\n Ingrese el Codigo de Asignacion: (Ejm. AS-001) \n");
	gets(incidente->codigoAsignacion);
	printf("\n Ingrese la Descripcion de Incidente: \n");
	printf(" (Ejm. Requerimiento no terminado, con errores, o incompleto)\n");
	gets(incidente->descripcionIncidente);
	printf("\n Ingrese la Fecha del Incidente: (Ejm. 10/3/2020) \n");
	gets(incidente->fecha);
	printf("\n");
	incidente->siguiente=NULL;

	guardarIncidentes(incidente);
	liberarColaIncidentes(C);
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
	Entradas: Un puntero a una lista del tipo ListaIncidentes de Incidentes.
	Salidas: Una lista   enlazada con los diferentes objetos de la estructura Incidente (codigoRequerimiento, codigoAsignacion, 
			descripcionIncidente, fecha). 
	Restricciones: Ninguna.
*/
int cargarIncidentes(struct ColaIncidentes *C){
	
	struct Incidentes *aux;

	

	ArchIncidentes = fopen("Archivos\\Incidentes.txt","r");

	if(ArchIncidentes==NULL){
		return 0;	
	}else{
	
		while(!feof(ArchIncidentes)){
			
			aux = (struct Incidentes *) malloc (sizeof(struct Incidentes));
			
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
				C->inicio = aux;
				C->inicio->siguiente = NULL; 
				C->final = C->inicio;
	
			}else{
				//Inserta al final de la lista	
				C->final->siguiente = aux;
				C->final->siguiente->siguiente = NULL; 
				C->final = C->final->siguiente;
			}		
		}
		fclose(ArchIncidentes);		
	}	
	return 1;
}

/*
	Entradas: Un dato que indique la c�dula del Miembro del Equipo por consultar los Incidentes
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
					if(compararFechas(fechaInicio, fechaIncidente)==1 || compararFechas(fechaFin, fechaIncidente)==2){
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
				if(strcmp(i->codigoAsignacion,iAs->codigoAsignacion)==0){
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
	liberarListaAsignaciones(LAs);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

/*
    Entradas: Una cadena de caracteres que indica el c�digo de requerimiento consultado
    Salidas: -1 en caso de que se tengan 3 o m�s incidentes relacionadas al requerimiento recibido, 1 si fueran menos de 3.
    Restricciones: Ninguna.
*/
int contarIncidentes(const char identificador[]){

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
    Entradas: Una cadena de caracteres que indica el c�digo del incidente registrado
    Salidas: -1 en caso de que exista un incidente con el identificador recibido, 1.
    Restricciones: Ninguna.
*/
int validarIncidentes(ColaIncidentes *C, const char identificador[]){

	struct Incidentes *i;
	char id [50];
	
	i = C->inicio;
	while( i->siguiente!= NULL){
		strcpy(id, i->codigoIncidente);		
        if(strcmp(id, identificador)==0){   
			return 1;
        }
		i = i->siguiente;
	}
	
	return -1;	

}

/****************************************************************Procedimientos para Calificaciones***********************************************************************************************/

/*
    Entradas: Un puntero a una lista del tipo ListaCalificaciones, y una cadena de caracteres indicando el c�digo de la asignacion.
    Salidas: Se modifica el valor de la calificacion registrada con el c�digo recibido por par�metro.
    Restricciones: Ninguna.
*/
void modificarCalificacion(struct ListaCalificaciones *L,  char idAsignacion[]){
	struct Calificacion *i;
	int calificacionInt=0;
	char calificacionChar [20];

    i = L->inicio;
    while( i->siguiente!= NULL){
        if(strcmp(idAsignacion, i->codigoAsignacion)==0){
			calificacionInt = atoi(i->calificacion) - 1;
			sprintf(calificacionChar, "%d", calificacionInt);
			strcpy(i->calificacion, calificacionChar);		
		}
        i = i->siguiente;
    }
	
	actualizarCalificacion(L);
}

/*
	Entradas: Un puntero a una lista del tipo ListaCalificaciones
	Salidas:  Se sobreescribe el archivo que almacena la lista de calificaciones con los valores modificados.
	Restricciones: Ninguna
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
	Entradas: Los diferentes objetos de la estructura Calificaci�n(codigoRequerimiento, codigoAsignacion, calificacion). 
	Salidas: LLama a la funci�n guardarCalificacion para guardar los datos al registrarlos en un archivo .txt. 
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
		printf("No ha resgistrado ninguna asignacion\n");
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
	calificacion->siguiente=NULL;
	
	if(res2==1){
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
	}    
	
	if(actualizar==1){
		actualizarCalificacion(LC);
	}else{
		guardarCalificacion(calificacion);
	}
	
	
	liberarListaAsignaciones(L);
	liberarListaCalificaciones(LC);	
	printf("\nPresione una tecla para regresar..." ); 
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
	Entradas: Un puntero a una lista del tipo ListaCalificaciones
	Salidas: carga los valroes de las calificaciones registradas en la lista referida por par�metro.
	Restricciones: Ninguna
*/
int cargarCalificaciones(struct ListaCalificaciones *L){
	
	struct Calificacion *aux;
	
	ArchCalificaciones = fopen("Archivos\\Calificaciones.txt","r");

	if(ArchCalificaciones==NULL){
		return 0;	
	}else{
	
		while(!feof(ArchCalificaciones)){
			
			aux = (struct Calificacion *) malloc (sizeof(struct Calificacion));
			
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
				L->inicio = aux;
				L->inicio->siguiente = NULL; 
				L->final = L->inicio;
	
			}else{
				//Inserta al final de la lista	
				L->final->siguiente = aux;
				L->final->siguiente->siguiente = NULL; 
				L->final = L->final->siguiente;
			}		
		}
		fclose(ArchCalificaciones);		
	}	
	return 1;
}

/*
	Entradas: Ninguna
	Salidas: El promedio de las calificaciones registradas para un requerimiento.
	Restricciones: Ninguna
*/
double promedioCalificaciones(const char idRequerimiento[]){
	
	struct ListaCalificaciones *LC;
	LC = (struct ListaCalificaciones *) malloc(sizeof(struct ListaCalificaciones));
    LC->inicio = NULL;
    LC->final = NULL;
    
    struct Calificacion *aux;
    
    int res, suma=0, cantidad=0;
    double promedio=0;
        
	res=cargarCalificaciones(LC);
	
	if(res == 0){	
		return 0;	
	}else{
		aux = LC->inicio;
		while( aux->siguiente!= NULL){	
	        if(strcmp(aux->codigoRequerimiento, idRequerimiento)==0){   
				suma += atoi(aux->calificacion);
				cantidad++;
	        }
			aux = aux->siguiente;
		}
		
	}
	
	promedio = suma/cantidad;	
	
	return promedio;
	
	liberarListaCalificaciones(LC);		
}



/****************************************************************Procedimientos para Analisis de Datos*******************************************************************************************/

/*
	Entradas: Un dato que indique el tipo de reporte que ser� solicitado por medio del an�lisis de los datos registrados
	Salidas: Se llama a la funcion corrspondiente para la consulta de cada uno de los reportes.
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
	Entradas:  Una cadena de caracteres y un valor entero.
	Salidas: Crea un nodo del tipo NodoTopAsignacion.
	Restricciones: Ninguna.
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
	Entradas: Un puntero a una lista del tipo ListaTopAsignaciones
	Salidas: La lista  recibida como par�metro, ordenada por el valordel dato cantidad
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
	Entradas: Ninguna
	Salidas: Desplegar los valores del top de requerimietnos con m�s asignaciones
	Restricciones: Ninguna
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

	if(res==1)
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
		return;
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
	liberarTopAsignaciones(LT);

	fflush(stdin);
}

/*
	Entradas: Una cadena de caracteres y un valor entero
	Salidas: Crea un nodo del tipo NodoTopHorario
	Restricciones: Ninguna
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
	Entradas: Un puntero a una lista del tipo ListaTopHorarios
	Salidas: La lista  recibida como par�metro, ordenada por el valordel dato cantidad
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
	Entradas: Ninguna
	Salidas: Desplegar los valores del top de horarios m�s utilizados
	Restricciones: Ninguna
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

	if(res==1)
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
		printf( "\n***No se han registrado Requerimientos***");
		return;
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
            if (strcmp(iOf->codigo , nA->identificador)==0){
            	
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
	liberarTopHorarios(LT);
	liberarListaOficinas(LOf);

	fflush(stdin);
}

/*
	Entradas:  Una cadena de caracteres y un valor entero
	Salidas: Crea un nodo del tipo NodoTopMiembro
	Restricciones: Ninguna
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
	Entradas: Un puntero a una lista del tipo ListaTopMiembros
	Salidas: La lista  recibida como par�metro, ordenada por el valor del dato cantidad
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
	Entradas: Ninguna
	Salidas: Desplegar los valores del top de miembros con m�s asignaciones
	Restricciones: Ninguna
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

	if(res==1)
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
		return;
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
	liberarTopMiembros(LT);
	
	fflush(stdin);
}

/*
	Entradas:  Una cadena de caracteres y un valor entero
	Salidas: Crea un nodo del tipo NodoTopEsfuerzo
	Restricciones: Ninguna
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
	Entradas: Un puntero a una lista del tipo ListaTopMiembros 
	Salidas: La lista  recibida como par�metro, ordenada por el valor del dato cantidad
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
	Entradas: Ninguna
	Salidas: Desplegar los valores del top de requerimientos con un mayor esfuerzo
	Restricciones: Ninguna
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

	if(res==1)
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
		printf( "\n***No se han registrado Requerimientos***");
		return;
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

/****************************************************************Procedimientos para liberar Est. de Datos***********************************************************************************/

/*
	Entradas: Un puntero a una lista de nodos de tipo struct Miembros de Equipo.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
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
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
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
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
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
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
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

/*
	Entradas: Un puntero a una lista de nodos de tipo struct Calificacion.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarListaCalificaciones(ListaCalificaciones *L){
	struct Calificacion *n, *aux;
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
	Entradas: Un puntero a una lista de nodos de tipo struct Oficina.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarListaOficinas(ListaOficinas *L){
	struct Oficina *n, *aux;
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
	Entradas: Un puntero a una lista de nodos de tipo struct NodoTopAsignacion.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarTopAsignaciones(ListaTopAsignaciones *L){
	struct NodoTopAsignacion *n, *aux;
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
	Entradas: Un puntero a una lista de nodos de tipo struct NodoTopHorario.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarTopHorarios(ListaTopHorarios *L){
		
	struct NodoTopHorario *n, *aux;
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
	Entradas: Un puntero a una lista de nodos de tipo struct NodoTopEsfuerzo.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarTopEsfuerzo(ListaTopEsfuerzo *L){
	struct NodoTopEsfuerzo *n, *aux;
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
	Entradas: Un puntero a una lista de nodos de tipo struct NodoTopMiembro.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarTopMiembros(ListaTopMiembros *L){
	struct NodoTopMiembro *n, *aux;
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
	Entradas: Un puntero a una lista de nodos de tipo struct PilaAsignaciones.
	Salidas: Se libera el espacio en memoria ocupado por los elementos de la lista a la cual se�ala el puntero recibido.
	Restricciones: Ninguna
*/
void liberarPilaAsignaciones(PilaAsignaciones *P){
	struct Asignacion *n, *aux;
	if(P->tope == NULL)
		return;
	if(P->tope->siguiente == NULL)
		return;		
	n = P->tope;
	
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
