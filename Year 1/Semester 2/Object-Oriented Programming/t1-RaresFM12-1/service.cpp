#include "service.h"

Service::Service(Repository r) :
	repo{ r }
{}

void Service::handleAddSchool(School c)
{
	repo.addSchool(c);
}

bool Service::handleRemoveSchool(std::string name, float lon, float lat)
{
	int pos = -1;
	DynamicVector<School> v = repo.getAll();
	for (int i = 0; i < v.getSize(); ++i)
		if (v.getElement(i).getName() == name && v.getElement(i).getLat() == lat && v.getElement(i).getLong() == lon)
			pos = i;

	if (pos == -1)
		return false;

	repo.deleteSchool(pos);
	return true;
}

DynamicVector<School> Service::handleShowAllSchoolsSorted()
{
	DynamicVector<School> v = repo.getAll();
	for (int i = 0; i < v.getSize() - 1; ++i)
		for (int j = i + 1; j < v.getSize(); ++j)
			if (v.getElement(i).getName() > v.getElement(j).getName())
			{
				School aux = v.getElement(i);
				v.updateElement(i, v.getElement(j));
				v.updateElement(j, aux);
			}

	return v;
}