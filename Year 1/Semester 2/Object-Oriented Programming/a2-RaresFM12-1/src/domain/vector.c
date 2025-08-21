#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector* createDefaultVector(DestructionFunction desFct)
{
	Vector* v = (Vector*)malloc(sizeof(Vector));
	v->capacity = 0;
	v->size = 0;
	v->elem = NULL;
	v->destroyFct = desFct;

	return v;
}

void destroyVector(Vector* v)
{
	if (v == NULL)
		return;

	for (int i = 0; i < v->size; ++i)
		v->destroyFct(v->elem[i]);

	free(v->elem);
	v->elem = NULL;
	free(v);
}

int getSize(Vector* v)
{
	if (v == NULL)
		return -1;

	return v->size;
}

void addElement(Vector* v, TElem e)
{
	if (v == NULL)
		return;

	if (v->elem == NULL)
	{
		v->elem = (TElem*)malloc(2 * sizeof(TElem));
		v->capacity = 2;
		v->elem[0] = e;
		v->size = 1;
		return;
	}

	if (v->size == v->capacity)
		resize(v);

	v->elem[v->size] = e;
	v->size++;
}

void resize(Vector* v)
{
	if (v == NULL || v->elem == NULL)
		return;

	v->capacity *= 2;
	TElem* aux = realloc(v->elem, v->capacity * sizeof(TElem));

	if (aux == NULL)
		return;

	v->elem = aux;
}

void deleteElement(Vector* v, int ind)
{
	v->destroyFct(v->elem[ind]);
	for (int i = ind; i < v->size; ++i)
		v->elem[i] = v->elem[i + 1];

	v->size--;
}



