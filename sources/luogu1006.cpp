#include<iostream>
#include<cstring>
using namespace std;
const int N=51;
int matrix[N][N];
unsigned long long dp[N][N][N][N];
int main(){
    memset(matrix,0,sizeof(int)*N*N);
    memset(dp,0,sizeof(unsigned long long)*N*N*N*N);
    int m,n;
    cin>>m>>n;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            cin>>matrix[i][j];
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            /*比较朴素的避免交叉的办法：两条路，一条行号大，一条列号大
             *简单起见，第一条路（外面的循环）任意，由于列坐标是第一条路的内循环，所以第一条路是列号大的，
             *那么，第二条路就是行号大的，所以k=i+1，但是l必须小于j，这样的话，终点是在dp[m-1][n][m][n-1]
            */
            for(int k=i+1;k<=m;k++)
                for(int l=1;l<j;l++)
                    dp[i][j][k][l]=max(max(dp[i-1][j][k-1][l],dp[i-1][j][k][l-1]),max(dp[i][j-1][k-1][l],dp[i][j-1][k][l-1]))+matrix[i][j]+matrix[k][l];
            /*下面这段是与P1004方格取数一样的代码，也能过，原因是两点重合时减去了一个值，就不可能两条路径都还会都要走这个点。
            for(int k=1;k<=m;k++)
                for(int l=1;l<=n;l++){
                    dp[i][j][k][l]=max(max(dp[i-1][j][k-1][l],dp[i-1][j][k][l-1]),max(dp[i][j-1][k-1][l],dp[i][j-1][k][l-1]))+matrix[i][j]+matrix[k][l];
                    if(i==k&&j==l)
                        dp[i][j][k][l]-=matrix[i][j];
                }
            */
    cout<<dp[m-1][n][m][n-1]<<endl;
}