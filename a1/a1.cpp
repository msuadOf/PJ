#include<stdio.h>
#include<string.h>
#include<iostream>

using namespace std;

void swap(char *p,char *q)
{
    char a[20];
    strcpy(a,p);
    strcpy(p,q);
    strcpy(q,a);
}

int main(){
    int score[5],i,j,score_temp;
    char name[5][10];
    cout<<"********学生成绩排序系统**********"<<endl;
    cout<<"请输入学生姓名成绩："<<endl;
    for(i=0;i<5;i++){
        cin>>name[i];
		cin>>score[i];
    }
    for(i=0;i<5;i++){
        for(j=i+1;j<5;j++){
            if(score[i]<score[j]){
                score_temp = score[i];
                score[i] = score[j];
                score[j] = score_temp;
                swap(name[i],name[j]);
            }
        }
    }
    printf("学生成绩排名如下：\n");
    for(i=0;i<5;i++){
        printf("%s %d\n",name[i],score[i]);
    }
    return 0;
}


/*
one 90
two 80
three 92
four 99
five 86
*/
//此处测试用例5个，可自行扩展
