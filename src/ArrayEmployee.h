/*
 * employee.h
 *
 *  Created on: 16 oct. 2021
 *      Author: USURIO
 */

#ifndef ARRAYEMPLOYEE_H_
#define ARRAYEMPLOYEE_H_
struct
{
 int id;
 char name[51];
 char lastName[51];
 float salary;
 int sector;
 int isEmpty;
}typedef Employee;
/*int initEmployees(Employee* list, int len);
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector);
int findEmployeeById(Employee* list, int len,int id);
int removeEmployee(Employee* list, int len, int id);
int sortEmployees(Employee* list, int len, int order);
int printEmployees(Employee* list, int length);*/

int initEmployees(Employee employeeList[],int len);
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector);
int printEmployees(Employee* pEmployee);
int findEmployeeById(Employee* pEmployee, int len, int IdBuscado);
int findEmptyPosition(Employee* pEmpoyee, int len);
int removeEmployee(Employee employeeList[], int len, int IdBuscado);
int modifyEmployee(Employee* pEmployee);
void menuEmployee (Employee employeeList[], int len);
int average(Employee *employeelist, int len);
int sortEmployeesByLastNameAndSector(Employee *employeelist, int limite);



#endif /* ARRAYEMPLOYEE_H_ */
