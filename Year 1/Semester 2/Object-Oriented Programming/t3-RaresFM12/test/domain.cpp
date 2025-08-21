#include "domain.h"
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

Engine::Engine() :
    name {""}, keywords {""}, content{""}
{}

Engine::Engine(string na, string key, string cont) :
    name {na}, keywords {key}, content {cont}
{}

string Engine::getName()
{
    return name;
}

string Engine::getKeyWords()
{
    return keywords;
}

string Engine::getContent()
{
    return content;
}

void Engine::setName(string na)
{
    name = na;
}

void Engine::setKeywords(string key)
{
    keywords = key;
}

void Engine::setContent(string cont)
{
    content = cont;
}

void Engine::operator=(const Engine& eng)
{
    name = eng.name;
    keywords = eng.keywords;
    content = eng.content;
}

istream& operator>>(istream& in, Engine& eng)
{
    string line;
    string na, co;
    string key;

    getline(in, line);
    vector<string> res = Engine::tokenize(line, '|');

    if (res.size() != 3)
        return in;

    na = res[0];
    key = res[1];
    co = res[2];

    eng.setContent(co);
    eng.setKeywords(key);
    eng.setName(na);
    return in;
}

vector<string> Engine::tokenize(string input, char sep)
{
    stringstream is{ input };
    string token;
    vector<string> res;

    while (getline(is, token, sep))
        res.push_back(token);

    return res;
}
