#pragma once

#include <vector>
#include "domain.h"

class Repository
{
private:
    vector<Engine> elems;

public:
    Repository();
    vector<Engine> getAll();
    void loadFromFile();
};