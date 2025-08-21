#pragma once
#include <iostream>
#include <cstring>
#include "date.h"

class Event {
private:
	std::string title;
	std::string description;
	datetime date;
	int nr_people;
	std::string link;

public:
	Event();

	Event(std::string t, std::string desc, datetime d, int n, std::string l);

	~Event();

	std::string getTitle();

	std::string getDescription();

	datetime getDateTime();

	int getNrOfPeople();

	std::string getLink();

	void setTitle(std::string t);

	void setDescription(std::string desc);

	void setDateTime(datetime d);

	void setNrOfPeople(int n);

	void setLink(std::string l);

	/// <summary>
	/// Assignement operator
	/// </summary>
	/// <param name="e">the event we want to copy</param>
	void operator=(const Event& e);

	bool operator<(const Event& e);

	friend std::ostream& operator<<(std::ostream& out, const Event& e);

	friend std::istream& operator>>(std::istream& in, Event& e);

	std::string toString();
};
