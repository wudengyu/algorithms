#include<iostream>
#include<cstring>
using namespace std;
unsigned dp[31][31],root[31][31];
void preorder(int left,int right){
    if(left>right)
        return;
    cout<<root[left][right]<<" ";
    preorder(left,root[left][right]-1);
    preorder(root[left][right]+1,right);
}
int main(){
    int n;
    cin>>n;
    memset(dp,0,sizeof(dp));
    memset(root,0,sizeof(root));
    for(int i=1;i<=n;i++){
        cin>>dp[i][i];
        root[i][i]=i;
        dp[i+1][i]=1;
    }
    dp[1][0]=1;
    for(int step=1;step<n;step++){//初始时已知的只是DP[][]的对角线，只能逐步向右填充
        for(int i=1;i<=n-step;i++){
            for(int j=i+step,k=i;k<=j;k++){
                if(dp[i][j]<dp[i][k-1]*dp[k+1][j]+dp[k][k]){
                    dp[i][j]=dp[i][k-1]*dp[k+1][j]+dp[k][k];
                    root[i][j]=k;
                }
            }
        }
    }
    cout<<dp[1][n]<<endl;
    preorder(1,n);
    cout<<endl;
}