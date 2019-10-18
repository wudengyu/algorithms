//DP大作战—状态压缩dp
#include <iostream>
#include <cstring>
using namespace std;
const int MAX_STATUS=1<<10;
struct{
    int status;
    int count;
}row[60];//用于记录有效的行，60是先调用一次solve_row算出来10位宽最多方案数。
int dp[102][60][60];//dp[i][j][k]表示当前行i，当前行状态编号，上一行状态编号对应的数量。
int solve_row(int wide){
    int scheme=0;
    for(int i=0;i<1<<wide;i++){
        if(!((i<<1)&i||(i<<2)&i)){
            row[scheme].status=i;
            for(int j=1;j<=row[scheme].status;j<<=1)
                if(row[scheme].status&j)
                    row[scheme].count++;
            scheme++;
        }
    }
    return scheme;
}
int main(){
    int n,m;
    int max_scheme,max_scheme_count;
    while(!(cin>>n>>m).eof()){
        memset(dp,0,sizeof(dp));
        memset(row,0,sizeof(row));
        int row_status_count=solve_row(m);//有效状态行的数量
        for(int i=2;i<n+2;i++){
            for(int j=0;j<row_status_count;j++){
                for(int k=0;k<row_status_count;k++){
                    if(row[j].status&row[k].status)continue;
                    for(int l=0;l<row_status_count;l++){
                        if(row[j].status&row[l].status)continue;
                        if(row[k].status&row[l].status)continue;
                        if(dp[i][j][k]<dp[i-1][k][l]+row[j].count)
                            dp[i][j][k]=dp[i-1][k][l]+row[j].count;
                    }
                }
            }
        }
        max_scheme=0,max_scheme_count=0;
        for(int j=0;j<row_status_count;j++){
            for(int k=0;k<row_status_count;k++){
                cout<<dp[n+1][j][k]<<' ';
                if(dp[n+1][j][k]>max_scheme){
                    max_scheme=dp[n+1][j][k];
                    max_scheme_count=1;
                }else if(dp[n+1][j][k]==max_scheme){
                    max_scheme_count++;
                }
            }
            cout<<endl;
        }
        cout<<max_scheme<<' '<<max_scheme_count<<endl;
    }
}
