#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n,a[201],dp[201][201];
    int ans=0;
    memset(dp,0,sizeof(dp));
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[n+i]=a[i];
    }
    for(int l=2;l<=n;l++){
        for(int i=1;i<=2*n-l+1;i++){/*起点。因为化圆为直，所以起点可能在1到2n-1之间，虽然最后找符合条件的答案起点最大不可能超过n，但是dp[n][2n-1]是需要把n到2n-1之间的都算出来的*/
            int j=i+l-1;
            for(int k=i;k<=j-1;k++){
                dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]+a[i]*a[k+1]*a[j+1]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(dp[i][i+n-1]>ans)
            ans=dp[i][i+n-1];
    }
    cout<<ans<<endl;
}