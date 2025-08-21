#pragma once
#include "date.h"

class School {
private:
	std::string name;
	float lo, lat;
	datetime date;
	bool visited;

public:
	School(std::string n, float longi, float lati, bool v, datetime d);

	std::string getName();
	float getLong();
	float getLat();
	bool getVisited();
	datetime getDate();

	void setName(std::string n);
	void setLong(float longi);
	void setLat(float lati);
	void setVisited(bool v);
	void setDate(datetime d);
};

