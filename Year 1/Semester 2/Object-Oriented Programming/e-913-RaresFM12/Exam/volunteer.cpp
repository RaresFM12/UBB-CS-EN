#include "volunteer.h"
#include <sstream>

Volunteer::Volunteer() {}

Volunteer::Volunteer(string na, string em, vector<string> l, string dep) :
    name {na}, email {em}, list {l}, department {dep}
{}

string Volunteer::getName()
{
    return name;
}

string Volunteer::getEmail()
{
    return email;
}

vector<string> Volunteer::getList()
{
    return list;
}

string Volunteer::getDepartment()
{
    return department;
}

void Volunteer::setName(string na)
{
    name = na;
}

void Volunteer::setEmail(string em)
{
    email = em;
}

void Volunteer::setList(vector<string> l)
{
    list = l;
}

void Volunteer::setDepartment(string dep)
{
    department = dep;
}

istream& operator>>(istream& is, Volunteer& v)
{
    string line;
    string na, em, dep;

    getline(is, line);
    vector<string> res = Volunteer::tokenize(line, ',');

    if (res.size() != 4)
        return is;

    na = res[0];
    em = res[1];
    dep = res[3];

    res = Volunteer::tokenize(res[2], '|');

    v.setName(na);
    v.setEmail(em);
    v.setList(res);
    v.setDepartment(dep);

    return is;
}

void Volunteer::operator=(const Volunteer& v)
{
    name = v.name;
    email = v.email;
    list = v.list;
    department = v.department;
}

ostream& operator<<(ostream& os, const Volunteer& v)
{
    os << v.name << ',' << v.email << ',';
    for (int i = 0; i < v.list.size() - 1; ++i)
        os << v.list[i] << '|';
    os << v.list[v.list.size() - 1] << ',';
    os << v.department << '\n';
    return os;
}

vector<string> Volunteer::tokenize(string input, char sep)
{
    stringstream is{ input };
    string token;
    vector<string> res;

    while (getline(is, token, sep))
        res.push_back(token);

    return res;
}
