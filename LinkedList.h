/*
 * LinkedList.h
 *
 *  Created on: Nov 27, 2018
 *      Author: ise
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
typedef struct node* Node;
typedef struct linkedList* LinkedList;

LinkedList createLinkedList(copyFunction copyF,freeFunction freeF,printFunction printF,equalFunction equalF);
status destroyList(LinkedList list);
status appendNode(LinkedList list , Element data);
status deleteNode (LinkedList list , Element data);
status displayList(LinkedList list);
Element searchInList(LinkedList list, Element data);

#endif /* LINKEDLIST_H_ */
