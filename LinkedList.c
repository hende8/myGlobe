/*
 * LinkedList.c
 *
 *  Created on: Nov 27, 2018
 *      Author: ise
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
typedef struct node{
	Element data;
	Node next;
}*Node;

typedef struct linkedList{
	Node head;
	Node tail;
	copyFunction copyFun;
	freeFunction freeFun;
	printFunction printFun;
	equalFunction equalFun;
	int numOfelement;
}*LinkedList;
/*
 * initiate a new link list and get pointer functions from the user
 */
LinkedList createLinkedList(copyFunction copyF , freeFunction freeF , printFunction printF, equalFunction equalF){
	if(copyF==NULL || freeF==NULL || printF==NULL|| equalF== NULL){
		return NULL;
	}
	//create new Linklist
	LinkedList newLinklist= (LinkedList)malloc(sizeof(struct linkedList));
	if (newLinklist== NULL ){
		printf("no memory available\n");
		return NULL;
	}
	//initiate Linklist functions
	newLinklist->copyFun=copyF;
	newLinklist->freeFun=freeF;
	newLinklist->printFun=printF;
	newLinklist->equalFun=equalF;
	//initiate Linklist-> head,tail
	newLinklist->head= NULL;
	newLinklist->tail= NULL;
	newLinklist->numOfelement=0;

	return newLinklist;
}
/*
 * delete all the list
 */
status destroyList(LinkedList list){
	for(int i=0 ; i < list->numOfelement;i++){
		if(list->freeFun(list->head->data)==failure){
			return failure;
		}
		Node tmp = list->head;
		list->head->data=NULL;
		list->head= list->head->next;
		free(tmp);
	}
	free(list);
	list=NULL;
	return success;
}
/*
 * add node to list
 */
status appendNode(LinkedList list , Element data){
	if(list==NULL || data==NULL){
		return failure;
	}
	//initiate new node
	Node tempNode= (Node)malloc(sizeof(struct node));
	if(tempNode==NULL){
		printf("no memory available\n");
		return failure;
	}
	tempNode->data= list->copyFun(data);
	tempNode->next=NULL;
	//add to empty list
	if(list->numOfelement==0){
		list->head=tempNode;
		list->tail=tempNode;
	}else{// add to exist list
		list->tail->next=tempNode;
		list->tail=tempNode;
	}
	list->numOfelement++;
	return success;
}
/*
 * delete node from the list
 */
status deleteNode (LinkedList list , Element data){
	if(list==NULL || data==NULL){
		return failure;
	}
	Node prev= NULL;
	Node tempNext= list->head;
	int i=0;
	for(i=0; i< list-> numOfelement; i++){
		if(list->equalFun(tempNext->data, data)== true){//if the node is found
			if(i==0 && i==list->numOfelement-1){//if this is the only node in the list
				list->freeFun(tempNext->data);
				free(tempNext);
				list->head=NULL;
				list->tail=NULL;
				list->numOfelement--;
				return success;
			}
			if(i==0){//if this is the first node and not the only one
				list->head= tempNext->next;
				list->freeFun(tempNext->data);
				free(tempNext);
				list->numOfelement--;
				return success;
			}

			if(i==list->numOfelement-1){//if this is the last node
				list->tail= prev;
				list->tail->next= NULL;
				list->freeFun(tempNext->data);
				free(tempNext);
				list->numOfelement--;
				return success;
			}
			//if the node found in the middle of the list
			prev->next= tempNext->next;
			list->freeFun(tempNext->data);
			free(tempNext);
			list->numOfelement--;
			return success;
		}
		prev= tempNext;
		tempNext=tempNext->next;
	}
	return failure;
}
/*
 * print the list
 */
status displayList(LinkedList list){
	if(list== NULL){
		return failure;
	}
	if(list->numOfelement == 1){
		return(list->printFun(list->head->data));
	}
	Node tempNode= list->head;//node for further
	for(int i= 0; i<list->numOfelement; i++){
		status temp= list->printFun(tempNode->data);
		if(temp== failure){
			return failure;
		}
		tempNode=tempNode->next;
	}
	return success;
}
/*
 * searching in the list if the date exists
 */
Element searchInList(LinkedList list, Element data){
	if(list== NULL || data== NULL){
		return NULL;
	}
	Node tempNode= list->head;
	for (int i=0; i<list->numOfelement; i++){
		if (list->equalFun(tempNode->data, data)){
			return tempNode->data;
		}
		tempNode=tempNode->next;
	}

	return NULL;
}
