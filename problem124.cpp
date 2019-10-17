//DP大作战—状态压缩dp
#include <iostream>
#include <cstring>
using namespace std;
const int MAX_STATUS=1<<10;
struct{
    short status;
    short count;
}row[MAX_STATUS];//用于记录有效的行
int dp[102][60][60];//dp[i][j][k]表示当前行i，上一行第j个状态，上上一行第k个状态的解，10位宽最多有60种状态。
int main(){
    int n,m;
    while(!(cin>>n>>m).eof()){
        memset(dp,0,sizeof(dp));
        int row_status_count=0;//有效状态行的数量
        for(int i=0;i<1<<m;i++){
            if(!((i<<1)&i||(i<<2)&i)){
                row[row_status_count].status=i;
                for(int j=1;j<=row[row_status_count].status;j<<=1)
                    if(row[row_status_count].status&j)
                        row[row_status_count].count++;
                row_status_count++;
            }
        }
        for(int i=2;i<n+2;i++){
            int jie=-1;
            for(int j=0;j<row_status_count;j++){
                for(int k=0;k<row_status_count;k++){
                    if(dp[i-1])

                }
            }
        }



    }
}
