/*
 * Countries.h
 *
 *  Created on: Nov 13, 2018
 *      Author: ise
 */

#ifndef COUNTRIES_H_
#define COUNTRIES_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct city* City;
typedef struct geoArea* GeoArea;
typedef struct country* Country;

Country addCountry (char *name, int x1, int y1, int x2, int y2);
status addCity( Country country , City city);
status deleteCity(Country country, char *cityName);
bool inCountry(int x, int y,Country country);
status freeCountry(Country country);
Country copyCountry(Country country);
status printCountry(Country country);

//help functions
City copyCity(City city);
City newCity(char *name, char *food,int residents);
GeoArea copyArea (GeoArea area);
bool isCity(char* nameCity, Country country);
void freeMemory(Country* countries,int numberOfCountries);

//GETTERS
char* getCountryName(Country country);
int getNumberOfCities(Country country);
City* getCitiesOfCountry(Country country);
GeoArea getAreaOfCountry(Country country);
char* getFaveFood(City city);
char* getCityName(City city);
int getResidents(City city);
//Assignmnet 3
char* copyCountryName(char* NameOfCountry);
status freeCountryName(char* country);
status printCountryName(Country country);
bool equalCountryName(Country c1, Country c2);
int transNameOfCountry(char* country);
#endif /* COUNTRIES_H_ */
