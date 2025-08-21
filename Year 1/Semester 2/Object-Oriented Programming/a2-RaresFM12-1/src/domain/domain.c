#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "domain.h"

Country* createCountry(char* name, char* continent, int population)
{
	Country* c = (Country*)malloc(sizeof(Country));
	c->name = malloc(sizeof(char) * (strlen(name) + 1));
	c->continent = malloc(sizeof(char) * (strlen(continent) + 1));

	strcpy(c->name, name);
	strcpy(c->continent, continent);
	c->population = population;

	return c;
}

void destroyCountry(Country* c)
{
	if (c == NULL)
		return;

	free(c->name);
	free(c->continent);
	free(c);
}

char* getName(Country* c)
{
	if (c == NULL)
		return NULL;

	return c->name;
}

char* getContinent(Country* c)
{
	if (c == NULL)
		return NULL;

	return c->continent;
}

int getPopulation(Country* c)
{
	if (c == NULL)
		return -1;

	return c->population;
}

void setPopulation(Country* c, int pop)
{
	if (c == NULL)
		return;

	c->population = pop;
}

void toString(Country* c, char str[])
{
	if (c == NULL)
		return;

	sprintf(str, "%s is in %s and has a population of %d mil.\n",
		c->name, c->continent, c->population);
}

Country* copyCountry(Country* c)
{
	if (c == NULL)
		return NULL;

	Country* co = createCountry(getName(c), getContinent(c), getPopulation(c));
	return co;
}