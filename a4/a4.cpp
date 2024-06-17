#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
int main(){
    string M;
    int K;
    cout<<"请输入明文M和密钥K："<<endl;
    cin>>M;
    cin>>K;
    char C[100];
    strcpy(C,M.c_str());
    for(unsigned int i=0;i<M.length();i++){
        C[i] =  C[i]+K;
    }
    cout<<"加密后的密文是："<<endl;
    cout<<C<<endl;
    return 0;
}
