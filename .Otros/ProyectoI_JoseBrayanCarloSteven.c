#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include <time.h>

FILE* ArchEmpleados;
FILE* ArchRepuestos;
FILE* ArchCliente;
FILE* ArchServicios;
FILE* ArchServCliente;
FILE* ArchFactura;

struct Empleado{
	char nombre[50];
	char cedula[12];
	char edad[4];
	char especialidad[50];
	char areatrabajo[30];
	char telefono[15];
}datosEmpleado;

struct Vehiculo{
	char placa[10];
	char marca[15];
	char year[6];
	char descripcion[30];
	struct Vehiculo *siguiente;
}datosVehiculo;

struct Cliente{
	char nombre[25];
	char cedula[15];
	char telefono[15];
	struct Cliente *next;
}datosCliente;

struct Vehiculo *primero, *ultimo;
struct Cliente *first, *last;

//Procedimientos Principales
void Menu_Principal();
void Clientes_Vehiculos();
void Empleados();
void Servicios();
void Inventario();
void Facturacion();

//Procedimientos para Clientes-Vehiculos
void agregar_cliente();
void mostrar_cliente();
void guardar_cliente();

//Procedimientos para Empleados
void agregar_empleado();
void mostrar_empleados();
void buscar_empleados();
char* obtener_especialidad();

//Procedimientos de Servicios
void seleccion_servicio();

//Procedimientos de Inventario
void mostrar_articulos();
void agregar_articulo();
void buscar_articulo();
void consultar_precio();


int main(){   
    Menu_Principal();     
}

void Menu_Principal(){
	char opcion;
	
	do{
        system( "CLS" );
        fflush(stdin);
        printf( "\n\t Taller Los Madrid\n" );
		printf( "\n\t  Menu Principal\n" );
		printf( "\n 1 - Control de Clientes/Vehiculos" );
	    printf( "\n 2 - Control de Empleados" );
	    printf( "\n 3 - Control de Inventario" );
	    printf( "\n 4 - Facturacion" );   
	    printf( "\n 5 - Salir" );
	    printf("\n");
	    printf("\n\n Elija una opcion : ");
        opcion = getchar();
        
        switch ( opcion ){
            case '1': Clientes_Vehiculos();
                break;
			case '2': Empleados();
                break;
            case '3': Inventario();
                break;
			case '4': Facturacion();
                break;
            case '5': exit(1);
				break;
            default:
            	fflush(stdin);
				printf("Opcion invalida.Intente de nuevo.\n");
				getchar();
                break;
        }
    } while (opcion!='6');    
    fflush(stdin);
	getchar();	
}


/*++++++++++++++++++Clientes/Vehiculos++++++++++++++++++++++++++++++++++++++++++++++*/

void Clientes_Vehiculos(){
	char opcion, ch;	
	primero= (struct Vehiculo *) NULL;
	ultimo= (struct Vehiculo *) NULL;
	first= (struct Cliente *) NULL;
	last= (struct Cliente *) NULL;

	do{
		system( "CLS" );
		fflush(stdin);
		printf( "\n\t Taller Los Madrid\n" );
		printf( "\n\t Clientes/Vehiculos\n" );
		printf("\n 1. Agregar cliente con su respectivo vehiculo.");
		printf("\n 2. Mostrar informacion del vehiculo y cliente.");
		printf("\n 3. Volver al Menu Principal.");
		printf("\n");
		printf("\n\nElija una opcion : ");	
		opcion=getchar();
		
		while((ch = getchar()) != EOF && ch != '\n');
			switch(opcion){
				case '1': agregar_cliente();
						break;
				case '2': mostrar_cliente();
					break;
				case '3': Menu_Principal();
					break;
				default:
					fflush(stdin);
					printf("Opcion invalida.Intente de nuevo.\n");
					getchar();
					break;	
		}	
	}while(opcion!=3);			
	fflush(stdin);
	getchar();
}

void agregar_cliente(){
	system( "CLS" );
	printf( "\n\t  Taller Los Madrid\n" );
	printf( "\n\tAgregar Vehiculo/Cliente Nuevo\n" );	
	struct Vehiculo *equipo;
	struct Cliente *persona;
	
	equipo= (struct Vehiculo *) malloc (sizeof(struct Vehiculo));
	persona=(struct Cliente *) malloc (sizeof(struct Cliente));
	
	if(equipo == NULL || persona == NULL){
		printf("Espacio insuficiente para almacenar los datos.\n");	
	}
	
	printf("\n --VEHICULO--\n");
	printf("\n Ingrese la placa: ");
	gets(equipo->placa);
	printf("\n Ingrese la marca: ");
	gets(equipo->marca);
	printf("\n Ingrese el anno: ");
	gets(equipo->year);
	printf("\n Ingrese el servicio requerido: \n");
	Servicios(equipo->placa);
	printf("\n");
	printf("\n Ingrese la descripcion del vehiculo: ");
	gets(equipo->descripcion);
	equipo->siguiente=NULL;

	printf("\n");
	printf("\n --CLIENTE--\n");
	printf("\n Ingrese el nombre del cliente: ");
	gets(persona->nombre);
	printf("\n Ingrese el cedula del cliente: ");
	gets(persona->cedula);
	printf("\n Ingrese el telefono del cliente: ");
	gets(persona->telefono);
	persona->next=NULL;
	
	if(primero==NULL){
		primero=equipo;
		ultimo=equipo;	
	}else{
		ultimo->siguiente=equipo;
		ultimo=equipo;	
	}
	
	if(first==NULL){
		first=persona;
		last=persona;	
	}else{
		last->next=persona;
		last=persona;	
	}
	guardar_cliente();
	getchar();	
}

void guardar_cliente(){
	
	struct Vehiculo *equipo;
	struct Cliente *persona;
	equipo=primero;
	persona=first;
	
	//remove("ClienteVehiculo.txt");
	
	ArchCliente=fopen("Archivos\\ClienteVehiculo.txt","a+");
	if(ArchCliente==NULL){
		printf("\n Error al intentar usar el archivo.\n");	
	}else{
		while(equipo!=NULL && persona!=NULL){
			fprintf(ArchCliente,"%s %s %s %s %s %s %s\n", persona->cedula, persona->nombre, persona->telefono,
							equipo->placa,equipo->marca,equipo->year,equipo->descripcion);

			equipo=equipo->siguiente;
			persona=persona->next;	
		}	
	}
	fclose(ArchCliente);
	printf("\n\n ==>Informacion guardada<==.\n");
	
	printf("\n\nPresione una tecla para regresar..." ); 

}

void mostrar_cliente(){
	system( "CLS" );
	printf( "\n\t Taller Los Madrid\n" );
	struct Vehiculo *equipo;
	struct Cliente *persona;
	equipo=primero;
	persona=first;
	char cadena[256], placa[10], marca[15], year[6], servicio[25], 
		 descripcion[30], nombre[25], cedula[15], telefono[15];	
	
	ArchCliente=fopen("Archivos\\ClienteVehiculo.txt","r");
	if(ArchCliente==NULL){
		printf("\n Error al intentar abrir el archivo.\n");	
	}else{
		
		while(!feof(ArchCliente)){
			fscanf(ArchCliente,"%s %s %s %s %s %s %s \n",cedula, nombre, telefono, placa, marca, year, descripcion);
			printf("\n --CLIENTE--\n");	
			printf("\n\t Nombre: %s" ,nombre);
			printf("\n\t Cedula: %s" ,cedula);
			printf("\n\t Telefono: %s" ,telefono);
			printf("\n --VEHICULO--\n");
			printf("\n\t Placa: %s" ,placa);
			printf("\n\t Marca: %s" ,marca);
			printf("\n\t Anno: %s" ,year);
			printf("\n\t Descripcion: %s \n" ,descripcion);
			printf("------------------------------------------------------------------------------\n ");
		}
	}	
	fclose(ArchCliente);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
	
}

/*++++++++++++++++++Empleados+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Empleados(){
	int opc;
	
	do{
		system( "CLS" );
		printf("\n\tTaller Los Madrid\n" );
		printf("\n\tEmpleados\n" );
		printf("\n1. Agregar nuevo empleado");
		printf("\n2. Ver empleados existentes");
		printf("\n3. Buscar empleado.");
		printf("\n4. Volver al Menu Principal");
		printf("\n\n Elija una opcion......: ");
		scanf("%i",&opc);
		
		switch(opc){
			case 1: agregar_empleado();break;
				break;
			case 2: mostrar_empleados();break;
				break;
			case 3: buscar_empleados(); break;
				
			case 4: Menu_Principal();
				break;
			default:
					fflush(stdin);
					printf("Opcion invalida.Intente de nuevo.\n");
					getchar();
		}
		
	}while(opc != 4);
	
	fflush(stdin);
	getchar();	
}

void agregar_empleado(){
	system( "CLS" );
	printf( "\n\tTaller Los Madrid\n" );
	char rpt;
	char opcion;
	
		ArchEmpleados = fopen("Archivos\\Empleados.txt","at"); 
	
	if(ArchEmpleados== NULL){
		printf("Error al tratar de leer el archivo\n");
		return;
	}
	
	do{
		fflush(stdin);
		printf("Nombre: ");
		gets(datosEmpleado.nombre);
		printf("Cedula: ");
		gets(datosEmpleado.cedula);
		printf("Edad: ");
		gets(datosEmpleado.edad);
		printf("Especialidad: ");
		gets(datosEmpleado.areatrabajo);
		printf("Telefono: ");
		gets(datosEmpleado.telefono);
		printf("Area de trabajo: ");
		
		printf("\n  a. Ajuste de frenos.");
		printf("\n  b. Limpieza de inyectores.");
		printf("\n  c. Cambio de llantas.");
		printf("\n  d. Overhaul del motor.");
		printf("\n   e. Cambio de empaques de valvulas.");
		printf("\n   f. Control de emision de gases.");
		printf("\n   g. Cambio de aceite.");
		printf("\n   h. Enderezado y Pintura.");
		printf("\n   i. Alineacion y Balanceo.");
		printf("\n   j. Fallas Electricas.");
		printf("\n\n Elija una opcion......: ");
		opcion = getchar();
		
		switch(opcion){
			case 'a': 
				strcpy(datosEmpleado.areatrabajo,"Ajuste/de/frenos");	
			break;
			case 'b': 
				strcpy(datosEmpleado.areatrabajo,"Limpiar/Inyector");
			break;
			case 'c': 
				strcpy(datosEmpleado.areatrabajo,"Cambio/de/llantas");	
			break;
			case 'd': 
				strcpy(datosEmpleado.areatrabajo,"Overhaul/de/motor");
			break;
			case 'e': 
				strcpy(datosEmpleado.areatrabajo,"Cambio/de/empaques");
			break;
			case 'f': 
				strcpy(datosEmpleado.areatrabajo,"Emision/de/gases");			
			break;
			case 'g': 
				strcpy(datosEmpleado.areatrabajo,"Cambio/de/aceite");
			break;
			case 'h': 
				strcpy(datosEmpleado.areatrabajo,"Enderezado/Pintura");
			break;
			case 'i': 
				strcpy(datosEmpleado.areatrabajo,"Alineacion/y/Balanceo");
			break;
			case 'j': 
				strcpy(datosEmpleado.areatrabajo,"Fallas/electricas");		
			break;
			default:
				fflush(stdin);
				printf("Opcion invalida.Intente de nuevo.\n");
				getchar();
			break;
		}

		fprintf(ArchEmpleados, "%s %s %s %s %s %s\n", datosEmpleado.nombre,datosEmpleado.cedula, datosEmpleado.edad,datosEmpleado.especialidad,datosEmpleado.areatrabajo,datosEmpleado.telefono);		
		printf("Desea agregar otro empleado: Si(s) No(n) ");
		scanf("%c",&rpt);		
	}while(rpt == 's');
	
	fclose(ArchEmpleados);
	fflush(stdin);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
}

void mostrar_empleados(){
	
	system( "CLS" );
	printf( "\n\t Taller Los Madrid\n" );
	printf( "\n\t Lista de Empleados\n\n" );
	char nombre[50],cedula[12],edad[4],especialidad[30],areatrabajo[30],telefono[15];	
	
	ArchEmpleados = fopen("Archivos\\Empleados.txt","r");
	
	if(ArchEmpleados==NULL){
		printf("\n Error al intentar abrir el archivo.\n");	
	}else{
		
		while(!feof(ArchEmpleados)){
			fscanf(ArchEmpleados,"%s %s %s %s %s %s\n",nombre,cedula,edad,areatrabajo,especialidad,telefono);	
			printf("\n\t Nombre: %s" ,nombre);
			printf("\n\t Cedula: %s" ,cedula);
			printf("\n\t Edad: %s" ,edad);
			printf("\n\t Especialidad: %s" ,especialidad);
			printf("\n\t Area de trabajo: %s",areatrabajo);
			printf("\n\t Telefono: %s",telefono);
			printf("\n------------------------------------------------------------------------------\n ");
		}
		getchar();
	}	
	fclose(ArchEmpleados);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();
	fflush(stdin);
}

void buscar_empleados(){	
 	system( "CLS" );
	printf( "\n\tTaller Los Madrid\n" );
	printf( "\n\tBuscar Empleado\n" );	
    char nombrebuscar[50],nombre[50],cedula[12],edad[4],especialidad[30],areatrabajo[30],telefono[15];
    int i=0;
	ArchEmpleados = fopen("Archivos\\Empleados.txt","r");
	if(Empleados!= NULL){
		printf( "\nDigite el nombre del empleado a buscar..:" );
		scanf("%s", nombrebuscar);
		
		while(!feof(ArchEmpleados)){

				fscanf(ArchEmpleados, "%s %s %s %s %s %s ", nombre,cedula, edad, areatrabajo, especialidad, telefono);
			if(strcmp(nombrebuscar,nombre)==0){

				printf( "\nNombre: %s", nombre);
				printf( "\nCedula: %s", cedula);
				printf( "\nEdad: %s", edad);
				printf( "\nEspecialidad: %s", especialidad);
				printf("\nArea de trabajo: %s",areatrabajo);
				printf("\nTelefono: %s",telefono);
				i++;
			}	
		}
		if(i==0){
			printf("El empleado que usted ingreso no se encuentra.\n");	
			}	
	
		fclose(ArchEmpleados);		
	}else{		
		printf("\n\nError al abrir el archivo! ", strerror(errno));
	}	
	fflush(stdin);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();	
} 


/*++++++++++++++++++Servicios++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Servicios(char Matricula[10]){		
	char opcion; 
	char *palabra; 
	struct Vehiculo *vehiculo;  
	
	 	fflush(stdin);
		printf("\n\t a. Ajuste de frenos.");
		printf("\n\t b. Limpieza de inyectores.");
		printf("\n\t c. Cambio de llantas.");
		printf("\n\t d. Overhaul del motor.");
		printf("\n\t e. Cambio de empaques de valvulas.");
		printf("\n\t f. Control de emision de gases.");
		printf("\n\t g. Cambio de aceite.");
		printf("\n\t h. Enderezado y Pintura.");
		printf("\n\t i. Alineacion y Balanceo.");
		printf("\n\t j. Fallas Electricas.");
		printf("\n");
		printf("\n\n Elija una opcion......: ");
		opcion = getchar();
		
		switch(opcion){
			case 'a': 
			palabra = "Ajuste/de/frenos";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'b': 
			palabra = "Limpiar/Inyector";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'c': 
			palabra = "Cambio/de/llantas";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'd': 
			palabra = "Overhaul/de/motor";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'e': 
			palabra = "Cambio/de/empaques";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'f': 
			palabra = "Emision/de/gases";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'g': 
			palabra = "Cambio/de/aceite";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'h': 
			palabra = "Enderezado/Pintura";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'i': 
			palabra = "Alineacion/y/Balanceo";
			seleccion_servicio(palabra,Matricula);
			break;
			case 'j': 
			palabra = "Fallas/electricas";
			seleccion_servicio(palabra,Matricula);
			break;
			default:
			fflush(stdin);
			printf("Opcion invalida.Intente de nuevo.\n");
			getchar();
			break;
		}
	fflush(stdin);
}

void seleccion_servicio(char *serv, char matricula[10]){
	ArchServicios = fopen("Archivos\\Servicios.txt","r");
	ArchServCliente = fopen("Archivos\\ServCliente.txt","a");
	
	char *servClien = serv;
	char servicio[25], costo[10], material[25];
	int i = 0;
	if(ArchServicios == NULL){
		printf("\n Problema al abrir el archivo %s", strerror(errno));
	}else{
		do{
			fscanf(ArchServicios, "%s %s %s \n", servicio, costo, &material);
			if(strcmp(servicio,servClien) == 0){
				i=1;
			}
	  	}while(i!=1);
	  	fprintf(ArchServCliente,"%s %s %s %s \n", matricula,servicio,costo,material);
	}
	fclose(ArchServicios);
	fclose(ArchServCliente);
 }
 
 
/*++++++++++++++++++Inventario+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Inventario(){
	char opcion;
    
    do{
        system( "CLS" );
        fflush(stdin);
        printf( "\n\tTaller Los Madrid\n" );
		printf( "\n\tInventario de Repuestos\n" );
		printf( "\n 1. Buscar articulo en Inventario" );
	    printf( "\n 2. Mostrar Inventario Completo" );
	    printf( "\n 3. Agregar articulo a Inventario" );
	    printf( "\n 4. Consultar precio de articulo" );
	    printf( "\n 5. Volver al Menu Principal" );   
	    printf( "\n");
	    printf( "\n\n Elija una opcion : ");
        opcion = getchar();
        
        switch ( opcion ){
            case '1': buscar_articulo();
                break;
			case '2': mostrar_articulos();
                break;
            case '3': agregar_articulo();
                break;
			case '4': consultar_precio();
                break;
            case '5': Menu_Principal();
            default: 
            		fflush(stdin);
					printf("Opcion invalida.Intente de nuevo.\n");
					getchar();
                break;
        }
    } while (opcion!='5');     
    fflush(stdin);
	getchar();
	
}

void buscar_articulo(){
	system("CLS");
	printf( "\n\tTaller Los Madrid\n" );
	ArchRepuestos = fopen("Archivos\\Inventario.txt", "r");
	char articulo[40], nombre1[25], nombre2[25], marca[25], cantidad[5], precioUnit[15];
	int val=3;
		
	printf("\n\tBuscar Articulo");
	
	if( ArchRepuestos != NULL){
		
		printf( "\n\nDigite el nombre del articulo buscado..:" );
		scanf("%s", &nombre1);
		
		while(fscanf(ArchRepuestos, "%s %s %s %s ",nombre2,marca,cantidad,&precioUnit)!=EOF){
			val=strcmp(nombre1,nombre2);
			if(val==0){
				printf( "\n\tArticulo Encontrado!\n");
				printf( "\nNombre: %s", nombre2);
				printf( "\nMarca: %s", marca);
				printf( "\nCantidad: %s", cantidad);
				printf( "\nPrecio Unitario: %s", precioUnit);
			}
		}	
		if(val==1){
			printf( "\nArticulo no encontrado");
		}		
		fclose(ArchRepuestos);		
	}else{		
		printf("\n\nError al abrir el archivo! ", strerror(errno));
	}	
	fflush(stdin);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();	
}

void mostrar_articulos(){
	system( "CLS" );
	printf( "\n\tTaller Los Madrid\n" );
	ArchRepuestos = fopen("Archivos\\Inventario.txt", "r");
	char c, nombre[25], marca[25], cantidad[5], precioUnit[15];
		
	printf( "\n\tInventario Completo\n" );
	
	if( ArchRepuestos != NULL){

		while(fscanf(ArchRepuestos, "%s %s %s %s ",nombre,marca,cantidad,&precioUnit)!=EOF){
					
			printf( "\nNombre: %s", nombre );
			printf( "\n  Marca: %s", marca);
			printf( "\n  Cantidad Disponible: %s",cantidad );
			printf( "\n  Precio Unitario: %s",precioUnit );
			printf( "\n");
		}		
		fclose(ArchRepuestos);			
	}else{		
		printf("\n\nError al mostrar inventario! ", strerror(errno));
	}
	fflush(stdin);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();	
}

void agregar_articulo(){
	system( "CLS" );
	printf( "\n\tTaller Los Madrid\n" );
	ArchRepuestos = fopen("Archivos\\Inventario.txt", "a+");
	char nombre[25], marca[25], cantidad[5], precioUnit[15];
	printf( "\n\tAgregar Articulo" );
	
	if( ArchRepuestos != NULL){
			
		printf("\n\n Digite los datos del articulo ");	
		printf("\n\n\tNombre: "); 
		scanf("%s", &nombre);
		printf("\n\tMarca: "); 
		scanf("%s", &marca);		
	    printf("\n\tCantidad: "); 
		scanf("%s", &cantidad);			
	    printf("\n\tPrecio Unitario: "); 
		scanf("%s", &precioUnit);				
		
		fprintf(ArchRepuestos, "%s %s %s %s \n",nombre,marca,cantidad,precioUnit); 

		fclose(ArchRepuestos);
		
		printf("\n Articulo guardado exitosamente!");		
	}else{		
		printf("\n\nError al abrir el archivo de inventario! ", strerror(errno));
	}
		fflush(stdin);
		printf("\n\nPresione una tecla para regresar..." ); 
		getchar();	
}

void consultar_precio(){
	system("CLS");
	printf( "\n\tTaller Los Madrid\n" );
	ArchRepuestos = fopen("Archivos\\Inventario.txt", "r");
	char articulo[40], nombre1[25], nombre2[25], marca[25], cantidad[5], precioUnit[15];
	int val=3, precioCant=0, cantReq=0;
		
	printf( "\n\tConsultar Precio");
	
	if( ArchRepuestos != NULL){
		
		printf( "\n\nDigite el nombre del articulo buscado..:" );
		scanf("%s", &nombre1);
		printf( "\nCantidad requerida..:" );
		scanf("%d", &cantReq);
		
		while(fscanf(ArchRepuestos, "%s %s %s %s ",nombre2,marca,cantidad,&precioUnit)!=EOF){
			val=strcmp(nombre1,nombre2);
			if(val==0){
				precioCant = atoi(precioUnit);
				precioCant = cantReq * precioCant;
				printf( "\nNombre: %s", nombre2);
				printf( "\nMarca: %s", marca);
				printf( "\nCantidad disponible: %s", cantidad);
				printf( "\nPrecio Unitario: %s", precioUnit);
				printf( "\nPrecio Total: %d", precioCant);
				printf( "\n");
			}
		}	
		if(val==1){
			printf( "\nArticulo no encontrado");
		}	
		fclose(ArchRepuestos);		
	}else{	
		printf("\n\nError al abrir el archivo de inventario! ", strerror(errno));
	}	
	fflush(stdin);
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();	
}

/*++++++++++++++++++Facturacion+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void Facturacion(){
	system("CLS");
	printf( "\n\tTaller Los Madrid" );
	printf( "\n\tFacturacion");
	
	ArchEmpleados = fopen("Archivos\\Empleados.txt", "r");
	ArchRepuestos = fopen("Archivos\\Inventario.txt", "r");
	ArchCliente = fopen("Archivos\\ClienteVehiculo.txt", "r");
	ArchServCliente = fopen("Archivos\\ServCliente.txt","r");
	
	char matricula [10];

	//Datos Servicios
	char matriculaprecio[10];
	char servicio[25];
	char manobra[10];
	char material[25];
	
	int i=0, j=0, h=0;
	
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	
	if(ArchCliente == NULL && ArchEmpleados == NULL){
		printf("\n Error al intentar abrir el archivo\n");
	}else{
		printf("\n\n Digite la matricula de vehiculo: ");
		scanf("%s",matricula);
		
		do{
			fscanf(ArchCliente,"%s %s %s %s %s %s %s", datosCliente.cedula,datosCliente.nombre,datosCliente.telefono,
			datosVehiculo.placa,datosVehiculo.marca,datosVehiculo.year,&datosVehiculo.descripcion);				
			if(strcmp(matricula,datosVehiculo.placa)==0){
					h=1;					
			}
		}while(h!=1 && !feof(ArchCliente));
		
		if(h==0){
			printf("\n=>La matricula ingresada no se encuentra registrada");
			getchar();	
		}else{
			do{
				fscanf(ArchServCliente,"%s %s %s %s \n", matriculaprecio,servicio,manobra,&material);	
				if(strcmp(matricula,matriculaprecio) == 0){	
					i=1;
				}
			}while(i!=1 && !feof(ArchServCliente));
			
			if(i==0){
				printf("\n=>La matricula ingresada no registra ningun servicio");
				getchar();	
			}else{
				do{
						fscanf(ArchEmpleados, "%s %s %s %s %s %s\n", datosEmpleado.nombre,datosEmpleado.cedula,
						datosEmpleado.edad,datosEmpleado.areatrabajo,datosEmpleado.especialidad,datosEmpleado.telefono);
						if(strcmp(servicio,datosEmpleado.areatrabajo)==0){
							j=1;
						}
					}while(j!=1 && !feof(ArchEmpleados));
					
					if(j==0){
						printf("\n=>No hay ningun empleado asignado al servicio realizado");
						getchar();	
					}	
				
			}
			
		}
		
		if(i==1 && h==1 && j==1){
			system("CLS");
			printf("\n\n\t\t   TALLER MECANICO");
			printf("\n\t\t     LOS MADRID");	
			printf("\n     Telefono: 2552-0989   Correo: tm_madrid@gmail.com");
			printf("\n\t      %s",asctime(tm)); 
			
			printf("  ---------------------------------------------------------");
			printf("\n\n\t   ---> Datos del Cliente <---\n");
			printf("\n\t  Nombre: %s   Cedula: %s \n", datosCliente.nombre,datosCliente.cedula);
			printf("\n \t   ---> Datos del Vehiculo <---\n");
			printf("\n\t  Matricula: %s      Anno: %s", datosVehiculo.placa,datosVehiculo.year);
			printf("\n\n\t  Marca: %s      Descripcion: %s\n",datosVehiculo.marca,datosVehiculo.descripcion);	
		
			fflush(stdin);
			printf("  ---------------------------------------------------------");	
			printf("\n \t   ---> Datos del Empleado <---\n");
			printf("\n\t   Nombre: %s   Cedula: %s \n", datosEmpleado.nombre,datosEmpleado.cedula);	
			
			printf("  ---------------------------------------------------------");	
			printf("\n \t   ---> Datos del Servicio <---\n");
			printf("\n \t  Servicio: %s ", servicio);		
			printf("\n \t  Material: %s", material);
			printf("\n \t                             Costo: %s", manobra);
			printf("\n  --------------------------------------------------------");							
		
	
			char *txt=".txt";
			char carpetaFactura[]="Facturas\\";
			strcat(matricula,txt);
			strcat(carpetaFactura,matricula);
			
				
			ArchFactura = fopen(carpetaFactura,"w");
			if(ArchFactura==NULL){
				printf("\n Hubo un error con el manejo del archivo de facturacion %s.", strerror(errno));
			}else{
				
				fprintf(ArchFactura,"\n\n\t\t   TALLER MECANICO");
				fprintf(ArchFactura,"\n\t\t     LOS MADRID");	
				fprintf(ArchFactura,"\n     Telefono: 2552-0989   Correo: tm_madrid@gmail.com");
				fprintf(ArchFactura,"\n\t      %s",asctime(tm)); 
				
				fprintf(ArchFactura,"  ---------------------------------------------------------");
				fprintf(ArchFactura,"\n\n\t   ---> Datos del Cliente <---\n");
				fprintf(ArchFactura,"\n\t  Nombre: %s   Cedula: %s \n", datosCliente.nombre,datosCliente.cedula);
				fprintf(ArchFactura,"\n \t   ---> Datos del Vehiculo <---\n");
				fprintf(ArchFactura,"\n\t  Matricula: %s      Anno: %s", datosVehiculo.placa,datosVehiculo.year);
				fprintf(ArchFactura,"\n\n\t  Marca: %s      Descripcion: %s\n",datosVehiculo.marca,datosVehiculo.descripcion);	
			
				fflush(stdin);
				fprintf(ArchFactura,"  ---------------------------------------------------------");	
				fprintf(ArchFactura,"\n \t   ---> Datos del Empleado <---\n");
				fprintf(ArchFactura,"\n\t   Nombre: %s   Cedula: %s \n", datosEmpleado.nombre,datosEmpleado.cedula);	
				
				fprintf(ArchFactura,"  ---------------------------------------------------------");	
				fprintf(ArchFactura,"\n \t   ---> Datos del Servicio <---\n");
				fprintf(ArchFactura,"\n \t  Servicio: %s ", servicio);		
				fprintf(ArchFactura,"\n \t  Material: %s", material);
				fprintf(ArchFactura,"\n \t                             Costo: %s", manobra);
				fprintf(ArchFactura,"\n  --------------------------------------------------------");	
			}
				
		}else{
			printf("\n==>No fue posible generar la factura");
		}		

	}
	fclose(ArchCliente);	
	fclose(ArchEmpleados);
	fclose(ArchRepuestos);
	fclose(ArchServCliente);
	fclose(ArchFactura);
	
	printf("\n\nPresione una tecla para regresar..." ); 
	getchar();	
}
