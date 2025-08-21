#pragma once
#include <iostream>
#include "service_admin.h"
#include "service_user.h"

class UI {
private:
	AdminService adminService;
	UserService userService;

public:
	UI();
	UI(AdminService as, UserService us);
	~UI();

	void validDate(std::string date, int& hour, int& day, int& month, int& year);
	void validNrOfPeople(std::string nr, int& nr_people);

	void printMenuAdministrator();
	void printMenuUser();
	void run_ui();

	void defaultCases();
	void addEventAdmin();
	void deleteEventAdmin();
	void updateEventAdmin();
	void printAllEventsAdmin();
	void filterEventsByNrOfPeople();

	void seeEventsFromSpecificMonthUser();
	int transformMonth(std::string month);
	void deleteEventUserList();
	void seeAllEventsUserAttends();
};