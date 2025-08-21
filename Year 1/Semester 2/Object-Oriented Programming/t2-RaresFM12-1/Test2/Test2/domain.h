#pragma once
#include <iostream>
using namespace std;



class Engine {
protected:
	double basePrice;

public:
	Engine();
	virtual double getPrice();
	virtual string toString();
};

class ElectricEngine : public Engine {
private:
	int autonomy;

public:
	ElectricEngine(double pr, int aut);
	double getPrice() override;
	string toString() override;
};

class TurboEngine : public Engine {
public:
	TurboEngine(double pr);
	double getPrice() override;
	string toString() override;
};

class Car {
private:
	Engine* engine;
	int numberOfDoors;

public:
	Car();
	Car(int nr, Engine* e);
	~Car();
	int getDoors();
	double computePrice();
	string toString();
};