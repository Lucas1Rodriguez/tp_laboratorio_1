#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayEmployee.h"
#include "utn_biblioteca.h"

//prototipos globales
static int getId(void);
static int getFieldToModify(int*selectedField);
static int getName (char employeeName[]);
static int getLastName(char employeeLastName[]);
static int getSector(int *employeeSector);
static int getSalary(float *employeeSalary);
static int SelectModify(void);

#define NAME_AND_LAST_NAME_LEN 51


//Se inicializa la bandera isEmpty
int initEmployees(Employee employeeList[],int len)
{
	int index;
	int retorno = -1;

	if(employeeList != NULL && len > 0)
	{
		for(index=0; index < len; index++)
		{
			employeeList[index].isEmpty = 1;
		}
		retorno=1;
	}
	return retorno;
}

//cargo los empleados
//llamo a la funcion pedir,numero,texto y float
//devuelvo el resultado por puntero
//cambio el valor de la bandera a 0
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector)
{
	int retorno=-1;
	int auxSector;
	float auxSalary;
	char auxName[NAME_AND_LAST_NAME_LEN];
	char auxLastName[NAME_AND_LAST_NAME_LEN];

	if(list!=NULL)
	{
		if(utn_getText(auxName, 128 , "Ingrese el nombre del empleado: ", "Error\n",3)==0)
		{
			if(utn_getText(auxLastName,60, "\nIngrese el apellido del empleado: ", "Error\n",3)==0)
			{
				if(utn_getNumeroInt(&auxSector, "\nIngrese el sector del empleado:  ", "Error\n",1, 1000, 3)==0)
				{
					if(utn_getNumeroFloat(&auxSalary, "\nIngrese el salario del empleado:  ", "Error\n",1, 100000, 3)==0)
					{
						list-> sector= auxSector;
						list->salary= auxSalary;
						list->id = getId();
						strncpy(list->name,auxName,sizeof(list->name));
						strncpy(list->lastName,auxLastName,sizeof(list->lastName));
						list->isEmpty = 0;
						retorno=0;
					}
				}
			}
		}
	}
	return retorno;
}

//Funcion privada del archivo
//Genero un id y lo retorno
static int getId(void)
{
	static int contador=0;
	contador++;//es global : mantiene su valor
	return contador;
}
//Imprimo las posiciones que tengan la bandera isEmpty iniciada
int printEmployees(Employee* pEmployee)
{
	if(pEmployee->isEmpty ==0)
	{
		printf("id: %d, %s, %s, %d, %f\n",pEmployee->id, pEmployee->name, pEmployee->lastName, pEmployee->sector, pEmployee->salary);
	}
	return 1;
}
//recorro el array
//verifico que exista el id
//retorno la posicion
int findEmployeeById(Employee* pEmployee, int len, int idBuscado)
{
	int status=-1;
	int i;

	if(pEmployee!=NULL && len>0 && idBuscado>=0)
	{
		for(i=0; i<len ; i++)
		{
			if( pEmployee[i].id==idBuscado && pEmployee[i].isEmpty == 0)
			{
				status = i;
				break;
			}
		}
	}
	return status;
}
//recorro el array
//verifico que haya espacio
//retorno la posicion
int findEmptyPosition(Employee* pEmployee, int len)
{
	int retorno=-1;
	int i;

	if(pEmployee!=NULL && len>0)
	{
		for(i=0; i<len ;i++)
		{
			if(pEmployee[i].isEmpty==1)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

//Para eliminar los empleados
//Cambio el isEmpty del id recibido a 1
int removeEmployee(Employee EmployeeList[], int len, int idBuscado)
{
	int status = -1;
	if(EmployeeList != NULL)
	{
		status = 1;
		EmployeeList[idBuscado].isEmpty=1;
	}
	return status;
}
//Modifico posicion
//Llamo a funcion para seleccionar opcion
//Modifico la opcion elegida
int modifyEmployee(Employee* pEmployee)
{
	int status=-1;
	int idamodificar;
	int auxSector;
	float auxSalary;
	char auxname[NAME_AND_LAST_NAME_LEN];
	char auxLastName[NAME_AND_LAST_NAME_LEN];
	if(pEmployee !=NULL)
	{
		if(getFieldToModify(&idamodificar)==1)
		{
			status=1;
			switch (idamodificar)
			{
			case 1:
				if(getSector(&auxSector)==1)
				{
					pEmployee->sector =auxSector;
				}
				break;
			case 2:
				if(getSalary(&auxSalary)==1)
				{
					pEmployee->salary = auxSalary;
				}
				break;
			case 3:
				if(getName(auxname)==1)
				{
					strncpy(pEmployee->name, auxname, NAME_AND_LAST_NAME_LEN);
				}
				break;
			case 4:
				if(getLastName(auxLastName)==1)
				{
					strncpy(pEmployee->lastName, auxLastName, NAME_AND_LAST_NAME_LEN);
				}
				break;
			}
		}
	}
	return status;
}
//Funcion privada del archivo
//Llamo a la funcion pedir int
//Retorno por puntero el valor ingresado para la funcion modificar
static int getFieldToModify(int*selectedField)
{
	int status=-1;
	int auxSelectItem;

	if(utn_getNumeroInt(&auxSelectItem, "\nElegi la opcion:\n 1-sector\n 2-salario\n 3-nombre\n 4-apellido\n ", "Error",1 , 4, 2)==0)
	{
		status =1;
		*selectedField= auxSelectItem;
	}
	return status;
}
//Funcion privada del archivo
//Llamo a funcion pedir int
//Retorno el valor ingresado para la funcion ordenamiento
static int SelectModify(void)
{
	int status;
	int auxSelecionItem;

	if(utn_getNumeroInt(&auxSelecionItem, "\n1)Ordenar A-Z:\n2)Ordenar Z-A\n", "Error",1 , 2, 1)==0)
	{
		status = auxSelecionItem;
	}
	return status;
}
//Funcion privada del archivo
//Llamo a funcion pedir char
//Retorno por puntero el valor ingresado para la funcion modificar
static int getName (char empleadoNombre[])
{
	int status =-1;
	char mensaje[180];
	char auxName[NAME_AND_LAST_NAME_LEN];
	strncpy(mensaje, "\nIngrese nombre del empleado: ",sizeof(mensaje));
	if(utn_getText(auxName, NAME_AND_LAST_NAME_LEN , mensaje, "Error",1)==0)
	{
		status =1;
		strncpy(empleadoNombre, auxName, NAME_AND_LAST_NAME_LEN);
	}
	return status;
}

//Funcion privada del archivo
//Llamo funcion pedir char
//Retorno por puntero el valor ingresado para la funcion modificar
static int getLastName(char employeeLastName[])
{
	int status =-1;
	char mensaje[180];
	char auxLastName[NAME_AND_LAST_NAME_LEN];
	strncpy(mensaje, "\nIngrese apellido del empleado:",sizeof(mensaje));
	if(utn_getText(auxLastName, NAME_AND_LAST_NAME_LEN , mensaje, "Error",1)==0)
	{
		status =1;
		strncpy(employeeLastName, auxLastName, NAME_AND_LAST_NAME_LEN);
	}
	return status;
}
//Funcion privada del archivo
//Llamo funcion pedir int
//Retorno por puntero el valor ingresado para la funcion modificar
static int getSector(int *EmployeeSector)
{
	int status =-1;
	char mensaje[180];
	int auxSector;
	strncpy(mensaje,"\nIngrese sector del empleado:", sizeof(mensaje));
	if(utn_getNumeroInt(&auxSector, mensaje, "Error",0, 10, 3)==1)
	{
		status=1;
		*EmployeeSector=auxSector;
	}
	return status;
}

//Funcion privada del archivo
//Llamo a funcion pedir float
//Retorno por puntero el valor ingresado para la funcion modificar
static int getSalary(float *employeeSalary)
{
	int status =-1;
	char mensaje[180];
	float auxSalary;
	strncpy(mensaje,"\nIngrese salario del empleado:", sizeof(mensaje));
	if(utn_getNumeroFloat(&auxSalary, mensaje, "Error",1, 100000, 3)==0)
	{
		status=1;
		*employeeSalary = auxSalary;
	}
	return status;
}
//Funcion ordenamiento
//Llamo a funcion seleccionar
//Ordeno segun la opcion ingresada
int sortEmployeesByLastNameAndSector(Employee *employeeList, int limit)
{
	int status=-1;
	int flagSwap;
	int aux;
	Employee buffer;

	if(employeeList != NULL && limit>=0)
	{
		flagSwap=0;
		if(SelectModify()==0)
		{
			do{
				flagSwap=0;
				for(int i=0; i<limit-1; i++)
				{
					aux = strncmp(employeeList[i].lastName,employeeList[i+1].lastName,NAME_AND_LAST_NAME_LEN);
					if(aux >0 || (aux==0 && employeeList[i].sector < employeeList[i+1].sector))
					{
					flagSwap = 1;
					buffer = employeeList[i];
					employeeList[i] = employeeList[i+1];
					employeeList[i+1] = buffer;
					status=0;
					}
				}
				limit--;
			}while(flagSwap);
		}
		else
		{
			do{
				flagSwap=0;
			for(int i=0; i<limit-1; i++)
			{
				aux = strncmp(employeeList[i].lastName,employeeList[i+1].lastName,NAME_AND_LAST_NAME_LEN);
				if(aux < 0 || (aux==0 && employeeList[i].sector < employeeList[i+1].sector))
				{
					flagSwap = 1;
					buffer = employeeList[i];
					employeeList[i] = employeeList[i+1];
					employeeList[i+1] = buffer;
					status=0;
			   }
			}
			limit--;
			}while(flagSwap);
		}
	}
	return status;
}
//Funcion promedio
//Recorro el array
//Guardo un contador y un acumulador
//Saco el promedio
int average(Employee *employeelist, int len)
{
	int status=-1;
	int cont=0;
	float acum=0;
	float average=0;
	int contMasPromedio=0;

	for(int i=0; i <len ;i++)
	{
		if(employeelist[i].isEmpty==0)
		{
			cont++;
			acum = acum + employeelist[i].salary;
			status=0;
		}
	}
	average= acum/cont;
	for(int indice = 0; indice <len ;indice++)
	{
		if(employeelist[indice].isEmpty==0 && employeelist[indice].salary > average)
		{
			contMasPromedio++;
		}
	}
	printf("\nEl promedio es: %f\n",average);
	printf("Cobran mas que el promedio: %d",contMasPromedio);
		return status;
}
//Menu
//Llamo a funcion pedir int para que usuario eliga la opcion del menu
void menuEmployee (Employee employeeList[], int len)
	{
		int option;
		int lugarLibre;
		int flag;
		do{
			if (utn_getNumeroInt(&option, "\nBienvenido \n1)Altas:\n2)Modificar:\n3)Baja:\n4)Informar:", "\nError opcion Invalida",  1, 4, 5)==0)
				{
				switch (option)
					{
						case 1:
							//Busco lugar libre
							lugarLibre = findEmptyPosition(employeeList, len);
							//Pido y cargo los datos ingresados
							addEmployee(&employeeList[lugarLibre], len, employeeList[lugarLibre].id, employeeList[lugarLibre].name, employeeList[lugarLibre].lastName, employeeList[lugarLibre].salary, employeeList[lugarLibre].sector);
							flag=1;
							break;
						case 2:
							//verifico que se haya cumplido la opcion 1
							if(flag==1)
							{
								//recorro el array para imprimir los datos cargados
								for(int i=0;i< len ;i++)
								{
									printEmployees(&employeeList[i]);
								}

								int idIngresado;
								int indexAModif;
								//pido que ingrese un numero a buscar
								//verifico que exista
								//llamo a la funcion modificar y imprimo
								if (utn_getNumeroInt(&idIngresado, "\ningrese ID\n", "Error", 1, 9999, 5) ==0)
								{
									indexAModif = findEmployeeById(employeeList,len,idIngresado);
									if(indexAModif >=0)
									{
										modifyEmployee(&employeeList[indexAModif]);
										printEmployees(&employeeList[indexAModif]);
									}
								}
							}
							else{
								printf("Error, no hay empleados cargados\n");
							}
							break;
						case 3:
							//verifico que la opcion 1 se haya ingresado
							if(flag ==1)
							{
								//recorro el array para imprimir los datos cargados
								for(int i=0;i< len ;i++)
								{
									printEmployees(&employeeList[i]);
								}
									int idingresado;
									int idDarBaja;
									//pido que ingrese un numero a buscar
									//verifico que exista
									//llamo a la funcion eliminar y imprimo
									if (utn_getNumeroInt(&idingresado, "\ningrese ID a eliminar\n", "Error", 1, 9999, 5) ==0)
									{
										idDarBaja = findEmployeeById(employeeList,len,idingresado);
										if(idDarBaja>=0)
										{
											removeEmployee(employeeList,len,idingresado);
											printf("Empleado eliminado\n");
										}
									}
							}
							else
							{
								printf("Error, no hay empleados cargados\n");
							}
							break;
						case 4:
							//verifico que la opcion 1 se haya ingresado
							if(flag==1)
							{
								//llamo funcion ordenar
								//verifico que la funcion ordenar devuelva 0
								//imprimo
								if(sortEmployeesByLastNameAndSector(employeeList, len)==0)
								{
									for(int index=0;index< len ;index++)
									{
										printEmployees(&employeeList[index]);
									}
								}
									average(employeeList,len);
							}
							else
							{
								printf("\nError, No hay empleados cargados\n");
							}

						break;
					}
				}
		}while (option <=4);
	}
