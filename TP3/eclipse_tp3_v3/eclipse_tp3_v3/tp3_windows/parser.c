#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromTextLec(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int cantidad;
	char bufferId[1024];
	char bufferNombre[1024];
	char bufferHorasTrabajadas[1024];
	char bufferSueldo[1024];

	Employee* newEmployee;

	if(pFile !=NULL && pArrayListEmployee != NULL)
	{

	fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);

		while(!feof(pFile))
		{
			cantidad = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
			if(cantidad < 4)
			{
				break;
			}

			newEmployee = employee_newParametros(bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);

			ll_add(pArrayListEmployee,newEmployee);

			retorno=0;
		}
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */


int parser_EmployeeFromTextEsc(FILE* pFile , LinkedList* pArrayListEmployee)
{
	Employee* auxEmployee = NULL;
	int retorno=-1;
	int id;
	char nombre[128];
	int cantidadHoras;
	int sueldo;

	if(pFile!=NULL && pArrayListEmployee !=NULL)
	{
		fprintf(pFile, "id,nombre,horasTrabajadas,sueldo\n");

		for(int i=0; i<ll_len(pArrayListEmployee); i++)
		{
			auxEmployee = (Employee*)ll_get(pArrayListEmployee, i);
			if(auxEmployee!=NULL)
			{
				if(employee_getId(auxEmployee, &id)==0 &&
				employee_getNombre(auxEmployee, nombre)==0 &&
				employee_getHorasTrabajadas(auxEmployee, &cantidadHoras)==0 &&
				employee_getSueldo(auxEmployee, &sueldo)==0)
				{
				fprintf(pFile,"%d,%s,%d,%d\n", id, nombre, cantidadHoras, sueldo);
				retorno=0;
				}
			}
		}
	}

	return retorno;
}



int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	Employee* auxEmpleados=NULL;
	int retorno=-1;
	int cantidad=0;

	Employee aux;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		while(!feof(pFile))
		{
			cantidad = fread(&aux, sizeof(Employee),1,pFile);
			if(cantidad<1)
			{
				break;
			}
			auxEmpleados = employee_newParametrosAdd(aux.id, aux.nombre, aux.horasTrabajadas, aux.sueldo);
			if(auxEmpleados!=NULL)
			{
			ll_add(pArrayListEmployee, auxEmpleados);
			retorno=0;
			}
		}
	}
    return retorno;
}

int parser_EmployeeFromBinaryEsc(FILE* pFile, LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int cantidad;
	int cantidadAux=0;

	Employee* empleado;

	if(pFile != NULL && pArrayListEmployee!=NULL)
	{
		for(int i=0; i< ll_len(pArrayListEmployee); i++)
		{
			empleado = (Employee*)ll_get(pArrayListEmployee, i);

			if(empleado!=NULL)
			{
				cantidad = fwrite(empleado, sizeof(Employee),1,pFile);

				if(cantidad<1)
				{
					break;
				}

				cantidadAux++;

				if(cantidadAux==ll_len(pArrayListEmployee))
				{
					retorno=0;
				}
			}
		}
	}
	return retorno;
}

