#include "service_admin.h"
#include <algorithm>

AdminService::AdminService(Repository& r) :
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
	std::vector<Event> v = repo.getAll();

	for (int i = 0; i < v.size(); ++i)
		if (title == v[i].getTitle())
			pos = i;

	if (pos == -1)
		throw NotInAdminListException("This event is not in the list!!!");

	repo.deleteEvent(pos);
	return true;
}

bool AdminService::HandleUpdateEvent(Event e)
{
	int pos = -1;
	std::vector<Event> v = repo.getAll();

	for (int i = 0; i < v.size(); ++i)
		if (e.getTitle() == v[i].getTitle())
			pos = i;

	if (pos == -1)
		throw NotInAdminListException("This event is not in the list!!!");

	repo.updateEvent(pos, e);
	return true;
}

std::vector<Event> AdminService::handleGetAll()
{
	return repo.getAll();
}

std::vector<Event> AdminService::handleGetAllSorted()
{
	std::vector<Event> v = repo.getAll();
	sort(v.begin(), v.end());

	return v;
}

std::vector<Event> AdminService::handleFilterEvents(int nr)
{
	std::vector<Event> v = repo.getAll();
	std::vector<Event> vec;

	std::copy_if(v.begin(), v.end(), std::back_inserter(vec), [nr](Event i) {
			return i.getNrOfPeople() >= nr;
		});

	return vec;
}


std::vector<Event> AdminService::HandleGetEventsByMonth(int mo)
{
	std::vector<Event> v = repo.getAllByMonth(mo);
	sort(v.begin(), v.end());

	return v;
}

Event AdminService::handleGetEventByName(std::string title)
{
	return repo.getEventByName(title);
}


