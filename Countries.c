/*
 * Countries.c

 *
 *  Created on: Nov 13, 2018
 *      Author: ise
 */
#include "Countries.h"
typedef struct city{
	char *name;
	char *favoriteFood;
	int residents;
}*City;

typedef struct geoArea{
	int x1;
	int x2;
	int y1;
	int y2;
}*GeoArea;

typedef struct country
{
	char *name;
	City *cities;
	int numberOfCities;
	GeoArea area;

}*Country;

//Add country and return a object instance of Country
Country addCountry (char *name, int x1, int y1, int x2, int y2){

	if(name == NULL){
		printf("no memory available\n");
		return NULL;
	}
	Country newC;
	newC = (Country)malloc(sizeof(struct country));
	if(newC!=NULL){
		newC-> name= (char*)malloc(strlen(name)+1);
		if(newC->name==NULL){
			printf("no memory available\n");
			free(newC);
			newC=NULL;
			return NULL;
		}
		strcpy(newC->name,name);
		newC->cities= NULL;
		newC -> numberOfCities= 0;
		newC->area=(GeoArea)malloc(sizeof(struct geoArea));
		if(newC->area==NULL){
			printf("no memory available\n");
			free(newC->name);
			newC->name=NULL;
			free(newC);
			newC=NULL;
			return NULL;
		}
		newC ->area->x1=x1;
		newC ->area->y1=y1;
		newC ->area->x2=x2;
		newC ->area->y2=y2;
		return newC;
	}
	else{
		printf("no memory available\n");
		return NULL;
	}
}
/*
 * Add City to Country :
 * get from the user : country , city
 * return status if the city added to the country
 */
status addCity( Country country , City city){
	if(country==NULL || city==NULL){
		printf("no memory available\n");
		return failure;
	}
	country->cities= (City*)realloc(country->cities,(country->numberOfCities+1)*sizeof(struct city));
	if(country->cities==NULL){
		printf("no memory available\n");
		return failure;
	}
	country->numberOfCities++;
	country->cities[country->numberOfCities -1]= copyCity(city);
	free(city->name);
	city->name=NULL;
	free(city->favoriteFood);
	city->favoriteFood=NULL;
	free(city);
	city=NULL;
	return success;
}
/*
 * deleteCity : delete city from the country
 * get : country , name of city
 * return : status- if deleted = true
 * if not = false
 */
status deleteCity(Country country, char *cityName){
	if (country == NULL || cityName == NULL){
		printf("no memory available\n");
		return failure;
	}
	int i;
	for (i= 0; i<country-> numberOfCities; i++){
		if (strcmp(country-> cities[i]->name, cityName) == 0){
			free(country -> cities[i]->name);
			country -> cities[i]->name= NULL;
			free(country -> cities[i]->favoriteFood);
			country -> cities[i]->favoriteFood= NULL;
			free(country -> cities[i]);
			country -> cities[i]= NULL;
			country-> numberOfCities--;
			if(i!=country->numberOfCities){
				country->cities[i]=country->cities[country->numberOfCities];
				country->cities[country->numberOfCities]=NULL;
			}
			if(country->numberOfCities==0){
				country->cities=(City*)realloc(country->cities, sizeof(City));
			}else{
				country->cities= (City*)realloc(country->cities,(country->numberOfCities )* sizeof(struct city));
			}
			if(country->cities==NULL){
				printf("no memory available\n");
				return failure;
			}
			return success;
		}
	}

	return failure;
}

/*
 * deep copy of a city
 */
City copyCity (City copyCity)
{
	City newCity= (City)malloc(sizeof(struct city));
	if(newCity==NULL){
		printf("no memory available\n");
		return NULL;
	}
	newCity->name=(char*)malloc(strlen(copyCity->name)+1);
	if(newCity->name==NULL){
		printf("no memory available\n");
		free(newCity);
		newCity=NULL;
		return NULL;
	}
	strcpy(newCity->name,copyCity->name);
	newCity->favoriteFood=(char*)malloc(strlen(copyCity->favoriteFood)+1);
	if(newCity->favoriteFood==NULL){
		printf("no memory available\n");
		free(newCity->name);
		newCity->name=NULL;
		free(newCity);
		newCity=NULL;
		return NULL;
	}
	strcpy(newCity->favoriteFood,copyCity->favoriteFood);
	newCity->residents=copyCity->residents;

	return newCity;
}
/*
 * create new city with new parameters and return the new city
 */
City newCity(char *name, char *food, int residents){
	if(name==NULL || food==NULL){
		printf("no memory available\n");
		return NULL;
	}
	City newCity;

	newCity= (City)malloc(sizeof(struct city));
	if(newCity==NULL){
		printf("no memory available\n");
		return NULL;
	}
	newCity->name=(char*)malloc(strlen(name)+1);
	if(newCity->name==NULL){
		printf("no memory available\n");
		free(newCity);
		newCity=NULL;
		return NULL;
	}
	strcpy(newCity->name,name);
	newCity->favoriteFood=(char*)malloc(strlen(food)+1);
	if(newCity->favoriteFood==NULL){
		printf("no memory available\n");
		free(newCity->name);
		newCity->name=NULL;
		free(newCity);
		newCity=NULL;
		return NULL;
	}
	strcpy(newCity->favoriteFood,food);
	newCity->residents=residents;
	return newCity;
}
/*
 * print the Country that the function get
 */
status printCountry(Country country)
{
	if (country == NULL)
		return failure;
	printf("‫‪Country‬‬ %s ‫‪coordinates:‬‬ ‪<%d,%d> ‫‪,‬‬ <%d,%d>‬ \n",country->name, country->area->x1, country->area->y1,country->area->x2,country->area->y2);
	int i;
	for (i=0; i<country-> numberOfCities; i++){
		printf("\t%s ‫‪includes‬‬ ‫‪%d ‫‪residents‬‬ ‫‪and‬‬ ‫‪their‬‬ ‫‪favorite‬‬ ‫‪food‬‬ ‫‪is‬‬ %s \n",country -> cities[i]-> name, country->cities[i]->residents, country-> cities[i]->favoriteFood);
	}
	return success;
}

bool inCountry(int x, int y,Country country){
	if(x>=country->area->x1 && x<=country->area->x2 && y<=country->area->y1 && y>=country->area->y2)
		return true;

	return false;
}
/*
 * delete the country and use the free function to free the memory of the country
 */
status freeCountry(Country country){
	if(country!=NULL){
		int i;
		for(i=0;i<country->numberOfCities && country->cities != NULL;i++){
			free(country->cities[i]->name);
			country->cities[i]->name=NULL;
			free(country->cities[i]->favoriteFood);
			country->cities[i]->favoriteFood=NULL;
			free(country->cities[i]);
			country->cities[i]=NULL;
		}
		free(country->cities);
		country->cities=NULL;
		free(country->area);
		country->area=NULL;
		free(country->name);
		country->name=NULL;
		free(country);
		country=NULL;
	}
	else{
		printf("no memory available\n");
		return failure;
	}
	return success;
}
/*
 * copy the area
 */
GeoArea copyArea (GeoArea area){
	if (area == NULL){
		return NULL;
	}
	GeoArea copyArea= (GeoArea)malloc(sizeof(struct geoArea));
	if (copyArea == NULL){
		printf("no memory available\n");
		return NULL;
	}
	copyArea->x1= area->x1;
	copyArea->y1= area->y1;
	copyArea-> x2= area->x2;
	copyArea->y2= area->y2;

	return copyArea;
}
/*
 * deep copy of the country
 * get country object and return a deep copy of the same country
 */
Country copyCountry(Country country){
	if (country== NULL){
		return NULL;
	}
	Country copyOfCountry = (Country)malloc(sizeof(struct country));
	if(copyOfCountry==NULL){
		printf("no memory available\n");
		return NULL;
	}
	copyOfCountry -> name= (char*)malloc(strlen(country-> name)+1);
	if(copyOfCountry->name==NULL){
		printf("no memory available\n");
		free(copyOfCountry);
		copyOfCountry=NULL;
		return NULL;
	}
	strcpy(copyOfCountry-> name, country->name);
	copyOfCountry->cities= (City*)malloc(sizeof(City)* country->numberOfCities);
	if(copyOfCountry->cities==NULL){
		free(copyOfCountry->name);
		copyOfCountry->name=NULL;
		free(copyOfCountry);
		copyOfCountry=NULL;
		printf("no memory available\n");
		return NULL;
	}
	int i;
	for(i=0; i<country-> numberOfCities;i++){
		copyOfCountry->cities[i]=copyCity(country-> cities[i]);
	}
	copyOfCountry-> numberOfCities= country-> numberOfCities;
	copyOfCountry-> area= copyArea(country->area);

	return copyOfCountry;
}


//GETERS of Country
char* getCountryName(Country country){
	if(country==NULL){
		return NULL;
	}
	return country->name;
}
int getNumberOfCities(Country country){
	if(country==NULL){
		return -1;
	}
	return country->numberOfCities;
}
City* getCitiesOfCountry(Country country){
	if(country==NULL){
		return NULL;
	}
	return country->cities;
}
GeoArea getAreaOfCountry(Country country){
	if(country==NULL){
		return NULL;
	}
	return country->area;
}
//ASSIGNMENT 3
/*
 * copy the country name and return cahr*
 */
char* copyCountryName(char* NameOfCountry){
	if(NameOfCountry==NULL){
		return NULL;
	}

	char* copyName = (char*)malloc(strlen(NameOfCountry)+1);
	strcpy(copyName,NameOfCountry);
	return copyName;
}
/*
 * free the country name (char*)
 */
status freeCountryName(char* country){
	if(country==NULL){
		return failure;
	}
	free(country);
	return success;
}
/*
 * print the country name only
 */
status printCountryName(Country country){
	if(country==NULL){
		return failure;
	}
	printf("%s", country->name);
	return success;
}
/*
 * checkc if the names of the country equals
 */
bool equalCountryName(Country c1, Country c2){
	if(c1==NULL || c2==NULL){
		return false;
	}
	if(strcmp(c1->name,c2->name)==0){
		return true;
	}
	return false;
}
/*
 * transform name to ascii code
 */
int transNameOfCountry(char* country){
	int sum=0;
	for(int i=0;i<strlen(country);i++){
		sum=(int)country[i]+sum;
	}
	return sum;
}

//GETEERS of city
char* getCityName(City city){

	return city->name;
}
char* getFaveFood(City city){
	return city->favoriteFood;
}
int getResidents(City city){
	return city->residents;
}

/////main HELPER
/*
 * free all the memory
 */

void freeMemory(Country* countries,int numberOfCountries){
	int i;
	for(i=0;i<numberOfCountries;i++){
		freeCountry(countries[i]);
		countries[i]=NULL;
	}
}
/*
 * check if the city exist in the country
 */
bool isCity(char* cityName, Country country){
	if(cityName== NULL || country==NULL){
		return false;
	}
	for(int i=0; i<country->numberOfCities; i++){
		if(strcmp(country->cities[i]->name, cityName)==0){
			return true;

		}
	}
	return false;
}

