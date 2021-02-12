#include<iostream>
#include<cstring>
using namespace std;
const int N=10;
int main(){
    int matrix[N][N];
    int dp[N][N][N][N];
    memset(matrix,0,sizeof(int)*N*N);
    memset(dp,0,sizeof(int)*N*N*N*N);
    int n,x,y,z;
    cin>>n;
    while(1){
        cin>>x>>y>>z;
        if(x==0&&y==0&&z==0)
            break;
        matrix[x][y]=z;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
                for(int l=1;l<=n;l++){
                    dp[i][j][k][l]=max(max(dp[i-1][j][k-1][l],dp[i][j-1][k][l-1]),max(dp[i-1][j][k][l-1],dp[i][j-1][k-1][l]))+matrix[i][j]+matrix[k][l];
                    if(i==k&&j==l)
                        dp[i][j][k][l]-=matrix[i][j];
                }
    }
    cout<<dp[n][n][n][n]<<endl;
}