#include "BoardManager.h"
#include <iostream>
#include <conio.h>
#include <iomanip>

BoardManager *boardManager;

int main()
{
    system("chcp 65001");
    setlocale(LC_ALL,"zh-CN");
    system("CLS");
    //cin>>input;
    //cout<<input<<" "<<input.length();
    //system("pause");
    // unsigned char input;
    // while (1)
    // {
    //     if (_kbhit())
    //     {
    //         input = _getch();
    //         printf("%d\n", input);
    //     }
    // }
    boardManager = new BoardManager();
    boardManager->setState(boardManager->BoardState::MENU);
    boardManager->Start();
    printf("AAA\n");
    system("pause");
}