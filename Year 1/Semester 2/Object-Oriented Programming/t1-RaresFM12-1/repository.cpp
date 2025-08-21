#include "repository.h"

Repository::Repository() :
	elems{ DynamicVector<School>() }
{}

DynamicVector<School> Repository::getAll()
{
	return elems;
}

void Repository::addSchool(School s)
{
	elems.addElement(s);
}

void Repository::deleteSchool(int pos)
{
	elems.removeElement(pos);
}