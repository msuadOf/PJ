// conio.c
#include "conio.h"
#include <stdio.h>

char getch()
{
    char c;
    system("stty -echo");   // 不回显
    system("stty -icanon"); // 设置一次性读完操作，如使用getchar()读操作，不需要按enter
    c = getchar();
    system("stty icanon"); // 取消上面的设置
    system("stty echo");   // 回显
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
