#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "service.h"

Service* createService(Repository* repo)
{
	Service* s = (Service*)malloc(sizeof(Service));
	s->undoVector = createDefaultVector(&destroyOperation);
	s->redoVector = createDefaultVector(&destroyOperation);
	s->repo = repo;
	s->undoOp = 0;

	return s;
}

void destroyService(Service* s)
{
	if (s == NULL)
		return;

	destroyVector(s->undoVector);
	destroyVector(s->redoVector);
	destroyRepository(s->repo);
	free(s);
}

bool addCountryService(Service* s, Country* c, bool ok)
{
	for (int i = 0; i < s->repo->v->size; ++i)
		if (strcmp(getName(s->repo->v->elem[i]), c->name) == 0)
			return false;

	if (ok == true)
	{
		Operation* op = createOperation(1, c);
		pushUndo(s->undoVector, op);
		s->undoOp = 0;
	}

	return addCountry(s->repo, c);
}

bool deleteCountryService(Service* s, char* name, bool ok)
{
	int pos = -1;
	for (int i = 0; i < s->repo->v->size; ++i)
		if (strcmp(getName(s->repo->v->elem[i]), name) == 0)
			pos = i;

	if (pos == -1)
		return false;

	if (ok == true)
	{
		Operation* op = createOperation(2, s->repo->v->elem[pos]);
		pushUndo(s->undoVector, op);
		s->undoOp = 0;
	}


	return deleteCountry(s->repo, pos);
}

bool updateCountryService(Service* s, char* name, int population, bool ok)
{
	if (ok == true)
	{
		Country* c = returnCountryByName(s->repo, name);
		Operation* op = createOperation(3, c);
		pushUndo(s->undoVector, op);
		s->undoOp = 0;
	}

	return updateCountry(s->repo, name, population);
}


bool checkCountryInListService(Service* s, char* name)
{
	return checkCountryInList(s->repo, name);
}

Country* returnCountryByNameService(Service* s, char* name)
{
	return returnCountryByName(s->repo, name);
}

Vector* returnCountriesByStringService(Service* s, char* name)
{
	return returnCountriesByString(s->repo, name);
}

Vector* returnCountriesByStringSortedByPopulationService(Service* s, char* name)
{
	Vector* vec = returnCountriesByString(s->repo, name);
	sortVectorByPopulation(vec);

	return vec;
}

Vector* returnCountriesFromContinentService(Service* s, char* name, int pop)
{
	Vector* vec = returnCoutriesFromContinent(s->repo, name, pop);
	sortVectorByPopulation(vec);

	return vec;
}

void sortVectorByPopulation(Vector* vec)
{
	Country* aux;
	for (int i = 0; i < vec->size - 1; ++i)
		for (int j = i + 1; j < vec->size; ++j)
			if (getPopulation(vec->elem[i]) > getPopulation(vec->elem[j]))
			{
				aux = vec->elem[i];
				vec->elem[i] = vec->elem[j];
				vec->elem[j] = aux;
			}
}

// Undo-Redo

bool undo(Service* s)
{
	if (s->undoVector->size == 0)
		return false;

	Operation* op = s->undoVector->elem[s->undoVector->size - 1];
	s->undoVector->size--;

	if (op->type == 1)
	{
		deleteCountryService(s, op->country->name, false);
		pushRedo(s->redoVector, op);
	}

	else if (op->type == 2)
	{
		Country* c = copyCountry(op->country);
		addCountryService(s, c, false);
		pushRedo(s->redoVector, op);
	}

	else if (op->type == 3)
	{
		Country* new_country = copyCountry(returnCountryByName(s->repo, op->country->name));
		int new_type = op->type;
		updateCountryService(s, op->country->name, op->country->population, false);
		destroyOperation(op);
		op = createOperation(new_type, new_country);
		destroyCountry(new_country);
		pushRedo(s->redoVector, op);

		Operation* op2 = s->undoVector->elem[s->undoVector->size - 1];
		s->undoVector->size--;

		new_country = copyCountry(returnCountryByName(s->repo, op2->country->name));
		new_type = op2->type;
		updateCountryService(s, op2->country->name, op2->country->population, false);
		destroyOperation(op2);
		op2 = createOperation(new_type, new_country);
		destroyCountry(new_country);
		pushRedo(s->redoVector, op2);
	}

	s->undoOp++;
	return true;
}

bool redo(Service* s)
{
	if (s->redoVector->size == 0)
		return false;

	if (s->undoOp == 0)
		return false;

	Operation* op = s->redoVector->elem[s->redoVector->size - 1];
	s->redoVector->size--;

	if (op->type == 1)
	{
		Country* c = createCountry(op->country->name, op->country->continent, op->country->population);
		addCountryService(s, c, false);
		pushUndo(s->undoVector, op);
	}
	else if (op->type == 2)
	{
		deleteCountryService(s, op->country->name, true);
		pushUndo(s->undoVector, op);
	}
	else if (op->type == 3)
	{
		Country* new_country = copyCountry(returnCountryByName(s->repo, op->country->name));
		int new_type = op->type;
		updateCountryService(s, op->country->name, op->country->population, false);
		destroyOperation(op);
		op = createOperation(new_type, new_country);
		destroyCountry(new_country);
		pushUndo(s->undoVector, op);

		Operation* op2 = s->redoVector->elem[s->redoVector->size - 1];
		s->redoVector->size--;

		new_country = copyCountry(returnCountryByName(s->repo, op2->country->name));
		new_type = op2->type;
		updateCountryService(s, op2->country->name, op2->country->population, false);
		destroyOperation(op2);
		op2 = createOperation(new_type, new_country);
		destroyCountry(new_country);
		pushUndo(s->undoVector, op2);
	}

	s->undoOp--;
	return true;
}

void pushUndo(Vector* undoVector, Operation* op)
{
	addElement(undoVector, op);
}

void pushRedo(Vector* redoVector, Operation* op)
{
	addElement(redoVector, op);
}