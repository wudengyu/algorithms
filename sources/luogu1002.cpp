#include<iostream>
using namespace std;
bool horse(int hx,int hy,int x,int y){
    return (abs(hx-x)==2&&abs(hy-y)==1)||(abs(hx-x)==1&&abs(hy-y)==2)||(hx==x&&hy==y);
}
int main(){
    int bx,by,hx,hy;
    unsigned long long dp[21];
    for(int i=0;i<21;i++)
        dp[i]=0;
    cin>>bx>>by>>hx>>hy;
    for(int i=bx;i>=0;i--){
        if(i==bx)
            dp[by]=1;
        else
            dp[by]=dp[by]==0?0:1;
        for(int j=by;j>=0;j--){
            if(horse(hx,hy,i,j))
                dp[j]=0;
            else
                dp[j]+=dp[j+1];

        }
    }
    cout<<dp[0]<<endl;
}