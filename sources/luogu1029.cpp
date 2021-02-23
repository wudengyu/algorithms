#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int x,y;
    int r,sum=0;
    cin>>x>>y;
    if(x%y!=0&&y%x!=0)
        cout<<0<<endl;
    else{
        r=x>y?x/y:y/x;
        for(int i=1;i<=r;i++)
            if(r%i==0&&__gcd(r/i,i)==1)
                sum++;
        cout<<sum<<endl;
    }
}