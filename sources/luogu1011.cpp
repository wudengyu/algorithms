#include<iostream>
using namespace std;
int main(){
    int a,n,m,x;
    cin>>a>>n>>m>>x;
    int s[n]={0,a};
    int train[n]={0,a,a};
    int no=1;
    int step[2];
    do{
        s[2]=no;
        for(int i=3;i<n;i++){
            s[i]=s[i-1]+s[i-2];
            train[i]=train[i-1]+s[i-2];
        }
        if(no==1||no==2){
            step[no-1]=train[n-1];
            no++;
        }else if(no==3){
            no+=(m-train[n-1])/(step[1]-step[0]);
        }else
            no++;
    }while(train[n-1]!=m);
    cout<<train[x]<<endl;
}