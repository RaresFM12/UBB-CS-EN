#include "ui.h"
#include "domain.h"
#include <string>

UI::UI(Service service) :
	s{ service }
{}

void UI::run_ui()
{
	basic_cases();
	while (true)
	{
		print_menu();
		std::string cmd;

		std::cout << "Choose your option: ";
		std::cin >> cmd;
		if (cmd == "1")
			remove_element();

		else if (cmd == "2")
			show_all();

		else if (cmd == "3")
			mark_school();

		else if (cmd == "0")
			break;

		else
			std::cout << "Bad command!\n";
	}
}

void UI::remove_element()
{
	std::string name;
	float lon, lat;
	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "Longitude: ";
	std::cin >> lon;

	std::cout << "Latitude: ";
	std::cin >> lat;

	if (s.handleRemoveSchool(name, lon, lat))
		std::cout << "The school was removed!";
	else
		std::cout << "There is no such school!";
}

void UI::print_menu()
{
	std::cout << "Please, choose one option:\n";
	std::cout << "1) Remove school\n";
	std::cout << "2) Show all school\n";
	std::cout << "3) Mark all schools\n";
	std::cout << "0) Exit\n";
}

void UI::basic_cases()
{
	datetime d1(15, 4, 2023);
	s.handleAddSchool(School("Avram_Iancu", 46.77, 23.60, d1, true));

	datetime d2(8, 4, 2023);
	s.handleAddSchool(School("George_Cosbuc", 46.77, 23.58, d2, false));

	datetime d3(23, 4, 2023);
	s.handleAddSchool(School("Alexandru_Vaida", 46.77, 23.63, d3, false));

	datetime d4(4, 5, 2023);
	s.handleAddSchool(School("Romulus_Guga", 46.53, 24.57, d4, false));

	datetime d5(3, 5, 2023);
	s.handleAddSchool(School("Colegiul_Transilvania", 46.54, 24.57, d5, false));
}