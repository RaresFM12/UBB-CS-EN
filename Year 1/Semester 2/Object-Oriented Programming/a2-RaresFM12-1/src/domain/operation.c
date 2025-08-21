#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operation.h"

Operation* createOperation(int type, Country* c)
{
	Operation* op = (Operation*)malloc(sizeof(Operation));
	op->type = type;
	op->country = copyCountry(c);

	return op;
}

void destroyOperation(Operation* op)
{
	if (op == NULL)
		return;

	destroyCountry(op->country);
	free(op);
}

int getType(Operation* op)
{
	if (op == NULL)
		return -1;

	return op->type;
}

Country* getCountry(Operation* op)
{
	if (op == NULL)
		return NULL;

	return op->country;
}