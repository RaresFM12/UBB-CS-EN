#ifndef RECIPE_H
#define RECIPE_H

#include <iostream>
#include <vector>
using namespace std;

class Recipe
{
private:
    string name;
    string cuisine;
    int time;
    vector<string> ingredients;

public:
    Recipe();
    Recipe(string na, string cui, int t, vector<string> ing);

    string getName();
    string getCuisine();
    int getTime();
    vector<string> getIngredients();

    void setName(string na);
    void setCuisine(string cu);
    void setTime(int t);
    void setIngredients(vector<string> ing);

    void operator=(Recipe& r);
    friend istream& operator>>(istream& is, Recipe& r);
    friend ostream& operator<<(ostream& os, const Recipe& r);
    static vector<string> tokenize(string input, char sep);
};

#endif // RECIPE_H
