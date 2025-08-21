#ifndef SERVICE_H
#define SERVICE_H
#include "repository.h"

class Service
{
private:
    Repository& repo;

public:
    Service(Repository& re);

    vector<Department> getAllDepartmentsService();
    vector<Volunteer> getAllVolunteersService(string name);
    vector<Volunteer> getAllVol();
    vector<Volunteer> getAllUnVol();

    void addVolunteer(Volunteer v);
    void modifyDepartmentService(string na, string dep);
};

#endif // SERVICE_H
