#include "event.h"
#include <string>

Event::Event() : 
	title {""}, description {""}, date {datetime()}, nr_people {0}, link {""}
{}

Event::Event(std::string t, std::string desc, datetime d, int n, std::string l) :
	title {t}, description {desc}, date {d}, nr_people {n}, link {l}
{}

Event::~Event() {}

std::string Event::getTitle()
{
	return title;
}

std::string Event::getDescription()
{
	return description;
}

datetime Event::getDateTime()
{
	return date;
}

int Event::getNrOfPeople()
{
	return nr_people;
}

std::string Event::getLink()
{
	return link;
}

void Event::setTitle(std::string t)
{
	this->title = t;
}

void Event::setDescription(std::string desc)
{
	this->description = desc;
}

void Event::setDateTime(datetime d)
{
	this->date = d;
}

void Event::setNrOfPeople(int n)
{
	this->nr_people = n;
}

void Event::setLink(std::string l)
{
	this->link = l;
}

void Event::operator=(const Event& e)
{
	title = e.title;
	description = e.description;
	date = e.date;
	nr_people = e.nr_people;
	link = e.link;
}

bool Event::operator<(const Event& e)
{
	datetime d = e.date;
	int day = d.getDay();
	int mo = d.getMonth();
	int year = d.getYear();
	int h = d.getHour();

	if (date.getYear() < year)
		return true;

	if (date.getYear() > year)
		return false;

	if (date.getYear() == year)
	{
		if (date.getMonth() < mo)
			return true;

		if (date.getMonth() > mo)
			return false;

		if (date.getMonth() == mo)
		{
			if (date.getDay() < day)
				return true;

			if (date.getDay() > day)
						return false;

			if (date.getDay() == day)
			{
				if (date.getHour() < h)
					return true;

				if (date.getHour() > h)
					return false;

				if (date.getHour() == h)
					return false;
			}
		}
		
	}

}


std::string Event::toString()
{
	std::string str = "TITLE: " + title + "\n" + "DESCRIPTION: " + description + "\n" +
		"DATE AND TIME: " + date.toString() + "NUMBER OF PEOPLE: " + std::to_string(nr_people) + "\n" +
		"LINK: " + link + "\n";
	
	return str;
}
