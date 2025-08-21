#pragma once 
#include <iostream>
#include <vector>
#include "domain.h"
#include "repository.h"
using namespace std;

class UI {
private:
	Service serv;

public:
	UI(Service c);
	void basic_cases();
	void run_ui();
	void add();
	void showAll();
	void saveFile();
};