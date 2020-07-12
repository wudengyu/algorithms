/*零崎的补番计划Ⅱ
*这是一个01背包问题
*/
#include <iostream>
using namespace std;
int main(){
    int T,k;
    int v[301],t[301];
    int dp[20001];
    while(!(cin>>T>>k).eof()){
        int sum=0;
        for(int i=0;i<=T;i++)
            dp[i]=0;
        for(int i=1;i<=k;i++){
            cin>>v[i]>>t[i];
            sum+=t[i];
        }
        for(int i=1;i<=k;i++){
            int tp=max(T-sum,t[i]);
            for(int j=T;j>=tp;j--)
                dp[j]=max(dp[j],dp[j-t[i]]+v[i]);
            sum-=t[i];
        }
        cout<<dp[T]<<endl;
    }
}