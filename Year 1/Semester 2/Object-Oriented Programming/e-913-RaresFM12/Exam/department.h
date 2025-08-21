#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
#include <vector>
using namespace std;

class Department {
private:
    string name;
    string desc;

public:
    Department();
    Department(string na, string de);

    string getName();
    string getDesc();

    void setName(string na);
    void setDesc(string de);

    void operator=(const Department& d);
    friend istream& operator>>(istream& is, Department& d);
    static vector<string> tokenize(string input, char sep);
};

#endif // DEPARTMENT_H
