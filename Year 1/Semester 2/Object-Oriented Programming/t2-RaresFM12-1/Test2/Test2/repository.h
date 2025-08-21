#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "domain.h"
using namespace std;

class Service {
private:
	vector<Car*> elems;

public:
	Service();
	void addCar(Car* b);
	vector<Car*> getCarsWithMaxPrice(double price);
	vector<Car*> getCars();
	void writeToFile(string filename, vector<Car*> human);
};