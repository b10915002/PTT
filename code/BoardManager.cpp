#include "BoardManager.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <ctime>
BoardManager::BoardManager()
{
    initBoards();

    initUsers();

    initPosts();

    viewer = Viewer();

    setCurrentBoard(0);
}
void BoardManager::Start()
{
    do
    {
        switch (getState())
        {
        case BoardState::MENU:
            system("CLS");
            std::cout <<"\
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⡇我⢸⣿⣿⣿⣿⣿⡏⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿\n\
⡇就⢸⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀⣿\n\
⡇靜⢸⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠙⠿⠿⠿⠻⠿⠿⠟⠿⠛⠉⠀⠀⠀⠀⠀⣸⣿\n\
⡇靜⢸⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿\n\
⡇看⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴⣿⣿⣿⣿\n\
⡇你⢸⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⢰⣹⡆⠀⠀⠀⠀⠀⠀⣭⣷⠀⠀⠀⠸⣿⣿⣿⣿\n\
⡇裝⢸⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠈⠉⠀⠀⠤⠄⠀⠀⠀⠉⠁⠀⠀⠀⠀⢿⣿⣿⣿\n\
⡇逼⢸⣿⣿⣿⣿⣿⣿⣿⣿⢾⣿⣷⠀⠀⠀⠀⡠⠤⢄⠀⠀⠀⠠⣿⣿⣷⠀⢸⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠉⠀⠀⠀⠀⠀⢄⠀⢀⠀⠀⠀⠀⠉⠉⠁⠀⠀⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿\n\n";
            std::cout << "請輸入帳號(訪客登入請輸入guest):";
            cin >> account;
            if (account == "guest")
            {
                setCurrentUser(0);
                setCurrentBoard(0);
                setCurrentRow(0);
                setState(BoardState::SELECT_BOARD);
            }
            else if (account == "new")
            {
                while (account != "q")
                {
                    system("CLS");
                    std::cout << "請輸入要註冊帳號(至少兩個字 輸入q以離開):";
                    cin >> account;
                    bool isAccountUsed = false;
                    for (int i = 0; i < users.size(); i++)
                    {
                        if (account == users[i]->getAccount())
                        {
                            system("CLS");
                            std::cout << "此帳號已被使用";
                            isAccountUsed = true;
                        }
                    }
                    if (account.length() < 2)
                    {
                        system("CLS");
                        std::cout << "此帳號小於兩個字";
                        isAccountUsed = true;
                    }
                    if (isAccountUsed == false)
                    {
                        break;
                    }
                }
                if (account == "q")
                {
                    continue;
                }
                while (1)
                {
                    system("CLS");
                    std::cout << "請輸入密碼(至少四個字 輸入q以離開):";
                    cin >> password;
                    if (password == "q")
                    {
                        break;
                    }
                    else if (password.length() < 4)
                    {
                        system("CLS");
                        std::cout << "此密碼小於四個字";
                    }
                    else
                    {
                        break;
                    }
                }
                if (password == "q")
                {
                    continue;
                }
                string name;
                while (1)
                {
                    system("CLS");
                    std::cout << "請輸入暱稱(至少兩個字 輸入q以離開):";
                    cin >> name;
                    if (name == "q")
                    {
                        break;
                    }
                    else if (name.length() < 2)
                    {
                        system("CLS");
                        std::cout << "此暱稱小於兩個字";
                    }
                    else
                    {
                        break;
                    }
                }
                if (name == "q")
                {
                    continue;
                }
                insertUser(account, password, name);
                initUsers();
                system("CLS");
                std::cout << "已完成註冊 請重新登入";
            }
            else
            {
                for (int i = 0; i < users.size(); i++)
                {
                    if (account == users[i]->getAccount())
                    {
                        std::cout << "請輸入密碼:";
                        cin >> password;
                        if (password == users[i]->getPassword())
                        {
                            setCurrentUser(i);
                            setCurrentBoard(0);
                            setCurrentRow(0);
                            setState(BoardState::SELECT_BOARD);
                            break;
                        }
                    }
                }
                system("CLS");
                std::cout << "查無此帳號 請按任意鍵繼續\n";
                break;
            }
            break;
        case BoardState::SELECT_BOARD: // 112 80 pP
            //if (_kbhit())
            {
                //char ch = _getch(); 72 80 75 77 UDLR
                Keys key = getInput();
                switch (key)
                {
                case KEY_UP:
                    if (getCurrentRow() > 0)
                    {
                        setCurrentRow(getCurrentRow() - 1);
                    }
                    break;
                case KEY_DOWN:
                    if (getCurrentRow() < boards[getCurrentBoard()].getMembers().size() - 1)
                    {
                        setCurrentRow(getCurrentRow() + 1);
                    }
                    break;
                case KEY_LEFT:
                    if (getCurrentBoard() == 0)
                    {
                        system("CLS");
                        setState(BoardState::MENU);
                        password = "";
                        account = "";
                        std::cout << "NICO : 將退出到登入介面 請按任意鍵繼續~\n";
                        std::cout << "她不是沒嘴巴只是帶了黑色口罩 全民防疫 人人有責" << '\n';
                        //cout << "⢕⢕⢕⢕⢕⠅⢗⢕⠕⣠⠄⣗⢕⢕⠕⢕⢕⢕⠕⢠⣿⠐⢕⢕⢕⠑⢕⢕⠵⢕\n⢕⢕⢕⢕⠁⢜⠕⢁⣴⣿⡇⢓⢕⢵⢐⢕⢕⠕⢁⣾⢿⣧⠑⢕⢕⠄⢑⢕⠅⢕\n⢕⢕⠵⢁⠔⢁⣤⣤⣶⣶⣶⡐⣕⢽⠐⢕⠕⣡⣾⣶⣶⣶⣤⡁⢓⢕⠄⢑⢅⢑\n⠍⣧⠄⣶⣾⣿⣿⣿⣿⣿⣿⣷⣔⢕⢄⢡⣾⣿⣿⣿⣿⣿⣿⣿⣦⡑⢕⢤⠱⢐\n⢠⢕⠅⣾⣿⠋⢿⣿⣿⣿⠉⣿⣿⣷⣦⣶⣽⣿⣿⠈⣿⣿⣿⣿⠏⢹⣷⣷⡅⢐\n⣔⢕⢥⢻⣿⡀⠈⠛⠛⠁⢠⣿⣿⣿⣿⣿⣿⣿⣿⡀⠈⠛⠛⠁⠄⣼⣿⣿⡇⢔\n⢕⢕⢽⢸⢟⢟⢖⢖⢤⣶⡟⢻⣿⡿⠻⣿⣿⡟⢀⣿⣦⢤⢤⢔⢞⢿⢿⣿⠁⢕\n⢕⢕⠅⣐⢕⢕⢕⢕⢕⣿⣿⡄⠛⢀⣦⠈⠛⢁⣼⣿⢗⢕⢕⢕⢕⢕⢕⡏⣘⢕\n⢕⢕⠅⢓⣕⣕⣕⣕⣵⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣷⣕⢕⢕⢕⢕⡵⢀⢕⢕\n⢑⢕⠃⡈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃⢕⢕⢕\n";
                        //cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣶⣶⣶⣶⣶⣾⣿⣿⣿⣿⣿⣶⣶⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣶⣾⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⢨⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⢀⣠⣤⣀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣿⣿⣿⣿⣷⣄⠀\n⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆\n⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⢸⣿⣿⣿⣿⠋⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⠀⠀⠀⠀⠀⠀⠛⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⢸⣿⣿⣿⣿⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⢸⣿⣿⣿⡇⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠸⣿⠸⣿⡇⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿\n⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⠃⢀⡤⢤⣀⠀⢻⠀⢹⣇⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⣿⣿⣿⣿⣿⣿⣿\n⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⠠⠏⠀⠀⣿⣷⠀⠀⠀⠛⠀⠀⠀⣴⠖⠒⣶⣿⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⣿⣿⣿⣿⣿⣿⣿\n⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⣿⣛⣻⠀⠀⠀⠀⠀⠀⠀⠁⢠⣤⣿⣿⣿⡌⢻⣿⣿⣿⠿⠻⠿⠃⠀⠀⠀⣿⣿⣿⣿⣿⣿⡇\n⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠘⠿⢬⠿⠃⠁⢸⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⠁\n⠀⠀⠀⠀⢸⡏⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⢹⣿⣿⣿⣿⠀\n⠀⠀⠀⠀⢸⠀⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⠀\n⠀⠀⠀⠀⢸⠀⣿⣿⣿⡿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⣶⣦⣄⠀⠀⠀⣿⣿⣿⣿⠀\n⠀⠀⠀⠀⢸⡆⢻⣿⣿⡇⢻⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣷⣴⠀⢹⣿⣿⣿⠀\n⠀⠀⠀⠀⠈⣷⠘⣿⣿⡇⠀⢿⣿⣄⣀⣀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⢸⣿⣿⣿⠀\n⠀⠀⠀⠀⠀⠈⠀⠹⣿⣿⣤⣾⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⠁⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣾⣿⠸⡿⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⣄⠄⠰⠋⠀⠿⢿⣿⣿⣿⣿⣿⡟⠻⠛⢿⣿⣿⣿⣿⣿⣿⡿⠀⠁⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠃⠀⠀⠀⠀⠀⠀⢻⣿⡿⠋⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣇⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⣀⣄⡈⠟⠁⣀⡄⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⡀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⡇⠀⠀\n⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠜⠿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⠀⠀\n";
                        std::cout << "\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣶⣶⣶⣶⣶⣾⣿⣿⣿⣿⣿⣶⣶⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣶⣾⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⢨⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⢀⣠⣤⣀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣿⣿⣿⣿⣷⣄⠀\n\
⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆\n\
⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⢸⣿⣿⣿⣿⠋⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⠀⠀⠀⠀⠀⠀⠛⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⢸⣿⣿⣿⣿⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⢸⣿⣿⣿⡇⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠸⣿⠸⣿⡇⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⠃⢀⡤⢤⣀⠀⢻⠀⢹⣇⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⣿⣿⣿⣿⣿⣿⣿\n\
⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⠠⠏⠀⠀⣿⣷⠀⠀⠀⠛⠀⠀⠀⣴⠖⠒⣶⣿⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⣿⣿⣿⣿⣿⣿⣿\n\
⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⣿⣛⣻⠀⠀⠀⠀⠀⠀⠀⠁⢠⣤⣿⣿⣿⡌⢻⣿⣿⣿⠿⠻⠿⠃⠀⠀⠀⣿⣿⣿⣿⣿⣿⡇\n\
⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠘⠿⢬⠿⠃⠁⢸⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⠁\n\
⠀⠀⠀⠀⢸⡏⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⢹⣿⣿⣿⣿⠀\n\
⠀⠀⠀⠀⢸⠀⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⠀\n\
⠀⠀⠀⠀⢸⠀⣿⣿⣿⡿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⣶⣦⣄⠀⠀⠀⣿⣿⣿⣿⠀\n\
⠀⠀⠀⠀⢸⡆⢻⣿⣿⡇⢻⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣷⣴⠀⢹⣿⣿⣿⠀\n\
⠀⠀⠀⠀⠈⣷⠘⣿⣿⡇⠀⢿⣿⣄⣀⣀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⢸⣿⣿⣿⠀\n\
⠀⠀⠀⠀⠀⠈⠀⠹⣿⣿⣤⣾⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⠁⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣾⣿⠸⡿⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⣄⠄⠰⠋⠀⠿⢿⣿⣿⣿⣿⣿⡟⠻⠛⢿⣿⣿⣿⣿⣿⣿⡿⠀⠁⠀\n\
⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠃⠀⠀⠀⠀⠀⠀⢻⣿⡿⠋⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣇⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⣀⣄⡈⠟⠁⣀⡄⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⡀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⡇⠀⠀\n\
⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠜⠿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⠀⠀\n"
                                  << '\n';
                                  system("pause");
                    }
                    else
                    {
                        setCurrentBoard(getLastBoard());
                        setLastBoardPopBack();
                        setCurrentRow(0);
                    }
                    break;
                case KEY_RIGHT:
                    if (boards[getCurrentBoard()].getMembers().size() <= 0)
                    {
                        break;
                    }
                    setLastBoardPushBack(getCurrentBoard());
                    if (boards[getCurrentBoard()].getMembers()[getCurrentRow()].type == "board")
                    {
                        if (boards[boards[getCurrentBoard()].getMembers()[getCurrentRow()].id].getMembers().size() > 0)
                        {
                            if (boards[boards[getCurrentBoard()].getMembers()[getCurrentRow()].id].getMembers()[0].type == "board")
                            {
                                setState(BoardState::SELECT_BOARD);
                            }
                            else
                            {
                                setState(BoardState::BOARD);
                            }
                        }
                        setCurrentBoard(boards[getCurrentBoard()].getMembers()[getCurrentRow()].id);
                        setCurrentRow(0);
                    }
                    else if (boards[getCurrentBoard()].getMembers()[getCurrentRow()].type == "post")
                    {
                        //exception TO DO
                    }
                    break;
                case KEY_P:
                {
                    users[currentUser]->addBoard();
                    break;
                }
                case KEY_D:
                {
                    users[currentUser]->deleteBoard();
                    break;
                }
                case KEY_N:
                {
                    if (boardJson["Boards"][getCurrentBoard()]["members"].size()>0){
                        break;
                    }
                    users[currentUser]->addPost();
                    setState(BoardState::BOARD);
                    break;
                }
                break;
                default:
                    break;
                }
            }
            break;
        case BoardState::BOARD:
        {
            Keys key = getInput();
            switch (key)
            {
            case KEY_UP:
                if (boards[getCurrentBoard()].getMembers().size() > 0 && getCurrentRow() > 0)
                {
                    setCurrentRow(getCurrentRow() - 1);
                }
                break;
            case KEY_DOWN:
                if (boards[getCurrentBoard()].getMembers().size() > 0 && getCurrentRow() < boards[getCurrentBoard()].getMembers().size() - 1)
                {
                    setCurrentRow(getCurrentRow() + 1);
                }
                break;
            case KEY_LEFT:
                setState(BoardState::SELECT_BOARD);
                setCurrentBoard(getLastBoard());
                setLastBoardPopBack();
                setCurrentRow(0);
                break;
            case KEY_RIGHT:
                if (boards[getCurrentBoard()].getMembers().size() <= 0)
                {
                    break;
                }
                setLastBoardPushBack(getCurrentBoard());
                if (boards[getCurrentBoard()].getMembers()[getCurrentRow()].type == "post")
                {
                    setCurrentPost(boards[getCurrentBoard()].getMembers()[getCurrentRow()].id);
                    setCurrentRow(0);
                    setState(BoardState::POST);
                }
                break;
            case KEY_D:
                users[currentUser]->deletePost();
                break;
            case KEY_N:
                users[currentUser]->addPost();
                break;
            default:
                break;
            }
        }
        break;
        case BoardState::POST:
        {
            Keys key = getInput();

            switch (key)
            {
            case KEY_UP:
                if (posts[getCurrentPost()].getPushes().size() > 0 && getCurrentRow() > 0)
                {
                    setCurrentRow(getCurrentRow() - 1);
                }
                break;
            case KEY_DOWN:
                if (posts[getCurrentPost()].getPushes().size() > 0 && getCurrentRow() < posts[getCurrentPost()].getPushes().size() - 1)
                {
                    setCurrentRow(getCurrentRow() + 1);
                }
                break;
            case KEY_LEFT:
                setState(BoardState::BOARD);
                setCurrentBoard(getLastBoard());
                setLastBoardPopBack();
                setCurrentRow(0);
                break;
            case KEY_1:
                users[getCurrentUser()]->addPush(1);
                break;
            case KEY_2:
                users[getCurrentUser()]->addPush(2);
                break;
            case KEY_3:
                users[getCurrentUser()]->addPush(3);
                break;
            case KEY_D:
                users[currentUser]->deletePush();
                break;
            case KEY_E:
                users[currentUser]->editPost();
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        };
        viewer.updateScreen();
    } while (1); //inputChar = _getch()
};
void BoardManager::initBoards()
{
    boards.clear();
    std::fstream ifs("Boards.json");
    boardJson = json::parse(ifs);
    ifs.close();
    boards.resize(boardJson["Boards"].size());
    for (int i = 0; i < boardJson["Boards"].size(); i++)
    {
        boards[i] = Board(boardJson["Boards"][i]);
    }
}
void BoardManager::insertBoard(string name, string type, int father)
{
    bool isIDCanBeUsed = true;
    int id;
    for (id = 0; id < boardJson["Boards"].size(); id++)
    {
        isIDCanBeUsed = true;
        for (int j = 0; j < boardJson["Boards"].size(); j++)
        {
            if (boardJson["Boards"][j]["id"].get<int>() == id)
            {
                isIDCanBeUsed = false;
                break;
            }
        }
        if (isIDCanBeUsed == true)
        {
            break;
        }
    }
    std::fstream ofs("Boards.json", ios::out);
    json newBoard = {
        {"name", name},
        {"id", id},
        {"type", type},
        {"members", {}}};
    newBoard["members"] = json::parse("[]");
    boardJson["Boards"].push_back(newBoard);

    for (int i = 0; i < boardJson["Boards"].size(); i++)
    {
        if (boardJson["Boards"][i]["id"].get<int>() == father)
        {
            boardJson["Boards"][i]["members"].push_back({{"id", id}, {"type", type}});
        }
    }
    ofs << boardJson << endl;
    ofs.close();
}
void BoardManager::deleteBoard(int id)
{
    int toremove = 0;
    for (auto &it : boardJson["Boards"].items())
    {
        if (it.value().at("id").get<int>() == id)
            toremove = stoi(it.key());
    }

    for (int i = 0; i < boardJson["Boards"][toremove]["members"].size(); i++) //delete member post and board
    {
        if (boardJson["Boards"][toremove]["members"][i]["type"].get<string>() == "board")
        {
            deleteBoard(boardJson["Boards"][toremove]["members"][i]["id"].get<int>());
        }
        else
        {
            postsJson["Posts"].erase(postsJson["Posts"].begin() + boardJson["Boards"][toremove]["members"][i]["id"].get<int>());
        }
    }
    for (int i = 0; i < boardJson["Boards"].size(); i++) //delete another boards member if contain this
    {
        for (int j = 0; j < boardJson["Boards"][i]["members"].size(); j++)
        {
            if (boardJson["Boards"][i]["members"][j]["type"].get<string>() == "board" && boardJson["Boards"][i]["members"][j]["id"].get<int>() == id)
            {
                boardJson["Boards"][i]["members"].erase(j);
            }
        }
    }
    std::fstream Pofs("Posts.json", ios::out);
    Pofs << postsJson << endl;
    Pofs.close();
    boardJson["Boards"].erase(boardJson["Boards"].begin() + toremove);
    std::fstream ofs("Boards.json", ios::out);
    ofs << setw(6) << boardJson << endl;
    ofs.close();
}
void BoardManager::initUsers()
{
    users.clear();
    std::fstream ifs("Users.json");
    usersJson = "";
    usersJson = json::parse(ifs);
    ifs.close();
    users.resize(usersJson["Users"].size());
    for (int i = 0; i < usersJson["Users"].size(); i++)
    {
        if (usersJson["Users"][i]["Permission_level"].get<int>() == 3)
        {
            users[i] = new Admin(usersJson["Users"][i]);
        }
        else
        {
            users[i] = new User(usersJson["Users"][i]);
        }
    }
}
void BoardManager::insertUser(string _account, string _password, string _name)
{
    std::fstream ofs("Users.json", ios::out);
    //json emptyJson(json::value_type::array);
    json newUser = {
        {"account", _account},
        {"password", _password},
        {"name", _name},
        {"postsID", {}},
        {"Permission_level", 1}};
    newUser["postsID"] = json::parse("[]");
    usersJson["Users"].push_back(newUser);
    ofs << usersJson << endl;
    ofs.close();
}

void BoardManager::initPosts()
{
    std::fstream ifs("Posts.json");
    postsJson = json::parse(ifs);
    ifs.close();
    posts.resize(postsJson["Posts"].size());
    for (int i = 0; i < postsJson["Posts"].size(); i++)
    {
        posts[i] = Post(postsJson["Posts"][i]);
    }
}
void BoardManager::deletePosts(int id)
{

    int toremove = 0;
    for (auto &it : postsJson["Posts"].items())
    {
        if (it.value().at("id").get<int>() == id)
            toremove = stoi(it.key());
    }
    postsJson["Posts"][toremove]["title"] = "本文已被刪除";
    postsJson["Posts"][toremove]["content"] = " ";
    /*for (int i = 0; i < boardJson["Boards"][postsJson["Posts"][toremove]["boardID"].get<int>()]["members"].size(); i++) //delete another boards member if contain this
    {
        if (boardJson["Boards"][postsJson["Posts"][toremove]["boardID"].get<int>()]["members"][i]["type"].get<string>() == "post" && boardJson["Boards"][postsJson["Posts"][toremove]["boardID"].get<int>()]["members"][i]["id"].get<int>() == id)
        {
            boardJson["Boards"][postsJson["Posts"][toremove]["boardID"].get<int>()]["members"].erase(i);
            break;
        }
    }
    postsJson["Posts"].erase(postsJson["Posts"].begin() + toremove);


    std::fstream ofs("Boards.json", ios::out);
    ofs << boardJson << endl;
    ofs.close();*/
    std::fstream Pofs("Posts.json", ios::out);
    Pofs << postsJson << endl;
    Pofs.close();
}
void BoardManager::deletePosts(int id, string deleteMessage)
{

    int toremove = 0;
    for (auto &it : postsJson["Posts"].items())
    {
        if (it.value().at("id").get<int>() == id)
            toremove = stoi(it.key());
    }
    postsJson["Posts"][toremove]["title"] = "本文已被刪除";
    postsJson["Posts"][toremove]["content"] = deleteMessage;
    std::fstream Pofs("Posts.json", ios::out);
    Pofs << postsJson << endl;
    Pofs.close();
}
void BoardManager::deletePush(int id, int pushIndex)
{
    int toremove = 0;
    for (auto &it : postsJson["Posts"].items())
    {
        if (it.value().at("id").get<int>() == id)
            toremove = stoi(it.key());
    }
    postsJson["Posts"][toremove]["pushes"][pushIndex]["content"] = "本推文已被刪除";
    std::fstream Pofs("Posts.json", ios::out);
    Pofs << postsJson << endl;
    Pofs.close();
}
void BoardManager::deletePush(int id, int pushIndex, string deleteMessage)
{

    int toremove = 0;
    for (auto &it : postsJson["Posts"].items())
    {
        if (it.value().at("id").get<int>() == id)
            toremove = stoi(it.key());
    }
    postsJson["Posts"][toremove]["pushes"][pushIndex]["content"] = "本推文已被刪除(" + deleteMessage + ")";
    std::fstream Pofs("Posts.json", ios::out);
    Pofs << postsJson << endl;
    Pofs.close();
}
void BoardManager::insertPush(string _account, string _content, int type)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string _time = ((ltm->tm_mon + 1 < 10) ? "0" : "") + to_string(ltm->tm_mon + 1) + "/" + ((ltm->tm_mday < 10) ? "0" : "") + to_string(ltm->tm_mday) + " " + ((ltm->tm_hour < 10) ? "0" : "") + to_string(ltm->tm_hour) + ":" + ((ltm->tm_min < 10) ? "0" : "") + to_string(ltm->tm_min);
    json newPush = {
        {"type", type},
        {"authorID", _account},
        {"content", _content},
        {"time", _time}};
    for (int i = 0; i < postsJson["Posts"].size(); i++)
    {
        if (postsJson["Posts"][i]["id"].get<int>() == getCurrentPost())
        {
            postsJson["Posts"][i]["pushes"].push_back(newPush);
        }
    }
    std::fstream ofs("Posts.json", ios::out);
    ofs << postsJson << endl;
    ofs.close();
}
void BoardManager::insertPost(string _title, string _content)
{
    bool isIDCanBeUsed = true;
    int id;
    for (id = 0; id < postsJson["Posts"].size(); id++)
    {
        isIDCanBeUsed = true;
        for (int j = 0; j < postsJson["Posts"].size(); j++)
        {
            if (postsJson["Posts"][j]["id"].get<int>() == id)
            {
                isIDCanBeUsed = false;
                break;
            }
        }
        if (isIDCanBeUsed == true)
        {
            break;
        }
    }

    time_t now = time(0);
    tm *ltm = localtime(&now);
    //time qwq
    string _time = "";
    string week[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    _time += week[ltm->tm_wday] + " ";
    _time += month[ltm->tm_mon] + " ";
    _time += ((ltm->tm_mday < 10) ? "0" : "") + to_string(ltm->tm_mday) + " ";
    _time += ((ltm->tm_hour < 10) ? "0" : "") + to_string(ltm->tm_hour) + ":";
    _time += ((ltm->tm_min + 1 < 10) ? "0" : "") + to_string(ltm->tm_min + 1) + ":";
    _time += ((ltm->tm_sec + 1 < 10) ? "0" : "") + to_string(ltm->tm_sec + 1) + " ";
    _time += to_string(ltm->tm_year + 1900);
    //time end qwq
    json newPost = {
        {"authorID", getCurrentAccount()},
        {"boardID", getCurrentBoard()},
        {"content", _content},
        {"id", id},
        {"pushes", {}},
        {"time", _time}, //ex "Wed May 26 23:44:32 2021"
        {"title", _title}};

    newPost["pushes"] = json::parse("[]");
    postsJson["Posts"].push_back(newPost);

    boardJson["Boards"][getCurrentBoard()]["members"].push_back({{"id", id}, {"type", "post"}});

    std::fstream Pofs("Posts.json", ios::out);
    Pofs << postsJson << endl;
    Pofs.close();
    std::fstream ofs("Boards.json", ios::out);
    ofs << boardJson << endl;
    ofs.close();
}
BoardManager::BoardState BoardManager::getState()
{
    return state;
};
void BoardManager::setState(BoardState _state)
{
    state = _state;
};

int BoardManager::getCurrentUser()
{
    return currentUser;
};
void BoardManager::setCurrentUser(int _currentUser)
{
    currentUser = _currentUser;
};

void BoardManager::setCurrentPage(int _currentPage)
{
    currentPage = _currentPage;
};
int BoardManager::getCurrentPage()
{
    return currentPage;
};

void BoardManager::setCurrentRow(int _currentRow)
{
    currentRow = _currentRow;
};
int BoardManager::getCurrentRow()
{
    return currentRow;
};
void BoardManager::setCurrentBoard(int _currentBoard)
{
    currentBoard = _currentBoard;
};
int BoardManager::getCurrentBoard()
{
    return currentBoard;
};
void BoardManager::setCurrentPost(int _currentPost)
{
    currentPost = _currentPost;
};
int BoardManager::getCurrentPost()
{
    return currentPost;
};
void BoardManager::setLastBoardPushBack(int _lastBoard)
{
    lastBoard.push_back(_lastBoard);
};
void BoardManager::setLastBoardPopBack()
{
    lastBoard.pop_back();
};
int BoardManager::getLastBoard()
{
    return lastBoard[lastBoard.size() - 1];
};
string BoardManager::getCurrentAccount()
{
    return account;
}