/*零崎的朋友很多Ⅱ
*还是一个01背包问题，只不过要求必须装满背包，所以可能无解，用-1表示无解。
*除了初始数据需要注意与普通01背包不同外，转移方程找最大价值时，还需注意不能仅仅比大小，还要注意前一状态是否有解。
*/
#include <iostream>
using namespace std;
int main(){
    int P,N;
    int p[301],c[301];
    int dp[20001];
    while(!(cin>>P>>N).eof()){
        int sum=0;
        for(int i=1;i<=N;i++){
            cin>>p[i]>>c[i];
            sum+=c[i];
        }
        for(int i=1;i<=P;i++)
            dp[i]=-1;
        dp[0]=0;
        for(int i=1;i<=N;i++){
            int tp;
            if(c[i]>P-sum)
                tp=c[i];
            else
                tp=P-sum;
            for(int j=P;j>=tp;j--){
                if(dp[j-c[i]]>=0&&dp[j]<dp[j-c[i]]+p[i])
                    dp[j]=dp[j-c[i]]+p[i];
            }
            sum-=c[i];
        }
        if(dp[P]>0)
            cout<<dp[P]<<endl;
        else
            cout<<"jpx"<<endl;        
    }
}