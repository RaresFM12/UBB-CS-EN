#pragma once

#include "repository.h"

class Service
{
private:
    Repository repo;

public:
    Service();
    vector<Engine> getAllService();
};