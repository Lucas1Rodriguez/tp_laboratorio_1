/*
 ============================================================================
 Name        : TP2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ArrayEmployee.h"
#include "utn_biblioteca.h"

#define EMPLOYEE_LEN 1000
int main(void) {
		setbuf(stdout,NULL);

		Employee employeeList[EMPLOYEE_LEN];
		//llamo a funcion de inicializar
		initEmployees(employeeList,EMPLOYEE_LEN);
		//llamo a la funcion menu
		menuEmployee(employeeList, EMPLOYEE_LEN);

	return EXIT_SUCCESS;
}
