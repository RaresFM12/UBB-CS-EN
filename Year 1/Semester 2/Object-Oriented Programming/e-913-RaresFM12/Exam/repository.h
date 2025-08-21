#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "volunteer.h"
#include "department.h"
#include <vector>
#include <string>
#include "subject.h"
using namespace std;

class Repository : public Subject
{
private:
    vector<Volunteer> volunteers;
    vector<Department> departments;

public:
    Repository();

    vector<Department> getAllDepartments();
    vector<Volunteer> getAllVolunteers();

    void addVolunteerRepo(Volunteer v);
    void modifyDepartment(string na, string dep);

    void loadFromFile();
    void loadToFile();
};

#endif // REPOSITORY_H
