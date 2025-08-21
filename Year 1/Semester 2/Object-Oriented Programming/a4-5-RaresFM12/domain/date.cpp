#include <iostream>
#include <string>
#include "date.h"


datetime::datetime() : 
	day {0}, month {0}, year {0}, hour {0}
{}

datetime::datetime(int hour, int day, int month, int year) :
	day{ day }, month{ month }, year{ year }, hour{ hour }
{}

datetime::~datetime() {}

int datetime::getHour()
{
	return hour;
}

int datetime::getDay()
{
	return day;
}

int datetime::getMonth()
{
	return month;
}

int datetime::getYear()
{
	return year;
}

std::string datetime::toString()
{
	std::string str = std::to_string(day) + "/" + std::to_string(month) + "/" +
		std::to_string(year) + " at " + std::to_string(hour) + ":00\n";

	return str;
}

void datetime::operator=(const datetime& d)
{
	hour = d.hour;
	day = d.day;
	month = d.month;
	year = d.year;
}



