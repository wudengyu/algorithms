#include<iostream>
#include<cstring>
using namespace std;
const int N=80;
void printint128(__int128_t x){
    if(x==0) return;
    printint128(x/10);
    putchar(x%10+'0');
}
int main(){
    int n,m;
    int matrix[N][N+1];
    __int128_t dp[N+1][N+1];
    /*dp[i][j]表示每行还剩i到j时，能够取到的最大结果；那么：
     *对于第n行数，第一次如果从前面取，结果是dp[2][m]+matrix[n][1]*2，从后面取是dp[1][m-1]+matrix[n][m]*2；
     *同样，要求dp[2][m]和dp[1][m-1]需要先求dp[3][m]、dp[2][m-1]、dp[1][m-2]；
     *继续往前推，要先求出dp[4][m]、dp[3][m-1]、dp[2][m-2]、dp[1][m-3]；
     *显然，这里的行号不能大于列号，dp是一个m行m列的三角矩阵，dp[i][i]表示最后取第i个数；
     *所以，可以先把矩阵对角线dp[1][1]、dp[2][2]、……、dp[m][m]初始化好，然后：dp[1][1]、dp[2][2]->dp[1][2]，d[2][2]、dp[3][3]->dp[2][3]、……
     *就像杨辉三角，每个可以从其左、下得出，直至dp[1][m]，再进一步，对角线上的dp[1][1]、dp[2][2]也可以同样得出，只需矩阵多第0列和第m+1行，然后左下三角矩阵全为0
     *最后得到递推公式：dp[i][j]=max(dp[i+1][j]+base[l]*matrix[k][i],dp[i][j-1]+base[l]*matrix[k][j]);可以理解为：
     *base是2的次方，只跟第几次取有关，matrix的行号是原数据的行号，列号就是取出来的那个数。
     */
    __int128_t total=0;
    __int128_t base[N+1]={1};
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        base[i]=base[i-1]<<1;
    for(int i=0;i<n;i++){
        for(int j=1;j<=m;j++){
            cin>>matrix[i][j];
        }
    }
    for(int k=0;k<n;k++){//k是原数据矩阵的行号
        memset(dp,0,sizeof(__int128_t)*(N+1)*(N+1));
        for(int l=m;l>=1;l--){//开始DP，l是第几次取
            for(int i=1;i<=l;i++){//i，j是DP矩阵的坐标，自底向上计算DP的右上三角；
                int j=i+m-l;
                dp[i][j]=max(dp[i+1][j]+base[l]*matrix[k][i],dp[i][j-1]+base[l]*matrix[k][j]);
            }
        }
        total+=dp[1][m];
    }
    if(total==0)
        cout<<0<<endl;
    else{ 
        printint128(total);
        cout<<endl;
    }
    
}