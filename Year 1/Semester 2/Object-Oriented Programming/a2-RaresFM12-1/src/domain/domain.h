#pragma once

typedef struct {
	char* name;
	char* continent;
	int population;
} Country;

/// <summary>
/// Constructor of the struct Country
/// </summary>
/// <param name="name">name of the country</param>
/// <param name="continent">name of the continent</param>
/// <param name="population">the population</param>
/// <returns>a country</returns>
Country* createCountry(char* name, char* continent, int population);

/// <summary>
/// Destructor of the struct Country
/// </summary>
/// <param name="c">the country</param>
void destroyCountry(Country* c);

/// <summary>
/// Function that returns the name of a country
/// </summary>
/// <param name="c">the country</param>
/// <returns>name of the country</returns>
char* getName(Country* c);

/// <summary>
/// Function that returns the continent of a country
/// </summary>
/// <param name="c">name of the country</param>
/// <returns>name of the continent of the specific country</returns>
char* getContinent(Country* c);

/// <summary>
/// Function that returns the population of a country
/// </summary>
/// <param name="c">the country</param>
/// <returns>the population of the country</returns>
int getPopulation(Country* c);

/// <summary>
/// Sets a new value for the population field
/// </summary>
/// <param name="c">the country</param>
/// <param name="pop">the new population</param>
void setPopulation(Country* c, int pop);

/// <summary>
/// Function that transforms the fields of a country into a string
/// </summary>
/// <param name="c">the country</param>
/// <param name="str">the string</param>
void toString(Country* c, char str[]);

/// <summary>
/// This function creates another country with the same fields as the one given as a parameter
/// </summary>
/// <param name="c">the country</param>
/// <returns>the new copy</returns>
Country* copyCountry(Country* c);


