#include<iostream>
#include<string>
#include<cstring>
using namespace std;
bool palindrome(const string &s){
    for(int i=0;i<s.length()/2;i++){
        if(s.at(i)!=s.at(s.length()-i-1)){
            return false;
        }
    }
    return true;
}
void reverse_add(int radix,string &s){
    int temp[200];
    for(int i=0;i<200;i++){
        temp[i]=0;
    }
    string::const_iterator p;
    string::const_reverse_iterator q;
    int pos=0;
    for(p=s.cbegin(),q=s.crbegin();p!=s.cend();p++,q++,pos++){
        int x,y,carry=pos;
        if(*p>='0'&&*p<='9')
            x=*p-'0';
        if(*p>='A'&&*p<='F')
            x=*p-'A'+10;
        if(*p>='a'&&*p<='f')
            x=*p-'a'+10;
        if(*q>='0'&&*q<='9')
            y=*q-'0';
        if(*q>='A'&&*q<='F')
            y=*q-'A'+10;
        if(*q>='a'&&*q<='f')
            y=*q-'a'+10;
        temp[pos]+=x+y;
        while(temp[carry]>=radix){
            temp[carry]-=radix;
            carry++;
            temp[carry]+=1;
        }
    }
    s.clear();
    pos++;
    while(temp[pos]==0)pos--;
    for(int i=pos;i>=0;i--)
        s.push_back(temp[i]>9?temp[i]-10+'A':temp[i]+'0');
}
int main(){
    int n,step=0;
    string m;
    cin>>n>>m;
    while((!palindrome(m))&&step<=30){
        step++;
        reverse_add(n,m);
    }
    if(step<=30)
        cout<<"STEP="<<step<<endl;
    else
        cout<<"Impossible!"<<endl;
}