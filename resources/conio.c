// conio.c
#include "conio.h"
#include <stdio.h>

char getch()
{
    char c;
    #ifndef AUTO_TEST
    system("stty -echo");   // 不回显
    system("stty -icanon"); // 设置一次性读完操作，如使用getchar()读操作，不需要按enter
    #endif
    c = getchar();
    #ifndef AUTO_TEST
    system("stty icanon"); // 取消上面的设置
    system("stty echo");   // 回显
    #endif
    return c;
}

char getche()
{
    char c;
    system("stty -icanon");
    c = getchar();
    system("stty icanon");
    return c;
}
