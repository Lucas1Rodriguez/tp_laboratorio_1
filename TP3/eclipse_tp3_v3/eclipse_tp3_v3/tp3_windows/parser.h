/*
 * parser.h
 *
 *  Created on: 14 nov. 2021
 *      Author: USURIO
 */

#ifndef ECLIPSE_TP3_V3_ECLIPSE_TP3_V3_TP3_WINDOWS_SRC_PARSER_H_
#define ECLIPSE_TP3_V3_ECLIPSE_TP3_V3_TP3_WINDOWS_SRC_PARSER_H_

int parser_EmployeeFromTextLec(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromTextEsc(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinaryEsc(FILE* pFile, LinkedList* pArrayListEmployee);



#endif /* ECLIPSE_TP3_V3_ECLIPSE_TP3_V3_TP3_WINDOWS_SRC_PARSER_H_ */
