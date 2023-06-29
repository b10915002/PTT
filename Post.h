#pragma once
#include "json.hpp"
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
using json = nlohmann::json;

class Post
{
public:
    struct push
    {
        int type;
        string authorID;
        string content;
        string time;
    };

private:
    string title;
    int id;
    int boardID;
    string authorID;
    string content;
    string time;
    vector<push> pushes;

public:
    Post();
    Post(json);
    string getTitle();
    int getID();
    int getBoardID();
    string getAuthorID();
    string getContent();
    string getTime();
    vector<push> getPushes();

    /*string getName();
    int getID();
    string getType();
    vector<push> getMembers();*/
};