#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <crtdbg.h>
#include "ui.h"
#include "test.h"


int main()
{
	test_all();
	Repository* repo = createRepository();
	Service* s = createService(repo);
	UI* ui = createUI(s);

	startUI(ui);
	destroyUI(ui);

	_CrtDumpMemoryLeaks();
	return 0;
}