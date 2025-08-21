#include <iostream>
#include <crtdbg.h>
#include "ui.h"
#include "repository.h"
#include "service_admin.h"
#include "service_user.h"
#include "test.h"
using namespace std;


int main()
{
	{
		Test t;
		t.run_all();

		Repository repo;
		AdminService admin_service(repo);
		UserService user_service(repo);
		UI ui(admin_service, user_service);

		ui.run_ui();
	}
	
	_CrtDumpMemoryLeaks();

	return 0;
}