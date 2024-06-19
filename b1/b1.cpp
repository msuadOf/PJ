#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "macro.h"
inline void SYSTEM_CLS()
{
    IFDEF(_WIN64, system("cls"));
    IFDEF(__linux__
              IFDEF(AUTO_TEST, printf("\n===== clear ======\n"));
              IFNDEF(AUTO_TEST, system("clear"));
          );
}

using namespace std;

struct stu
{
    char code[10];
    float s1, s2, s3;
    float score;
    char grade;
} temp;

void set_choice(char *choice)
{
    printf(">>>>>>>>>     1、从文件读取数据        <<<<<<<\n");
    printf(">>>>>>>>>     2、计算并显示成绩         <<<<<<<\n");
    printf(">>>>>>>>>     3、按等级查询              <<<<<<<\n");
    printf(">>>>>>>>>     4、按总评成绩排序         <<<<<<<\n");
    printf(">>>>>>>>>     5、按学号查询             <<<<<<<\n");
    printf(">>>>>>>>>     6、查询所有等级           <<<<<<<\n");
    printf(">>>>>>>>>     7、保存到文件            <<<<<<<\n");
    printf(">>>>>>>>>     0、退出系统               <<<<<<<\n");
    printf("请选择您所需要操作的功能（输入数字）：");
    *choice = getchar();
    while (getchar() != '\n')
        ;
}

void dispinfo()
{
    SYSTEM_CLS();
    // printf("\n\n");
    printf("*****************学生成绩核算系统*****************\n");
}

int readfile(struct stu *list)
{
    dispinfo();
    int n;
    int i = 0;
    FILE *fp;
    fp = fopen("note.dat", "r");
    fscanf(fp, "%d", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%s%f%f%f\n", list[i].code, &list[i].s1, &list[i].s2, &list[i].s3);
    }
    printf("\t学号\t\t平时成绩 期中成绩 期末成绩\n");
    for (i = 0; i < n; i++)
    {
        printf("\t%s\t%5.1lf\t%5.1lf\t%5.1lf\n", list[i].code, list[i].s1, list[i].s2, list[i].s3);
    }
    printf("***********读取文件成功!按任意键继续！**************\n");
    // scanf("%d",i);
    getch();
    fclose(fp);
    return n;
}

void view(struct stu *list, int amount)
{
    int i = 0;
    float average = 0;
    printf("\t学号\t\t总评\t等级\n");
    for (i = 0; i < amount; i++)
    {
        average += list[i].score;
        printf("\t%10s\t%6.1f\t%c\n", list[i].code, list[i].score, list[i].grade);
    }
    average /= amount;
    printf("   本班总人数%d  本班平均成绩%.1f\n", amount, average);
    printf("\n******按任意键继续！********\n");
    getch();
}

void discharge(struct stu *list, int amount)
{
    dispinfo();
    float temp;
    char temp1;
    char temp2[10];
    int i, j;
    for (i = 0; i < amount; i++)
    { // 对分数排序
        for (j = 0; j < amount; j++)
        {
            if (list[j].score > list[i].score)
            { // 比较分数
                temp = list[j].score;
                list[j].score = list[i].score;
                list[i].score = temp;

                strcpy(temp2, list[j].code);
                strcpy(list[j].code, list[i].code);
                strcpy(list[i].code, temp2);

                temp = list[j].s1;
                list[j].s1 = list[i].s1;
                list[i].s1 = temp;

                temp = list[j].s2;
                list[j].s2 = list[i].s2;
                list[i].s2 = temp;

                temp = list[j].s3;
                list[j].s3 = list[i].s3;
                list[i].s3 = temp;

                temp1 = list[j].grade;
                list[j].grade = list[i].grade;
                list[i].grade = temp1;
            }
        }
    }
    view(list, amount);
}

void calculate(struct stu *list, int amount)
{
    int i = 0;
    for (i = 0; i < amount; i++)
    {
        list[i].score = list[i].s1 * 0.3 + list[i].s2 * 0.3 + list[i].s3 * 0.4;

        if (list[i].score >= 90)
            list[i].grade = 'A';
        else if (list[i].score >= 80)
            list[i].grade = 'B';
        else if (list[i].score >= 70)
            list[i].grade = 'C';
        else if (list[i].score >= 60)
            list[i].grade = 'D';
        else
            list[i].grade = 'E';
    }
    dispinfo();
    view(list, amount);
}

void findgrade(struct stu *list, int amount)
{
    int i = 0, j = 0;
    char g;
    dispinfo();
    printf("\n请选择您需要查询的等级（输入大写A/B/C/D/E）:\n");
    g = getch();
    printf("\t\t学号\t\t总评\t等级\n");
    for (i = 0; i < amount; i++)
    {
        if (list[i].grade == g)
        {
            j++;
            printf("\t\t%10s\t%6.1f\t%c\n", list[i].code, list[i].score, list[i].grade);
        }
    }
    printf("\n\n    等级为%c总共有%d人，总人数%d，占总人数的%.2lf\n", g, j, amount, (double)j / amount);
    printf("\n******按任意键继续！********\n");
    getch();
}

void gradelist(struct stu *list, int amount)
{
    dispinfo();
    int i = 0;
    printf("\t\t等级\t人数\t百分比\n");
    int j = 0;
    for (i = 0; i < amount; i++)
    {
        if (list[i].grade == 'A')
            j++;
    }
    printf("\t\tA\t%d\t%6.3lf\n", j, (double)j / amount);

    for (i = 0; i < amount; i++)
    {
        if (list[i].grade == 'B')
            j++;
    }
    printf("\t\tB\t%d\t%6.3lf\n", j, (double)j / amount);

    for (i = 0; i < amount; i++)
    {
        if (list[i].grade == 'C')
            j++;
    }
    printf("\t\tC\t%d\t%6.3lf\n", j, (double)j / amount);

    for (i = 0; i < amount; i++)
    {
        if (list[i].grade == 'D')
            j++;
    }
    printf("\t\tD\t%d\t%6.3lf\n", j, (double)j / amount);

    for (i = 0; i < amount; i++)
    {
        if (list[i].grade == 'E')
            j++;
    }
    printf("\t\tE\t%d\t%6.3lf\n", j, (double)j / amount);

    printf("\n******按任意键继续！********\n");
    getch();
}

void find(struct stu *list, int amount)
{
    int i = 0;
    int flag = 1;
    char temp[10];
    dispinfo();
    int flag2;
    do
    {
        flag2 = 1;
        printf("    请输入学号：");
        scanf("%s", temp);
        for (i = 0; i < amount; i++)
        {
            flag = strcmp(temp, list[i].code);
            if (flag == 0)
            {
                flag2 = 0;
                break;
            }
        }
        if (flag2 == 1)
        {
            printf("    您所输入的学号不存在，请重新输入!\n");
        }
    } while (flag2);

    printf("\t\t学号\t总评\t等级\n");
    printf("\t\t%10s\t%6.1f\t%6c\n", list[i].code, list[i].score, list[i].grade);
    printf("\n******按任意键继续！********\n");
    getch();
#ifdef __linux__
    getch();
#endif // DEBUG
}

void save(struct stu *list, int amount)
{
    int i = 0;
    FILE *fp;
    fp = fopen("out.dat", "w");
    printf( "\t%10s\t\t%7s\t\t%6s\n","学号","总评","等级");
    fprintf(fp, "\t%10s\t\t%7s\t\t%6s\n","学号","总评","等级");
    for (i = 0; i < amount; i++)
    {
        printf("\t%10s\t\t%6.1f\t\t%c\n", list[i].code, list[i].score, list[i].grade);
    }
    for (i = 0; i < amount; i++)
    {
        fprintf(fp,"\t%10s\t\t%6.1f\t\t%c\n", list[i].code, list[i].score, list[i].grade);
    }
    printf("\n\n****输出成功！请查看，按任意键继续*******\n");
    fclose(fp);
    getch();
}

int main()
{
    // system("colorF9");
    struct stu list[100];
    char choice;
    int amount;
    while (1)
    {
        dispinfo();
        set_choice(&choice);
        switch (choice)
        {
        case '1':
            amount = readfile(list);
            break;
        case '2':
            calculate(list, amount);
            break;
        case '3':
            findgrade(list, amount);
            break;
        case '4':
            discharge(list, amount);
            break;
        case '5':
            find(list, amount);
            break;
        case '6':
            gradelist(list, amount);
            break;
        case '7':
            save(list, amount);
            break;
        case '0':
            SYSTEM_CLS();
            printf("*******欢迎再次光临**********\n");
            getch();
            return 0; // 正确退出
            break;
        }
    }
    return 0;
}
