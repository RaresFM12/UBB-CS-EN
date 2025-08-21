#pragma once
#include "repository.h"

class UserService {
private:
	Repository repo;

public:
	UserService();
	UserService(Repository r);
	~UserService();

	/// <summary>
	/// Handles the add of an event in the user list
	/// </summary>
	/// <param name="e">the event</param>
	/// <returns>true if the event was already added, false otherwise</returns>
	bool HandleAddEventToUserList(Event e);
	
	/// <summary>
	/// Handles the delete of an event from the user list
	/// </summary>
	/// <param name="title">the title</param>
	/// <returns>true if the event was deleted, false otherwise</returns>
	bool HandleDeleteEventUserList(std::string title);

	/// <summary>
	/// deletes all the events from the user list
	/// </summary>
	void handleClearUserList();

	DynamicVector<Event> HandleGetAllUserEvents();
};