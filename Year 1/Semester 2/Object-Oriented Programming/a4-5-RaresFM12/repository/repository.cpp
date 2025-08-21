#include "repository.h"

Repository::Repository() :
	events { DynamicVector<Event>() }, userEvents { DynamicVector<Event>()  }
{}

Repository::~Repository() {}

bool Repository::addEvent(Event e)
{
	for (int i = 0; i < events.getSize(); ++i)
		if (events.getElement(i).getTitle() == e.getTitle())
			return false;

	events.addElement(e);
	return true;
}

void Repository::deleteEvent(int pos)
{
	events.removeElement(pos);
}

void Repository::updateEvent(int pos, Event e)
{
	events.updateElement(pos, e);
}

DynamicVector<Event> Repository::getAll()
{
	return this->events;
}

void Repository::addEventToUserList(Event e)
{
	userEvents.addElement(e);
}

DynamicVector<Event> Repository::getAllUserEvents()
{
	return userEvents;
}

void Repository::deleteEventUserList(int pos)
{
	userEvents.removeElement(pos);
}


DynamicVector<Event> Repository::getAllByMonth(int mo)
{
	DynamicVector<Event> v;
	for (int i = 0; i < events.getSize(); ++i)
		if (events.getElement(i).getDateTime().getMonth() == mo)
			v.addElement(events.getElement(i));

	return v;
}

Event Repository::getEventByName(std::string title)
{
	for (int i = 0; i < events.getSize(); ++i)
		if (events.getElement(i).getTitle() == title)
			return events.getElement(i);

	throw std::exception("This event is not in the list!");
}

void Repository::clearUserList()
{
	userEvents.setSize(0);
}




