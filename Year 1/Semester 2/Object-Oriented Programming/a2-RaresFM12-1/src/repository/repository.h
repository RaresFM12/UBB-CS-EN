#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "domain.h"
#include "vector.h"

typedef struct {
	Vector* v;

} Repository;

/// <summary>
/// Constructor of the Repository struct
/// </summary>
/// <returns>the repository</returns>
Repository* createRepository();

/// <summary>
/// Destructor of the Repository struct
/// </summary>
/// <param name="r">the repository</param>
void destroyRepository(Repository* r);

/// <summary>
/// Adds an element to the repository vector
/// </summary>
/// <param name="r">the repository</param>
/// <param name="c">the element</param>
/// <returns>true if it's added, false otherwise</returns>
bool addCountry(Repository* r, TElem c);

/// <summary>
/// Deletes an element from the repository vector
/// </summary>
/// <param name="r">the repository</param>
/// <param name="pos">the position</param>
/// <returns>true if it's deleted, false otherwise</returns>
bool deleteCountry(Repository* r, int pos);

/// <summary>
/// Updates an element from the repository vector
/// </summary>
/// <param name="r">the repository</param>
/// <param name="name">the name of the country</param>
/// <param name="population">the new population</param>
/// <returns>true if it's updated, false otherwise</returns>
bool updateCountry(Repository* r, char* name, int population);

/// <summary>
/// Checks if a country is in the repository vector
/// </summary>
/// <param name="r">the repository</param>
/// <param name="name">the name of the country</param>
/// <returns>true if it's in the vector, false otherwise</returns>
bool checkCountryInList(Repository* r, char* name);

/// <summary>
/// Returns a country by name from the repository vector
/// </summary>
/// <param name="r">the repository</param>
/// <param name="name">the name of the country</param>
/// <returns>the country</returns>
Country* returnCountryByName(Repository* r, char* name);

/// <summary>
/// Returns a vector of coutries that contain a specific substring
/// </summary>
/// <param name="r">the repository</param>
/// <param name="name">the string</param>
/// <returns>the vector of countries</returns>
Vector* returnCountriesByString(Repository* r, char* name);

/// <summary>
/// Returns a given word, but with lower cases
/// </summary>
/// <param name="word">the string</param>
void toLower(char* word);

/// <summary>
/// Returns all the countries from a continent with a minimum number of people
/// </summary>
/// <param name="r">the repository</param>
/// <param name="name">the name of the continent</param>
/// <param name="pop">the minimum population</param>
/// <returns>the vector of countries</returns>
Vector* returnCoutriesFromContinent(Repository* r, char* name, int pop);

