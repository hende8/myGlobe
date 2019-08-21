/*
 * KeyValuePair.h
 *
 *  Created on: Dec 2, 2018
 *      Author: ise
 */

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct KeyValuePair* keyVP;
keyVP createKeyValuePair(Element k , Element val ,transformIntoNumberFunction transF,copyFunction copyFK,copyFunction copyFV , freeFunction freeFK,freeFunction freeFV , printFunction printFK, printFunction printFV,equalFunction equalFK);
status displayValue(keyVP val);
status displayKey(keyVP val);
Element getValue (keyVP val);
Element getKey(keyVP val);
bool isEqualKey(keyVP v1 , keyVP v2);
Element deepCopy(Element elem);
status destroyElementHash (Element elem);
status destroyKeyValuePair(keyVP val);
#endif /* KEYVALUEPAIR_H_ */
