#include "ui.h"
#include <iostream>
#include <string>
#include "date.h"
#include "event.h"
#include <windows.h> 
#include <iostream>
#include <fstream>

UI::UI(AdminService as, UserService us, std::string f) :
	adminService{ as }, userService{ us }, format {f}
{}

UI::~UI() {}


void UI::run_ui()
{
	while (true)
	{
		std::cout << "\n========= Main Menu =========\n";
		std::cout << "Please, choose your mode:\n";
		std::cout << "a) Admin\n";
		std::cout << "b) User\n";
		std::cout << "c) Exit\n";
		std::cout << "Your option is: ";

		std::string cmd;
		std::cin >> cmd;

		if (cmd == "admin")
			printMenuAdministrator();

		else if (cmd == "user")
			printMenuUser();

		else if (cmd == "exit")
			break;

		else
			std::cout << "Bad command!\n";
	}
}

void UI::printMenuAdministrator()
{
	while (true)
	{
		std::cout << "\n============ Administrator Menu ============\n";
		std::cout << "Please, choose one option:\n";
		std::cout << "1) Add a new event\n";
		std::cout << "2) Delete an event\n";
		std::cout << "3) Update an event\n";
		std::cout << "4) See all events\n";
		std::cout << "5) Filter the events by number of participants\n";
		std::cout << "0) Exit\n";
		std::cout << "Your option is: ";

		std::string cmd;
		std::cin >> cmd;

		if (cmd == "1")
			addEventAdmin();

		else if (cmd == "2")
			deleteEventAdmin();

		else if (cmd == "3")
			updateEventAdmin();

		else if (cmd == "4")
			printAllEventsAdmin();

		else if (cmd == "5")
			filterEventsByNrOfPeople();

		else if (cmd == "0")
			break;

		else
			std::cout << "Bad command!\n";

	}
}

void UI::printMenuUser()
{
	userService.handleClearUserList();
	while (true)
	{
		std::cout << "\n============ User Menu ============\n";
		std::cout << "Please, choose one option:\n";
		std::cout << "1) See events from a specific month\n";
		std::cout << "2) Delete an event from the list\n";
		std::cout << "3) The list of events that I attend\n";
		std::cout << "4) Display the list in the specified format\n";
		std::cout << "0) Exit\n";
		
		std::cout << "Your option is: ";

		std::string cmd;
		std::cin >> cmd;

		if (cmd == "1")
			seeEventsFromSpecificMonthUser();
			
		if (cmd == "2")
			deleteEventUserList();
			
		if (cmd == "3")
			seeAllEventsUserAttends();

		if (cmd == "4")
			displayInCorrectFormat();

		else if (cmd == "0")
			break;

	}
}

void UI::deleteEventUserList()
{
	std::cout << "Please, enter the title of the event you want to delete: ";
	std::string title;
	std::cin.get();
	std::getline(std::cin, title);
	EventValidator v;

	try {
		v.validateEventTitle(title);
		bool ok = userService.HandleDeleteEventUserList(title);
		if (ok)
		{
			Event e = adminService.handleGetEventByName(title);
			int nr = e.getNrOfPeople();
			e.setNrOfPeople(nr - 1);
			adminService.HandleUpdateEvent(e);
		}
	}
	catch (NotInAdminListException& ue) {
		std::cout << ue.what() << '\n';
	}
	catch (EventExceptions& ne) {
		std::cout << ne.what() << '\n';
	}
	catch (FileRepoException& ee) {
		std::cout << ee.what() << '\n';
	}
}

void UI::seeEventsFromSpecificMonthUser()
{
	std::string month;
	std::cout << "Please, enter the month: ";
	std::cin.get();
	std::getline(std::cin, month);
	std::cout << '\n';

	if (month == "")  // if no month was given
	{
		std::vector<Event> v = adminService.handleGetAllSorted();
		bool ok = true;

		while (ok)
		{
			for (int i = 0; i < v.size() && ok; ++i)
			{
				std::cout << v[i].toString();
				std::cout << '\n';
				std::string url = v[i].getLink();
				std::string com = "start " + url;
				system(com.c_str());
				std::string str;

				while (true)
				{
					std::cout << "Please, enter one the following options(add/pass/stop): ";
					std::cin >> str;

					if (str == "add")
					{
						int nr = v[i].getNrOfPeople();
						Event e = Event(v[i]);
						e.setNrOfPeople(nr + 1);

						try {
							if (userService.HandleAddEventToUserList(e))
								adminService.HandleUpdateEvent(e);
								
						}
						catch (InTheUserListException& ue) {
							std::cout << ue.what() << '\n';
						}
						catch (FileRepoException& ee) {
							std::cout << ee.what() << '\n';
						}

						std::cout << '\n';
						break;
					}
					else if (str == "pass")
					{
						std::cout << '\n';
						break;
					}
					else if (str == "stop")
					{
						ok = false;
						std::cout << '\n';
						break;
					}

					else
						std::cout << "Bad command!\n";
				}
				

			}
		}
		
	}
	else
	{
		int mo = transformMonth(month);
		if (mo == -1)
		{
			std::cout << "The value for month is not valid!\n";
			return;
		}

		std::vector<Event> v = adminService.HandleGetEventsByMonth(mo);
		if (v.size() == 0)
		{
			std::cout << "There are no events in this month!\n";
			return;
		}
		bool ok = true;

		while (ok)
		{
			for (int i = 0; i < v.size() && ok; ++i)
			{
				std::cout << v[i].toString();
				std::cout << '\n';
				std::string url = v[i].getLink();
				std::string com = "start " + url;
				system(com.c_str());
				std::string str;

				while (true)
				{
					std::cout << "Please, enter one the following options(add/pass/stop): ";
					std::cin >> str;

					if (str == "add")
					{
						int nr = v[i].getNrOfPeople();
						Event e = Event(v[i]);
						e.setNrOfPeople(nr + 1);

						try {
							if (userService.HandleAddEventToUserList(e))
								adminService.HandleUpdateEvent(e);
								
						}
						catch (InTheUserListException& ue) {
							std::cout << ue.what() << '\n';
						}
						catch (FileRepoException& ee) {
							std::cout << ee.what() << '\n';
						}

						std::cout << '\n';
						break;
					}
					else if (str == "pass")
					{
						std::cout << '\n';
						break;
					}
					else if (str == "stop")
					{
						ok = false;
						std::cout << '\n';
						break;
					}

					else
						std::cout << "Bad command!\n";
				}


			}
		}

	}
}

int UI::transformMonth(std::string month)
{
	if (month.size() > 2)
		return -1;

	int mo;
	if (month.size() == 1)
		mo = month[0] - '0';
	else
		mo = (month[0] - '0') * 10 + (month[1] - '0');

	if (mo > 0 && mo < 13)
		return mo;

	return -1;
}

void UI::seeAllEventsUserAttends()
{
	std::vector<Event> v = userService.HandleGetAllUserEvents();
	if (v.size() == 0)
	{
		std::cout << "There are no events!\n";
		return;
	}

	std::cout << "The events that I attend:\n\n";
	for (auto a : v)
	{
		std::cout << a.toString();
		std::cout << '\n';
	}
}



void UI::validDate(std::string date, int& hour, int& day, int& month, int& year)
{
	if (date.size() != 13)
		throw EventExceptions("The values for date and time are not correct!");

	day = (date[0] - '0') * 10 + (date[1] - '0');
	month = (date[3] - '0') * 10 + (date[4] - '0');
	year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
		+ (date[8] - '0') * 10 + (date[9] - '0');
	hour = (date[11] - '0') * 10 + (date[12] - '0');

 	/*if ((hour < 0 || hour > 23) || (day < 1 || day > 30) ||
		(month < 1 || month > 12) || (year < 1900 || year > 2030))
		throw std::exception("The values for date and time are not correct!");*/

	EventValidator v;
	v.validateEventDate(datetime(hour, day, month, year));
}

void UI::validNrOfPeople(std::string nr, int& nr_people)
{
	for (int i = 0; i < nr.size(); ++i)
		if (!isdigit(nr[i]))
			throw NrPeopleException("The number of people must be an integer!");
		else
		{
			nr_people *= 10;
			nr_people += nr[i] - '0';
		}

	EventValidator v;
	v.validateEventNrPeople(nr_people);
}

void UI::addEventAdmin()
{
	std::string title;
	std::string desc;
	int nr_people = 0;
	std::string link;
	int hour, day, month, year;
	std::string date;
	std::string nr;
	EventValidator v;

	try {
		std::cout << "Title of the new event: ";
		std::cin.get();
		getline(std::cin, title);
		v.validateEventTitle(title);

		std::cout << "The description of the new event: ";
		std::getline(std::cin, desc); 
		v.validateEventDesc(desc);

		std::cout << "Link to the event: ";
		std::getline(std::cin, link);
		v.validateEventLink(link);
	
		std::cout << "Date and time(dd/mm/yyyy hh): ";
		std::getline(std::cin, date);
		validDate(date, hour, day, month, year);
		datetime d = datetime(hour, day, month, year);

		std::cout << "The number of people that can attend: ";
		std::getline(std::cin, nr);
		validNrOfPeople(nr, nr_people);

		Event e = Event(title, desc, d, nr_people, link);
		bool ok = adminService.HandleAddEvent(e);

		if (ok)
			std::cout << "The event was succesfully added!\n";
		
	}
	catch (EventExceptions& e)	{
		std::cout << e.what() << '\n';
	}
	catch (NrPeopleException& ne) {
		std::cout << ne.what() << '\n';
	}
	catch (InTheEventListException& ee) {
		std::cout << ee.what() << '\n';
	}
	catch (FileRepoException& ee) {
		std::cout << ee.what() << '\n';
	}
}

void UI::printAllEventsAdmin()
{
	std::vector<Event> v = adminService.handleGetAll();
	std::cout << "The events are:\n\n";
	for (auto a : v)
	{
		std::cout << a.toString();
		std::cout << '\n';
	}
}

void UI::deleteEventAdmin()
{
	std::string title;
	std::cout << "The title of the event you want to delete: ";
	std::cin.get();
	std::getline(std::cin, title);
	EventValidator v;
	try {
		v.validateEventTitle(title);
		bool ok = adminService.HandleDeleteEvent(title);
		if (ok)
			std::cout << "The event was succesfully deleted!\n";
	}
	catch (EventExceptions& ne) {
		std::cout << ne.what() << '\n';
	}
	catch (NotInAdminListException& ae) {
		std::cout << ae.what() << '\n';
	}
	catch (FileRepoException& ee) {
		std::cout << ee.what() << '\n';
	}
}

void UI::updateEventAdmin()
{
	std::string title;
	std::string desc;
	int nr_people = 0;
	std::string link;
	int hour, day, month, year;
	std::string date;
	std::string nr;
	EventValidator v;

	try {
		std::cout << "Title of the new event: ";
		std::cin.get();
		getline(std::cin, title);
		v.validateEventTitle(title);

		std::cout << "The description of the new event: ";
		std::getline(std::cin, desc);
		v.validateEventDesc(desc);

		std::cout << "Link to the event: ";
		std::getline(std::cin, link);
		v.validateEventLink(link);
	
		std::cout << "Date and time(dd/mm/yyyy hh): ";
		std::getline(std::cin, date);
		validDate(date, hour, day, month, year);
		datetime d = datetime(hour, day, month, year);

		std::cout << "The number of people that can attend: ";
		std::getline(std::cin, nr);
		validNrOfPeople(nr, nr_people);

		Event e = Event(title, desc, d, nr_people, link);
		bool ok = adminService.HandleUpdateEvent(e);
		if (ok)
			std::cout << "The event was succesfully updated!\n";
	}
	catch (EventExceptions& e) {
		std::cout << e.what() << '\n';
	}
	catch (NrPeopleException& ne) {
		std::cout << ne.what() << '\n';
	}
	catch (NotInAdminListException& ae) {
		std::cout << ae.what() << '\n';
	}
	catch (FileRepoException& ee) {
		std::cout << ee.what() << '\n';
	}
}

void UI::filterEventsByNrOfPeople()
{
	int nr;
	std::cout << "The minimum number of people: ";
	std::cin >> nr;

	std::vector<Event> v = adminService.handleFilterEvents(nr);
	std::cout << "The events are:\n\n";
	for (auto a : v)
	{
		std::cout << a.toString();
		std::cout << '\n';
	}
}

void UI::displayInCorrectFormat()
{
	std::string path;
	if (format == "csv")
		path = "date.csv";
	else
		path = "date.html";

	std::string com = "start " + path;
	system(com.c_str());
}

