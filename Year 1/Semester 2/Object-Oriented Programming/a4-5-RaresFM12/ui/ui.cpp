#include "ui.h"
#include <iostream>
#include <string>
#include "date.h"
#include "event.h"
#include <windows.h> 

UI::UI() :
	adminService{ AdminService() }, userService{ UserService() }
{}

UI::UI(AdminService as, UserService us) :
	adminService{ as }, userService{ us }
{}

UI::~UI() {}

void UI::defaultCases()
{
	adminService.HandleAddEvent(Event("Slate & Evenimente Crystal", "Căutare pe internet motoare. În rezultate ar trebui să apară companiile locale cu numele companiei dvs. sau nume similare.",
		datetime(14, 16, 3, 2000), 123, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));

	adminService.HandleAddEvent(Event("Planificarea evenimentelor Indigo", "Am creat o serie de 101 idei de nume de companii pentru a vă inspira. Încercați să vă bucurați de exerciții și amintiți-vă, totul merge deocamdată.",
		datetime(13, 4, 5, 2001), 432, "https://www.geeksforgeeks.org/exception-handling-c/"));

	adminService.HandleAddEvent(Event("Evenimente Buttercup", "Odată ce v-ați stabilit un nume pentru compania dvs. de gestionare a evenimentelor care nu este deja utilizat în regiunea dvs.", 
		datetime(15, 14, 3, 2001), 235, "https://stackoverflow.com/questions/8611815/determine-if-char-is-a-num-or-letter"));

	adminService.HandleAddEvent(Event("Designuri de evenimente corecte", "Oficiul pentru brevete și mărci din Statele Unite (USPTO). Sistemul de căutare electronică a mărcii vă permite să căutați toate înregistrările mărcilor",
		datetime(20, 27, 10, 1999), 100, "https://learn.microsoft.com/en-us/dotnet/api/system.char.isnumber?view=net-9.0"));

	adminService.HandleAddEvent(Event("Evenimente slefuite", "Înregistrați bazele de date privind înregistrarea companiei și mărcile comerciale. Companiile sunt înregistrate la nivel de stat.",
		datetime(9, 20, 7, 2000), 400, "https://www.geeksforgeeks.org/c-sharp-char-isnumber-method/"));

	adminService.HandleAddEvent(Event("Ana are mere", "This method is used to check whether the specified Unicode character matches number or not. If it matches then it returns True otherwise return False.",
		datetime(10, 17, 5, 1998), 535, "https://cppscripts.com/cpp-check-if-char-is-a-number"));

	adminService.HandleAddEvent(Event("As vrea sa termin", "The application will have a database that holds all the dogs in the shelter at a given moment. The shelter employees must be able to update the database, meaning.",
		datetime(11, 11, 3, 2000), 54, "https://www.youtube.com/watch?v=KYKBGj24AhI"));

	adminService.HandleAddEvent(Event("Life after school", "Apoi, rulați lista de câțiva oameni ale căror opinii le respectați ; este posibil ca aceasta să micșoreze și mai mult lista.",
		datetime(7, 2, 7, 2001), 65, "https://www.youtube.com/watch?v=t7LJBj6Jc-Q"));

	adminService.HandleAddEvent(Event("Keep calm", "Cătălin Măruță le aduce telespectatorilor două ore pline de energie și distracție. Cei mai iubiți artiști din România, concursuri, competiții inedite",
		datetime(12, 23, 6, 1997), 77, "https://www.youtube.com/watch?v=x9MGGgxBnOM"));

	adminService.HandleAddEvent(Event("This is no joke", "For centuries, Solomon’s name has been tied to wisdom, power, and divine favour. But some say his influence went beyond kingship, that he commanded spirits.",
		datetime(6, 14, 8, 2000), 144, "https://www.youtube.com/watch?v=CcgoFyBEZZk"));
}

void UI::run_ui()
{
	defaultCases();
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

	bool ok = userService.HandleDeleteEventUserList(title);
	if (ok)
	{
		Event e = adminService.handleGetEventByName(title);
		int nr = e.getNrOfPeople();
		e.setNrOfPeople(nr - 1);
		adminService.HandleUpdateEvent(e);
	}
	else
		std::cout << "This event is not in your attend list!\n";
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
		DynamicVector<Event> v = adminService.handleGetAllSorted();
		bool ok = true;

		while (ok)
		{
			for (int i = 0; i < v.getSize() && ok; ++i)
			{
				std::cout << v.getElement(i).toString();
				std::cout << '\n';
				std::string url = v.getElement(i).getLink();
				std::string com = "start " + url;
				system(com.c_str());
				std::string str;

				while (true)
				{
					std::cout << "Please, enter one the following options(add/pass/stop): ";
					std::cin >> str;

					if (str == "add")
					{
						int nr = v.getElement(i).getNrOfPeople();
						Event e = Event(v.getElement(i));
						e.setNrOfPeople(nr + 1);

						if (userService.HandleAddEventToUserList(e))
							adminService.HandleUpdateEvent(e);
						else
							std::cout << "You already added this event to your list!\n";

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

		DynamicVector<Event> v = adminService.HandleGetEventsByMonth(mo);
		if (v.getSize() == 0)
		{
			std::cout << "There are no events in this month!\n";
			return;
		}
		bool ok = true;

		while (ok)
		{
			for (int i = 0; i < v.getSize() && ok; ++i)
			{
				std::cout << v.getElement(i).toString();
				std::cout << '\n';
				std::string url = v.getElement(i).getLink();
				std::string com = "start " + url;
				system(com.c_str());
				std::string str;

				while (true)
				{
					std::cout << "Please, enter one the following options(add/pass/stop): ";
					std::cin >> str;

					if (str == "add")
					{
						int nr = v.getElement(i).getNrOfPeople();
						Event e = Event(v.getElement(i));
						e.setNrOfPeople(nr + 1);

						if (userService.HandleAddEventToUserList(e))
							adminService.HandleUpdateEvent(e);
						else
							std::cout << "You already added this event to your list!\n";

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
	DynamicVector<Event> v = userService.HandleGetAllUserEvents();
	if (v.getSize() == 0)
	{
		std::cout << "There are no events!\n";
		return;
	}

	std::cout << "The events that I attend:\n\n";
	for (int i = 0; i < v.getSize(); ++i)
	{
		std::cout << v.getElement(i).toString();
		std::cout << '\n';
	}
}



void UI::validDate(std::string date, int& hour, int& day, int& month, int& year)
{
	if (date.size() != 13)
		throw std::exception("The values for date and time are not correct!");

	day = (date[0] - '0') * 10 + (date[1] - '0');
	month = (date[3] - '0') * 10 + (date[4] - '0');
	year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
		+ (date[8] - '0') * 10 + (date[9] - '0');
	hour = (date[11] - '0') * 10 + (date[12] - '0');

 	if ((hour < 0 || hour > 23) || (day < 1 || day > 30) ||
		(month < 1 || month > 12) || (year < 1900 || year > 2030))
		throw std::exception("The values for date and time are not correct!");
}

void UI::validNrOfPeople(std::string nr, int& nr_people)
{
	for (int i = 0; i < nr.size(); ++i)
		if (!isdigit(nr[i]))
			throw std::exception("The number of people must be an integer!");
		else
		{
			nr_people *= 10;
			nr_people += nr[i] - '0';
		}
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

	std::cout << "Title of the new event: ";
	std::cin.get();
	getline(std::cin, title);

	std::cout << "The description of the new event: ";
	std::getline(std::cin, desc); 

	std::cout << "Link to the event: ";
	std::getline(std::cin, link);

	try {
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
		else
			std::cout << "There is already one event with that name!\n";
	}
	catch (const std::exception& e)	{
		std::cout << e.what() << '\n';
	}
}

void UI::printAllEventsAdmin()
{
	DynamicVector<Event> v = adminService.handleGetAll();
	std::cout << "The events are:\n\n";
	for (int i = 0; i < v.getSize(); ++i)
	{
		std::cout << v.getElement(i).toString();
		std::cout << '\n';
	}
		
}

void UI::deleteEventAdmin()
{
	std::string title;
	std::cout << "The title of the event you want to delete: ";
	std::cin.get();
	std::getline(std::cin, title);

	bool ok = adminService.HandleDeleteEvent(title);
	if (ok)
		std::cout << "The event was succesfully deleted!\n";
	else
		std::cout << "There is no such event in the list!\n";
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

	std::cout << "Title of the new event: ";
	std::cin.get();
	getline(std::cin, title);

	std::cout << "The description of the new event: ";
	std::getline(std::cin, desc);

	std::cout << "Link to the event: ";
	std::getline(std::cin, link);

	try {
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
		else
			std::cout << "There is no such event in the list!\n";
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void UI::filterEventsByNrOfPeople()
{
	int nr;
	std::cout << "The minimum number of people: ";
	std::cin >> nr;

	DynamicVector<Event> v = adminService.handleFilterEvents(nr);
	std::cout << "The events are:\n\n";
	for (int i = 0; i < v.getSize(); ++i)
	{
		std::cout << v.getElement(i).toString();
		std::cout << '\n';
	}
}

