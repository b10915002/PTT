#pragma once
#include <vector>
#include <cstring>
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

class User
{
	private:
	string account;

public:
	User();
	User(json);
	string name;
	string password;
	std::vector<int> postsID;
	int Permission_level;	  // 0:guest,1:user,2:BM,3:System
	virtual string getAccount();
	virtual string getPassword();
	virtual int getPermissionLevel();
    virtual void addBoard();
    virtual void deleteBoard();
	virtual void deletePost();
    virtual void deletePush();
	virtual void editPost();
	void addPush(int);

};