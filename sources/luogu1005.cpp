#include<iostream>
using namespace std;
const int N=80;
void printint128(__uint128_t x){
    if(x==0) return;
    printint128(x/10);
    putchar(x%10+'0');
}
int main(){
    int n,m;
    int matrix[N][N];
    int dp[N][N];
    /*dp[i][j]表示每行还剩i到j时，能够取到的最大结果；那么：
     *对于第n行数，要求dp[1][m]需要考虑从前面取得到的结果dp[2][m]+matrix[n][1]*2大还是dp[1][m-1]+matrix[n][m]*2大；
     *同样，要求dp[2][m]和dp[1][m-1]需要先求dp[3][m]、dp[2][m-1]、dp[1][m-2]；
     *继续往前推，要先求出dp[4][m]、dp[3][m-1]、dp[2][m-2]、dp[1][m-3]；
     *显然，这里的行号不能大于列号，dp是一个m行m列的三角矩阵，dp[m][m]表示最后只剩第m个数，只有有一种取法，dp[m-1][m-1]表示最后取的是第m-1个数；
     *所以，可以先把矩阵对角线dp[1][1]、dp[2][2]、……、dp[m][m]初始化好，然后：dp[1][1]->dp[1][2]
     *如果是从前取，即上一步取之后是dp[i-1][j]，结果应该是dp[i-1][j]+2^(第几步)*matrix[i-1][j]，
     *如果是从后取，即上一步取之后是dp[i][j+1]，结果应该是dp[i][j+1]+2^(第几步)*matrix[i][j+1]。
     *当然，取大者。
     *显然，是行是从上到下，列是从右到左递推的。
     *
    __uint128_t ans=0;
    __uint128_t base[N]={1};
    cin>>n>>m;
    for (int i=1;i<=m;i++)
        base[i]=base[i-1]<<1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>matrix[i][j];
        }
    }
    for(int i=0;i<n;i++){

    }
    for(int j=0;j<m;j++){
        int sum=0;
        base++;
        for(int i=0;i<n;i++){
            if(matrix[i][point[i][0]]<=matrix[i][point[i][1]]){
                sum+=matrix[i][point[i][0]];
                point[i][0]++;
            }else{
                sum+=matrix[i][point[i][1]];
                point[i][1]--;
            }
        }
        ans+=(sum<<base);
    }
    printint128(ans);
}