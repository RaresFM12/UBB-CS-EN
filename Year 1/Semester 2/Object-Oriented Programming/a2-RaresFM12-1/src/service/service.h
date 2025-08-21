#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "repository.h"
#include "operation.h"

typedef struct {
	Repository* repo;
	Vector* undoVector;
	Vector* redoVector;
	int undoOp;
} Service;

/// <summary>
/// Constructor of the Service struct
/// </summary>
/// <param name="repo">the repository</param>
/// <returns>the service</returns>
Service* createService(Repository* repo);

/// <summary>
/// Destructor of the Service struct
/// </summary>
/// <param name="s">the service</param>
void destroyService(Service* s);

/// <summary>
/// Adds a country to repository 
/// </summary>
/// <param name="s">the service</param>
/// <param name="c">the country</param>
/// <param name="ok">is true if undo is taken into consideration</param>
/// <returns>true if the operation was performed, false otherwise</returns>
bool addCountryService(Service* s, Country* c, bool ok);

/// <summary>
/// Deletes a country from the repository
/// </summary>
/// <param name="s">the service</param>
/// <param name="name">the country</param>
/// <param name="ok">is true if undo is taken into consideration</param>
/// <returns>true if the operation was performed, false otherwise</returns>
bool deleteCountryService(Service* s, char* name, bool ok);

/// <summary>
/// Updates a country from the repository
/// </summary>
/// <param name="s">the service</param>
/// <param name="name">the name of the country</param>
/// <param name="population">the population</param>
/// <param name="ok">is true if undo is taken into consideration</param>
/// <returns>Updates a country from the repository</returns>
bool updateCountryService(Service* s, char* name, int population, bool ok);

// Returns true if a country is the list, false otherwise

/// <summary>
/// Cheks if a country is in the repo
/// </summary>
/// <param name="s">the service</param>
/// <param name="name">the name of the country</param>
/// <returns>true if a country is the list, false otherwise</returns>
bool checkCountryInListService(Service* s, char* name);

/// <summary>
/// Returns a country from the repository by name
/// </summary>
/// <param name="s">the service</param>
/// <param name="name">the name of the country</param>
/// <returns>a country from the repository by name</returns>
Country* returnCountryByNameService(Service* s, char* name);

/// <summary>
/// Returns all the countries which contain a given substring
/// </summary>
/// <param name="s">the service</param>
/// <param name="name">the name of the country</param>
/// <returns>all the countries which contain a given substring</returns>
Vector* returnCountriesByStringService(Service* s, char* name);

/// <summary>
/// Returns all the countries which contain a given substring ordered in ascending order by population
/// </summary>
/// <param name="s">the service</param>
/// <param name="name">the name of the country</param>
/// <returns>all the countries which contain a given substring ordered in ascending order by population</returns>
Vector* returnCountriesByStringSortedByPopulationService(Service* s, char* name);

/// <summary>
/// Returns all the countries from a given continent that a minimum of pop people
/// </summary>
/// <param name="s">the service</param>
/// <param name="name">the name of the country</param>
/// <param name="pop">the population</param>
/// <returns>all the countries from a given continent that a minimum of pop people</returns>
Vector* returnCountriesFromContinentService(Service* s, char* name, int pop);

/// <summary>
/// Sorts the vector in ascending order by population
/// </summary>
/// <param name="v">the vector</param>
void sortVectorByPopulation(Vector* v);

/// <summary>
/// Undo the LPO
/// </summary>
/// <param name="s">the service</param>
/// <returns>true if the undo was done, false otherwise</returns>
bool undo(Service* s);

/// <summary>
/// Redo the LPO
/// </summary>
/// <param name="s">the service</param>
/// <returns>true if the undo was done, false otherwise</returns>
bool redo(Service* s);

/// <summary>
/// Push the undo LPO on the stack
/// </summary>
/// <param name="v">the vector</param>
/// <param name="op">the operation</param>
void pushUndo(Vector* v, Operation* op);

/// <summary>
/// Push the redo LPO on the stack
/// </summary>
/// <param name="v">the vector</param>
///  <param name="op">the operation</param>
void pushRedo(Vector* v, Operation* op);