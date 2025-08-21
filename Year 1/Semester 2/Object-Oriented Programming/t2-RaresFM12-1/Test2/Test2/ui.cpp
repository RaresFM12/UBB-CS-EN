#include "ui.h"

UI::UI(Service s) :
	serv {s}
{}

void UI::run_ui()
{
	basic_cases();
	while (true)
	{
		cout << "Please, choose one of the following options:\n";
		cout << "1) Add a new car\n";
		cout << "2) Show all\n";
		cout << "3) Save to file\n";

		string cmd;
		cout << "Your option is: ";
		cin >> cmd;

		if (cmd == "1")
			add();

		else if (cmd == "2")
			showAll();

		else if (cmd == "3")
			saveFile();

		else
			cout << "Bad command!\n";
	}
}

void UI::add()
{
	Car* c;
	cout << "Choose the type of engine(electric/turbo): ";
	string type;
	cin >> type;

	if (type == "electric")
	{
		int doo;
		cout << "The nr of doors: ";
		cin >> doo;

		cout << "The autonomy: ";
		int aut;
		cin >> aut;

		c = new Car(doo, new ElectricEngine(3000, aut));
		serv.addCar(c);
	}
	else
	{
		int doo;
		cout << "The nr of doors: ";
		cin >> doo;

		c = new Car(doo, new TurboEngine(3000));
		serv.addCar(c);
	}

	cout << c->toString() << "\n";
	cout << '\n';
}

void UI::showAll()
{
	cout << "The cars are:\n";
	vector<Car*> vec = serv.getCars();

	for (auto e : vec)
		cout << e->toString() << '\n';

	cout << '\n';
}


void UI::saveFile()
{
	double price;
	cout << "The price: ";
	cin >> price;
	vector<Car*> c = serv.getCarsWithMaxPrice(price);
	vector<Car*> c_new;

	for (auto e : c)
		if (e->getDoors() == 2)
			c_new.push_back(e);

	for (auto e : c)
		if (e->getDoors() == 4)
			c_new.push_back(e);

	serv.writeToFile("cars.txt", c_new);
	
	cout << '\n';
}

void UI::basic_cases()
{
	Car* c1 = new Car(2, new ElectricEngine(3000, 1500));
	Car* c2 = new Car(4, new TurboEngine(3000));
	Car* c3 = new Car(2, new TurboEngine(3000));
	Car* c4 = new Car(4, new ElectricEngine(3000, 2000));

	serv.addCar(c1);
	serv.addCar(c2);
	serv.addCar(c3);
	serv.addCar(c4);
}