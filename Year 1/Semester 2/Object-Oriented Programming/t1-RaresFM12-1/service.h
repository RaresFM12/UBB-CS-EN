#pragma once
#include <iostream>
#include "repository.h"

class Service {
private:
	Repository repo;

public:
	Service(Repository r);

	void handleAddSchool(School s);

	bool handleRemoveSchool(std::string name, float lon, float lat);

	DynamicVector<School> handleShowAllSchoolsSorted();

};