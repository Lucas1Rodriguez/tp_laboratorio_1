#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "utn_biblioteca.h"
#include "parser.h"
#include "Controller.h"
#define NOMBRE_LEN 128

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE *auxP;
	auxP =fopen(path,"r");
	if(auxP!=NULL)
	{
		if(parser_EmployeeFromTextLec(auxP, pArrayListEmployee)==0)
		{
			retorno=0;
		}
	}
	else
	{
		printf("Hay un error");
	}
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE *auxP;
	auxP =fopen(path,"rb");

	if(auxP!=NULL)
	{
		if(parser_EmployeeFromBinary(auxP, pArrayListEmployee)==0)
		{
		retorno=0;
		}
	}
	else
	{
		retorno=-1;
		printf("hay un error");
	}
	fclose(auxP);
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	char auxnombre[128];
	int auxsueldo;
	int auxhorasTrabajadas;
	int id;
	Employee* NewEmployee;
	Employee* auxId;

	if(utn_getText(auxnombre, 128 , "Ingrese el nombre del empleado:\n", "Error\n",3)==0 &&
	utn_getNumeroInt(&auxhorasTrabajadas, "Ingrese la cantidad de horas:\n", "Error\n",1, 1000, 3)==0 &&
	utn_getNumeroInt(&auxsueldo, "Ingrese el salario del empleado:\n  ", "Error\n",1, 100000, 3)==0)
	{
		auxId= ll_get(pArrayListEmployee, ll_len(pArrayListEmployee)-1);

		employee_getId(auxId, &id);

		id++;
		NewEmployee = employee_newParametrosAdd(id,auxnombre,auxhorasTrabajadas,auxsueldo);
		retorno=0;
	}

	if(NewEmployee!=NULL)
	{
		ll_add(pArrayListEmployee, NewEmployee);
		retorno=0;
	}

	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	Employee* aux;
	int retorno=-1;
	int len;
	int idBuscado;
	int id;
	char auxnombre[128];
	int auxCantidadHoras;
	int auxSueldo;
	int opcion;

	if(pArrayListEmployee!=NULL)
	{
		len = ll_len(pArrayListEmployee);
		if(len>=0)
		{
			controller_ListEmployee(pArrayListEmployee);

			utn_getNumeroInt(&id,"Ingrese id del empleado a modificar\n" , "Error\n", 1, 2000, 3);

			idBuscado = Controller_buscarPorId(pArrayListEmployee, len, id);

			if(idBuscado!=-1)
			{
				aux = (Employee*)ll_get(pArrayListEmployee, idBuscado);

				employee_imprimir(aux, idBuscado);

				printf("1)Modificar nombre\n");
				printf("2)Modificar cantidad de horas\n");
				printf("3)Modificar sueldo\n");
				utn_getNumeroInt(&opcion, "Ingrese opcion a modificar\n", "Error, ingrese opcion a modificar", 1, 3, 3);
				retorno = 0;
				switch(opcion)
				{
					case 1:
						utn_getText(auxnombre, 128, "Ingrese nuevo nombre:\n", "Error, Ingrese nuevo nombre\n", 3);

						employee_setNombre(aux,auxnombre);

						break;
					case 2:
						utn_getNumeroInt(&auxCantidadHoras, "Ingrese cantidad de horas a modificar\n", "Error, ingrese hora a modificar", 1, 1000, 3);

						employee_setHorasTrabajadas(aux, auxCantidadHoras);

						break;
					case 3:
						utn_getNumeroInt(&auxSueldo, "Ingrese sueldo a modificar\n", "Error, ingrese sueldo a modificar", 1, 10000, 3);

						employee_setSueldo(aux, auxSueldo);

						break;
				}
			}
			else
			{
				printf("No se encontro el id.");
			}
		}
		else
		{
			printf("No hay nada cargado.");
		}
	}

    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */


int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int auxId;
	int idBuscado;
	int retorno = -1;
	for(int i = 0; i<ll_len(pArrayListEmployee);i++)
	{
		controller_ListEmployee(pArrayListEmployee);

		if(utn_getNumeroInt(&idBuscado,"Ingrese un id a eliminar","Error. No se encontro el id",1,ll_len(pArrayListEmployee),3) == 0)
		{
			auxId = Controller_buscarPorId(pArrayListEmployee, ll_len(pArrayListEmployee), idBuscado);
			ll_remove(pArrayListEmployee,auxId);
			retorno = 0;
			break;
		}
	}
    return retorno;
}


/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	Employee* aux;
	if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		for(i =0;i< ll_len(pArrayListEmployee); i++)
		{
			aux = (Employee*)ll_get(pArrayListEmployee,i);
			employee_imprimir(aux,i);
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int opcion;
	int retorno = -1;

	utn_getNumeroInt(&opcion,"Elija una opcion de ordenamiento: \n1.Por nombre \n2.Por id \n","Error. Elija un numero valido",1,2,3);
	switch(opcion)
	{
	case 1:
		utn_getNumeroInt(&opcion,"Elija una opcion de ordenamiento: \n0.Ascendente \n1.Descendente \n","Error. Elija un numero valido",0,1,3);
		if(opcion == 0)
		{
			ll_sort(pArrayListEmployee,employee_funcionSort,0);
			controller_ListEmployee(pArrayListEmployee);
			retorno = 0;
		}
		else if(opcion == 1)
		{
			ll_sort(pArrayListEmployee,employee_funcionSort,1);
			controller_ListEmployee(pArrayListEmployee);
			retorno = 0;
		}
		break;
	case 2:
		utn_getNumeroInt(&opcion,"Elija una opcion de ordenamiento: \n0.Ascendente \n1.Descendente \n","Error. Elija un numero valido",0,1,3);
		if(opcion == 0)
				{
					ll_sort(pArrayListEmployee,OrdenamientoPorId,0);
					controller_ListEmployee(pArrayListEmployee);
					retorno = 0;
				}
				else if(opcion == 1)
				{
					ll_sort(pArrayListEmployee,OrdenamientoPorId,1);
					controller_ListEmployee(pArrayListEmployee);
					retorno = 0;
				}
		break;
	}
	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* aux;
	if(pArrayListEmployee!=NULL)
	{
		aux = fopen(path,"w");

		if(aux!=NULL)
		{
			parser_EmployeeFromTextEsc(aux, pArrayListEmployee);
			retorno=0;
		}
	}
	fclose(aux);
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* aux;

	if(pArrayListEmployee!=NULL)
	{
		aux = fopen(path,"wb");
		if(aux!=NULL)
		{
			if(parser_EmployeeFromBinaryEsc(aux, pArrayListEmployee)==0)
			{
				retorno=0;
			}
		}
	}
	fclose(aux);
	return retorno;
}
int Controller_buscarPorId(LinkedList* pArrayList,int len, int IdBuscado)
{
	int status=-1;
	int index;
	int idAux;
	Employee* aux;

	if(pArrayList!=NULL && len>0 && IdBuscado>=0 && IdBuscado<=len)
	{

		for(index=0; index<len ; index++)
		{
			aux = (Employee*)ll_get(pArrayList, index);

			employee_getId(aux, &idAux);

			if(idAux==IdBuscado)
			{
				status = index;
				break;
			}
		}
	}
	return status;
}

int OrdenamientoPorId(void* empleado1,void* empleado2)
{
	int retorno=0;
	if(((Employee*)empleado1)->id > ((Employee*)empleado2)->id)
		{
			retorno=1;
		}
		else
		{
			if(((Employee*)empleado1)->id < ((Employee*)empleado2)->id)
			{
				retorno=-1;
			}
			else
			{
				retorno=0;
			}
		}
	return retorno;
}
