#include <iostream>
#include "date.h"


datetime::datetime() :
	day{ 0 }, month{ 0 }, year{ 0 }
{}

datetime::datetime(int day, int month, int year) :
	day{ day }, month{ month }, year{ year }
{}

datetime::~datetime() {}

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

void datetime::operator=(const datetime& d)
{
	hour = d.hour;
	day = d.day;
	month = d.month;
	year = d.year;
}