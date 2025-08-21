#include "service.h"

Service::Service(Repository& re) :
    repo {re}
{}

vector<Volunteer> Service::getAllVolunteersService(string name)
{
    vector<Volunteer> vec = repo.getAllVolunteers();
    vector<Volunteer> vol;
    for (auto a : vec)
        if (a.getDepartment() == name)
            vol.push_back(a);

    for (int i = 0; i < vol.size(); ++i)
        for (int j = i + 1; j < vol.size(); ++j)
            if (vol[i].getName() > vol[j].getName())
            {
                Volunteer aux = vol[i];
                vol[i] = vol[j];
                vol[j] = aux;
            }

    return vol;
}

void Service::addVolunteer(Volunteer v)
{
    repo.addVolunteerRepo(v);
}

void Service::modifyDepartmentService(string na, string dep)
{
    repo.modifyDepartment(na, dep);
}

vector<Volunteer> Service::getAllVol()
{
    return repo.getAllVolunteers();
}

vector<Volunteer> Service::getAllUnVol()
{
    vector<Volunteer> vec = repo.getAllVolunteers();
    vector<Volunteer> vol;
    for (auto a : vec)
        if (a.getDepartment() == "None")
            vol.push_back(a);

    return vol;
}

vector<Department> Service::getAllDepartmentsService()
{
    return repo.getAllDepartments();
}
