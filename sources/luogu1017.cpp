#include<iostream>
using namespace std;
int main(){
    int n,r;
    int s[100],p=0;
    cin>>n>>r;
    cout<<n<<"=";
    while(n){
        s[p]=n%r;
        n/=r;
        if(s[p]<0){
            s[p]-=r;
            n+=1;
        }
        p++;
    }
    while(--p>=0){
        if(s[p]>=10){
            cout<<(char)(s[p]-10+'A');
        }else
            cout<<(char)(s[p]+'0');
    }
    cout<<"(base"<<r<<")"<<endl;
}