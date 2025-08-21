#include "domain.h"
#include <iostream>
#include <fstream>
#include <string>

Car::Car(int nr, Engine* e)
{
	numberOfDoors = nr;
	engine = e;
}


Car::~Car()
{
	delete engine;
}

Engine::Engine()
{}

double Car::computePrice()
{
	if (numberOfDoors == 2)
		return 7000 + engine->getPrice();

	if (numberOfDoors == 4)
		return 8500 + engine->getPrice();
}

int Car::getDoors()
{
	return numberOfDoors;
}

string Car::toString()
{
	string en = engine->toString();
	en += ",";

	string doo = to_string(numberOfDoors);
	en += doo;

	string price = to_string(computePrice());
	en += ",";
	en += price;

	return en;
}

double Engine::getPrice()
{
	return 0;
}

string Engine::toString()
{
	return "";
}


ElectricEngine::ElectricEngine(double pr, int aut)
{
	basePrice = pr;
	autonomy = aut;
}

TurboEngine::TurboEngine(double pr)
{
	basePrice = pr;
}

double ElectricEngine::getPrice()
{
	return 3000 + autonomy / 100;
}

double TurboEngine::getPrice()
{
	return 3000 + 100;
}

string ElectricEngine::toString()
{
	string price = to_string(getPrice());
	string aut = to_string(autonomy);

	string res = price;
	res += ",";
	res += aut;

	return res;
}

string TurboEngine::toString()
{
	string price = to_string(getPrice());
	return price;
}

