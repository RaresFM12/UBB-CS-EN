#include "repository.h"
#include <fstream>

Repository::Repository()
{
    loadFromFile();
}

vector<Chef> Repository::getAllChefs()
{
    return chefs;
}

vector<Recipe> Repository::getAllRecipes()
{
    return recipes;
}

void Repository::addRecipe(Recipe r)
{
    recipes.push_back(r);
    loadToFile();
}

void Repository::loadToFile()
{
    std::ofstream fout("../../recipes.txt");
    if (fout.is_open() == false)
        throw exception();

    vector<Recipe> vec = recipes;
    for (int i = 0; i < vec.size() - 1; ++i)
    {
        for (int j = i + 1; j < vec.size(); ++j)
            if (vec[i].getCuisine() > vec[j].getCuisine())
            {
                Recipe aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
            else if ((vec[i].getCuisine() == vec[j].getCuisine()) && (vec[i].getTime() > vec[j].getTime()))
            {
                Recipe aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }
    }

    for (auto a : vec)
        fout << a;

    fout.close();
}

void Repository::loadFromFile()
{
    std::ifstream fin1("../../chefs.txt");
    if (fin1.is_open() == false)
        throw exception();

    Chef c;
    while (fin1 >> c)
        chefs.push_back(c);

    fin1.close();

    std::ifstream fin2("../../recipes.txt");
    if (fin2.is_open() == false)
        throw exception();

    Recipe r;
    while (fin2 >> r)
        recipes.push_back(r);

    fin2.close();
}


