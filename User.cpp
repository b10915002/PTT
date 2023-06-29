#include "User.h"
#include "BoardManager.h"
#include <iostream>
extern BoardManager *boardManager;

User::User()
{
    Permission_level = 0;
    postsID.clear();
}
User::User(json _json)
{
    for (int i = 0; i < _json["posts"].size(); i++)
    {
        postsID.push_back(_json["posts"][i]);
    }
    name = _json["name"].get<string>();
    account = _json["account"].get<string>();
    password = _json["password"].get<string>();
    Permission_level = _json["Permission_level"].get<int>();
}
string User::getAccount()
{
    return account;
}
string User::getPassword()
{
    return password;
}
int User::getPermissionLevel()
{
    return Permission_level;
}
void User::addBoard()
{
    return;
}
void User::deleteBoard()
{
    return;
}
void User::addPush(int type)
{
    for (int i = 0; i < boardManager->postsJson["Posts"].size(); i++)
    {
        if (type == 3)
        {
            break;
        }
        if (boardManager->postsJson["Posts"][i]["id"].get<int>() == boardManager->getCurrentPost())
        {
            for (int j = 0; j < boardManager->postsJson["Posts"][i]["pushes"].size(); j++)
            {
                if (boardManager->postsJson["Posts"][i]["pushes"][j]["authorID"].get<string>() == boardManager->getCurrentAccount() && boardManager->postsJson["Posts"][i]["pushes"][j]["type"].get<int>() == type)
                {
                    std::system("CLS");
                    std::cout << "推/噓過了喔:)" << endl;
                    std::system("pause");
                    return;
                }
            }
            break;
        }
    }

    string content;
    while (1)
    {
        std::system("CLS");
        switch (type)
        {
        case 1:
            std::cout << "推文 ";
            break;
        case 2:
            std::cout << "噓文 ";
            break;
        case 3:
            std::cout << "-> ";
            break;
        default:
            break;
        }
        std::cout << "內容:";
        //cin >> content;
        getline(std::cin, content, '\n');

        if (content.length() < 1)
        {
            getline(std::cin, content, '\n');
        }
        if (content.length() > 70)
        {
            std::system("CLS");
            std::cout << "內容太長拉~" << endl;
            std::system("pause");
        }
        else
        {
            break;
        }
    }
    boardManager->insertPush(boardManager->getCurrentAccount(), content, type);
    boardManager->initPosts();
}
void User::deletePost()
{
    int id = boardManager->boards[boardManager->getCurrentBoard()].getMembers()[boardManager->getCurrentRow()].id;
    int toremove = 0;
    for (auto &it : boardManager->postsJson["Posts"].items())
    {
        if (it.value().at("id").get<int>() == id)
            toremove = stoi(it.key());
    }
    if (boardManager->postsJson["Posts"][toremove]["authorID"].get<string>() != boardManager->getCurrentAccount())
    {
        std::system("CLS");
        std::cout << "不要亂刪別人的東西qwq" << endl;
        std::system("pause");
        return;
    }
    if (boardManager->getState() == boardManager->BoardState::BOARD)
    {
        boardManager->deletePosts(boardManager->boards[boardManager->getCurrentBoard()].getMembers()[boardManager->getCurrentRow()].id);
        boardManager->initPosts();
        boardManager->setCurrentRow(0);
    }
};
void User::deletePush()
{
    int id = boardManager->getCurrentPost();
    int toremove = 0;
    for (auto &it : boardManager->postsJson["Posts"].items())
    {
        if (it.value().at("id").get<int>() == id)
            toremove = stoi(it.key());
    }
    if (boardManager->postsJson["Posts"][toremove]["authorID"].get<string>() != boardManager->getCurrentAccount())
    {
        std::system("CLS");
        std::cout << "不要亂刪別人的東西qwq" << endl;
        std::system("pause");
        return;
    }
    if (boardManager->getState() == boardManager->BoardState::POST)
    {
        boardManager->deletePush(boardManager->getCurrentPost(),boardManager->getCurrentRow());
        boardManager->initPosts();
        boardManager->setCurrentRow(0);
    }
};

#define NC "\e[0m"
#define WB "\e[0;30;47m"
void User::editPost()
{
    //if authorID not same
    if (boardManager->postsJson["Posts"][boardManager->getCurrentPost()]["authorID"].get<string>() != boardManager->getCurrentAccount())
    {
        return;
    }

    //boardManager->postsJson["Posts"][boardManager->getCurrentPost()]["content"].get<string>()
    //boardManager->postsJson["Posts"][boardManager->getCurrentPost()]["content"]="ASDASD"
    string post = boardManager->postsJson["Posts"][boardManager->getCurrentPost()]["content"].get<string>() + " ";
    string inStr = "";
    int index = post.length() - 1, ct = 0;
    while (1)
    {
        //update
        system("CLS");
        cout << "[←][→]選擇文字  [n]插入文字  [backspace]刪除文字   [enter]結束編輯"
             << endl;
        int len = post.length();
        for (int i = 0; i < len; i++)
        {
            if(i==index){
                if(post[i]<0){
                    cout << WB << post[i] << post[i+1]<< post[i+2] << NC;
                    i+=2;
                }else{
                    if(post[i]=='\n'){
                        cout << WB << "\\n\n" << NC;
                    }else{
                        cout << WB << post[i] << NC;
                    }
                }
            }else{
                cout << post[i];
            }
        }

        //
        Keys key = getInput();
        switch (key)
        {
        case KEY_LEFT:
            if(index>0){
                if(post[index-1]<0){
                    index-=3;
                }else{
                   index-=1;
                }
            }
            break;
        case KEY_RIGHT:
            if(index<post.length()-1){
                if(post[index]<0){
                    index+=3;
                }else{
                   index+=1;
                }
            }
            break;
        case KEY_B:
            if(index>0){
                if(post[index-1]<0){
                    ct=3;
                }else{
                    ct=1;
                }
                index-=ct;
            post.erase(index,ct);
            }
            break;
        case KEY_N:
            cout << endl << endl << endl << "欲新增文字:";
            getline(cin,inStr);
            if(post[index]<0){
                ct=3;
            }else{
                ct=1;
            }
            post.insert(index+ct,inStr);
            break;
        default:
            cout << endl << endl << endl << "是否儲存編輯? (y/n)";
            char ch = _getch();
            if(ch == 'y'){
                //error
                boardManager->postsJson["Posts"][boardManager->getCurrentPost()]["content"] = post;
            }
            return;
            break;
        }
    }
};