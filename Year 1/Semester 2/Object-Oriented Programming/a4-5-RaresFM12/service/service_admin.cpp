#include "service_admin.h"

AdminService::AdminService() :
	repo{ Repository() }
{}

AdminService::AdminService(Repository r) :
	repo { r }
{}

AdminService::~AdminService() {}

bool AdminService::HandleAddEvent(Event e)
{
	return repo.addEvent(e);
}

bool AdminService::HandleDeleteEvent(std::string title)
{
	int pos = -1;
	DynamicVector<Event> v = repo.getAll();

	for (int i = 0; i < v.getSize(); ++i)
		if (title == v.getElement(i).getTitle())
			pos = i;

	if (pos == -1)
		return false;

	repo.deleteEvent(pos);
	return true;
}

bool AdminService::HandleUpdateEvent(Event e)
{
	int pos = -1;
	DynamicVector<Event> v = repo.getAll();

	for (int i = 0; i < v.getSize(); ++i)
		if (e.getTitle() == v.getElement(i).getTitle())
			pos = i;

	if (pos == -1)
		return false;

	repo.updateEvent(pos, e);
	return true;
}

DynamicVector<Event> AdminService::handleGetAll()
{
	return repo.getAll();
}

DynamicVector<Event> AdminService::handleGetAllSorted()
{
	DynamicVector<Event> v = repo.getAll();
	for (int i = 0; i < v.getSize() - 1; ++i)
		for (int j = i + 1; j < v.getSize(); ++j)
			if (v.getElement(j) < v.getElement(i))
			{
				Event e = v.getElement(i);
				v.updateElement(i, v.getElement(j));
				v.updateElement(j, e);
			}

	return v;
}

DynamicVector<Event> AdminService::handleFilterEvents(int nr)
{
	DynamicVector<Event> v = repo.getAll();
	DynamicVector<Event> vec;
	for (int i = 0; i < v.getSize(); ++i)
		if (v.getElement(i).getNrOfPeople() >= nr)
			vec.addElement(v.getElement(i));

	return vec;
}


DynamicVector<Event> AdminService::HandleGetEventsByMonth(int mo)
{
	DynamicVector<Event> v = repo.getAllByMonth(mo);
	for (int i = 0; i < v.getSize() - 1; ++i)
		for (int j = i + 1; j < v.getSize(); ++j)
			if (v.getElement(j) < v.getElement(i))
			{
				Event e = v.getElement(i);
				v.updateElement(i, v.getElement(j));
				v.updateElement(j, e);
			}

	return v;
}

Event AdminService::handleGetEventByName(std::string title)
{
	return repo.getEventByName(title);
}


