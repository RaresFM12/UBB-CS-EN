#include "recipe.h"
#include <sstream>

Recipe::Recipe() {}

Recipe::Recipe(string na, string cui, int t, vector<string> ing) :
    name {na}, cuisine {cui}, time {t}, ingredients {ing}
{}

string Recipe::getName()
{
    return name;
}

string Recipe::getCuisine()
{
    return cuisine;
}

int Recipe::getTime()
{
    return time;
}

vector<string> Recipe::getIngredients()
{
    return ingredients;
}

void Recipe::setName(string na)
{
    name = na;
}

void Recipe::setCuisine(string cu)
{
    cuisine = cu;
}

void Recipe::setTime(int t)
{
    time = t;
}

void Recipe::setIngredients(vector<string> ing)
{
    ingredients = ing;
}

void Recipe::operator=(Recipe& r)
{
    name = r.name;
    cuisine = r.cuisine;
    time = r.time;
    ingredients = r.ingredients;
}

istream& operator>>(istream& is, Recipe& r)
{
    string line;
    string na, cu;
    int t;
    vector<string> ing;

    getline(is, line);
    vector<string> res = Recipe::tokenize(line, ',');

    if (res.size() != 4)
        return is;

    na = res[0];
    cu = res[1];
    t = stoi(res[2]);

    ing = Recipe::tokenize(res[3], '|');


    r.setName(na);
    r.setCuisine(cu);
    r.setTime(t);
    r.setIngredients(ing);
    return is;
}

ostream& operator<<(ostream& os, const Recipe& r)
{
    os << r.name << ',' << r.cuisine << ',' << r.time << ',';
    for (int i = 0; i < r.ingredients.size() - 1; ++i)
        os << r.ingredients[i] << '|';

    os << r.ingredients[r.ingredients.size() - 1] << '\n';

    return os;
}

vector<string> Recipe::tokenize(string input, char sep)
{
    stringstream is{ input };
    string token;
    vector<string> res;

    while (getline(is, token, sep))
        res.push_back(token);

    return res;
}
