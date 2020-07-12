#include <iostream>
#include <cstring>
#include <typeinfo>
#include <cstdio>
using namespace std;
int main(){
    cout<<"Hello World!"<<endl;
    string s;
    char buf[10010];
    cin>>s;
    cin.get();
    cout<<"String s is "<<s<<"lang is "<<s.size()<<endl;
    cin.getline(buf,10010,'\n');
    cout<<"Line is "<<buf<<"lang is "<<strlen(buf)<<endl;
    cin.getline(buf,10010,'\n');
    cout<<"Line is "<<buf<<"lang is "<<strlen(buf)<<endl;
}