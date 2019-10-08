#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
using namespace std;
int main(){
    cout<<"Hello World!"<<endl;
    string a;
    char b[100000];
    while(!getline(cin,a).eof()){
        //a=' '+a;
        a.copy(b+1,a.length(),0);
        b[a.length()+1]='\0';
        cout<<"string length:"<<a.length()<<endl;
        cout<<"char[] length:"<<strlen(b)<<endl;
        for(int i=0;i<=a.length();i++)
            if(a[i]!=b[i])
                cout<<a[i];
    }
}