#include "service_user.h"

UserService::UserService(Repository& r) :
	repo{ r }
{}

UserService::~UserService() {}

bool UserService::HandleAddEventToUserList(Event e)
{
	std::vector<Event> v = repo.getAllUserEvents();
	for (auto a : v)
		if (e.getTitle() == a.getTitle())
			throw InTheUserListException("This event was already added in your list!!!");

	repo.addEventToUserList(e);
	return true;
}

bool UserService::HandleDeleteEventUserList(std::string title)
{
	int pos = -1;
	std::vector<Event> v = repo.getAllUserEvents();
	for (int i = 0; i < v.size(); ++i)
		if (title == v[i].getTitle())
			pos = i;

	if (pos == -1)
		throw NotInAdminListException("This event is not in your list!!!");

	repo.deleteEventUserList(pos);
	return true;
}


std::vector<Event> UserService::HandleGetAllUserEvents()
{
	return repo.getAllUserEvents();
}

void UserService::handleClearUserList()
{
	repo.clearUserList();
}
