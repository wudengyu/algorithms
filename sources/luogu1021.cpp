#include<iostream>
#include<cstring>
using namespace std;
int a[20],ans[20];
int n,s=0;
int solve(int s[],int pos){
/*根据数组s的前pos个数，计算出可以贴n（全局变量）张邮票的情况下，可以组合出的连续的最大值。
 *首先计算组合出某一面值需要的最少邮票数，然后在需要的邮票数不大于n的情况下，
 *找出从1开始连续的最大的值。
 *这是一个完全背包问题。对于第i种邮票，可以使用0、1、2、……、n次，设dp[i][j]表示
 *用i种邮票能够组合出面值为j需要的最少的邮票张数，那么就是dp[i-1][j-k*a[i]]+k
 *当k=0时表示不用第i种邮票，只用前面i-1种就组合出j面值需要的张数；
 *当K=1时表示使用1张第i种邮票，那么前面i-1种邮票组合出的面值必须恰好少i邮票的面值a[i]
 *即dp[i-1][j-a[i]]，再加上1就得到了组合出j需要的邮票张数。
 *k=2、3、……、n时同理，dp[i][j]就应该取其中最小的。在动态规划中，dp[i-1][……]都是上一步计算出的
 *上一步没有计算出来的实际上就是不可能组合出来的面值，需要用∞表示（因为这里是求最小值，所以不能用0）
 *即初始化dp数组时要用非常大的数。
 *实际编程时，降维优化显然是可行的。然后j-k*a[i]如果按推导过程直接写，那么是跳跃性的，有很多值没有处理
 *但是j-k*a[i]的意义无非就是组合出的面值，所以直接用一个循环变量，控制其从0到n*a[i]就行了。
*/
    int dp[10000];
    memset(dp,0x7f,sizeof(dp));
    dp[0]=0;
    for(int i=1;i<=pos;i++){
        for(int j=a[i];j<=n*a[i];j++)
            dp[j]=min(dp[j],dp[j-a[i]]+1);
    }
    for(int i=1;i<=n*a[pos]+1;i++){
        if(dp[i]>n)
            return i-1;
    }
    return 0;
}
void dfs(int a[],int pos,int k){//遍历所有组合，用到的值放在数组中，pos是当前位置，k是最大深度，当数组增长到k时，需要保存并比较结果
    if(pos<k){//还没有到最大深度，需要递归
        int temp=solve(a,pos-1);//之前的最大连续值
        for(int i=a[pos-1]+1;i<=temp+1;i++){
            a[pos]=i;
            dfs(a,pos+1,k);//递归调用，填充下一个位置。
        }
    }else{//已经到最大深度，仍然要遍历，但不继续递归，而是要保存、判断结果
        int temp=solve(a,pos-1);//之前的最大连续值
        for(int i=a[pos-1]+1;i<=temp+1;i++){
            a[pos]=i;
            /*
            for(int i=1;i<=k;i++)
                cout<<a[i]<<" ";
            cout<<endl;
            */
            int result=solve(a,pos);
            if(s<result){
                s=result;
                for(int j=1;j<=k;j++)
                    ans[j]=a[j];
            }
        }

    }
}
int main(){
    int k;
    memset(a,0,sizeof(a));
    cin>>n>>k;
    a[1]=1;
    dfs(a,2,k);
    for(int i=1;i<=k;i++)
        cout<<ans[i]<<" ";
    cout<<endl;
    cout<<"MAX="<<s<<endl;
}