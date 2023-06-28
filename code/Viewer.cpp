#include "Viewer.h"
#include "BoardManager.h"
#include "Board.h"
//#include "Post.h"
#include <iostream>
#include <cstring>
#include <conio.h>
#include <iomanip>
#define NC "\e[0m"
#define RED "\e[1;31m"
#define BB "\e[44m"
#define WB "\e[0;30;47m"
#define Y "\e[0;33m"
#define Y2 "\e[1;33m"

extern BoardManager *boardManager;
using namespace std;
Viewer::Viewer(/* args */)
{
}

void Viewer::updateScreen()
{
    if (boardManager->getState() != boardManager->BoardState::MENU)
    {
        system("CLS");
    }
    switch (boardManager->getState())
    {
    case boardManager->BoardState::MENU:
        break;
    case boardManager->BoardState::SELECT_BOARD:
    {
        Board _board = boardManager->boards[boardManager->getCurrentBoard()];
        cout << left << BB << "【看板列表】              批踢踢作業坊              看板《 " << _board.getName() << "》class BoardState::SELECT_BOARD\n"
             << setw(99) << " " << endl
             << "[↑][↓]選擇列  [←]回到上一層  [→]進入下一層";
        if (boardManager->users[boardManager->getCurrentUser()]->getPermissionLevel() == 3)
        {
            cout << "  [p]在當前位置開新看板 [d]刪除所選看板與子內容      " << NC;
        }else{
            cout << setw(53)<< " " << NC;
        }
        cout << endl
             << endl
             << setw(5) << "編號" << setw(51) << " " << setw(50) << "看板名稱"
             << endl
             << endl
             << endl;
        if (_board.getMembers().size() <= 0)
        {
            cout << "此看板無任何子成員\n";
            break;
        }
        for (int i = 0; i < _board.getMembers().size(); i++)
        {
            Board _memberBoard = boardManager->boards[_board.getMembers()[i].id];
            cout << right << setw(2) << ((boardManager->getCurrentRow() == i) ? "●" : "") << setw(3) << _memberBoard.getID() << setw(50) << " " << setw(50) << left << _memberBoard.getName() << endl;
        }
        break;
    }
    case boardManager->BoardState::BOARD:
    {
        Board _board = boardManager->boards[boardManager->getCurrentBoard()];
        cout << left << BB << "【看板列表】              批踢踢作業坊              看板《" << _board.getName() << "》class BoardState::BOARD\n"
             << setw(94) << " " << endl
             << "[↑][↓]選擇列  [←]回到上一層  [→]進入下一層  [n]新增貼文  [d]刪除所選貼文" << setw(18) << " " << NC
             << endl
             << endl
             << setw(5) << "編號" << setw(51) << " " << setw(50) << "文章名稱"
             << endl
             << endl
             << endl;
        if (_board.getMembers().size() <= 0)
        {
            cout << "此看板無任何子成員\n";
            break;
        }
        for (int i = 0; i < _board.getMembers().size(); i++)
        {
            //Board _memberBoard = boardManager->boards[_board.getMembers()[i].id];
            Post _memberPost = boardManager->posts[_board.getMembers()[i].id];
            cout << right << setw(2) << ((boardManager->getCurrentRow() == i) ? "●" : "") << setw(3) << _memberPost.getID() << setw(50) << " " << setw(50) << left << _memberPost.getTitle() << endl;
        }
        break;
    }
    case boardManager->BoardState::POST:
    {
        Post _post = boardManager->posts[boardManager->getCurrentPost()];
        cout << BB << "[↑][↓]選擇列  [←]回到上一層  [1][2][3]值得推薦/給他噓聲/只加註解  [d]刪除所選推文  [e]編輯文章" << NC << endl
             << endl
             << left << "作者:" << _post.getAuthorID() << right << setw(85) << WB << "看板:" << boardManager->boards[_post.getBoardID()].getName() << NC << endl
             << left << "標題:" << _post.getTitle() << endl
             << "時間:" << _post.getTime()
             << endl
             << endl
             << _post.getContent()
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;
        for (int i = 0; i < _post.getPushes().size(); i++)
        {
            cout << left << setw(2) << ((boardManager->getCurrentRow() == i) ? "●" : "");
            switch (_post.getPushes()[i].type)
            {
            case 1:
                cout << setw(2) << "推";
                break;
            case 2:
                cout << setw(2) << RED << "噓" << NC;
                break;
            case 3:
                cout << setw(2) << RED << "->" << NC;
                break;
            default:
                break;
            };
            int spaceCount = 0;
            for (int j = 0; j < _post.getPushes()[i].content.size(); j++)
            {
                //cout<<(int)_post.getPushes()[i].content[j];
                if (_post.getPushes()[i].content[j] < 0)
                {
                    spaceCount++;
                };
            }
            spaceCount /= 3;
            cout << right
                 << setw(25) << _post.getPushes()[i].authorID;
            for (int j = 0; j < spaceCount; j++)
            {
                cout << " ";
            }
            cout << setw(70) << _post.getPushes()[i].content
                 << setw(15) << _post.getPushes()[i].time
                 << endl;
        }
        break;
    }
    default:
        break;
    }
}