#include "repository.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Repository::Repository() :
	events { std::vector<Event>() }, userEvents { std::vector<Event>()  }, format {nullptr}
{}

Repository::Repository(const std::string& path) :
	events{ std::vector<Event>() }, userEvents{ std::vector<Event>() }
{
	if (!path.empty())
		if (path == "csv")
			format = new FileTypeCSV("date.csv");
		else
			format = new FileTypeHTML("date.html");
}

Repository::~Repository()
{
	delete format;
}

bool Repository::addEvent(Event e)
{
	for (auto v : events)
		if (v.getTitle() == e.getTitle())
			throw InTheEventListException("This event is already in the list!!!");

	events.push_back(e);
	return true;
}

void Repository::deleteEvent(int pos)
{
	events.erase(events.begin() + pos);
}

void Repository::updateEvent(int pos, Event e)
{
	events[pos] = e;
}

std::vector<Event> Repository::getAll()
{
	return events;
}

void Repository::addEventToUserList(Event e)
{
	userEvents.push_back(e);
	format->writeToFile(userEvents);
}

std::vector<Event> Repository::getAllUserEvents()
{
	return userEvents;
}

void Repository::deleteEventUserList(int pos)
{
	userEvents.erase(userEvents.begin() + pos);
	format->writeToFile(userEvents);
}


std::vector<Event> Repository::getAllByMonth(int mo)
{
	/*std::vector<Event> v;
	for (auto a : events)
		if (a.getDateTime().getMonth() == mo)
			v.push_back(a);*/

	std::vector<Event> vec;

	std::copy_if(events.begin(), events.end(), std::back_inserter(vec), [mo](Event i) {
		return i.getDateTime().getMonth() == mo;
		});

	return vec;
}

Event Repository::getEventByName(std::string title)
{
	for (auto a : events)
		if (a.getTitle() == title)
			return a;

	throw NotInAdminListException("This event is not in the list!");
}

void Repository::clearUserList()
{
	userEvents.clear();
	format->writeToFile(userEvents);
}





