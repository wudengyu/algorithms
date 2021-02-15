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
    __int128_t dp[N+1];
    /*dp[i][j]表示每行还剩i到j时，能够取到的最大结果；那么：
     *对于第n行数，第一次如果从前面取，结果是dp[2][m]+matrix[n][1]*2，从后面取是dp[1][m-1]+matrix[n][m]*2；
     *同样，要求dp[2][m]和dp[1][m-1]需要先求dp[3][m]、dp[2][m-1]、dp[1][m-2]；……
     *最后得出递推公式：dp[i][j]=max(dp[i+1][j]+2^(m-j+i)*matrix[k][i],dp[i][j-1]+2^(m-j+i)*matrix[k][j])
     *这个公式可以理解为：当数列还剩下i,j时，从左边取得到一个结果，从右边取得到一个结果，根据题意取其中较大的；
     *动态规划的特点就是从最后结果往前推导，显然i>=j,当i=j时数列就只剩一个数了，取出来乘以2^m就行，dp的过程
     *其实就是先取最后一个，最后取第一个，既然如此，每次取出来都剩以2，那么最后一个取出的刚好就乘了m次；
     *另外，这其实是一个上三角矩阵，如果从下往上、从左向右计算，前一步的结果不会被后一步覆盖，所以可以降维；
     *状态转移方程可以简化为：dp[j]=2*max(dp[j]+martix[k][i],dp[j-1]+martix[k][j])；
     *（循环变量i依然存在，降维只是节约空间，并不能减少计算量）
     */
    __int128_t total=0;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=1;j<=m;j++){
            cin>>matrix[i][j];
        }
    }
    for(int k=0;k<n;k++){//k是原数据矩阵的行号
        memset(dp,0,sizeof(__int128_t)*(N+1));
        for(int i=m;i>=1;i--){//开始DP
            for(int j=i;j<=m;j++){//i，j是DP矩阵的坐标，自底向上，从左到右计算DP的右上三角；
                dp[j]=2*max(dp[j]+matrix[k][i],dp[j-1]+matrix[k][j]);
            }
        }
        total+=dp[m];
    }
    if(total==0)
        cout<<0<<endl;
    else{ 
        printint128(total);
        cout<<endl;
    }
    
}