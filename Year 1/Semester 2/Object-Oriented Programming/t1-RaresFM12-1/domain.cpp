#include "domain.h"

School::School(std::string n, float longi, float lati, bool v, datetime d) :
	name {n}, lo {longi}, lat {lati}, visited {v}, date {d}
{}

std::string School::getName()
{
	return name;
}

float School::getLong()
{
	return lo;
}

float School::getLat()
{
	return lat;
}

bool School::getVisited()
{
	return visited;
}

datetime School::getDate()
{
	return date;
}

void School::setName(std::string n)
{
	name = n;
}

void School::setLong(float longi)
{
	lo = longi;
}

void School::setLat(float lati)
{
	lat = lati;
}

void School::setVisited(bool v)
{
	visited = v;
}

void School::setDate(datetime d)
{
	date = d;
}