#include "repository.h"

Service::Service() :
	elems { vector<Car*>() }
{}

void Service::addCar(Car* c)
{
	elems.push_back(c);
}

vector<Car*> Service::getCars()
{
	return elems;
}

vector<Car*> Service::getCarsWithMaxPrice(double price)
{
	vector<Car*> vec;
	for (auto e : elems)
		if (e->computePrice() <= price)
			vec.push_back(e);

	return vec;
}

void Service::writeToFile(string filename, vector<Car*> cars)
{
	ofstream fout(filename);
	if (fout.is_open() == false)
		throw exception();

	for (auto e : cars)
		fout << e->toString() << '\n';

	fout.close();
}

