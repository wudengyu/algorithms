#include<iostream>
#include<cstring>
using namespace std;
int n,k,sum=0;
int dp[201][7];
void dfs(int s[],int pos,int total){
    for(int i=s[pos-1];i<=n-k+1;i++){
        int temp=total;
        s[pos]=i;
        temp+=i;
        if(temp>n)
            break;
        if(pos<k){//没有到底，递归
            dfs(s,pos+1,temp);
        }else{
            if(temp==n){
                sum+=1;
                break;
            }
        }
    }
}
int main(){
    int s[7];
    cin>>n>>k;
    s[0]=1;
    /*
    dfs(s,1,0);
    cout<<sum<<endl;
    */
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=k&&j<=i;j++)
            dp[i][j]=dp[i-j][j]+dp[i-1][j-1];
    cout<<dp[n][k]<<endl;
}