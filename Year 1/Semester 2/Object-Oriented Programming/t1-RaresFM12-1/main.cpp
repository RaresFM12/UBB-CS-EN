#include <iostream>
#include "ui.h"
#include "service.h"
#include "repository.h"
#include "test.h"
using namespace std;

// cl main.cpp
// main

int main()
{
	//Test t;
	//t.testAll();

	Repository repo;
	Service serv(repo);
	UI ui(serv);
	ui.run_ui();
	std::cout << "asdfadsf";

	return 0;
}