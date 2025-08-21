#pragma once
#include <iostream>
#include "vector.h"
#include "domain.h"

class Repository {
private:
	DynamicVector<School> elems;

public:
	Repository();

	DynamicVector<School> getAll();

	void addSchool(School c);

	/// <summary>
	/// Removes a school from the repository
	/// </summary>
	/// <param name="pos">the position of the school in the repository</param>
	void deleteSchool(int pos);
};