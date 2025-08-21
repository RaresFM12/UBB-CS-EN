#include "event.h"
#include "utils.h"
#include <string>
#include <vector>

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

std::ostream& operator<<(std::ostream& out, const Event& e)
{
	datetime d = e.date;
	out << e.title << ',' << e.description << ',' << d.getDay() << '/' << d.getMonth()
		<< '/' << d.getYear() << ' ' << d.getHour() << ',' << e.nr_people << ',' << e.link << '\n';

	return out;
}

std::istream& operator>>(std::istream& in, Event& e)
{
	std::string str;
	std::string t;
	std::string desc;
	int h, d, m, y;
	int pop;
	std::string link;

	std::getline(in, str);
	std::vector<std::string> result = tokenize(str, ',');

	if (result.size() != 5)
		return in;

	t = result[0];
	desc = result[1];
	pop = stoi(result[3]);
	link = result[4];

	vector<string> date1 = tokenize(result[2], '/');
	d = stoi(date1[0]);
	m = stoi(date1[1]);

	vector<string> date2 = tokenize(date1[2], ' ');
	y = stoi(date2[0]);
	h = stoi(date2[1]);

	datetime dat(h, d, m, y);
	e.setTitle(t);
	e.setDescription(desc);
	e.setDateTime(dat);
	e.setNrOfPeople(pop);
	e.setLink(link);

	return in;
}

std::string Event::toString()
{
	std::string str = "TITLE: " + title + "\n" + "DESCRIPTION: " + description + "\n" +
		"DATE AND TIME: " + date.toString() + "NUMBER OF PEOPLE: " + std::to_string(nr_people) + "\n" +
		"LINK: " + link + "\n";
	
	return str;
}
