#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
   LinkedList* this;
   this = (LinkedList*) malloc(sizeof(LinkedList*)); //Se crea espacio en memoria dinamica
	if(this!=NULL)//Verifico que no sea NULL
	{
		this->size=0;//Inicio el size en 0
		this->pFirstNode=NULL;//Pongo en NULL el puntero al primer nodo
	}
	return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
	int returnAux = -1;
	if(this!=NULL)
	{
		returnAux = this->size; //Retorno el tamaño de la linkedlist
	}
	return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* nodoAux = NULL;
	int i;
	if(this!=NULL && nodeIndex>=0 && ll_len(this)>nodeIndex)
	{
		nodoAux = this->pFirstNode; //Guardo en una variable el puntero al primer nodo

		for(i = 0; i < nodeIndex; i++)
		{
			nodoAux = nodoAux->pNextNode; //
		}
	}
	return nodoAux;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	 int retorno = -1;
	//construyo un nuevo nodo
	Node* auxNodo;
	Node* pNodoAnterior;

	if(this!=NULL && nodeIndex >=0 && nodeIndex<= this->size)
	{
		auxNodo =(Node*)malloc(sizeof(Node));
		if(auxNodo!=NULL)
		{
			auxNodo->pElement = pElement; //me guardo

			//diferenciar los 3 casos
			if(nodeIndex==0)
			{
				//me quieren agregar el nodo en la primera posicion
				//1)leer el primer nodo de this y guardarlo en pNodo->next
				auxNodo->pNextNode = this->pFirstNode;
				//2)escribir la dire del nuevo nodo dentro del firsNodo de this
				this->pFirstNode = auxNodo;
				//3)aumento el size
				this->size++;
			}
			/*else
			{
				if(nodeIndex == this->size)
				{
					//lo agrego al final
					//1(escribo un NULL en el nodo nuevo por que es el ultimo
					auxNodo->pNextNode=NULL;
					//2)escribir la direccion del nodo nuevo en el pNext del ultimo en la lista
					pNodoAnterior = getNode(this,nodeIndex-1);
					pNodoAnterior->pNextNode = auxNodo;
					//3) aumento el size
					this->size++;
				}*/
				else
				{
					//son los del medio
					//1)obtengo nodo anterior
					pNodoAnterior = getNode(this,nodeIndex-1);
					//2)le leo la dire del siguiente y la escribo en pNext del nodo nuevo
					auxNodo->pNextNode =pNodoAnterior->pNextNode;
					//3)escribo en el pNext del anterior, la dire de nuevo
					pNodoAnterior->pNextNode=auxNodo;
					//4) aumento el size
					this->size++;
				}
				retorno = 0;
		}
	}
	return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	int returnAux = -1;

	if(this!=NULL)
	{
		returnAux = addNode(this,this->size,pElement);
	}

	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
	void* returnAux = NULL;
	Node* pNodo = getNode(this,index);

	if(this!=NULL && index>=0 && index<ll_len(this))
	{
		if(pNodo!=NULL)
		{
			returnAux = pNodo->pElement;
		}
	}
	return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
	int returnAux = -1;
	Node* nodoAux;
	if(this != NULL && index >= 0 && index < this->size)
	{
		nodoAux = getNode(this, index);
		if(nodoAux!= NULL)
		{
			nodoAux->pElement = pElement;
		}
		returnAux = 0;
	}

	return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	 int returnAux = -1;
		Node* pNodo;
		Node* pNodoAnterior;

		if(this != NULL && index>=0 && index< this->size)
		{
			if(index==0)
			{
			//tengo que borrar el primero
				//1)obtengo el nodo a borrar(posicion 0)
				pNodo = this->pFirstNode;//pNodo = getNode(this,0);
				//2)escribo como pFirst el siguiente del nodo que borro
				this->pFirstNode = pNodo->pNextNode;
				//3)Borro el nodo
				free(pNodo);
				//4)size --
				this->size--;
			}
			else
			{
			//tengo que borrar uno del medio
				pNodo = getNode(this,index);
				//1)
				pNodoAnterior = getNode(this,index-1);
				//2)ato el anterior con el siguiente del que voy a borrar
				pNodoAnterior->pNextNode= pNodo->pNextNode;
				//3)borro el nodo
				free(pNodo);
				//4)size--
				this->size--;
			}
			returnAux = 0;
		}
	return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;
	if (this != NULL)
	{
		for (i = ll_len(this); i >= 0; i--)
		{
			ll_remove(this, i);
		}
		returnAux = 0;
	}
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(ll_clear(this)==0)
    	{
    		free(this);
    		returnAux = 0;
    	}

    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    if(this != NULL)
    {
    	for(i = 0;i<ll_len(this);i++)
    	{
    		if(ll_get(this,i) == pElement)
    		{
    			returnAux = i;
    			break;
    		}
    	}
    }


    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(ll_len(this)>0)
    	{
    		returnAux = 0;
    	}
    	else
    	{
    		returnAux = 1;
    	}

    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
	int returnAux = -1;

	if(this!=NULL && index>= 0 && index<= ll_len(this))
	{
		if(addNode(this,index,pElement)==0)
		{
			returnAux = 0;
		}
	}
	return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
	void* returnAux = NULL;
	if(this!=NULL && index>= 0 && index<= ll_len(this))
	{
		returnAux = ll_get(this,index);
		if(returnAux != NULL)
		{
			ll_remove(this,index);
		}
	}
	return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int index;
    if(this != NULL)
    {
    	returnAux = 0;
		index = ll_indexOf(this,pElement);
		if(index >= 0)
		{
			returnAux = 1;
    	}

    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
	void* pElement;
    if(this != NULL && this2 != NULL)
    {
    	returnAux = 0;
    	for(i = 0; i<ll_len(this2);i++)
    	{
    		pElement = ll_get(this2,i);
    		if(ll_contains(this,pElement)==1)
    		{
    			returnAux = 1;
    			break;
    		}
    		else
    		{
    			returnAux = 0;
    			break;
    		}
    	}
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;
    if(this != NULL && from >=0 && from <= ll_len(this))
    {
    	if(to > from && to <= ll_len(this))
    	{
    		cloneArray = ll_newLinkedList();

    		for(i = from; i<to;i++)
    		{
    			pElement = ll_get(this,i);
    			ll_add(cloneArray,pElement);
    		}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;
    if(this != NULL)
    {
    	cloneArray = ll_newLinkedList();
		for(i = 0; i<ll_len(this);i++)
		{
			pElement = ll_get(this,i);
			ll_add(cloneArray,pElement);
		}
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
	 int returnAux =-1;
	 int i;
	 int fSwap=1;
	 void* pElementUno;
	 void* pElementDos;

		if (this!=NULL && pFunc!=NULL)
		{
			if(order == 0 || order == 1)
			{
				if(ll_len(this)>=2)
				{
					while(fSwap==1)
					{
						fSwap=0;

						for(i=0;i<=ll_len(this);i++)
						{
							pElementUno = ll_get(this,i);

							pElementDos = ll_get(this,i+1);

							if(pElementUno!= NULL && pElementDos!= NULL)
							{
									if (order == 1)
									{
										if(pFunc(pElementUno, pElementDos) >0)
										{
											ll_set(this,i,pElementDos);

											ll_set(this,i+1,pElementUno);

											fSwap=1;
										}
									}
									else
									{
										if(pFunc(pElementUno,pElementDos) <0)
										{
										ll_set(this,i,pElementDos);

										ll_set(this,i+1,pElementUno);

										fSwap=1;
										}
									}
							}
						}
					}
					returnAux=0;
				}
				else
				{
					returnAux=0;
				}
			}
		}
    return returnAux;

}

