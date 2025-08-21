#include "service.h"

Service::Service(Repository& r) :
    repo {r}
{}

vector<Chef> Service::getAllChefsService()
{
    return repo.getAllChefs();
}

vector<Recipe> Service::getAllRecipesService()
{
    return repo.getAllRecipes();
}

void Service::addRecipeService(Recipe r)
{
    repo.addRecipe(r);
    notify();
}
