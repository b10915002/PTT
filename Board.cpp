#include "Board.h"
#include <iostream>

Board::Board()
{
    std::ifstream ifs("Boards.json");
    json jf = json::parse(ifs)["Boards"][0];
    ifs.close();
    for (int i = 0; i < jf["members"].size(); i++)
    {
        member _member = {id = jf["members"][i]["id"].get<int>(),
                          type = jf["members"][i]["type"].get<string>()};
        members.push_back(_member);
    }
}
Board::Board(json inputJson)
{
    for (int i = 0; i < inputJson["members"].size(); i++)
    {
        member _member = {id = inputJson["members"][i]["id"].get<int>(),
                          type = inputJson["members"][i]["type"].get<string>()};
        members.push_back(_member);
    }
    name = inputJson["name"].get<string>();
    id = inputJson["id"].get<int>();
    type = inputJson["type"].get<string>();
}
string Board::getName()
{
    return name;
};
int Board::getID()
{
    return id;
};
string Board::getType()
{
    return type;
};
vector<Board::member> Board::getMembers()
{
    return members;
};