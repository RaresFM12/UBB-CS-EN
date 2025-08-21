#ifndef CHEF_H
#define CHEF_H

#include <iostream>
#include <vector>
using namespace std;

class Chef
{
private:
    string name;
    string speciality;

public:
    Chef();
    Chef(string na, string spe);

    string getName();
    string getSpeciality();

    void setName(string na);
    void setSpeciality(string spe);

    void operator=(const Chef& c);
    friend istream& operator>>(istream& is, Chef& c);
    static vector<string> tokenize(string input, char sep);
};

#endif // CHEF_H
