#pragma once
#include "event.h"
#include "vector.h"

class Repository {
private:
	DynamicVector<Event> events;
	DynamicVector<Event> userEvents;

public:
	Repository();
	~Repository();

	/// <summary>
	/// Adds an event in the list of events
	/// </summary>
	/// <param name="e">the event</param>
	/// <returns>true if the event was added, false otherwise</returns>
	bool addEvent(Event e);

	/// <summary>
	/// Deletes an event from the vector
	/// </summary>
	/// <param name="pos">the position</param>
	void deleteEvent(int pos);

	/// <summary>
	/// Updates an event from a specific position
	/// </summary>
	/// <param name="pos">the position</param>
	/// <param name="e">the event</param>
	void updateEvent(int pos, Event e);

	/// <summary>
	/// Returns the whole vector
	/// </summary>
	/// <returns>the whole vector</returns>
	DynamicVector<Event> getAll();

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

	DynamicVector<Event> getAllUserEvents();
	DynamicVector<Event> getAllByMonth(int mo);
	Event getEventByName(std::string title);
	void clearUserList();
};