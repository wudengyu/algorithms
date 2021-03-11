#include<iostream>
#include<queue>
using namespace std;
int main(){
    int n,dp[1001];
    cin>>n;
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<=i/2;j++)
            dp[i]+=dp[j];
    }
    cout<<dp[n]<<endl;
}