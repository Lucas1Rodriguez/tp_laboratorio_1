#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "utn_biblioteca.h"
#include "Validacion.h"

static int getFieldToModify(int* selectedField);


Employee* employee_new()
{
	Employee* pEmployeeAux = NULL;

	pEmployeeAux = (Employee*) malloc(sizeof(Employee));

	return pEmployeeAux;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* pEmployeeAux = NULL;

	pEmployeeAux = employee_new();
	if(pEmployeeAux != NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		if(employee_setNombre(pEmployeeAux,nombreStr) == -1 ||
			employee_setId(pEmployeeAux,atoi(idStr)) == -1 ||
		employee_setHorasTrabajadas(pEmployeeAux,atoi(horasTrabajadasStr)) == -1 ||
		employee_setSueldo(pEmployeeAux,atoi(sueldoStr)))
		{
			free(pEmployeeAux);
			printf("algo salio mal\n");
		}
	}
	return pEmployeeAux;
}

/*void employee_delete(Employee* this, int indice)
{
	if(this != NULL && ll_len(this)>0 && indice >=0)
	{
		ll_remove(this,indice);
	}
}*/

int employee_setId(Employee* this,int id)
{
	int retorno = -1;

	if(this != NULL && id >= 0)
	{
		retorno = 0;
		this->id = id;
	}
	return retorno;
}
int employee_getId(Employee* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}

int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(esTexto(nombre)==0){
			retorno = 0;
			strncpy(this->nombre,nombre,128);
		}
	}
	return retorno;
}

int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre,this->nombre,128);
	}
	return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL)
	{
		retorno = 0;
		this->horasTrabajadas = horasTrabajadas;
	}
	return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		retorno = 0;
		*horasTrabajadas =this->horasTrabajadas;
	}
	return retorno;
}

int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this != NULL)
	{
		retorno = 0;
		this->sueldo = sueldo;
	}
	return retorno;
}
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		retorno = 0;
		*sueldo = this -> sueldo;
	}
	return retorno;
}

int employee_funcionSort(void* pEmpleado1, void* pEmpleado2)
{
	Employee* emp1 = (Employee*) pEmpleado1;
	Employee* emp2 = (Employee*) pEmpleado2;
	char auxNombre1[128];
	char auxNombre2[128];
	int aux;
	int retorno;
		employee_getNombre(emp1,auxNombre1);
		employee_getNombre(emp2,auxNombre2);
		aux = strcmp(auxNombre1,auxNombre2);
		if(aux>0)
		{
			retorno = 1;
		}
		else if(aux==0)
		{
			retorno = 0;
		}
		else
		{
			retorno = -1;
		}
	return retorno;
}

int employee_modificar(Employee* this, int indice)
{
	int retorno=-1;
	int auxSueldo;
	char auxNombre[128];
	int auxHorasTrabajadas;
	int opcion;
	if(this !=NULL)
	{
		if(getFieldToModify(&opcion)==1)
		{
			retorno=1;
			switch (opcion)
			{
			case 1:
				if(employee_getNombre(this,auxNombre)==1)
				{
					employee_setNombre(this,auxNombre);
				}
				break;
			case 2:
				if(employee_getSueldo(this,&auxSueldo)==1)
				{
					employee_setSueldo(this,auxSueldo);
				}
				break;
			case 3:
				if(employee_getHorasTrabajadas(this,&auxHorasTrabajadas)== 1)
				{
					employee_setHorasTrabajadas(this,auxHorasTrabajadas);
				}
				break;
			}
		}
	}
	return retorno;
}

static int getFieldToModify(int* selectedField)
{
	int retorno=-1;
	int auxSelectItem;

	if(utn_getNumeroInt(&auxSelectItem, "\nElegi la opcion:\n 1-Nombre del empleado\n 2-Sueldo del empleado\n 3- Cantidad de horas trabajadas del empleado", "Error",1 , 3, 3)==0)
	{
		retorno = 1;
		*selectedField= auxSelectItem;
	}
	return retorno;
}

int employee_List(Employee* this)
{
	int retorno = -1;
	int auxSueldo;
	char auxNombre[128];
	int auxHorasTrabajadas;
	int auxid;
		if(employee_getNombre(this,auxNombre)!=-1)
		{

			if(employee_getSueldo(this,&auxSueldo)!=-1)
			{

				if(employee_getHorasTrabajadas(this,&auxHorasTrabajadas)!=-1)
				{

					if(employee_getId(this,&auxid)!=-1)
					{
						retorno = 1;
						printf("Id: %d Nombre: %s Horas Trabajadas : %d Sueldo: %d",auxid,auxNombre,auxHorasTrabajadas,auxSueldo);
					}
				}
			}
		}
	return retorno;
}
int employee_imprimir(Employee* auxEmpleado, int indice)
{
	int retorno=-1;
	int auxId;
	int auxHorasTrabajadas;
	int auxSueldo;
	char auxnombre[128];

	employee_getId(auxEmpleado,&auxId);
	employee_getNombre(auxEmpleado,auxnombre);
	employee_getHorasTrabajadas(auxEmpleado,&auxHorasTrabajadas);
	employee_getSueldo(auxEmpleado,&auxSueldo);

	if(auxEmpleado!=NULL && indice>=0)
	{
		printf("id:%d - nombre:%s - horas:%d - salario:%d \n",auxId,auxnombre,auxHorasTrabajadas,auxSueldo);
		retorno=0;
	}
	return retorno;
}
Employee* employee_newParametrosAdd(int idStr,char* nombreStr,int horasTrabajadasStr, int sueldoStr)
{
    Employee* aux = employee_new();
	if(idStr>=0 && nombreStr != NULL && horasTrabajadasStr >=0 && sueldoStr>=0)
	{
		if(aux != NULL)
		{
			if(employee_setId(aux, idStr)==1 ||
			employee_setNombre(aux, nombreStr)==1 ||
			employee_setHorasTrabajadas(aux, horasTrabajadasStr)==1 ||
			employee_setSueldo(aux, sueldoStr)==1)
			{
				printf("Algo salio mal\n");
			}
		}
    }
    return aux;
}
