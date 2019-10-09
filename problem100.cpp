/*零崎的朋友很多Ⅰ
 *完全背包问题
*/
#include <iostream>
using namespace std;
int main(){
    int P,N;
    int p[301],c[301];
    int dp[20001];
    while(!(cin>>P>>N).eof()){
        for(int i=1;i<=N;i++){
            cin>>p[i]>>c[i];
        }
        for(int i=0;i<=P;i++)
            dp[i]=0;
        for(int i=1;i<=N;i++){
            for(int j=c[i];j<=P;j++){
                if(dp[j]<dp[j-c[i]]+p[i])
                    dp[j]=dp[j-c[i]]+p[i];
            }
        }
        cout<<dp[P]<<endl;
    }
}