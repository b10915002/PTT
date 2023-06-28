#include "Keys.h"

Keys getInput()
{
    unsigned char ch = _getch();
    if (ch == '\b')
    {
        return KEY_B;
    }else if (ch == 224)
    {
        ch = _getch();

        switch (ch)
        {
        case 72:
            return KEY_UP;
        case 80:
            return KEY_DOWN;
        case 75:
            return KEY_LEFT;
        case 77:
            return KEY_RIGHT;
        default:
            return KEY_UP;
        }
    }
    else
    {
        if (ch >= 65 && ch <= 90) //A~Z
        {
            ch += 32;
        }
        switch (ch)
        {
        case 'p':
            return KEY_P;
        case 'd':
            return KEY_D;
        case 'e':
            return KEY_E;
        case 'n':
            return KEY_N;
        case '1':
            return KEY_1;
        case '2':
            return KEY_2;
        case '3':
            return KEY_3;
        default:
            break;
        }
    }
}