/*
 * utn_biblioteca.c
 *
 *  Created on: 7 sep. 2021
 *      Author: CSPINELLI
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn_biblioteca.h"
static int myGets (char* cadena, int longitud);
static int esNumerica (char* cadena);
static int getInt (int* pResultado);
static int myGetsFloat (char* cadena, int longitud);
static int esNumericaFloat (char* cadena);
static int getFloat (float* pResultado);
static int myGetsChar (char* cadena, int longitud);
static int esTexto (char* cadena);

/**
 *\brief lee de stdin hasta que encuentr un \n o hasta que haya copiado en cadena
 *un maximo de 'longitud - 1' caracteres.
 *\param pResultado puntero al espacio en memoria donde se copiara la cadena optenida
 *\param longitud define el tamano de la cadena
 *\retorna 0 en el caso de que este todo bien y -1 en caso de error
 */
static int myGets (char* cadena, int longitud)
{

	fflush(stdin);
		//stdin lee el archivo temporal de lo que ingresa el usuario por consola
					//longitud de hasta donde leer
	fgets (cadena, longitud, stdin); //esto sirve para reemplazar el scanf
	cadena [strlen (cadena) - 1] = '\0';

	return 0;

}
/**
 *\brief verifica si un dato es de tipo numerico o no
 *\param pResultado es la cadena de caracteres a ser analizada
 *\retorna 0 en caso de ser falso y 1 en caso de ser positivo
 */
static int esNumerica (char* cadena)
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
/**
 *\brief funsion para transformar la cadena a una variable de tipo int
 *\param pResultado puntero al espacio en memoria donde se almacenara el resultado de la funsion
 *\return retorna 0 en el caso de que este todo bien y -1 en caso de error
 */
static int getInt (int* pResultado)
{
	int retorno;
	char buffer [7500];
	if (myGets(buffer, sizeof (buffer))== 0 && esNumerica(buffer))
	{
		retorno = 0;
		*pResultado = atoi(buffer); //se transforma el dato string a un tipo de dato int
	}
	return retorno;
}
/**
 *\brief solicita un numero al usuario, luego de verificarlo devuelve el resultado
 *\param pResultado es el punter al espacio en memoria donde se almacenara el resultado de la funsion
 *\param mensaje es el mensaje que se mostrara al usuario
 *\param mensajeError es el mensaje de error que se le mostrara al usuario en caso de que ingrese un dato no valido
 *\param minimo es el minimo que sera aceptado
 *\param maximo es el maximo que sera aceptado
 *\param reintentos son los reintentos que tendra el usuario para ingresar el dato correctamente
 *\return 0 si se optuvo el dato o -1 en el caso de que no
 */
int utn_getNumeroInt (int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int bufferInt = -1;
	int retorno;
	int i;

	if (minimo<maximo){
	for (i = 0; i <= reintentos; i++){
		if (pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos != 0){
			printf ("%s", mensaje);
			if (getInt (&bufferInt) == 0 && bufferInt>=minimo && bufferInt<=maximo){
				*pResultado = bufferInt;
				retorno = 0;
				break;
				}else{
					retorno = 1;
					printf ("%s\n",mensajeError);}
		}
	}
	}
	return retorno;
}

static int myGetsFloat (char* cadena, int longitud)
{

	fflush(stdin);
		//stdin lee el archivo temporal de lo que ingresa el usuario por consola
					//longitud de hasta donde leer
	fgets (cadena, longitud, stdin); //esto sirve para reemplazar el scanf
	cadena [strlen (cadena) - 1] = '\0';

	return 0;

}
/**
 *\brief verifica si un dato es de tipo numerico o no
 *\param pResultado es la cadena de caracteres a ser analizada
 *\retorna 0 en caso de ser falso y 1 en caso de ser positivo
 */
static int esNumericaFloat (char* cadena)
{
	int retorno = 1;
	int i=0;
	int contSigno = 0;
	int contPuntos = 0;
	while (cadena [i] != '\0' && (retorno == 1))
	{
		if (cadena [i] == '-')
		{
			contSigno++;
		}
		if (cadena [i] == '.')
		{
			contPuntos++;
		}
		if (isdigit (cadena [i]) || (cadena [0] == '-') || (cadena [i] == '.')){
			retorno = 1;
		}
		else
		{
			retorno = 0;
		}
		i++;
	}
	if (contSigno > 1 || contPuntos > 1){
		retorno = 0;
	}
	return retorno;
}
/**
 *\brief funsion para transformar la cadena a un numero float
 *\param pResultado puntero al espacio en memoria donde se almacenara el resultado de la funsion
 *\retorna 0 en el caso de que este todo bien y -1 en caso de error
 */
static int getFloat (float* pResultado)
{
	int retorno;
	char buffer [7500];
	if (myGetsFloat(buffer, sizeof (buffer))== 0 && esNumericaFloat(buffer))
	{
		retorno = 0;
		*pResultado = atof(buffer); //se transforma el dato string a un tipo de dato float
	}
	return retorno;
}
/**
 *\brief solicita un numero al usuario, luego de verificarlo devuelve el resultado
 *\param pResultado es el punter al espacio en memoria donde se almacenara el resultado de la funsion
 *\param mensaje es el mensaje que se mostrara al usuario
 *\param mensajeError es el mensaje de error que se le mostrara al usuario en caso de que ingrese un dato no valido
 *\param minimo es el minimo que sera aceptado
 *\param maximo es el maximo que sera aceptado
 *\param reintentos son los reintentos que tendra el usuario para ingresar el dato correctamente
 *\return 0 si se optuvo el dato o -1 en el caso de que no
 */
int utn_getNumeroFloat (float* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	float bufferFloat=-1;
	int retorno;
	int i;

	if (minimo<maximo){
	for (i = 0; i <= reintentos; i++){
		if (pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos != 0){
			printf ("%s", mensaje);
			if (getFloat (&bufferFloat) == 0 && bufferFloat>=minimo && bufferFloat<=maximo){
				*pResultado = bufferFloat;
				retorno = 0;
				break;
				}else{
					retorno = 1;
					printf ("%s\n",mensajeError);}
		}
	}
	}
	return retorno;
}

static int myGetsChar (char* cadena, int longitud)
{
	int indexFinal;
	fflush(stdin);
		//stdin lee el archivo temporal de lo que ingresa el usuario por consola
					//longitud de hasta donde leer
	fgets (cadena, longitud, stdin); //esto sirve para reemplazar el scanf
	indexFinal = strlen (cadena) - 1;
	if (cadena [indexFinal] == '\n')
		{
			cadena [indexFinal] = '\0';
 		}
	return 0;

}
/**
 *\brief verifica si un dato es de tipo texto o no
 *\param pResultado es la cadena de caracteres a ser analizada
 *\retorna 0 en caso de ser positivo y 1 en caso de ser negativo
 */

static int esTexto (char* cadena)
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
/**
 *\brief solicita una cadena de texto al usuario, luego de verificarlo devuelve el resultado
 *\param pResultado es el punter al espacio en memoria donde se almacenara el resultado de la funsion
 *\param mensaje es el mensaje que se mostrara al usuario
 *\param mensajeError es el mensaje de error que se le mostrara al usuario en caso de que ingrese un dato no valido
 *\param minimo es el minimo que sera aceptado
 *\param maximo es el maximo que sera aceptado
 *\param reintentos son los reintentos que tendra el usuario para ingresar el dato correctamente
 *\return 0 si se optuvo el dato o -1 en el caso de que no
 */
int utn_getText(char pResultado[], int len, char* mensaje, char* mensajeError, int reintentos)
{
    int retorno = -1;
    int i;
    for(i=0; i<=reintentos; i++)
    {
        if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos >= 0)
        {
            printf("%s", mensaje);
            if ((myGetsChar (pResultado, len)==0) && esTexto(pResultado) ==0)
            {
                retorno = 0;
                break;
            }
            else
                printf("%s", mensajeError);

        }
    }
    return retorno;
}

