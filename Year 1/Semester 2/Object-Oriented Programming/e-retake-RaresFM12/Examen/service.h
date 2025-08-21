#ifndef SERVICE_H
#define SERVICE_H

#include "subject.h"
#include "repository.h"

class Service : public Subject
{
private:
    Repository& repo;

public:
    Service(Repository& r);

    vector<Chef> getAllChefsService();
    vector<Recipe> getAllRecipesService();
    void addRecipeService(Recipe r);
};

#endif // SERVICE_H
