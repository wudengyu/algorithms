#include<iostream>
#include<cstring>
using namespace std;
int t[101],c[101];
long long dp[101][1001];
int main(){
    int tn,mn;
    memset(dp,0,sizeof(dp));
    cin>>tn>>mn;
    for(int i=1;i<=mn;i++)
        cin>>t[i]>>c[i];
    for(int i=1;i<=mn;i++)
        for(int j=1;j<=tn;j++){
            if(j<t[i])
                dp[i][j]=dp[i-1][j];
            else
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-t[i]]+c[i]);
        }
    cout<<dp[mn][tn]<<endl;
}
