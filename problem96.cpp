/*最长公共子序列（LCS Longest-Common-Subsequence Problem）
 *动态规划
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#define mod 100000000
using namespace std;
const int N=10000005;
char x[N],y[N];
int dp[2][N],sum[2][N];
int main(){
    while(scanf("%s%s",x+1,y+1)!=EOF){
        int m=strlen(x+1)-1;
        int n=strlen(y+1)-1;
        for(int i=0;i<=n;i++){
            dp[0][i]=0;
            dp[1][i]=0;
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
            }
        }
        cout<<dp[m&1][n]<<endl;
        cout<<sum[m&1][n]<<endl;
    }
}