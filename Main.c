/*
 * Main.c

 *
 *  Created on: Nov 13, 2018
 *      Author: ise
 */
#include "Countries.h"
#include "HashTable.h"
#include "KeyValuePair.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc ,char* argv[]){
	char *food1;
	int residents;
	int x1,x2,y1,y2, ch;
	ch=0;
	char nameOfCountry[300];
	char nameOfCity[300];
	char faveFood[300];
	int x,y;
	int indexOfCountries;
	int numberOfCountries;
	int hashTableSize;
	FILE *fp;
	char line[300];
	hashTableSize=atoi(argv[1]);
	numberOfCountries=atoi(argv[2]);
	Country countries[numberOfCountries];
	hashTable countriesHashTable;
	char *path=argv[3];
	/*
	 * Casting functions for Country
	 */
	Element copyValCountry(Element country){
		if(country== NULL){
			return NULL;
		}
		return (Element)copyCountry((Country)country);
	}
	Element copyKeyCountry(Element country){
		if(country== NULL){
			return NULL;
		}
		return (Element)copyCountryName((char*)country);
	}
	status freeValCountry(Element country){
		if(country== NULL){
			return success;
		}
		return freeCountry((Country)country);
	}
	status freeKeyCountry(Element country){
		if(country== NULL){
			return success;
		}
		return freeCountryName((char*)country);
	}
	status printValCountry(Element country){
		Country temp= (Country)getValue((keyVP)country);

		if(printCountry(temp)== failure){
			freeCountry(temp);
			return failure;
		}
		return success;
	}
	status printKeyCountry(Element country){
		return printCountryName((Country)country);
	}
	bool equalKeyCountry(Element country1 ,Element country2){
		return equalCountryName((Country)country1 ,(Country)country2);
	}
	int transformCountryNameToInt(Element country){
		return transNameOfCountry((char*)country);
	}
	//create hash table for country
	countriesHashTable=createHashTable(copyKeyCountry,freeKeyCountry,printKeyCountry,copyValCountry,freeValCountry,printValCountry,equalKeyCountry,transformCountryNameToInt,hashTableSize);
	//reading from file
	fp=fopen(path,"r");
	if (fp == NULL)///to check what to do with null return
	{
		printf("Could not open file %s",path);
		exit(1);
	}
	indexOfCountries =0;
	while (fgets(line,300,fp)!=NULL)
	{
		char* name = strtok(line,",");
		if(line[0]!='\t')
		{
			x1=atoi(strtok(NULL,","));
			y1=atoi(strtok(NULL,","));
			x2=atoi(strtok(NULL,","));
			y2=atoi(strtok(NULL,","));
			countries[indexOfCountries]=addCountry(name,x1,y1,x2,y2);
			if(countries[indexOfCountries]==NULL){
				exit(1);
			}
			indexOfCountries++;
		}
		else
		{
			name++;
			food1=strtok(NULL,",");
			residents=atoi(strtok(NULL,","));
			if(addCity(countries[indexOfCountries-1],newCity(name,food1,residents))==failure){
				exit(1);
			}
		}
	}
	fclose(fp);
	//add countries to hash table
	for(int i=0; i<numberOfCountries;i++){
		if(addToHashTable(countriesHashTable,(Element)getCountryName(countries[i]),(Element)countries[i])==failure){
			freeMemory(countries,numberOfCountries);
			exit(1);
		}
	}
	freeMemory(countries,numberOfCountries);//delete the countries array
	//MAIN
	while (ch!=8){
		printf("‫‪please‬‬ ‫‪choose‬‬ ‫‪one‬‬ ‫‪of‬‬ ‫‪the‬‬ ‫‪following‬‬ ‫‪numbers:‬‬\n");
		printf("‫‪1‬‬ ‫‪:‬‬ ‫‪print‬‬ ‫‪Countries‬‬\n‬‬");
		printf("‫‪2‬‬ ‫‪:‬‬ ‫‪add‬‬ ‫‪country‬‬‬‬\n");
		printf("‫‪3‬‬ ‫‪:‬‬ ‫‪add‬‬ ‫‪city‬‬ ‫‪to‬‬ ‫‪country‬‬\n");
		printf("‫‪4‬‬ ‫‪:‬‬ ‫‪delete‬‬ ‫‪city‬‬ ‫‪from‬‬ ‫‪country‬‬\n");
		printf("‫‪‫‪5‬‬ ‫‪:‬‬ ‫‪print‬‬ ‫‪country‬‬ ‫‪by‬‬ ‫‪name‬‬‬‬\n");
		printf("6 : ‫‪delete‬‬ ‫‪country‬‬\n");
		printf("‫‪7‬‬ ‫‪:‬‬ ‫‪is‬‬ ‫‪country‬‬ ‫‪in‬‬ ‫‪area‬‬\n");
		printf("‫‪8‬‬ ‫‪:‬‬ ‫‪exit‬‬\n");
		scanf("%d", &ch);
		switch(ch)
		{
		case 1: //print countries
			displayHashElements(countriesHashTable);
			break;

		case 2: //add‬‬ ‫‪country
			printf("please enter a new country name\n");
			scanf("%s", nameOfCountry);
			Country countryTemp=(Country)lookupInHashTable(countriesHashTable, nameOfCountry);
			if(countryTemp == NULL){//in case of not exist country in this name
				printf("please enter two x and y coordinates :x1,y1,x2,y2\n");
				scanf("%d,%d,%d,%d",&x1,&y1,&x2,&y2);
				Country tempCountry= addCountry(nameOfCountry,x1,y1,x2,y2);
				addToHashTable(countriesHashTable,(Element)nameOfCountry, (Element)tempCountry);
				freeCountry(tempCountry);
			}
			else{
				printf("country with this name already exist\n");
			}
			break;
		case 3: //add‬‬ ‫‪city‬‬ ‫‪to‬‬ ‫‪country‬‬
			printf("please enter a country name\n");
			scanf("%s", nameOfCountry);
			Country tempCountry0= (Country)lookupInHashTable(countriesHashTable, nameOfCountry);
			if(tempCountry0!= NULL){//in case of exist country in this name
				printf("please enter a city name\n");
				scanf("%s", nameOfCity);
				if(!isCity(nameOfCity, tempCountry0)){
					printf("please enter the city favorite food\n");
					scanf("%s",faveFood);
					printf("please enter number of residents in city\n");
					scanf("%d",&residents);
					City cityToAdd=newCity(nameOfCity,faveFood,residents);
					if(cityToAdd==NULL){//check if the creating of the city done
						destroyHashTable(countriesHashTable);
						exit(1);
					}
					addCity(tempCountry0, cityToAdd);//add new city to country
				}
				else{
					printf("this city already exist in this country\n");

				}
			}
			else{
				printf("country not exist\n");
			}

			break;
		case 4://delete city from country
			printf("please enter a country name\n");
			scanf("%s", nameOfCountry);

			Country tempCountry1= (Country)lookupInHashTable(countriesHashTable, nameOfCountry);
			if(tempCountry1!= NULL){//in case of exist country in this name
				printf("please enter a city name\n");
				scanf("%s", nameOfCity);
				if(isCity(nameOfCity,tempCountry1)){//check if the city exist in the country
					if(deleteCity(tempCountry1,nameOfCity)==failure){//check if the city delete
						destroyHashTable(countriesHashTable);
						exit(1);
					}
				}else{
					printf("the city not exist in this country\n");
				}
			}
			break;
		case 5://print country name
			printf("please enter a country name\n");
			scanf("%s", nameOfCountry);

			Country tempCountry2= (Country)lookupInHashTable(countriesHashTable, nameOfCountry);
			if(tempCountry2!= NULL){//in case of exist country in this name
				printCountry(tempCountry2);
			}
			else{
				printf("country name not exist\n");
			}

			break;
		case 6://‫‪delete‬‬ ‫‪country
			printf("please enter a country name\n");
			scanf("%s", nameOfCountry);
			Country tempCountry3= (Country)lookupInHashTable(countriesHashTable, nameOfCountry);
			if(tempCountry3!= NULL){//in case of exist country in this name
				removeFromHashTable(countriesHashTable,(Element)getCountryName(tempCountry3));
				printf("country deleted\n");
			}
			else{
				printf("can't delete the country\n");
			}
			break;
		case 7://is‬‬ ‫‪country‬‬ ‫‪in‬‬ ‫‪area‬‬
			printf("please enter a country name\n");
			scanf("%s", nameOfCountry);
			Country tempCountry4= (Country)lookupInHashTable(countriesHashTable, nameOfCountry);
			if(tempCountry4!= NULL){//in case of exist country in this name
				printf("please enter x and y coordinations:x,y\n");
				scanf("%d,%d",&x,&y);
				if(inCountry(x,y,tempCountry4)){
					printf("the coordinate in the country\n");
				}
				else{
					printf("the coordinate not in the country\n");
				}
			}
			else{
				printf("country name not exist\n");
			}
			break;

		case 8 ://exit the program
			destroyHashTable(countriesHashTable);
			printf("‫‪all‬‬ ‫‪the‬‬ ‫‪memory‬‬ ‫‪cleaned‬‬ ‫‪and‬‬ ‫‪the‬‬ ‫‪program‬‬ ‫‪is‬‬ ‫‪safely‬‬ ‫‪closed‬‬\n");
			break;
		default :
			printf("‫‪please‬‬ ‫‪choose‬‬ ‫‪a‬‬ ‫‪valid‬‬ ‫‪number‬‬\n");
			break;
		}//switch
	}//while

}

