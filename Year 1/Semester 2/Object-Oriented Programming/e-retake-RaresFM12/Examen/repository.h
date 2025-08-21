#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "chef.h"
#include "recipe.h"

class Repository
{
private:
    vector<Chef> chefs;
    vector<Recipe> recipes;

public:
    Repository();

    vector<Chef> getAllChefs();
    vector<Recipe> getAllRecipes();
    void addRecipe(Recipe r);

    void loadFromFile();
    void loadToFile();
};

#endif // REPOSITORY_H

