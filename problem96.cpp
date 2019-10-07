/*暗号
 *动态规划
*/
#include <iostream>
#include <cstring>
#define MOD 100000000
using namespace std;
int main(){
    string x,y;
    while(!getline(cin,x).eof()&&!getline(cin, y).eof())
    {
        int xl=x.length()-1;
        int yl=y.length()-1;
        x=' '+x;
        y=' '+y;
        int **dp=new int*[xl+1];
        int **sum=new int*[xl+1];
        for(int i=0;i<2;i++){
            dp[i]=new int[yl+1];
            sum[i]=new int[yl+1];
        }
        for(int i=0;i<=xl;i++){
            dp[i][0]=0;
            sum[i][0]=1;
        }
        for(int j=0;j<=yl;j++){
            dp[0][j]=0;
            sum[0][j]=1;
        }
        for(int i=1;i<=xl;i++){
            for(int j=1;j<=yl;j++){
                if (x[i]==y[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                    sum[i][j]=sum[i-1][j-1];
                    if(dp[i][j]==dp[i][j-1])
                        sum[i][j]=(sum[i][j]+sum[i][j-1])%MOD;
                    if(dp[i][j]==dp[i-1][j])
                        sum[i][j]=(sum[i][j]+sum[i-1][j])%MOD;
                else
                    dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
                    if(dp[i][j]==dp[i][j-1])
                        sum[i][j]=(sum[i][j]+sum[i][j-1])%MOD;
                    if(dp[i][j]==dp[i-1][j])
                        sum[i][j]=(sum[i][j]+sum[i-1][j])%MOD;
                    if(dp[i][j]==dp[i-1][j-1])
                        sum[i][j]=(sum[i][j]-sum[i-1][j]+MOD)%MOD;
            }
        }
        cout<<dp[xl][yl]<<endl;
        if(dp[xl][yl]==0)
            cout<<0<<endl;
        else
            cout<<sum[xl][yl]<<endl;
        for(int i=0;i<xl;i++)
        {
            delete[] * (dp + i);
            delete[] * (sum + i);
        }
        delete[] dp;
        delete[] sum;
    }
}