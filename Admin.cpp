#include "Admin.h"
#include "BoardManager.h"
#include <iostream>
extern BoardManager *boardManager;

Admin::Admin()
{
    Permission_level = 0;
    postsID.clear();
}
Admin::Admin(json _json)
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
string Admin::getAccount()
{
    return account;
}
string Admin::getPassword()
{
    return password;
}
int Admin::getPermissionLevel()
{
    return Permission_level;
}
void Admin::addBoard()
{
    string name = "";
    string type = "";
    while (1)
    {
        std::system("CLS");
        std::cout << "看板名稱(目前不建議輸入中文):";
        cin >> name;
        if (name.length() < 1)
        {
            std::system("CLS");
            std::cout << "此名稱小於一個字";
            std::system("pause");
        }
        else
        {
            break;
        }
    }
    // while (1)
    // {
    //     std::system("CLS");
    //     std::cout << "看板種類(select_board or board):";
    //     cin >> type;
    //     if (type.length() > 0 && (type == "select_board" || type == "board"))
    //     {
    //         break;
    //     }
    //     else
    //     {
    //         std::system("CLS");
    //         std::cout << "此輸入不正確";
    //         std::system("pause");
    //     }
    // }
    boardManager->insertBoard(name, "board", boardManager->getCurrentBoard());
    boardManager->initBoards();
    std::system("CLS");
    std::cout << "已建立新看板 " << name << endl;
    std::system("pause");
}
void Admin::deleteBoard()
{

    boardManager->deleteBoard(boardManager->boards[boardManager->getCurrentBoard()].getMembers()[boardManager->getCurrentRow()].id);
    boardManager->initBoards();
    boardManager->initPosts();
    boardManager->setCurrentRow(0);
    //boardManager->setCurrentBoard(boardManager->getLastBoard());
}
void Admin::deletePost()
{
    string deleteMessage;
    while (1)
    {
        std::system("CLS");
        std::cout << "原因訊息:";
        //cin >> content;
        getline(std::cin, deleteMessage, '\n');

        if (deleteMessage.length() < 1)
        {
            getline(std::cin, deleteMessage, '\n');
        }
        if (deleteMessage.length() > 70)
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
    if (boardManager->getState() == boardManager->BoardState::BOARD)
    {
        boardManager->deletePosts(boardManager->boards[boardManager->getCurrentBoard()].getMembers()[boardManager->getCurrentRow()].id, deleteMessage);
        boardManager->initPosts();
        boardManager->setCurrentRow(0);
    }
}

void Admin::deletePush()
{
    string deleteMessage;
    while (1)
    {
        std::system("CLS");
        std::cout << "原因訊息:";
        //cin >> content;
        getline(std::cin, deleteMessage, '\n');

        if (deleteMessage.length() < 1)
        {
            getline(std::cin, deleteMessage, '\n');
        }
        if (deleteMessage.length() > 70)
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
    boardManager->deletePush(boardManager->getCurrentPost(),boardManager->getCurrentRow(), deleteMessage);
    boardManager->initPosts();
    boardManager->setCurrentRow(0);
}
