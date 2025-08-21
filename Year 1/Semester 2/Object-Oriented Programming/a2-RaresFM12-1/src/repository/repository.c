#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "repository.h"

Repository* createRepository()
{
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	repo->v = createDefaultVector(&destroyCountry);

	return repo;
}

void destroyRepository(Repository* r)
{
	if (r == NULL)
		return;

	destroyVector(r->v);
	free(r);
}

bool addCountry(Repository* r, Country* c)
{
	addElement(r->v, c);
	return true;
}

bool deleteCountry(Repository* r, int pos)
{
	deleteElement(r->v, pos);
	return true;
}

bool updateCountry(Repository* r, char* name, int population)
{
	for (int i = 0; i < r->v->size; ++i)
		if (strcmp(getName(r->v->elem[i]), name) == 0)
		{
			setPopulation(r->v->elem[i], population);
			return true;
		}

	return false;
}

bool checkCountryInList(Repository* r, char* name)
{
	for (int i = 0; i < r->v->size; ++i)
		if (strcmp(getName(r->v->elem[i]), name) == 0)
			return true;

	return false;
}

Country* returnCountryByName(Repository* r, char* name)
{
	for (int i = 0; i < r->v->size; ++i)
		if (strcmp(getName(r->v->elem[i]), name) == 0)
			return r->v->elem[i];
}

Vector* returnCountriesByString(Repository* r, char* name)
{
	Vector* vec = createDefaultVector(&destroyCountry);
	for (int i = 0; i < r->v->size; ++i)
	{
		char str1[35];
		char str2[35];

		strcpy(str1, getName(r->v->elem[i]));
		strcpy(str2, name);

		toLower(str1);
		toLower(str2);

		if (strstr(str1, str2) != NULL)
		{
			Country* c = copyCountry(r->v->elem[i]);
			addElement(vec, c);
		}
	}

	return vec;
}

void toLower(char* word)
{
	for (int i = 0; i < strlen(word); ++i)
		word[i] = tolower(word[i]);
}

Vector* returnCoutriesFromContinent(Repository* r, char* name, int pop)
{
	Vector* vec = createDefaultVector(&destroyCountry);

	if (name == NULL)
	{
		for (int i = 0; i < r->v->size; ++i)
			if (getPopulation(r->v->elem[i]) > pop)
			{
				Country* c = copyCountry(r->v->elem[i]);
				addElement(vec, c);
			}

		return vec;
	}

	for (int i = 0; i < r->v->size; ++i)
		if (strcmp(getContinent(r->v->elem[i]), name) == 0 && getPopulation(r->v->elem[i]) > pop)
		{
			Country* c = copyCountry(r->v->elem[i]);
			addElement(vec, c);
		}

	return vec;
}



