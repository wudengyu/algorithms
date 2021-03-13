#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int r,a[1001][1001],dp[1001][1001];
    int ans=0;
    memset(dp,0,sizeof(dp));
    cin>>r;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=i;j++){
            cin>>a[i][j];
            dp[i][j]=max(dp[i-1][j-1]+a[i][j],dp[i-1][j]+a[i][j]);
        }
    }
    for(int i=1;i<=r;i++){
        if(dp[r][i]>ans)
            ans=dp[r][i];
    }
    cout<<ans<<endl;
}