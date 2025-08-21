#ifndef VOLUNTEER_H
#define VOLUNTEER_H
#include <string>
#include <vector>
using namespace std;

class Volunteer {
private:
    string name;
    string email;
    vector<string> list;
    string department;

public:
    Volunteer();
    Volunteer(string na, string em, vector<string> l, string dep);

    string getName();
    string getEmail();
    vector<string> getList();
    string getDepartment();

    void setName(string na);
    void setEmail(string em);
    void setList(vector<string> l);
    void setDepartment(string dep);

    friend istream& operator>>(istream& is, Volunteer& v);
    friend ostream& operator<<(ostream& os, const Volunteer& v);
    void operator=(const Volunteer& v);
    static vector<string> tokenize(string input, char sep);
};

#endif // VOLUNTEER_H
