/*
 * Validacion.c
 *
 *  Created on: 12 nov. 2021
 *      Author: USURIO
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Validacion.h"

int esNumerica (char* cadena)
{
	int retorno = 1;
	int i=0;
	if (cadena [0] == '-') //si en la posicion 0 el usuario ingresa un - el array comienza a almacenar los numeros desde la pocision 1
	{
		i = 1;
	}
	for (;cadena [i] > '\0'; i++){
		if (cadena [i] < '0' || cadena [i] > '9')  //solo se pueden ingresar numeros del 0 al 9
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

int esTexto (char* cadena)
{
	int i= 0;
	int retorno = -1;

	if(cadena!=NULL&&strlen(cadena)>0)
	{
		retorno= 0;

		while(cadena[i]!='\0')
		{
			if((cadena[i] >= 'A' && cadena[i] <= 'z' ) || cadena[i] == 32 || cadena[i] == '.' || cadena[i] == ',' || cadena[i] == '-'|| cadena[i] == '_')
			{
				if(cadena[i] > 'Z' && cadena[i] < 'a')
				{
					retorno = -1;
					break;
				}
				i++;

			}
			else
			{
				retorno= -1;
				break;
			}
		}
	}
	return retorno;
}
