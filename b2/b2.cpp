#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#include "macro.h"
inline void SYSTEM_CLS()
{
    IFDEF(_WIN64, system("cls"));
    IFDEF(__linux__
              IFDEF(AUTO_TEST, printf("\n===== clear ======\n"));
          IFNDEF(AUTO_TEST, system("clear"));)
}

#define amount 20

using namespace std;
struct s1{
    char aera1[5];
    char calling[10];
    char aera2[5];
    char called[10];
    int time;
};

struct s2{
    char aera[5];
    double rate;
};

struct s3{
    char num[10];
    char name[10];
};

struct s4{
    char calling[10];
    char type[10];
    double money;
};

void readfile(struct s1 *list1,struct s2 *list2,struct s3 *list3){
    int i;
    FILE *fp;
    fp = fopen("hd.dat","r");
    for(i=0;i<amount;i++){
        fscanf(fp,"%s   %s  %s  %s  %d",list1[i].aera1,list1[i].calling,list1[i].aera2,list1[i].called,&list1[i].time);
    }
    fclose(fp);

    fp = fopen("fl.dat","r");
    for(i=0;i<4;i++){
        fscanf(fp,"%s%lf",list2[i].aera,&list2[i].rate);
    }
    fclose(fp);

    fp = fopen("yh.dat","r");
    for(i=0;i<5;i++){
        fscanf(fp,"%s%s",list3[i].num,list3[i].name);
    }
    fclose(fp);
}

void savefile(struct s4 *list4){
    int i;
    FILE *fp;
    fp = fopen("fy.dat","w");
    fprintf(fp,"%s\n","主叫电话号码   通话类型    话费余额（元）");
    for(i=0;i<amount;i++){
        fprintf(fp,"%10s    %10s    %6.2lf\n",list4[i].calling,list4[i].type,list4[i].money);
    }
    fclose(fp);
    printf("    \n\n【信息已输出至费用文件fy.dat，请查看！按任意键返回！】\n");
    getch();
    #ifdef __linux__
    getch();
#endif // DEBUG
}

void calculate(struct s1 *list1,struct s2 *list2,struct s4 *list4){
    int i;
    int flag = 1;
    double sum = 0;
    double bill;
    int j;
    int k;
    double rate;
    for(i=0;i<amount;i++){
        flag = strcmp(list1[i].aera1,list1[i].aera2);   //全部相等 flag 为0；
        if(flag == 0){
            strcpy(list4[i].type,"本地通话");
            strcpy(list4[i].calling,list1[i].calling);
            if(list1[i].time<180)
                bill = 0.3;
            else{
                k = list1[i].time-180;
                if(k%60 == 0)
                    bill = 0.3+(k/60)*0.2;
                else
                    bill = 0.3+(k/60+1)*0.2;
            }
            list4[i].money = bill;
            sum = sum+bill;
        }
        else{       //flag不为0时为长途话费
            strcpy(list4[i].type,"长途话费");
            strcpy(list4[i].calling,list1[i].calling);
            for(j=0;j<4;j++){
                if(strcmp(list1[i].aera2,list2[j].aera)==0){
                    rate = list2[j].rate;
                }
            }
            if(list1[i].time%60==0){
                k = list1[i].time-180;
                bill = rate*(list1[i].time/60);
            }else{
                k = list1[i].time-180;
                bill = rate*(list1[i].time/60+1);
            }
            list4[i].money = bill;
            sum = sum+bill;
        }
    }
    printf("    主叫电话    通话类型    通话费用\n");
    for(i=0;i<amount;i++){
        printf("    %s      %s      %5.2lf\n",list4[i].calling,list4[i].type,list4[i].money);
    }
    printf("    话费总额为：%.2lf\n\n",sum);
    printf("    按任意键继续：");
    getch();
}

void searchmoney(struct s3 *list3,struct s4 *list4){    //查询话费
    char ch[10];
    double sum1 = 0;
    double sum2 = 0;
    double sum = 0;
    int i,j,flag,flag1,flag2=1;
    do{
        flag2 = 1;
        printf("    请输入电话号码：");
        scanf("%s",ch);
        for(i=0;i<5;i++){   //从用户信息中根据电话号码查询用户名
            flag = strcmp(ch,list3[i].num);
            if(flag==0){
                flag2 = 0;
                break;
            }
        }
        if(flag2==1){
            printf("    您输入的电话号码不存在，请重新输入！\n");
        }
    }while(flag2);
    for(j=0;j<amount;j++){
        flag = strcmp(ch,list4[j].calling);
        if(flag==0){
            flag1 = strcmp(list4[j].type,"本地通话");
            if(flag1==0)
                sum1 = sum1+list4[j].money;
            else
                sum2 = sum2+list4[j].money;
        }
    }
    sum = sum1+sum2;
    printf("    用户名     主叫电话号码  本地通话费用  长途通话费用  总费用\n");
    printf("    %s          %s        %4.2lf        %4.2lf          %4.2lf\n",list3[i].name,ch,sum1,sum2,sum);
    printf("\n按任意键返回！");
    getch();
    #ifdef __linux__
    getch();
#endif // DEBUG
}

void searchbill(struct s1 *list1,struct s3 *list3,struct s4 *list4){    //话费账单查询
    char ch[10];
    char user[10];
    int i,flag2,flag,sum1=0,sum2=0,sum=0;

    do{
        flag2 = 1;
        printf("    请输入电话号码：");
        scanf("%s",ch);
        for(i=0;i<5;i++){
            flag = strcmp(ch,list3[i].num);
            if(flag==0){
                flag2 = 0;
                break;
            }
        }
        if(flag2==1){
            printf("    您输入的号码不存在，请重新输入！\n");
        }
    }while(flag2);
    strcpy(user,list3[i].name);
    printf("    用户名 主叫号码    被叫号码    通话时长\n");
    for(i=0;i<amount;i++){
        if(!(strcmp(ch,list4[i].calling))){
            printf("    %s   %s  %s %5d\n",user,list4[i].calling,list1[i].called,list1[i].time);
            if(!(strcmp(list1[i].aera1,list1[i].aera2)))
                sum1 = sum1+list1[i].time;
            else
                sum2 = sum2+list1[i].time;
        }
    }
    sum = sum1+sum2;
    printf("    您的总通话时长为%d秒，其中本地通话时长为%d秒，长途通话时长为%d秒\n",sum,sum1,sum2);
    printf("    按任意键返回！");
    getch();
    #ifdef __linux__
    getch();
#endif // DEBUG
}

void menu(){
    printf("**************电信计费系统*****************\n\n");
    printf(">>>>>>>>>>>   1、读取话费文件  <<<<<<<<<<<<\n");
    printf(">>>>>>>>>>>   2、查询通用话费  <<<<<<<<<<<<\n");
    printf(">>>>>>>>>>>   3、话费查询       <<<<<<<<<<<<\n");
    printf(">>>>>>>>>>>   4、话费账单查询   <<<<<<<<<<<<\n");
    printf(">>>>>>>>>>>   5、输出至文件   <<<<<<<<<<<<\n");
    printf(">>>>>>>>>>>  0、退出系统      <<<<<<<<<<<<\n");
    printf("********************************************\n");
}

void menu1(){
    printf("****************读取话费文件*****************\n\n");
    printf(">>>>>>>>>>>   1、显示源数据文件  <<<<<<<<<<<<\n");
    printf(">>>>>>>>>>>   2、显示长话费率文件 <<<<<<<<<<<<\n");
    printf(">>>>>>>>>>>   3、显示用户信息文件<<<<<<<<<<<<\n");
    printf(">>>>>>>>>>>   0、返回主菜单       <<<<<<<<<<<<\n");
    printf("************************************************\n");
}

void output1(struct s1 *list1){
    printf("主叫区号    主叫电话号码  被叫区号    被叫电话号码  通话时长\n");
    int i;
    for(i=0;i<amount;i++){
        printf("    %s      %s    %5s         %s  %6d\n",list1[i].aera1,list1[i].calling,list1[i].aera2,list1[i].called,list1[i].time);
    }
}

void output2(struct s2 *list2){
    int i;
    printf("    区号  费率\n");
    for(i=0;i<4;i++){
        printf("    %4s     %.2lf\n",list2[i].aera,list2[i].rate);
    }
}

void output3(struct s3 *list3){
    int i;
    printf("    电话号码  用户姓名\n");
    for(i=0;i<4;i++){
        printf("    %s   %8s\n",list3[i].num,list3[i].name);
    }
}

int main(){
    int choice,choice2;
    struct s1 list1[20];
    struct s2 list2[5];
    struct s3 list3[5];
    struct s4 list4[20];
    while(1){
        SYSTEM_CLS();
        menu();
        printf("请选择：");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            readfile(list1,list2,list3);
            do{
                menu1();
                printf("请选择要查询的文件：");
                scanf("%d",&choice2);
                if(choice2==1){
                    printf("\n");
                    output1(list1);
                }else if(choice2==2){
                    printf("\n");
                    output2(list2);
                }else if(choice2==3){
                    printf("\n");
                    output3(list3);
                }else if(choice2==0)
                    break;
                else
                    printf("\n您的输入有误，请重新输入！\n");
            }while(choice2);
            break;
        case 2:
            calculate(list1,list2,list4);
            getch();
            break;
        case 3:
            searchmoney(list3,list4);
            break;
        case 4:
            searchbill(list1,list3,list4);
            break;
        case 5:
            savefile(list4);
            break;
        case 0:
            SYSTEM_CLS();
            printf("*************谢谢使用！****************\n");
            getch();
            return 0;
            break;
        default:
            printf("您的输入有误，请重新输入！\n");
            getch();
        }
    }
    return 0;
}
