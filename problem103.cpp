/*双“11”的抉择
 *动态规划
 *假设∀a[i]>=m，那么dp[i][j]=dp[i-1][j]+dp[i-1][j-1]+……+dp[i-1][0]
 *若是按照『填表』的动作，相当于每一个单元格的值等于上一行从第0列到本列的累计
 *所以，dp[i][j]=dp[i-1][j]+dp[i][j-1]，从数学上解释就是：从i个物品中选
 *j个可以分两类：一类是不取物品i，取法有dp[i-1][j]种，一类是取1个物品i，取
 *法有dp[i][j-1]种。根据题意，取1个跟取几个是同样的方案。
 *当a[i]<j时，第一个式子不能累加到dp[i-1][0]因为这个方案表示前i-1个物品里选
 *0个，那么到选择i物品时就必须选择j个，但是i物品的数量不够j个。所以，只能累加到
 *dp[i-1][j-a[i]]，后面的要舍去，也就是要减去dp[i-1][0]+dp[i-1][1]+……+dp[j-a[i]-1]=dp[i][j-a[i]-1]
 */
#include <iostream>
using namespace std;
int main(){
    int N,m,M,a[1001];
    int dp[1001][1001];
    while(!(cin>>N>>m>>M).eof()){
        for(int i=1;i<=N;i++){
            cin>>a[i];
            dp[i][0]=1;
        }
        dp[0][0]=1;
        for(int i=1;i<=m;i++)
            dp[0][i]=0;
        for(int i=1;i<=N;i++){
            for(int j=1;j<=m;j++){
                dp[i][j]=(dp[i-1][j]+dp[i][j-1])%M;
                if(j<a[i])
                    dp[i][j]=(dp[i][j]-dp[i-1][j-a[i]-1]+M)%M;
                cout<<dp[i][j]<<' ';
            }
            cout<<endl;
        }
       
        cout<<dp[N][m]<<endl;
    }
}