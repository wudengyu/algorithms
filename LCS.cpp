/*最长公共子序列（LCS Longest-Common-Subsequence Problem）
 *动态规划
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#define mod 100000000
using namespace std;
int main(){
    char x[5005],y[5005];
    int *dp[2],*sum[2];
    int n,m;
    scanf("%s",x+1);
    scanf("%s",y+1);
    m=strlen(x+1)-1;
    n=strlen(y+1)-1;
    for(int i=0;i<2;i++){
        dp[i]=new int[n+1];
        sum[i]=new int[n+1];
    }
    for(int i=0;i<=n;i++){
        sum[0][i]=1;
    }
    sum[1][0]=1;
    for(int i=1;i<=m;i++){
        int curr=i&1;
        int prev=curr^1;
        for(int j=1;j<=n;j++){
            if (x[i]==y[j]){
                dp[curr][j]=dp[prev][j-1]+1;
                sum[curr][j]=sum[prev][j-1];
            }else{
                dp[curr][j]=max(dp[prev][j], dp[curr][j-1]);
                sum[curr][j]=0;
            }
            if(dp[curr][j]==dp[curr][j-1])
                sum[curr][j]=(sum[curr][j]+sum[curr][j-1])%mod;
            if(dp[curr][j]==dp[prev][j])
                sum[curr][j]=(sum[curr][j]+sum[prev][j])%mod;
            if(dp[curr][j]==dp[prev][j-1]){
                sum[curr][j]=(sum[curr][j]-sum[prev][j-1]+mod)%mod;
            }
            cout<<dp[curr][j]<<':'<<sum[curr][j]<<' ';
        }
        cout<<endl;
    }
    cout<<dp[m&1][n]<<endl;
    cout<<sum[m&1][n]<<endl;
    for(int i=0;i<2;i++){
        delete[] dp[i];
        delete[] sum[i];
    }
}