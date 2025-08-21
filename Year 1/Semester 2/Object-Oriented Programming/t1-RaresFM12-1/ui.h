#pragma once
#include <iostream>
#include "service.h"

class UI {
private:
	Service s;

public:
	UI(Service s);

	void run_ui();
	void print_menu();
	void remove_element();
	void show_all();
	void mark_school();
	void basic_cases();
};

