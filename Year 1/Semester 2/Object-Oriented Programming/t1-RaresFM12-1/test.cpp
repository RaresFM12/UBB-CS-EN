#include "test.h"
#include "service.h"
#include "repository.h"
#include <cassert>

void Test::testAll()
{
	testAdd();
	testVintage();
}

void Test::testAdd()
{
	Repository r;
	Service s(r);

	s.handleAddCar(Car("Ford", "Mara", 1999, "red"));
	DynamicVector<Car> v = s.handleShowAllSorted();
	Car c = v.getElement(0);
	assert(c.getYear() == 1999);

	s.handleAddCar(Car("Skoda", "Octavia", 1976, "blue"));
	s.handleAddCar(Car("Mercedes", "New", 1990, "red"));

	v = s.handleShowAllSorted();
	assert(v.getSize() == 3);

	r.addCar(Car("Skoda", "Octavia", 1950, "blue"));
	r.addCar(Car("Skoda", "Octavia", 1946, "blue"));

	v = r.getAll();
	assert(v.getSize() == 2);
}