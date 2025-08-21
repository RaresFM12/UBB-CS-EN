#include "department.h"
#include <sstream>

Department::Department() {}

Department::Department(string na, string de) :
    name {na}, desc {de}
{}

string Department::getName()
{
    return name;
}

string Department::getDesc()
{
    return desc;
}

void Department::setName(string na)
{
    name = na;
}

void Department::setDesc(string de)
{
    desc = de;
}

void Department::operator=(const Department& d)
{
    name = d.name;
    desc = d.desc;
}

istream& operator>>(istream& is, Department& d)
{
    string line;
    string na, de;

    getline(is, line);
    vector<string> res = Department::tokenize(line, ',');

    if (res.size() != 2)
        return is;

    na = res[0];
    de = res[1];

    d.setName(na);
    d.setDesc(de);

    return is;
}

vector<string> Department::tokenize(string input, char sep)
{
    stringstream is{ input };
    string token;
    vector<string> res;

    while (getline(is, token, sep))
        res.push_back(token);

    return res;
}
