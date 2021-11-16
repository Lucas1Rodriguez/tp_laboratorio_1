#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn_biblioteca.h"
#include "parser.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/



int main()
{
	setbuf(stdout,NULL);
    LinkedList* listaEmpleados = ll_newLinkedList();
    int option;
    do{
    	if (utn_getNumeroInt(&option, "\nBienvenido \n1)Cargar los datos de los empleados modo texto:\n2)Cargar los datos de los empleados modo binario:\n3)Alta de empleado:\n4)Modificar datos de empleado:\n5)Baja de empleado:\n6)Listar empleados:\n7)Ordenar empleados:\n8)Guardar los datos de los empleados modo texto:\n9)Guardar los datos de los empleados modo binario:\n10)Salir \n", "\nError opcion Invalida",  1, 10, 5)==0)
    	{
			switch(option)
			{
				case 1:
					// 1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
					if(controller_loadFromText("data.csv",listaEmpleados) ==0)
					{
						printf("Se cargaron los datos como texto");
					}
					else{
						printf("Algo salio mal");
					}
					break;
				case 2:
					// 2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).

					if(controller_loadFromBinary("data2.bin",listaEmpleados) ==0)
					{
						printf("Se cargaron los datos como texto");
					}
					else{
						printf("Algo salio mal");
					}
					break;
				case 3:
					//	3. Alta de empleado
					if(controller_addEmployee(listaEmpleados) == 0)
					{
						printf("Empleado agregado con exito");
					}
					else
					{
						printf("No se pudo cargar al empleado");
					}

					break;
				case 4:
					//	4. Modificar datos de empleado
					if(controller_editEmployee(listaEmpleados) == 0)
					{
						printf("Empleado modificado con exito");
					}
					else
					{
						printf("No se pudo editar al empleado");
					}
					break;
				case 5:
					//	5. Baja de empleado
					if(controller_removeEmployee(listaEmpleados) == 0)
					{
						printf("Empleado borrado con exito");
					}
					else
					{
						printf("No se pudo borrar al empleado");
					}
					break;
				case 6:
					// 6. Listar empleados
					if(controller_ListEmployee(listaEmpleados) == 0)
					{
						printf("Empleados listados");
					}
					else
					{
						printf("No se pudo listar a los empleados");
					}
					break;
				case 7:
					// 7. Ordenar empleados
					if(controller_sortEmployee(listaEmpleados) == 0)
					{
						printf("Empleados ordenados");
					}
					else
					{
						printf("No se pudo ordenar a los empleados");
					}

					break;
				case 8:
					// 8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
					if(controller_saveAsText("data.csv",listaEmpleados) == 0)
					{

						printf("Lista guardada como texto");
					}
					else
					{
						printf("No se pudo guardar como texto");
					}

					break;
				case 9:
					// 9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
					if(controller_saveAsBinary("data2.bin",listaEmpleados) == 0)
					{
						printf("Lista guardada como binario");
					}
					else
					{
						printf("No se pudo guardar como binario");
					}

					break;
				case 10:
					// 10.Salir
					printf("Saliendo");
					break;
			}
    	}
	}while (option <10);
return 0;
}
