#include "service.h"

Service::Service() :
    repo{ Repository() }
{}

vector<Engine> Service::getAllService()
{
    vector<Engine> vec = repo.getAll();;
    for (int i = 0; i < vec.size() - 1; ++i)
        for (int j = i + 1; j < vec.size(); ++j)
            if (vec[i].getKeyWords().length() > vec[j].getKeyWords().length())
            {
                Engine aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }

    return vec;
}



