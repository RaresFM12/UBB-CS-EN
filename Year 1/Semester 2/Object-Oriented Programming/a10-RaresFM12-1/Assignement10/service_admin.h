#pragma once
#include "repository.h"
#include "exceptions.h"
#include "file_repository.h"

class AdminService {
private:
	Repository* repo;

public:
	AdminService();
	AdminService(Repository* r);
	AdminService(std::string path);
	~AdminService();

	/// <summary>
	/// Handles the add of an event in the repo
	/// </summary>
	/// <param name="e">the event</param>
    /// <returns>true if the event was added, false otherwise</returns>
	bool HandleAddEvent(Event e);

	/// <summary>
	/// Handles the delete of an event from the repo
	/// </summary>
	/// <param name="title">the title of event</param>
	/// <returns>true if was deleted, false otherwise</returns>
	int HandleDeleteEvent(std::string title);

	/// <summary>
	/// Handles the update of an event from the repo
	/// </summary>
	/// <param name="e">the event</param>
	/// <returns>true if was updated, false otherwise</returns>
	int HandleUpdateEvent(Event e);

	/// <summary>
	/// Handles get all elements
	/// </summary>
	/// <returns>the whole vector</returns>
	std::vector<Event> handleGetAll();

	/// <summary>
	/// Filters the events by a minimum number of participants
	/// </summary>
	/// <param name="nr">the minimum number of participants</param>
	/// <returns>the list of events</returns>
	std::vector<Event> handleFilterEvents(int nr);

	/// <summary>
	/// Returns all the events sorted by date
	/// </summary>
	/// <returns>the events sorted</returns>
	std::vector<Event> handleGetAllSorted();

	/// <summary>
	/// Handles get all events from a specific month
	/// </summary>
	/// <param name="mo">the month</param>
	/// <returns>all the events from a specific month</returns>
	std::vector<Event> HandleGetEventsByMonth(int mo);

	Event handleGetEventByName(std::string title);

	bool HandleAddEventToUserList(Event e);
	int HandleDeleteEventUserList(std::string title);
	void handleClearUserList();
	std::vector<Event> HandleGetAllUserEvents();
};