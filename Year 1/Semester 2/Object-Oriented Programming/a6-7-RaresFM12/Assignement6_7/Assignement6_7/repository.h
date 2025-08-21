#pragma once
#include "event.h"
#include "exceptions.h"
#include "file_type.h"
#include <vector>

class Repository {
protected:
	FileType* format;
	std::vector<Event> events;
	std::vector<Event> userEvents;

public:
	Repository();
	Repository(const std::string& path);
	virtual ~Repository();

	/// <summary>
	/// Adds an event in the list of events
	/// </summary>
	/// <param name="e">the event</param>
	/// <returns>true if the event was added, false otherwise</returns>
	virtual bool addEvent(Event e);

	/// <summary>
	/// Deletes an event from the vector
	/// </summary>
	/// <param name="pos">the position</param>
	virtual void deleteEvent(int pos);

	/// <summary>
	/// Updates an event from a specific position
	/// </summary>
	/// <param name="pos">the position</param>
	/// <param name="e">the event</param>
	virtual void updateEvent(int pos, Event e);

	/// <summary>
	/// Returns the whole vector
	/// </summary>
	/// <returns>the whole vector</returns>
	std::vector<Event> getAll();

	/// <summary>
	/// Adds an event into the user list
	/// </summary>
	/// <param name="e">the event</param>
	void addEventToUserList(Event e);

	/// <summary>
	/// Deletes an event from user's list
	/// </summary>
	/// <param name="pos">the position of the event in the list</param>
	void deleteEventUserList(int pos);

	std::vector<Event> getAllUserEvents();
	std::vector<Event> getAllByMonth(int mo);
	Event getEventByName(std::string title);
	void clearUserList();
};