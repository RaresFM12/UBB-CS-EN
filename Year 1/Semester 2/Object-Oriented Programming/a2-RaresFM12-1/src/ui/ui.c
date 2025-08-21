#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"
#include "vector.h"

UI* createUI(Service* s)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->service = s;

	return ui;
}

void destroyUI(UI* u)
{
	if (u == NULL)
		return;

	destroyService(u->service);
	free(u);
}

void addDefaultCountries(UI* ui)
{
	bool ok;
	ok = addCountryService(ui->service, createCountry("Romania", "Europa", 20), true);
	ok = addCountryService(ui->service, createCountry("Franta", "Europa", 64), true);
	ok = addCountryService(ui->service, createCountry("Germania", "Europa", 72), true);
	ok = addCountryService(ui->service, createCountry("China", "Asia", 235), true);
	ok = addCountryService(ui->service, createCountry("SUA", "America", 200), true);
	ok = addCountryService(ui->service, createCountry("Mexic", "America", 137), true);
	ok = addCountryService(ui->service, createCountry("Brazilia", "America", 199), true);
	ok = addCountryService(ui->service, createCountry("Elvetia", "Europa", 17), true);
	ok = addCountryService(ui->service, createCountry("Japonia", "Asia", 77), true);
	ok = addCountryService(ui->service, createCountry("Australia", "Australia", 102), true);
}

void startUI(UI* ui)
{
	int cmd;
	char t[20];
	addDefaultCountries(ui);

	while (1)
	{
		printf("Welcome to our World Population Monitoring Organisation! Please, choose one of the following options:\n");
		printf("1) Add a new country\n");
		printf("2) Delete a country\n");
		printf("3) Update a country\n");
		printf("4) Display all countries by a given string\n");
		printf("5) Display all countries by a given string(sorted by population)\n");
		printf("6) Display all countries from a given continent(sorted by population)\n");
		printf("7) Undo LPO\n");
		printf("8) Redo LPO\n");
		printf("0) Exit\n");


		printf("Your choice is: ");
		scanf("%s", t);

		if (t[0] < '0' || t[0] > '9')
		{
			printf("Bad command!\n");
			continue;
		}
		else
			cmd = t[0] - '0';

		if (cmd == 1)
		{
			char name[35];
			char continent[20];
			char str[10];
			int population = -1;

			printf("Name of the country: ");
			scanf("%s", name);
			printf("Continent of the country: ");
			scanf("%s", continent);
			printf("Population of the country: ");
			scanf("%d", &population);
			gets(str);

			if (population <= 0)
				printf("The population must be a positive integer!\n");
			else
			{
				Country* c = createCountry(name, continent, population);
				if (addCountryService(ui->service, c, true))
					printf("The country was added!\n");
				else
				{
					printf("This country is already in!\n");
					destroyCountry(c);
				}
			}

		}
		else if (cmd == 2)
		{
			char name[35];

			printf("Name of the country: ");
			scanf("%s", name);

			if (deleteCountryService(ui->service, name, true))
				printf("The country was deleted!\n");
			else
				printf("There is no such country!\n");

		}
		else if (cmd == 3)
		{
			char name[35];
			printf("Name of the country you want to update: ");
			scanf("%s", name);

			int pop = -1;
			char name2[35];
			char str[10];
			printf("People migrated to: ");
			scanf("%s", name2);
			printf("The number of people who migrated: ");
			scanf("%d", &pop);
			gets(str);

			if (pop <= 0)
				printf("The number of people must be a positive integer!\n");
			else
			{
				if (checkCountryInListService(ui->service, name) && checkCountryInListService(ui->service, name2))
				{
					Country* c1 = returnCountryByNameService(ui->service, name);
					bool ok1 = updateCountryService(ui->service, name, c1->population - pop, true);

					Country* c2 = returnCountryByNameService(ui->service, name2);
					bool ok2 = updateCountryService(ui->service, name2, c2->population + pop, true);

					if (ok1 && ok2)
						printf("The country was updated succesfully!\n");
					else
						printf("The country is not in the list!\n");
				}
				else
					printf("One of the countries is not in the list!\n");
			}

		}
		else if (cmd == 4)
		{
			char str[35];
			gets(str);
			printf("The string: ");
			gets(str);

			Vector* vec = returnCountriesByStringService(ui->service, str);
			if (vec->size == 0)
				printf("There is no such country!\n");
			else
			{
				char text[100];
				for (int i = 0; i < vec->size; ++i)
				{
					toString(vec->elem[i], text);
					printf(text);
				}

			}

			destroyVector(vec);
		}
		else if (cmd == 5)
		{
			char str[35];
			gets(str);
			printf("The string: ");
			gets(str);

			Vector* vec = returnCountriesByStringSortedByPopulationService(ui->service, str);
			if (vec->size == 0)
				printf("There is no such country!\n");
			else
			{
				for (int i = 0; i < vec->size; ++i)
				{
					char text[100];
					toString(vec->elem[i], text);
					printf(text);
				}
			}

			destroyVector(vec);
		}
		else if (cmd == 6)
		{
			char str[35];
			char ok[10];
			int pop = -1;

			gets(str);
			printf("The continent: ");
			gets(str);
			printf("The minimum population: ");
			scanf("%d", &pop);
			gets(ok);

			if (pop <= 0)
				printf("The number of people must be a positive integer!\n");
			else
			{
				if (strlen(str) == 0)
				{
					Vector* vec = returnCountriesFromContinentService(ui->service, NULL, pop);
					if (vec->size == 0)
						printf("There is no such country!\n");
					else
					{
						for (int i = 0; i < vec->size; ++i)
						{
							char text[100];
							toString(vec->elem[i], text);
							printf(text);
						}
					}

					destroyVector(vec);
				}
				else
				{
					Vector* vec = returnCountriesFromContinentService(ui->service, str, pop);
					if (vec->size == 0)
						printf("There is no such country!\n");
					else
					{
						for (int i = 0; i < vec->size; ++i)
						{
							char text[100];
							toString(vec->elem[i], text);
							printf(text);
						}
					}

					destroyVector(vec);
				}
			}


		}
		else if (cmd == 7)
		{
			bool ok = undo(ui->service);
			if (ok)
				printf("The undo was a succes!\n");
			else
				printf("There are no undos left!\n");
		}
		else if (cmd == 8)
		{
			bool ok = redo(ui->service);
			if (ok)
				printf("The redo was a succes!\n");
			else
				printf("There are no redos left!\n");
		}
		else if (cmd == 0)
		{
			printf("The program is over! Thank you!");
			break;
		}
		else
			printf("Bad command!\n");
	}
}