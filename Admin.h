#pragma once
#include <vector>
#include <cstring>
#include "json.hpp"
#include "User.h"
using namespace std;

using json = nlohmann::json;

class Admin : public User
{
private:
    string account;

public:
    Admin();
    Admin(json);
    string name;
    string password;
    std::vector<int> postsID;
    int Permission_level; // 0:guest,1:User,2:BM,3:System
    string getAccount();
    string getPassword();
    int getPermissionLevel();
    void addBoard();
    void deleteBoard();
    void deletePost();
    void deletePush();
};