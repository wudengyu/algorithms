#include<iostream>
using namespace std;
int main(){
    int n,k,pos,sum=1;
    int s[7];
    cin>>n>>k;
    for(int i=1;i<k;i++)
        s[i]=1;
    s[0]=200;
    s[k]=n-k+1;
    pos=k;
    while(pos){
        if(s[pos]>s[pos-1]){
            do{
                s[pos--]--;
                s[pos]++;
            }while(s[pos]>s[pos+1]);
            sum++;
            pos=k;
            for(int i=0;i<=k;i++)
                cout<<s[i]<<" ";
            cout<<endl;
        }else
            pos--;
    }
    cout<<sum<<endl;
}