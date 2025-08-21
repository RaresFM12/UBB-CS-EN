#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Engine {
private:
    string name;
    string keywords;
    string content;

public:
    Engine();
    Engine(string name, string key, string cont);

    string getName();
    string getKeyWords();
    string getContent();

    void setName(string na);
    void setKeywords(string key);
    void setContent(string cont);

    void operator=(const Engine& tri);
    friend istream& operator>>(istream& in, Engine& bill);
    static vector<string> tokenize(string input, char sep);
};
