#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int v,n,ans=0,box[31]={0};
    int dp[20001];
    memset(dp,0,sizeof(dp));
    cin>>v>>n;
    for(int i=1;i<=n;i++)
        cin>>box[i];
    dp[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=box[i];j--){
            if(dp[j-box[i]]!=0)
                dp[j]=1;
        }
    }
    for(int i=v;i>=1;i--){
        if(dp[i]){
            ans=v-i;
            break;
        }
    }
    cout<<ans<<endl;
}