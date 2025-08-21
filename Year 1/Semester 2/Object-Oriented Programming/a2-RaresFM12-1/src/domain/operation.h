#pragma once
#include "domain.h"

// type 1 - add
// type 2 - delete
// type 3 - update
typedef struct {
	int type;
	Country* country;
} Operation;

/// <summary>
/// Constructor of the Operation struct
/// </summary>
/// <param name="type">type of the operation</param>
/// <param name="c">the country</param>
/// <returns>the operation</returns>
Operation* createOperation(int type, Country* c);

/// <summary>
/// Destructor of the Operation struct
/// </summary>
/// <param name="op">the operation</param>
void destroyOperation(Operation* op);

/// <summary>
/// Returns the type of the operation
/// </summary>
/// <param name="op">the operation</param>
/// <returns>the type of the operation</returns>
int getType(Operation* op);

/// <summary>
/// Returns the country
/// </summary>
/// <param name="op">the operation</param>
/// <returns>the country</returns>
Country* getCountry(Operation* op);

