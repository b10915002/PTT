#include "Post.h"
#include <iostream>

Post::Post()
{
    printf("empty Post Class ?\n");
}
Post::Post(json inputJson)
{
    for (int i = 0; i < inputJson["pushes"].size(); i++)
    {
        push _push = {.type = inputJson["pushes"][i]["type"].get<int>(),
                      .authorID = inputJson["pushes"][i]["authorID"].get<string>(),
                      .content = inputJson["pushes"][i]["content"].get<string>(),
                      .time = inputJson["pushes"][i]["time"].get<string>()};
        pushes.push_back(_push);
    }
    title = inputJson["title"].get<string>();
    id = inputJson["id"].get<int>();
    authorID = inputJson["authorID"].get<string>();
    boardID = inputJson["boardID"].get<int>();
    content = inputJson["content"].get<string>();
    time = inputJson["time"].get<string>();
}
string Post::getTitle()
{
    return title;
}

int Post::getID()
{
    return id;
};
int Post::getBoardID()
{
    return boardID;
};

string Post::getAuthorID()
{
    return authorID;
};

string Post::getContent()
{
    return content;
};

string Post::getTime()
{
    return time;
};

vector<Post::push> Post::getPushes()
{
    return pushes;
};