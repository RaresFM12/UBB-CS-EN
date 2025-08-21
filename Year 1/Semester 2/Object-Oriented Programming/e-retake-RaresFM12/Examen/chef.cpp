#include "chef.h"
#include <sstream>

Chef::Chef() {}

Chef::Chef(string na, string spe) :
    name {na}, speciality {spe}
{}

string Chef::getName()
{
    return name;
}

string Chef::getSpeciality()
{
    return speciality;
}

void Chef::setName(string na)
{
    name = na;
}

void Chef::setSpeciality(string spe)
{
    speciality = spe;
}

void Chef::operator=(const Chef& c)
{
    name = c.name;
    speciality = c.speciality;
}

istream& operator>>(istream& is, Chef& c)
{
    string line;
    string na, spe;

    getline(is, line);
    vector<string> res = Chef::tokenize(line, ',');

    if (res.size() != 2)
        return is;

    na = res[0];
    spe = res[1];

    c.setName(na);
    c.setSpeciality(spe);
    return is;
}

vector<string> Chef::tokenize(string input, char sep)
{
    stringstream is{ input };
    string token;
    vector<string> res;

    while (getline(is, token, sep))
        res.push_back(token);

    return res;
}
