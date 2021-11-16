#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete(Employee* this, int indice);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_funcionSort(void* pEmpleado1, void* pEmpleado2);
int employee_modificar(Employee* this, int indice);
int employee_List(Employee* this);
int employee_imprimir(Employee* auxEmpleado, int indice);
Employee* employee_newParametrosAdd(int idStr,char* nombreStr,int horasTrabajadasStr, int sueldoStr);


#endif // employee_H_INCLUDED
