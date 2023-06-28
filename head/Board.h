#pragma once
#include "json.hpp"
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
using json = nlohmann::json;

class Board
{
public:
    struct member
    {
        int id;
        string type;
    };

private:
    string name;
    int id;
    string type;

    vector<member> members;

public:
    Board();
    Board(json);
    string getName();
    int getID();
    string getType();
    vector<member> getMembers();
};