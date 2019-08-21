/*
 * KeyValuePair.c
 *
 *  Created on: Dec 2, 2018
 *      Author: ise
 */
#include "KeyValuePair.h"

typedef struct KeyValuePair{
	Element key;
	Element value;
	copyFunction copyFunKey;
	copyFunction copyFunVal;
	freeFunction freeFunKey;
	freeFunction freeFunVal;
	printFunction printFunKey;
	printFunction printFunVal;
	equalFunction equalFunKey;
	transformIntoNumberFunction transFun;
}*keyVP;
/*
 * initiate a new key value pair and get a pointers of functions
 */
keyVP createKeyValuePair(Element k , Element val ,transformIntoNumberFunction transF,copyFunction copyFK,copyFunction copyFV , freeFunction freeFK,freeFunction freeFV , printFunction printFK, printFunction printFV,equalFunction equalFK){
	if(k== NULL || copyFV==NULL || copyFK==NULL || freeFK==NULL ||freeFK==NULL||  printFK==NULL||printFV==NULL|| transF== NULL||equalFK== NULL){
		return NULL;
	}
	keyVP new=(keyVP)malloc(sizeof(struct KeyValuePair));
	if(new==NULL){
		printf("no memory available\n");
		return NULL;
	}

	new->copyFunVal=copyFV;
	new->copyFunKey=copyFK;
	new->freeFunKey=freeFK;
	new->freeFunVal=freeFV;
	new->printFunKey=printFK;
	new->printFunVal=printFV;
	new->equalFunKey=equalFK;
	new->transFun=transF;
	new->value= copyFV(val);//copy the value and the key
	new->key=copyFK(k);
	return new;
}
/*
 * delete the keyValuePair
 */
status destroyKeyValuePair(keyVP val){

	if(val==NULL){
		return failure;
	}
	if(val->freeFunVal(val->value)==failure){//delete value
		return failure;
	}
	val->value=NULL;
	if(val->freeFunKey(val->key)==failure){//delete Key
		return failure;
	}
	val->key=NULL;
	free(val);//delete the pointer keyValuePair
	val=NULL;
	return success;
}
/*
 * print the keyValuePair value
 */
status displayValue(keyVP val){
	if (val== NULL){
		return failure;
	}

	status temp= val->printFunVal(val->value);
	if(temp== failure){
		return failure;
	}
	return success;
}
/*
 * print the keyValuePair Key
 */
status displayKey(keyVP val){
	if (val== NULL){
		return failure;
	}
	status temp= val->printFunKey(val->key);
	if(temp== failure){
		return failure;
	}
	return success;
}
/*
 * get the source pointer of keyValuePairs value
 */
Element getValue (keyVP val){
	if (val== NULL){
		return NULL;
	}

	return val->value;
}
/*
 * get the copy pointer of keyValuePairs key
 */
Element getKey(keyVP val){
	if (val == NULL){
		return NULL;
	}
	return val->copyFunKey(val->key);
}
/*
 * boolean func check if the two keyValuePairs is equals by the keys
 */
bool isEqualKey(keyVP v1 , keyVP v2){
	if(v1==NULL ||v2==NULL ){
		return false;
	}
	return v1->equalFunKey(v1->key,v2->key);
}
//HELP FUNCTIONS
/*
 * casting function that do deepCopy of keyValuePair
 */
Element deepCopy(Element elem){
	keyVP temp= (keyVP)elem;
	return (Element)createKeyValuePair(temp->key,temp->value,temp->transFun,temp->copyFunKey,temp->copyFunVal,temp->freeFunKey,temp->freeFunVal,temp->printFunKey,temp->printFunVal,temp->equalFunKey);
}
/*
 * casting destroy function of keyValuePair
 */
status destroyElementHash (Element elem){
	return destroyKeyValuePair((keyVP)elem);
}
