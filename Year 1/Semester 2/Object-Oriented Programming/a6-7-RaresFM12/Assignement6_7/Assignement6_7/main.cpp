#include <iostream>
#include <crtdbg.h>
#include "ui.h"
#include "repository.h"
#include "file_repository.h"
#include "service_admin.h"
#include "service_user.h"
#include "test.h"
#include "validator.h"
using namespace std;

Repository* chooseTypeRepo(std::string s);
void initMemoryRepo(Repository& r);
std::string chooseFileType();

int main()
{
	{
		Test t;
		t.run_all();

		std::string str = chooseFileType();
		cout << '\n';
		Repository* repo = chooseTypeRepo(str);
		AdminService admin_service(*repo);
		UserService user_service(*repo);
		UI ui(admin_service, user_service, str);

		ui.run_ui();
		delete repo;
	}
	
	_CrtDumpMemoryLeaks();

	return 0;
}

std::string chooseFileType()
{
	while (true)
	{
		cout << "Choose your file type (1 - CSV, 2 - HTML):\n";
		cout << "Your choice is: ";
		string str;
		cin >> str;

		if (str == "1")
			return "csv";

		else if (str == "2")
			return "html";

		else
			cout << "Bad command!";
	}
}

Repository* chooseTypeRepo(string s)
{
	Repository* r = nullptr;

	while (true)
	{
		cout << "Choose your type of repo (1 - memory, 2 - file):\n";
		cout << "Your choice is: ";
		string str;
		cin >> str;

		if (str == "1")
		{
			r = new Repository(s);
			initMemoryRepo(*r);
			break;
		}
		else if (str == "2")
		{
			r = new FileRepository("date.txt", s);
			break;
		}
		else
			cout << "Bad command!";
	}

	return r;
}

void initMemoryRepo(Repository& r)
{
	r.addEvent(Event("Title1", "Description1", datetime(12, 13, 2, 1995), 34, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title2", "Description2", datetime(13, 17, 7, 1999), 145, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title3", "Description3", datetime(14, 23, 3, 2000), 300, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title4", "Description4", datetime(15, 24, 7, 2001), 340, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title5", "Description5", datetime(16, 1, 3, 2000), 314, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title6", "Description6", datetime(17, 7, 8, 2001), 213, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title7", "Description7", datetime(18, 22, 10, 1999), 100, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title8", "Description8", datetime(19, 25, 12, 1998), 123, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title9", "Description9", datetime(7, 17, 12, 1997), 156, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
	r.addEvent(Event("Title10", "Description10", datetime(20, 13, 11, 1999), 134, "https://restaurantesaranjuez.com/ro/101-idei-de-nume-de-companie-de-evenimente-pentru-afacerea-dvs/"));
}