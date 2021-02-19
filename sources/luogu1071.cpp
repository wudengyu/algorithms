#include<iostream>
#include<map>
using namespace std;
int main(){
    char secret[101],plain[101],question[101];
    int i;
    map<char,char> dict;
    for(int i=0;i<101;i++){
        secret[i]='\0';
        plain[i]='\0';
        question[i]='\0';
    }
    cin>>secret>>plain>>question;
    i=0;
    while(secret[i]!='\0'){
        if(dict.find(secret[i])==dict.end())
            dict[secret[i]]=plain[i];
        else if(dict[secret[i]]!=plain[i]){
            cout<<"Failed"<<endl;
            return 0;
        }
        i++;
    }
    if(dict.size()!=26){
        cout<<"Failed"<<endl;
        return 0;
    }
    i=0;
    while(question[i]!='\0'){
        cout<<dict[question[i++]];
    }
    cout<<endl;
}