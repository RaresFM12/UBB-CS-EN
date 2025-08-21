#include "repository.h"
#include <fstream>
#include <exception>

Repository::Repository() :
    elems{ vector<Engine>() }
{
    loadFromFile();
}

vector<Engine> Repository::getAll()
{
    return elems;
}

void Repository::loadFromFile()
{
    ifstream fin("text.txt");
    if (fin.is_open() == false)
        throw exception();

    Engine e;
    while (fin >> e)
        elems.push_back(e);

    cout << elems.size() << '\n';
    fin.close();
}
