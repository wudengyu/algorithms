/*最长公共子序列（LCS Longest-Common-Subsequence Problem）
 *动态规划
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#define mod 100000000
using namespace std;
char x[400000005],y[400000005];
int *dp[2],*sum[2];
int main(){
    while(scanf("%s%s",x+1,y+1)!=EOF){
        int m=strlen(x+1)-1;
        int n=strlen(y+1)-1;
        for(int i=1;i<=m;i++)
            if(x[i]>='a'&&x[i]<='z')
                x[i]-=32;
        for(int i=1;i<=n;i++)
            if(y[i]>='a'&&y[i]<='z')
                y[i]-=32;
        for(int i=0;i<2;i++){
            dp[i]=new int[n+1];
            sum[i]=new int[n+1];
            for(int j=0;j<=n;j++){
                dp[i][j]=0;
                sum[i][j]=0;
            }
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
            }
        }
        cout<<dp[m&1][n]<<endl;
        cout<<sum[m&1][n]<<endl;
        for(int i=0;i<2;i++){
            delete[] dp[i];
            delete[] sum[i];
        }
    }
}