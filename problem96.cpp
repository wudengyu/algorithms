/*暗号
 *动态规划
*/
#include <iostream>
#include <cstring>
#define MOD 100000000
using namespace std;
int main(){
    string x,y;
    int *dp[2],*sum[2];
    while(!getline(cin,x).eof()&&!getline(cin, y).eof())
    {
        int xl=x.length()-1;
        int yl=y.length()-1;
        x=' '+x;
        y=' '+y;
        for(int i=0;i<2;i++){
            dp[i]=new int[yl+1];
            sum[i]=new int[yl+1];
        }
        for(int i=0;i<2;i++){
            dp[i][0]=0;
            sum[i][0]=0;
        }
        for(int j=0;j<=yl;j++){
            dp[0][j]=0;
            sum[0][j]=0;
        }
        for(int i=1;i<=xl;i++){
            int curr=i&1;
            int prev=curr^1;
            for(int j=1;j<=yl;j++){
                if (x[i]==y[j]){
                    dp[curr][j]=dp[prev][j-1]+1;
                    if(sum[prev][j-1]==0)
                        sum[curr][j]=1;
                    else
                        sum[curr][j]=sum[prev][j-1];
                    if(dp[curr][j]==dp[curr][j-1])
                        sum[curr][j]=(sum[curr][j]+sum[curr][j-1])%MOD;
                    if(dp[curr][j]==dp[prev][j])
                        sum[curr][j]=(sum[curr][j]+sum[prev][j])%MOD;
                }else{
                    dp[curr][j]=max(dp[prev][j], dp[curr][j-1]);
                    sum[curr][j]=0;
                    if(dp[curr][j]==dp[curr][j-1])
                        sum[curr][j]=(sum[curr][j]+sum[curr][j-1])%MOD;
                    if(dp[curr][j]==dp[prev][j])
                        sum[curr][j]=(sum[curr][j]+sum[prev][j])%MOD;
                    if(dp[curr][j]==dp[prev][j-1]){
                        sum[curr][j]=sum[curr][j]-sum[prev][j-1];
                        while(sum[curr][j]<0)
                            sum[curr][j]+=MOD;
                    }
                }
            }
        }
        cout<<dp[xl&1][yl]<<endl;
        if(dp[xl&1][yl]==0)
            cout<<0<<endl;
        else
            cout<<(sum[xl&1][yl]+MOD)%MOD<<endl;
        for(int i=0;i<2;i++)
        {
            delete[] * (dp + i);
            delete[] * (sum + i);
        }
    }
}