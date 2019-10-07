/*最长公共子序列（LCS Longest-Common-Subsequence Problem）
 *动态规划
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#define mod 100000000
using namespace std;
int main(){
    string x,y;
    getline(cin,x);
    getline(cin,y);
    int m=x.length()-1;
    int n=y.length()-1;
    x=' '+x;
    y=' '+y;
    int dp[2][5005],sum[2][5005];
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
}