#include "service_user.h"

UserService::UserService() :
	repo{ Repository() }
{}

UserService::UserService(Repository r) :
	repo{ r }
{}

UserService::~UserService() {}

bool UserService::HandleAddEventToUserList(Event e)
{
	DynamicVector<Event> v = repo.getAllUserEvents();
	for (int i = 0; i < v.getSize(); ++i)
		if (e.getTitle() == v.getElement(i).getTitle())
			return false;

	repo.addEventToUserList(e);
	return true;
}

bool UserService::HandleDeleteEventUserList(std::string title)
{
	int pos = -1;
	DynamicVector<Event> v = repo.getAllUserEvents();
	for (int i = 0; i < v.getSize(); ++i)
		if (title == v.getElement(i).getTitle())
			pos = i;

	if (pos == -1)
		return false;

	repo.deleteEventUserList(pos);
	return true;
}


DynamicVector<Event> UserService::HandleGetAllUserEvents()
{
	return repo.getAllUserEvents();
}

void UserService::handleClearUserList()
{
	repo.clearUserList();
}
