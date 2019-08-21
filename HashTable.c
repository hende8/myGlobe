/*
 * HashTable.c
 *
 *  Created on: Dec 2, 2018
 *      Author: ise
 */
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

typedef struct hashTable_s{
	int sizeOfTable;
	LinkedList *listHash;
	copyFunction copyFunKey;
	copyFunction copyFunValue;
	freeFunction freeFunKey;
	freeFunction freeFunValue;
	printFunction printFunKey;
	printFunction printFunValue;
	equalFunction equalFunKey;
	transformIntoNumberFunction transFun;
}*hashTable;

/*
 * create a hashTable
 */
hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey, copyFunction copyValue, freeFunction freeValue, printFunction printValue, equalFunction equalKey, transformIntoNumberFunction transformKeyIntoNumber, int hashNumber){
	if(copyKey==NULL || freeKey==NULL || printKey==NULL || copyValue==NULL || freeValue==NULL || printValue==NULL || equalKey==NULL || transformKeyIntoNumber==NULL){
		return NULL;
	}
	hashTable newHash=(hashTable)malloc(sizeof(struct hashTable_s));
	if(newHash==NULL){
		printf("no memory available\n");
		return NULL;
	}
	newHash->listHash=(LinkedList*)malloc(sizeof(LinkedList)*hashNumber);
	if(newHash->listHash==NULL){
		printf("no memory available\n");
		free(newHash);
		return NULL;
	}
	newHash->copyFunKey=copyKey;
	newHash->freeFunKey=freeKey;
	newHash->printFunKey=printKey;
	newHash->equalFunKey=equalKey;
	newHash->copyFunValue=copyValue;
	newHash->freeFunValue=freeValue;
	newHash->printFunValue=printValue;
	newHash->transFun=transformKeyIntoNumber;
	newHash->sizeOfTable=hashNumber;
	int j;
	for(j=0;j<newHash->sizeOfTable;j++){
		newHash->listHash[j]=NULL;
	}
	return newHash;
}
/*
 * delete the hash table and the lists inside
 */
status destroyHashTable(hashTable table){
	int i;
	for(i=0;i<table->sizeOfTable;i++){
		if(table->listHash[i]!=NULL){
			if(destroyList(table->listHash[i])==failure){
				return failure;
			}
			table->listHash[i]=NULL;
		}
	}
	free(table->listHash);
	table->listHash=NULL;
	free(table);
	table=NULL;
	return success;
}
/*
 * add new element to the hash table by ascii code
 */
status addToHashTable(hashTable table, Element key,Element value){
	if(table== NULL || key == NULL || value== NULL){
		return failure;
	}
	keyVP newKeyVal=createKeyValuePair(key,value,table->transFun,table->copyFunKey,table->copyFunValue,table->freeFunKey,table->freeFunValue,table->printFunKey,table->printFunValue,table->equalFunKey);
	if(newKeyVal==NULL){
		return failure;
	}
	int index= table->transFun(key);
	//hash Function
	int iHash= index%(table->sizeOfTable);
	if(table->listHash[iHash]==NULL){//if there is not linkedlist in the cell
		table->listHash[iHash]=createLinkedList(deepCopy,destroyElementHash,table->printFunValue,table->equalFunKey);
		if(table->listHash[iHash]==NULL){//check if the list created
			destroyKeyValuePair(newKeyVal);
			return failure;
		}
		appendNode(table->listHash[iHash],(Element)newKeyVal);
		destroyKeyValuePair(newKeyVal);
	}
	else{//list in the cell
		if(searchInList(table->listHash[iHash],(Element)newKeyVal)!=NULL){//check if the country inside the list
			destroyKeyValuePair(newKeyVal);

			return failure;
		}
		appendNode(table->listHash[iHash],(Element)newKeyVal);
		destroyKeyValuePair(newKeyVal);

	}
	return success;
}
/*
 * search in hash table
 * return source pointer of the element
 */
Element lookupInHashTable(hashTable table, Element key){
	if(key==NULL || table==NULL){
		return NULL;
	}
	int index= table->transFun(key);
	//hash Function
	int iHash= index%(table->sizeOfTable);
	if(table->listHash[iHash]!=NULL){//in case of no linklist in the cell
		keyVP temp =createKeyValuePair(key,NULL,table->transFun,table->copyFunKey,table->copyFunValue,table->freeFunKey,table->freeFunValue,table->printFunKey,table->printFunValue,table->equalFunKey);
		Element elem = searchInList(table->listHash[iHash],(Element)temp);
		if(elem!=NULL){
			destroyKeyValuePair(temp);
			Element el=getValue((keyVP)elem);
			return el;//return the pointer of the element
		}
		destroyKeyValuePair(temp);
	}

	return NULL;
}
/*
 * delete element from hash table by key
 */
status removeFromHashTable(hashTable table, Element key){
	if(key==NULL || table==NULL){
		return failure;
	}
	int index= table->transFun(key);
	//hash Function
	int iHash= index%(table->sizeOfTable);
	if(table->listHash[iHash]!=NULL){//check if exist list in the cell
		keyVP temp =createKeyValuePair(key,NULL,table->transFun,table->copyFunKey,table->copyFunValue,table->freeFunKey,table->freeFunValue,table->printFunKey,table->printFunValue,table->equalFunKey);
		Element elem = searchInList(table->listHash[iHash],(Element)temp);//search the element in the list
		if(elem!=NULL){
			deleteNode(table->listHash[iHash],elem);//delete element
			destroyKeyValuePair(temp);
			return success;
		}
	}
	return failure;
}
/*
 * print the elements in the hash table
 */
status displayHashElements(hashTable table){
	if(table==NULL){
		return failure;
	}
	for(int i=0;i<table->sizeOfTable;i++){
		if(table->listHash[i]!=NULL){
			if(displayList(table->listHash[i])==failure){//print list of elements in cell of hashTable
				return failure;
			}
		}
	}
	return success;
}






