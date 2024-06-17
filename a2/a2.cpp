#include<stdio.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <unistd.h>


using namespace std;

char *randstr(char *str)
{
	srand(clock());//自动化脚本执行得快，书本上的方法不好使
	int i,len;
	len = rand()%10+2;
	for (i = 0; i < len; ++i)
	{
		switch ((rand() % 3))
		{
		case 1:
			str[i] = 'A' + rand() % 26;
			break;
		case 2:
			str[i] = 'a' + rand() % 26;
			break;
		default:
			str[i] = '0' + rand() % 10;
			break;
		}
	}
	str[i] = '\0';
	return str;
}

int main(){
    char name[20],inputstr[20];
    int i=0,error = 0,gailv,j=5;
    while(j!=0){
        cout << randstr(name)<< endl;
        cin>>inputstr;
        while(name[i]!='\0'){
            if(name[i]!= inputstr[i]){
                error++;
            }
            i++;
        }
        if(error == 0){
            cout<<"输入正确，正确率：100%\n"<<endl;
        }else{
            gailv = (1-error/(float)strlen(name))*100;
            printf("输入错误，正确率：");
            cout<<gailv;
            printf("%%\n");
        }
        j--;
        error=0;
        i=0;
        //usleep(1);
    }

    return 0;
}
