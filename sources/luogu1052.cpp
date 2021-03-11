#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int stone[101],flag[100001],dp[10];
int main(){
    int l,s,t,m,temp,pos=0;
    memset(flag,0,sizeof(flag));
    memset(dp,0x7f,sizeof(dp));
    cin>>l>>s>>t>>m;
    for(int i=1;i<=m;i++)
        cin>>stone[i];
    sort(stone+1,stone+m+1);
    stone[0]=0;
    if(s==t){
        int ans=0;
        for(int i=1;i<=m;i++)
            if(stone[i]%s==0)
                ans++;
        cout<<ans<<endl;
        return 0;
    }
    pos=0;
    for(int i=1;i<=m;i++){
        int dist=stone[i]-stone[i-1];
        if(dist>s*t)
            dist=s*t;
        pos+=dist;
        flag[pos]=1;
    }
    l=pos+s*t;
    dp[0]=0;
    for(int i=1;i<=l;i++){
        temp=1e9;
        for(int j=i-s;j>=0&&i-j<=t;j--)
            temp=min(temp,dp[j%10]);
        dp[i%10]=temp+flag[i];
    }
    cout<<dp[l%10]<<endl;
}