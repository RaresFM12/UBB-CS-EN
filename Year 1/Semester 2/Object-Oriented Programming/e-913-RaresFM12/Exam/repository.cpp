#include "repository.h"
#include <fstream>

Repository::Repository()
{
    loadFromFile();
}

vector<Volunteer> Repository::getAllVolunteers()
{
    return volunteers;
}

vector<Department> Repository::getAllDepartments()
{
    return departments;
}

void Repository::modifyDepartment(string na, string dep)
{
    for (int i = 0; i < volunteers.size(); ++i)
        if (volunteers[i].getName() == na)
        {
            volunteers[i].setDepartment(dep);
            break;
        }

    notify();
    loadToFile();
}

void Repository::addVolunteerRepo(Volunteer v)
{
    volunteers.push_back(v);
    loadToFile();
    notify();
}

void Repository::loadFromFile()
{
    std::ifstream fin1("../../departments.txt");
    if (fin1.is_open() == false)
        throw exception();

    Department d;
    while (fin1 >> d)
        departments.push_back(d);

    fin1.close();

    std::ifstream fin2("../../volunteers.txt");
    if (fin2.is_open() == false)
        throw exception();

    Volunteer v;
    while (fin2 >> v)
        volunteers.push_back(v);

    fin2.close();
}

void Repository::loadToFile()
{
    ofstream fout("../../volunteers.txt");
    if (fout.is_open() == false)
        throw exception();

    for (auto a : volunteers)
        fout << a;

    fout.close();

}
