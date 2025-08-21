#pragma once
#include <stdio.h>
#include "domain.h"

typedef void* TElem;

typedef void (*DestructionFunction)(TELem);

typedef struct {
	int size;
	int capacity;
	TElem* elem;
	DestructionFunction destroyFct;
} Vector;

/// <summary>
/// Creates a vector with no capacity
/// </summary>
/// <param name="desFct">the destruction function</param>
/// <returns>the vector</returns>
Vector* createDefaultVector(DestructionFunction desFct);

/// <summary>
/// Destroys a vector
/// </summary>
/// <param name="v">the vector</param>
void destroyVector(Vector* v);

/// <summary>
/// Returns the size of a specific vector
/// </summary>
/// <param name="v">the vector</param>
/// <returns>the size of the vector</returns>
int getSize(Vector* v);

/// <summary>
/// Adds an element on the last position of the vector
/// </summary>
/// <param name="v">the vector</param>
/// <param name="e">the element</param>
void addElement(Vector* v, TElem e);

/// <summary>
/// Resizes the capacity of the vector with capacity * 2
/// </summary>
/// <param name="v">the vector</param>
void resize(Vector* v);

/// <summary>
/// Deletes the element from index i
/// </summary>
/// <param name="v">the vector</param>
/// <param name="i">the index</param>
void deleteElement(Vector* v, int i);