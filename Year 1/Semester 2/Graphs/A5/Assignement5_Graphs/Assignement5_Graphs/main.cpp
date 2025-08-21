#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <exception>
#include <map>
#include "ui.h"


int main()
{
	UI ui;
	int cmd = 0;
	bool ok = true;

	while (ok)
	{
		ui.printMenu();
		std::cout << "Please, choose one option: ";
		std::cin >> cmd;

		if (cmd == 0)
			ok = false;

		else if (cmd == 1)
			ui.createRandomGraph();

		else if (cmd == 2)
			ui.printNrOfVertices();

		else if (cmd == 3)
			ui.printNrOfEdges();

		else if (cmd == 4)
			ui.printVertices();

		else if (cmd == 5)
			ui.printEdges();

		else if (cmd == 6)
			ui.readGraphFromFile();

		else if (cmd == 7)
			ui.writeGraphInFile();

		else if (cmd == 8)
			ui.seeIfIsEdge();

		else if (cmd == 9)
			ui.printAdjacentEdgesOfVertex();

		else if (cmd == 10)
			ui.modifyCostOfEdge();

		else if (cmd == 11)
			ui.retrieveCostOfEdge();

		else if (cmd == 12)
			ui.addVertex();

		else if (cmd == 13)
			ui.removeVertex();

		else if (cmd == 14)
			ui.addEdge();

		else if (cmd == 15)
			ui.removeEdge();

		else if (cmd == 16)
			ui.connected_components();

		else if (cmd == 17)
			ui.find_mst_ui();

		else if (cmd == 18)
			ui.find_hamilton();

		else
			std::cout << "Bad command!\n";
	}

	return 0;
}