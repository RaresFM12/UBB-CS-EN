#include <iostream>
#include "domain.h"
#include "repository.h"
#include "ui.h"
using namespace std;

int main()
{
	Service s;
	UI ui(s);
	ui.run_ui();

	return 0;
}